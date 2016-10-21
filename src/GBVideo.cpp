#include "GBVideo.hpp"

#include <iostream>
#include <cassert>

GBVideo::GBVideo(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description) : 
         _character_ram(0x8000, 0x9800), _background_map_1_ram(0x9800, 0x9C00), _background_map_2_ram(0x9C00, 0xA000),
         _oam_ram(0xFE00, 0xFEA0), 
         _lcd_control(0), _lcd_status(0), _background_vertical_scrolling(0), _background_horizontal_scrolling(0), 
         _current_scanline(0), _scanline_comparison(0), _background_palette(0), _sprite_palette_0(0), _sprite_palette_1(0), 
         _window_y_position(0), _window_x_position(0), _dma_transfer_control(0), 
         _screen_buffer(256 * 256, 0), _display(160*144, 0), 
         _current_pixel_x(0), _current_pixel_y(0),
         MemoryMappedModule(name, description, start_address, end_address) { }

GBVideo::~GBVideo() { }

void GBVideo::connect_to_memory(Memory& memory) {
    // connect video 
    memory.connect(&_character_ram);        // Character RAM 
    memory.connect(&_background_map_1_ram); // Background Map Data 1
    memory.connect(&_background_map_2_ram); // Background Map Data 2
    memory.connect(&_oam_ram);              // OAM - Object Attribute Memory
    
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
    // handle operation stuff (draw something, increase counters and so on) 
   //  static int counter = 0; 
   //  if(counter % 1 == 0) 
        next_render_step(); 
  //   counter++; 
}

void GBVideo::set_bit(uint8& r, int bit, bool value) {
    const uint8 r_masked_bit = r & ~(1 << bit); 
    const uint8 set_n = ((value ? 1 : 0) << bit); 
    r = r | set_n; 
}

// note: access to video RAM will happen transparent to this module currently
//       so currently we only have to handle I/O access
uint8 GBVideo::read_8(uint16 address) {
    // TODO: consider exchanging switch-statement
    switch(address) {
    case 0xFF40: 
        return _lcd_control; 
        break; // LCDCONT [RW] LCD Control
        
    case 0xFF41: 
        
        break; // LCDSTAT [RW] LCD Status
        
    case 0xFF42: 
        return _background_vertical_scrolling; 
        break; // SCROLLY [RW] Background Vertical Scrolling
        
    case 0xFF43: 
        return _background_horizontal_scrolling; 
        break; // SCROLLX [RW] Background Horizontal Scrolling
        
    case 0xFF44:
        return _current_scanline; 
        break; // CURLINE [RW] Current Scanline
        
    case 0xFF45: 
        return _scanline_comparison; 
        break; // CMPLINE [RW] Scanline Comparison
        
    case 0xFF46: 
        
        break; // DMACONT [W] DMA Transfer Control 
        
    case 0xFF47: 
        
        break; // BGRDPAL [W]  Background Palette
        
    case 0xFF48: 
        
        break; // OBJ0PAL [W]  Sprite Palette #0
        
    case 0xFF49: 
        
        break; // OBJ1PAL [W]  Sprite Palette #1
        
    case 0xFF4A:
        return _window_y_position; 
        break; // WNDPOSY [RW] Window Y Position
        
    case 0xFF4B: 
        return _window_x_position; 
        break; // WNDPOSX [RW] Window X Position  
        
    default: 
        std::cout << "[Video]: " << (int)address << " access [R] with unknown purpose" << std::endl; 
        break; 
    }
}

void GBVideo::next_render_step() {
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
    const int c_width_pixels = 8 * 16; 
    const int c_height_pixels = 8 * 16; 
    
    std::vector<uint8> vram_display(c_width_pixels * c_height_pixels, 0); 
    
    int current_address = 0; 
    for(int tile_id=0; tile_id<256; ++tile_id) { // for each tile 
        const int top_left_pos_in_display_x = (tile_id % 16) * 8; // 16 tiles per row 
        const int top_left_pos_in_display_y = (tile_id / 16) * 8; // 16 tiles in column
        
        for(int line_of_tile=0; line_of_tile<8; ++line_of_tile) {
            const uint8 data_byte_0 = _character_ram.read_8(0x8000 + current_address); 
            const uint8 data_byte_1 = _character_ram.read_8(0x8000 + current_address + 1); 

            for(int pixel_in_line=0; pixel_in_line<8; ++pixel_in_line) {
                const uint8 color = (((data_byte_0 >> (7 - pixel_in_line)) & 0x1) << 1) | // higher bit
                                    ((data_byte_1 >> (7 - pixel_in_line)) & 0x1);       // lower bit
                                    
                const int pixel_x = top_left_pos_in_display_x + pixel_in_line; 
                const int pixel_y = (top_left_pos_in_display_y + line_of_tile) * c_width_pixels; 
                vram_display.at(pixel_x + pixel_y) = color; 
            }
            current_address+= 2; 
        }
    }
    width = c_width_pixels; 
    height = c_height_pixels; 
    return vram_display; 
}

