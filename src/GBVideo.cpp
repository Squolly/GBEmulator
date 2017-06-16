#include "GBVideo.hpp"

#include "Utility/ScopedTimer.hpp"

#include <iostream>
#include <cassert>

GBVideo::GBVideo(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description) :
        MemoryMappedModule(name, description, start_address, end_address),
         _character_ram(0x8000, 0x9800), _background_map_1_ram(0x9800, 0x9C00), _background_map_2_ram(0x9C00, 0xA000),
         _oam_ram(0xFE00, 0xFEA0), 
         _lcd_control(0), _lcd_status(0), _background_vertical_scrolling(0), _background_horizontal_scrolling(0), 
         _current_scanline(0), _scanline_comparison(144), _background_palette(0), _sprite_palette_0(0), _sprite_palette_1(0), 
         _window_y_position(0), _window_x_position(0), _dma_transfer_control(0), 
         _screen_buffer(256 * 256, 0), _display(160*144, 0), _offscreen_display(160*144, 0), 
         _current_pixel_x(0), _current_pixel_y(0),
         _tileset(384, std::vector<std::vector<uint8> >(8, std::vector<uint8>(8, 0))), // 384 tiles x 8 x 8
         _mode_cycles(0),
         _current_mode(GPUMode::VBlank), 
         _current_cpu_cycles(0),
         _last_cpu_cycles(0), 
         _refresh(false), 
         _verbose(false),
         _dma_request(false), 
         _sprites(40, GBVideo::Sprite())
          { }

GBVideo::~GBVideo() { }

void GBVideo::connect_to_memory(Memory& memory) {
    // connect video 
    // memory.connect(&_character_ram);        // Character RAM 
    // need to capture access to character ram to update tiles
    memory.connect(this, _character_ram.start_address(), _character_ram.end_address()); 
    
    memory.connect(&_background_map_1_ram); // Background Map Data 1
    memory.connect(&_background_map_2_ram); // Background Map Data 2
    // memory.connect(&_oam_ram);              // OAM - Object Attribute Memory
    memory.connect(this, _oam_ram.start_address(), _oam_ram.end_address()); 
    
    // connect video I/O Ports
    memory.connect(this, 0xFF40); // LCDCONT [RW] LCD Control
    memory.connect(this, 0xFF41); // LCDSTAT [RW] LCD Status
    memory.connect(this, 0xFF42); // SCROLLY [RW] Background Vertical Scrolling
    memory.connect(this, 0xFF43); // SCROLLX [RW] Background Horizontal Scrolling
    memory.connect(this, 0xFF44); // CURLINE [RW] Current Scanline
    memory.connect(this, 0xFF45); // CMPLINE [RW] Scanline Comparison
    memory.connect(this, 0xFF47); // BGRDPAL [W]  Background Palette
    memory.connect(this, 0xFF48); // OBJ0PAL [W]  Sprite Palette #0
    memory.connect(this, 0xFF49); // OBJ1PAL [W]  Sprite Palette #1
    memory.connect(this, 0xFF4A); // WNDPOSY [RW] Window Y Position
    memory.connect(this, 0xFF4B); // WNDPOSX [RW] Window X Position
    memory.connect(this, 0xFF46); // DMACONT [W] DMA Transfer Control
}

void  GBVideo::init() {
    _character_ram.init(_character_ram.size()); 
    _background_map_1_ram.init(_background_map_1_ram.size()); 
    _background_map_2_ram.init(_background_map_2_ram.size()); 
    _oam_ram.init(_oam_ram.size()); 
}

void GBVideo::operate() {
    ScopedTimer st("GBVideo::operate"); 
    
    // handle operation stuff (draw something, increase counters and so on) 
   //  static int counter = 0; 
   //  if(counter % 1 == 0) 
   //  next_render_step(); // deprecated
  //   counter++; 
    
    
    // update mode cycles 
    update_mode_cycles(); 
    
    // std::cout << "Current Mode: " << (int)_current_mode << std::endl; 
    // std::cout << "Cycles: " << _mode_cycles << std::endl; 
    
    uint8 last_scanline = _current_scanline; 
    
    switch(_current_mode) {
        case GPUMode::HBlank: { // HBlank duration: 204 cycles
            if(_mode_cycles >= 204) {
                // HBlank done, switch to OAM unless this was the last line
                _mode_cycles -= 204;
                _current_scanline++; // after HBlank we go to the next line
                if(_current_scanline == 144) {
                    _current_mode = GPUMode::VBlank; 
                    // render image
                    render_image(); // update visible image
                    _refresh = true; 
                    
                    // vblank interrupt 
                    request_vblank_interrupt(); 
                }
                else {
                    _current_mode = GPUMode::OAM; 
                    request_oam_interrupt(); 
                }
            }
        }
        break; 
        
        case GPUMode::VBlank: {
            if(_mode_cycles >= 456) {
                _mode_cycles -= 456; 
                _current_scanline++; 
                
                if(_current_scanline > 153) { // 10 lines of vblank
                    // restart 
                    _current_mode = GPUMode::OAM; 
                    _current_scanline = 0; 
                    request_oam_interrupt(); 
                }
            }
        }
        break; 
        
        case GPUMode::OAM: {
            if(_mode_cycles >= 80) { // simulate OAM access
                _mode_cycles -= 80; 
                _current_mode = GPUMode::VRAM; 
            }
        }
        break; 
        
        case GPUMode::VRAM: { // simulate VRAM access
            if(_mode_cycles >= 172) {
                _mode_cycles -= 172; 
                _current_mode = GPUMode::HBlank; 
                // render scanline
                render_scanline(); // update scanline
                request_hblank_interrupt(); 
            }
        }
        break; 
    }
    
    if(_current_scanline == _scanline_comparison) {
        set_coincidence_flag(true); 
        if(last_scanline != _current_scanline) 
            request_coincidence_interrupt(); // only request coincidence interrupt if LYC == LY once per line
    }
    else {
        set_coincidence_flag(false); 
    }
    
    set_mode_flag(_current_mode); 
}

void GBVideo::set_bit(uint8& r, int bit, bool value) {
    const uint8 r_masked_bit = r & ~(1 << bit); 
    const uint8 set_n = ((value ? 1 : 0) << bit); 
    r = r_masked_bit | set_n; 
}

// note: access to video RAM will happen transparent to this module currently
//       so currently we only have to handle I/O access
uint8 GBVideo::read_8(uint16 address) {
    ScopedTimer st("GBVideo::read_8"); 
    
    uint8 ret = 0xFF; 
    if(address >= _character_ram.start_address() && address < _character_ram.end_address()) {
        ret = _character_ram.read_8(address); 
    }
    
    if(address >= _oam_ram.start_address() && address < _oam_ram.end_address()) {
        ret = _oam_ram.read_8(address); 
    }
    
    switch(address) {
    case 0xFF40: 
        ret = _lcd_control; 
        break; // LCDCONT [RW] LCD Control
        
    case 0xFF41: 
        ret = _lcd_status; 
        break; // LCDSTAT [RW] LCD Status
        
    case 0xFF42: 
        ret =  _background_vertical_scrolling; 
        break; // SCROLLY [RW] Background Vertical Scrolling
        
    case 0xFF43: 
        ret =  _background_horizontal_scrolling; 
        break; // SCROLLX [RW] Background Horizontal Scrolling
        
    case 0xFF44:
        ret =  _current_scanline; 
        break; // CURLINE [RW] Current Scanline
        
    case 0xFF45: 
        ret =  _scanline_comparison; 
        break; // CMPLINE [RW] Scanline Comparison
        
    case 0xFF46: 
        ret = 0; 
        break; // DMACONT [W] DMA Transfer Control 
        
    case 0xFF47: 
        ret = 0; 
        break; // BGRDPAL [W]  Background Palette
        
    case 0xFF48: 
        ret = 0; 
        break; // OBJ0PAL [W]  Sprite Palette #0
        
    case 0xFF49: 
        ret = 0; 
        break; // OBJ1PAL [W]  Sprite Palette #1
        
    case 0xFF4A:
        ret =  _window_y_position; 
        break; // WNDPOSY [RW] Window Y Position
        
    case 0xFF4B: 
        ret =  _window_x_position; 
        break; // WNDPOSX [RW] Window X Position  
        
    default: 
        if(address >= _character_ram.start_address() && address < _character_ram.end_address()) 
            break; 
        
        if(address >= _oam_ram.start_address() && address < _oam_ram.end_address()) 
            break; 
        
        std::cout << "[Video]: " << (int)address << " access [R] with unknown purpose" << std::endl; 
        break; 
    }
    
    return ret; 
}