void GBVideo::put_pixel(uint8 x, uint8 y, uint8 color) {
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
        
// note: access to video RAM will happen transparent to this module currently
//       so currently we only have to handle I/O access
void  GBVideo::write_8(uint16 address, uint8 value) {
    // TODO: consider exchanging switch-statement
    switch(address) {
    case 0xFF40: 
        _lcd_control = value; 
        std::cout << "[Video]: Changing LCD Control" << std::endl; 
        std::cout << "[Video]:     LCD Operation               : " << ( (_lcd_control & 0x80) ? "ON" : "OFF") << std::endl; 
        std::cout << "[Video]:     Window Tile Table Address   : " << ( (_lcd_control & 0x40) ? "0x9C00-0x9FFF" : "0x9800-0x9BFF") << std::endl;
        std::cout << "[Video]:     Window Display              : " << ( (_lcd_control & 0x20) ? "ON" : "OFF") << std::endl;
        std::cout << "[Video]:     Tile Pattern Table Address  : " << ( (_lcd_control & 0x10) ? "0x8000-0x8FFF" : "0x8800-0x97FF") << std::endl;
        
        // 32 * 32 - 1 = 0x3FF
        std::cout << "[Video]:     Background Tile Table Addr  : " << ( (_lcd_control & 0x08) ? "0x9C00-0x9FFF" : "0x9800-0x9BFF") << std::endl;
        std::cout << "[Video]:     Sprite Size                 : " << ( (_lcd_control & 0x04) ? "8x16" : "8x8") << std::endl;
        std::cout << "[Video]:     Color #0 transparency in win: " << ( (_lcd_control & 0x02) ? "SOLID" : "TRANSPARENT") << std::endl;
        std::cout << "[Video]:     Background display          : " << ( (_lcd_control & 0x01) ? "ON" : "OFF") << std::endl;
        break; // LCDCONT [RW] LCD Control
        
    case 0xFF41: 
        _lcd_status = value; 
        std::cout << "[Video]: Changing LCD Status" << std::endl; 
        std::cout << "[Video]:     Interrupt on scanline coinc    : " << ( (_lcd_status & 0x40) ? "ON" : "OFF") << std::endl;
        std::cout << "[Video]:     Interrupt on controller mode 10: " << ( (_lcd_status & 0x20) ? "ON" : "OFF") << std::endl;
        std::cout << "[Video]:     Interrupt on controller mode 01: " << ( (_lcd_status & 0x10) ? "ON" : "OFF") << std::endl;
        std::cout << "[Video]:     Interrupt on controller mode 00: " << ( (_lcd_status & 0x08) ? "ON" : "OFF") << std::endl;
        std::cout << "[Video]:     Scanline coinc flag            : " << ( (_lcd_status & 0x04) ? "ON" : "OFF") << std::endl;
        std::cout << "[Video]:     LCD Controller Mode            : "; 
        {
            const uint8 lcd_control_mode = _lcd_status & 0x03; 
            if(lcd_control_mode == 0) std::cout << "Horizontal blanking impulse" << std::endl; 
            else if(lcd_control_mode == 1) std::cout << "Vertical blanking impulse" << std::endl; 
            else if(lcd_control_mode == 2) std::cout << "OAM is accessed by LCD controller" << std::endl; 
            else if(lcd_control_mode == 3) std::cout << "OAM and VRAM are accessed by LCD controller" << std::endl; 
        }
        break; // LCDSTAT [RW] LCD Status
        
    case 0xFF42: 
        _background_vertical_scrolling = value; 
        std::cout << "[Video]: Setting background vertical scrolling to " << (int)value << std::endl; 
        break; // SCROLLY [RW] Background Vertical Scrolling
        
    case 0xFF43: 
        _background_horizontal_scrolling = value; 
        std::cout << "[Video]: Setting background horizontal scrolling to " << (int)value << std::endl; 
        break; // SCROLLX [RW] Background Horizontal Scrolling
        
    case 0xFF44:
        _current_scanline = value; // TODO: check if it is reset to 0 on writing
        std::cout << "[Video]: Resetting current scanline register" << std::endl; 
        break; // CURLINE [RW] Current Scanline
        
    case 0xFF45: 
        _scanline_comparison = value; 
        std::cout << "[Video]: Setting scanline comparison to " << (int)_scanline_comparison << std::endl; 
        break; // CMPLINE [RW] Scanline Comparison
        
    case 0xFF46: 
        _dma_transfer_control = value; 
        std::cout << "[Video]: DMA Transfer Controller triggered." << std::endl; 
        std::cout << "[Video]:     Should write from " << (int)_dma_transfer_control << "00 to OAM" << std::endl; 
        break; // DMACONT [W] DMA Transfer Control 
        
    case 0xFF47: 
        _background_palette = value; 
        std::cout << "[Video]: Changing background palette" << std::endl; 
        {
            const uint8 bg_color_3 = (_background_palette >> 6)&0x3; 
            const uint8 bg_color_2 = (_background_palette >> 4)&0x3; 
            const uint8 bg_color_1 = (_background_palette >> 2)&0x3; 
            const uint8 bg_color_0 = (_background_palette >> 0)&0x3; 
            std::cout << "[Video]:     Colors: #0 (" << (int)bg_color_0 << "), "; 
            std::cout <<                      "#1 (" << (int)bg_color_1 << "), "; 
            std::cout <<                      "#2 (" << (int)bg_color_2 << "), "; 
            std::cout <<                      "#3 (" << (int)bg_color_3 << ")" << std::endl; 
        }
        break; // BGRDPAL [W]  Background Palette
        
    case 0xFF48: 
        _sprite_palette_0 = value; 
        std::cout << "[Video]: Changing background palette" << std::endl; 
        {
            const uint8 sprite_0_color_3 = (_sprite_palette_0 >> 6)&0x3; 
            const uint8 sprite_0_color_2 = (_sprite_palette_0 >> 4)&0x3; 
            const uint8 sprite_0_color_1 = (_sprite_palette_0 >> 2)&0x3; 
            const uint8 sprite_0_color_0 = (_sprite_palette_0 >> 0)&0x3; 
            std::cout << "[Video]:     Colors: #0 (" << (int)sprite_0_color_3 << "), "; 
            std::cout <<                      "#1 (" << (int)sprite_0_color_2 << "), "; 
            std::cout <<                      "#2 (" << (int)sprite_0_color_1 << "), "; 
            std::cout <<                      "#3 (" << (int)sprite_0_color_0 << ")" << std::endl; 
        }
        break; // OBJ0PAL [W]  Sprite Palette #0
        
    case 0xFF49: 
        _sprite_palette_1 = value; 
        std::cout << "[Video]: Changing background palette" << std::endl; 
        {
            const uint8 sprite_1_color_3 = (_sprite_palette_1 >> 6)&0x3; 
            const uint8 sprite_1_color_2 = (_sprite_palette_1 >> 4)&0x3; 
            const uint8 sprite_1_color_1 = (_sprite_palette_1 >> 2)&0x3; 
            const uint8 sprite_1_color_0 = (_sprite_palette_1 >> 0)&0x3; 
            std::cout << "[Video]:     Colors: #0 (" << (int)sprite_1_color_3 << "), "; 
            std::cout <<                      "#1 (" << (int)sprite_1_color_2 << "), "; 
            std::cout <<                      "#2 (" << (int)sprite_1_color_1 << "), "; 
            std::cout <<                      "#3 (" << (int)sprite_1_color_0 << ")" << std::endl;
        }
        break; // OBJ1PAL [W]  Sprite Palette #1
        
    case 0xFF4A: 
        _window_y_position = value; 
        std::cout << "[Video]: Setting Window y-Position to " << (int)_window_y_position << std::endl; 
        break; // WNDPOSY [RW] Window Y Position
        
    case 0xFF4B: 
        _window_x_position = value; 
        std::cout << "[Video]: Setting Window x-Position to " << (int)_window_x_position << std::endl;
        break; // WNDPOSX [RW] Window X Position  
        
    default: 
        std::cout << "[Video]: " << (int)address << " access [W] with unknown purpose" << std::endl; 
        break; 
    }
}