void GBVideo::next_render_step() {
    ScopedTimer st("GBVideo::next_render_step"); 
    
    const uint8 pos_x = _current_pixel_x; 
    const uint8 pos_y = _current_pixel_y; 
    
    if(_current_pixel_y == _scanline_comparison) {
        set_coincidence_flag(true); 
    }
    else {
        set_coincidence_flag(false); 
    }
    
    // check if background is turned on 
    if(_lcd_control & 0x01) {
        // check witch bg set 
        const uint8 background_map_switch = _lcd_control & 0x08; 
        uint16 map_offset = (background_map_switch) ? 0x9C00 : 0x9800; 
        // size of tiles? 8x8 or 8x16
        const uint8 bg_tile_x = _current_pixel_x >> 3; 
        const uint8 bg_tile_y = _current_pixel_y >> 3;
        map_offset += (bg_tile_y * 32 + bg_tile_x); 
        
        // map_offset now point to the current tile of the background we want to draw
        GBRAM *background_map; 
        
        if(!background_map_switch) 
            background_map = &_background_map_1_ram; 
        else 
            background_map = &_background_map_2_ram;  
        
        const uint8 tile_id = background_map->read_8(map_offset); 
        
        const uint8 tile_table_switch = (_lcd_control & 0x10); 
        const uint16 tile_table_offset = (tile_table_switch ? 0x8000 : 0x8800); 
        const uint8 tile_id_mod = tile_id + (!tile_table_switch ? 128 : 0); 
        
        // tile_table_offset = 0x8000; 
        //assert(tile_table_offset == 0x8000); 

        // get tile information (16 bytes per tile) (8 bit * 8 lines * 2)
        const uint8 tile_y = _current_pixel_y % 8; 
        const uint8 tile_x = _current_pixel_x % 8; 
        
        const uint16 data_byte_address = tile_table_offset + tile_id_mod * 16 + tile_y * 2;
        
        const uint8 data_byte_0 = _character_ram.read_8(data_byte_address); 
        const uint8 data_byte_1 = _character_ram.read_8(data_byte_address + 1); 

        const uint8 color = (((data_byte_0 >> (7 - tile_x)) & 0x1) << 1) | // higher bit
                            ((data_byte_1 >> (7 - tile_x)) & 0x1);       // lower bit
        assert(color >= 0 && color <= 3); 
        
        put_pixel(_current_pixel_x, _current_pixel_y, color); 
        
    }
    
    // check if sprites are turned on
    bool sprites = true; 
    if(sprites) {
        // check all 40 sprites
        
    }
    
    if(_current_pixel_x == 255) {
        _current_pixel_y++; 
        _current_scanline = _current_pixel_y; 
    }
    _current_pixel_x++; 
}

std::vector<uint8> GBVideo::get_vram_visualization(int& width, int& height) {
    ScopedTimer st("GBVideo::get_vram_visualization"); 
    
    const int c_width_pixels = 8 * 16; 
    const int c_height_pixels = 8 * 16; 
    
    std::vector<uint8> vram_display(c_width_pixels * c_height_pixels, 0); 
    
    int current_address = 0; 
    for(int tile_id=0; tile_id<256; ++tile_id) { // for each tile 
        const int top_left_pos_in_display_x = (tile_id % 16) * 8; // 16 tiles per row 
        const int top_left_pos_in_display_y = (tile_id / 16) * 8; // 16 tiles in column
        
        for(int line_of_tile=0; line_of_tile<8; ++line_of_tile) {
            for(int pixel_in_line=0; pixel_in_line<8; ++pixel_in_line) {             
                const int pixel_x = top_left_pos_in_display_x + pixel_in_line; 
                const int pixel_y = (top_left_pos_in_display_y + line_of_tile) * c_width_pixels; 
                vram_display.at(pixel_x + pixel_y) = _tileset[tile_id][line_of_tile][pixel_in_line]; // color; 
            }
            current_address+= 2; 
        }
    }
    width = c_width_pixels; 
    height = c_height_pixels; 
    return vram_display; 
}

void GBVideo::put_pixel(uint8 x, uint8 y, uint8 color) { // deprecated
    ScopedTimer st("GBVideo::put_pixel"); 
    
    _screen_buffer[y * 256 + x] = color; 
    
    // check if in window
    
    const uint8 winx = _background_horizontal_scrolling; 
    const uint8 winy = _background_vertical_scrolling; 
    
    const uint16 test_y = ((y < winy) ? (y + 256) : y); 
    const uint16 test_x = ((x < winx) ? (x + 256) : x); 
    
    const uint16 maxy = winy + 144; 
    const uint16 maxx = winx + 160; 
    
    if(test_y >= (int)winy && test_y < (int)maxy && test_x >= (int)winx && test_x < (int)maxx) {
        const uint8 display_x = test_x - winx; 
        const uint8 display_y = test_y - winy; 
        _display[display_y * 160 + display_x] = color; 
    }
}
        
void GBVideo::update_tile(uint16 address, uint8 value) {
    ScopedTimer st("GBVideo::update_tile"); 
    
    const int tile_id = (address >> 4) & 0x1FF; // (each tile consists of 16 bytes beginning from 0x8000)
    const int tile_base_address = address & 0xFFFC; // tile address without least significant 4 bits
    const int tile_row = (address & 0xF) >> 1; // 2 rows are one line 
    
    address = (address & 0xFFFE); 

    const uint8 data0 = _character_ram.read_8(address); 
    const uint8 data1 = _character_ram.read_8(address + 1); 
    for(int i=0; i<8; ++i) {
        uint8 bit_idx = 1 << ( 7 - i ); 
        uint8 color = ((data0 & bit_idx) ? 1 : 0) | (((data1 & bit_idx) ? 2 : 0)); 
        _tileset[tile_id][tile_row][i] = color; 
    }
}

void GBVideo::update_sprite(uint16 address, uint8 value) {
    ScopedTimer st("GBVideo::update_sprite"); 
    
    uint16 relative_address = address - _oam_ram.start_address(); 
    
    int sprite_id = relative_address >> 2; // 4 bytes per sprite
    
    if(sprite_id >= 40) 
        return; // unknown sprite id
        
    uint8 sprite_byte = relative_address & 0x3; 
    
    // std::cout << "sprite: " << (int)sprite_id << ", sprite byte: " << (int)sprite_byte << std::endl; 
    switch(sprite_byte) {
        case 0: // Y-coordinate
            _sprites[sprite_id].y = value - 16; 
            break; 
            
        case 1: // X-coordinate
            _sprites[sprite_id].x = value - 8; 
            break; 
            
        case 2: // tile id
            _sprites[sprite_id].tile_id = value; 
            break; 
            
        case 3: // flags
            // bit 4 palette
            _sprites[sprite_id].palette = value & 0x10; 
            // bit 5 palette
            _sprites[sprite_id].flip_x  = value & 0x20; 
            // bit 6 palette
            _sprites[sprite_id].flip_y  = value & 0x40; 
            // bit 7 palette
            _sprites[sprite_id].priority = value & 0x80; 
            break; 
    }
    
}

uint8 GBVideo::get_background_pixel(uint8 x, uint8 y, bool window /* = false */) {
    // ScopedTimer st("GBVideo::get_background_pixel"); 
    
    uint8 background_map_switch = 0; 
    if(!window) {
        background_map_switch = _lcd_control & 0x08; 
    }
    else {
        background_map_switch = _lcd_control & 0x40; 
    }
    
    uint16 map_offset = (background_map_switch) ? 0x9C00 : 0x9800; 

    
    // background is 32 x 32 tiles wide
    // each tile is 8 x 8
    // --> background is 256 x 256 pixels 
    uint8 scroll_y = _background_vertical_scrolling; 
    uint8 scroll_x = _background_horizontal_scrolling; 
    
    if(window) {
        scroll_y = scroll_x = 0; 
    }
    
    const uint8 tile_y = (y + scroll_y) & 0x7;
    const uint8 tile_x = (x + scroll_x) & 0x7; 
    const uint8 bg_tile_y = ((y + scroll_y) & 0xFF) >> 3;
    const uint8 bg_tile_x = ((x + scroll_x) & 0xFF) >> 3; 
    map_offset += (bg_tile_y * 32 + bg_tile_x); 
    GBRAM *background_map; 
    if(!background_map_switch) 
        background_map = &_background_map_1_ram; 
    else 
        background_map = &_background_map_2_ram; 
        
    int tile_id = background_map->read_8(map_offset); 

    const uint8 tile_table_switch = (_lcd_control & 0x10); 
    // tile_table switch == 0 -> 0x8800 - 0x97FF (signed), 1 -> 0x8000 - 0x8FFF (unsigned)
     
   if(!tile_table_switch && tile_id < 128) 
       tile_id += 256; 
    
    
    return _tileset[tile_id][tile_y][tile_x]; 
}

void GBVideo::render_background_line(uint8 line, bool window, std::vector<uint8>& scanline_row) {
    uint8 background_map_switch = 0; 
    if(!window) {
        background_map_switch = _lcd_control & 0x08; 
    }
    else {
        background_map_switch = _lcd_control & 0x40; 
    }
    
    uint16 map_offset = (background_map_switch) ? 0x9C00 : 0x9800; 
    uint8 scroll_y = _background_vertical_scrolling; 
    uint8 scroll_x = _background_horizontal_scrolling; 

    if(window) {
        scroll_y = scroll_x = 0; 
    }
    
    GBRAM *background_map; 
    if(!background_map_switch) 
        background_map = &_background_map_1_ram; 
    else 
        background_map = &_background_map_2_ram; 
    
    const uint8 tile_table_switch = (_lcd_control & 0x10); 
    const uint8 tile_y = (line + scroll_y) & 0x7;
    const uint8 bg_tile_y = ((line + scroll_y) & 0xFF) >> 3;
    
    for(int i=0; i<160; ++i) {
      uint8 x_i = i; 
      
      if(window && i >= _window_x_position - 7) {
	x_i = i - (_window_x_position - 7); 
      }
      const uint8 tile_x = (x_i + scroll_x) & 0x7; 
      const uint8 bg_tile_x = ((x_i + scroll_x) & 0xFF) >> 3; 
      uint16 offset = map_offset + (bg_tile_y * 32 + bg_tile_x); 
  
      int tile_id = background_map->read_8(offset); 

      if(!tile_table_switch && tile_id < 128) 
	  tile_id += 256; 
      
      const uint8 color_ind = _tileset[tile_id][tile_y][tile_x];   
      const uint8 color = (_background_palette >> (color_ind * 2)) & 0x3; 
      _offscreen_display[_current_scanline * 160 + i] = color; 
      scanline_row[i] = color_ind; 
    }
}


void GBVideo::render_scanline() {
    ScopedTimer st("GBVideo::render_scanline"); 
    
    if(_current_scanline >= 144) 
        return; 
    
    static int count = 0; 
    
    std::vector<uint8> scanline_row(160, 0); 
    if(_lcd_control & 0x01) { // draw background if enabled
      /* 
        for(int i=0; i<160; ++i) {
            const uint8 color_ind = get_background_pixel(i, _current_scanline); 
            const uint8 color = (_background_palette >> (color_ind * 2)) & 0x3; 
            _offscreen_display[_current_scanline * 160 + i] = color; 
            scanline_row[i] = color_ind; 
        }
       */
      render_background_line(_current_scanline, false, scanline_row); 
    }
    
    // if window enabled
    if(_lcd_control & 0x20) {
      if(_current_scanline >= _window_y_position) {
	render_background_line(_current_scanline - _window_y_position, true, scanline_row); 
      }
      /*
        for(int i=0; i<160; ++i) {
            if(i >= _window_x_position - 7 && _current_scanline >= _window_y_position) {
                const uint8 color_ind = get_background_pixel(i - (_window_x_position - 7), _current_scanline - _window_y_position, true); 
                const uint8 color = (_background_palette >> (color_ind * 2)) & 0x3; 
                _offscreen_display[_current_scanline * 160 + i] = color; 
                scanline_row[i] = color_ind; 
            }
        }*/
    }
    
    
    if(_lcd_control & 0x02) { // draw sprites if enabled
        bool sprite_size_8x16 = _lcd_control & 0x04; 
        
        for(int i=0; i<40; ++i) {
            Sprite& sprite = _sprites.at(i); 
            
            // std::cout << "Sprite: " << (int)i << " pos: " << (int)sprite.x << ", " << (int)sprite.y << ", tile_id: " << (int)sprite.tile_id << std::endl; 
            // sprite in scanine? 
            if(!sprite_size_8x16) {
                if(!(_current_scanline >= sprite.y && _current_scanline < sprite.y + 8)) 
                    continue; 
            }
            else {
                if(!(_current_scanline >= sprite.y && _current_scanline < sprite.y + 16)) 
                    continue;
            }
            
            uint8 sprite_palette = _sprite_palette_0; 
            if(sprite.palette) {
                sprite_palette = _sprite_palette_1; 
            }
            
            uint8 tile_id = sprite.tile_id; 
            uint8 tile_id_ext = 0; 
            
            if(sprite_size_8x16) { // ignore least significant bit in 8x16 mode
                tile_id &= ~0x1; 
                tile_id_ext = tile_id + 1; 
            }
                
            std::vector<uint8> tilerow; 
            if(!sprite_size_8x16) {
                tilerow = _tileset.at(sprite.tile_id).at(_current_scanline - sprite.y); 
                if(sprite.flip_y) {
                    tilerow = _tileset.at(sprite.tile_id).at(7 - (_current_scanline - sprite.y)); 
                }
            }
            else {
                int sprite_tile_y = _current_scanline - sprite.y; 
                if(!sprite.flip_y) {
                    if(sprite_tile_y > 7) 
                        tilerow = _tileset.at(tile_id_ext).at(sprite_tile_y - 8); 
                    else 
                        tilerow = _tileset.at(tile_id).at(sprite_tile_y); 
                }
                else if(sprite.flip_y) {
                    sprite_tile_y = 15 - sprite_tile_y; 
                    if(sprite_tile_y > 7) 
                        tilerow = _tileset.at(tile_id_ext).at(sprite_tile_y - 8); 
                    else 
                        tilerow = _tileset.at(tile_id).at(sprite_tile_y); /// bug 
                }
            }

            
            for(int x=0; x<8; ++x) {
                if(x + sprite.x < 0 || x + sprite.x >= 160) // visible? 
                    continue; 
                
                uint8 color_ind = tilerow[sprite.flip_x ? (7 - x) : x]; 
                if(color_ind == 0) // transparent
                    continue; 
                
                if(sprite.priority && scanline_row[sprite.x + x]) 
                    continue; // low priority and background not 0 --> skip
                    
                // sprite is visible!
                // exchange color with true palette color
                uint8 color = (sprite_palette >> (color_ind * 2)) & 0x3; 
                
                // std::cout << "Sprite written with color " << (int)color << std::endl; 
                _offscreen_display[_current_scanline * 160 + sprite.x + x] = color; 
            }
        }
    }
}

void GBVideo::render_image() {
    ScopedTimer st("GBVideo::render_image"); 
    // std::lock_guard<std::mutex> lg(_display_mutex); 
    _display = _offscreen_display; 
}

// note: access to video RAM will happen transparent to this module currently
//       so currently we only have to handle I/O access
void GBVideo::write_8(uint16 address, uint8 value) {
    ScopedTimer st("GBVideo::write_8");
    
    if(address >= _character_ram.start_address() && address < _character_ram.end_address()) {
        _character_ram.write_8(address, value); 
        
        // update tile in _tileset
        update_tile(address, value); 
    }
    
    if(address >= _oam_ram.start_address() && address < _oam_ram.end_address()) {
        _oam_ram.write_8(address, value); 
        
        update_sprite(address, value); 
    }
    
    switch(address) {
    case 0xFF40: 
        _lcd_control = value; 
        if(_verbose) {
            std::cout << "[Video]: Changing LCD Control" << std::endl; 
            std::cout << "[Video]:     LCD Operation               : " << ( (_lcd_control & 0x80) ? "ON" : "OFF") << std::endl; 
            std::cout << "[Video]:     Window Tile Table Address   : " << ( (_lcd_control & 0x40) ? "0x9C00-0x9FFF" : "0x9800-0x9BFF") << std::endl;
            std::cout << "[Video]:     Window Display              : " << ( (_lcd_control & 0x20) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     Tile Pattern Table Address  : " << ( (_lcd_control & 0x10) ? "0x8000-0x8FFF" : "0x8800-0x97FF") << std::endl;
            
            // 32 * 32 - 1 = 0x3FF
            std::cout << "[Video]:     Background Tile Table Addr  : " << ( (_lcd_control & 0x08) ? "0x9C00-0x9FFF" : "0x9800-0x9BFF") << std::endl;
            std::cout << "[Video]:     Sprite Size                 : " << ( (_lcd_control & 0x04) ? "8x16" : "8x8") << std::endl;
            std::cout << "[Video]:     Sprites display             : " << ( (_lcd_control & 0x02) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     Background display          : " << ( (_lcd_control & 0x01) ? "ON" : "OFF") << std::endl;
        }
        break; // LCDCONT [RW] LCD Control
        
    case 0xFF41: 
        _lcd_status = value; 
        if(_verbose) {
            std::cout << "[Video]: Changing LCD Status" << std::endl; 
            std::cout << "[Video]:     Interrupt on scanline coinc    : " << ( (_lcd_status & 0x40) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     Interrupt on controller mode 10: " << ( (_lcd_status & 0x20) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     Interrupt on controller mode 01: " << ( (_lcd_status & 0x10) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     Interrupt on controller mode 00: " << ( (_lcd_status & 0x08) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     Scanline coinc flag            : " << ( (_lcd_status & 0x04) ? "ON" : "OFF") << std::endl;
            std::cout << "[Video]:     LCD Controller Mode            : "; 
        }
        {
            const uint8 lcd_control_mode = _lcd_status & 0x03; 
            if(_verbose) {
                if(lcd_control_mode == 0) std::cout << "Horizontal blanking impulse" << std::endl; 
                else if(lcd_control_mode == 1) std::cout << "Vertical blanking impulse" << std::endl; 
                else if(lcd_control_mode == 2) std::cout << "OAM is accessed by LCD controller" << std::endl; 
                else if(lcd_control_mode == 3) std::cout << "OAM and VRAM are accessed by LCD controller" << std::endl; 
            }
        }
        break; // LCDSTAT [RW] LCD Status
        
    case 0xFF42: 
        _background_vertical_scrolling = value; 
        if(_verbose) std::cout << "[Video]: Setting background vertical scrolling to " << (int)value << std::endl; 
        break; // SCROLLY [RW] Background Vertical Scrolling
        
    case 0xFF43: 
        _background_horizontal_scrolling = value; 
        if(_verbose) std::cout << "[Video]: Setting background horizontal scrolling to " << (int)value << std::endl; 
        break; // SCROLLX [RW] Background Horizontal Scrolling
        
    case 0xFF44:
        _current_scanline = value; // TODO: check if it is reset to 0 on writing
        if(_verbose) std::cout << "[Video]: Resetting current scanline register" << std::endl; 
        break; // CURLINE [RW] Current Scanline
        
    case 0xFF45: 
        _scanline_comparison = value; 
        if(_verbose) std::cout << "[Video]: Setting scanline comparison to " << (int)_scanline_comparison << std::endl; 
        break; // CMPLINE [RW] Scanline Comparison
        
    case 0xFF46: 
        _dma_transfer_control = value; 
        if(_verbose) std::cout << "[Video]: DMA Transfer Controller triggered." << std::endl; 
        if(_verbose) std::cout << "[Video]:     Should write from " << (int)_dma_transfer_control << "00 to OAM" << std::endl; 
        request_dma(); 
        break; // DMACONT [W] DMA Transfer Control 
        
    case 0xFF47: 
        _background_palette = value; 
        if(_verbose) std::cout << "[Video]: Changing background palette" << std::endl; 
        {
            const uint8 bg_color_3 = (_background_palette >> 6)&0x3; 
            const uint8 bg_color_2 = (_background_palette >> 4)&0x3; 
            const uint8 bg_color_1 = (_background_palette >> 2)&0x3; 
            const uint8 bg_color_0 = (_background_palette >> 0)&0x3; 
            if(_verbose) {
                std::cout << "[Video]:     Colors: #0 (" << (int)bg_color_0 << "), "; 
                std::cout <<                      "#1 (" << (int)bg_color_1 << "), "; 
                std::cout <<                      "#2 (" << (int)bg_color_2 << "), "; 
                std::cout <<                      "#3 (" << (int)bg_color_3 << ")" << std::endl; 
            }
        }
        break; // BGRDPAL [W]  Background Palette
        
    case 0xFF48: 
        _sprite_palette_0 = value; 
        if(_verbose) std::cout << "[Video]: Changing background palette" << std::endl; 
        {
            const uint8 sprite_0_color_3 = (_sprite_palette_0 >> 6)&0x3; 
            const uint8 sprite_0_color_2 = (_sprite_palette_0 >> 4)&0x3; 
            const uint8 sprite_0_color_1 = (_sprite_palette_0 >> 2)&0x3; 
            const uint8 sprite_0_color_0 = (_sprite_palette_0 >> 0)&0x3; 
            if(_verbose) {
                std::cout << "[Video]:     Colors: #0 (" << (int)sprite_0_color_3 << "), "; 
                std::cout <<                      "#1 (" << (int)sprite_0_color_2 << "), "; 
                std::cout <<                      "#2 (" << (int)sprite_0_color_1 << "), "; 
                std::cout <<                      "#3 (" << (int)sprite_0_color_0 << ")" << std::endl;
            }
        }
        break; // OBJ0PAL [W]  Sprite Palette #0
        
    case 0xFF49: 
        _sprite_palette_1 = value; 
        if(_verbose) std::cout << "[Video]: Changing background palette" << std::endl; 
        {
            const uint8 sprite_1_color_3 = (_sprite_palette_1 >> 6)&0x3; 
            const uint8 sprite_1_color_2 = (_sprite_palette_1 >> 4)&0x3; 
            const uint8 sprite_1_color_1 = (_sprite_palette_1 >> 2)&0x3; 
            const uint8 sprite_1_color_0 = (_sprite_palette_1 >> 0)&0x3; 
            if(_verbose) {
                std::cout << "[Video]:     Colors: #0 (" << (int)sprite_1_color_3 << "), "; 
                std::cout <<                      "#1 (" << (int)sprite_1_color_2 << "), "; 
                std::cout <<                      "#2 (" << (int)sprite_1_color_1 << "), "; 
                std::cout <<                      "#3 (" << (int)sprite_1_color_0 << ")" << std::endl;
            }
        }
        break; // OBJ1PAL [W]  Sprite Palette #1
        
    case 0xFF4A: 
        _window_y_position = value; 
        if(_verbose) std::cout << "[Video]: Setting Window y-Position to " << (int)_window_y_position << std::endl; 
        break; // WNDPOSY [RW] Window Y Position
        
    case 0xFF4B: 
        _window_x_position = value; 
        if(_verbose) std::cout << "[Video]: Setting Window x-Position to " << (int)_window_x_position << std::endl;
        break; // WNDPOSX [RW] Window X Position  
        
    default: 
        if(address >= _character_ram.start_address() && address < _character_ram.end_address()) 
            break; 
        if(address >= _oam_ram.start_address() && address < _oam_ram.end_address()) 
            break; 
        std::cout << "[Video]: " << (int)address << " access [W] with unknown purpose" << std::endl; 
        break; 
    }
}
