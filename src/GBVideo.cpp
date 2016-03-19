#include "GBVideo.hpp"

#include <iostream>

GBVideo::GBVideo(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description) : 
         _character_ram(0x8000, 0x9800), _background_map_1_ram(0x9800, 0x9C00), _background_map_2_ram(0x9C00, 0xA000),
         _oam_ram(0xFE00, 0xFEA0), 
         _lcd_control(0), _lcd_status(0), _background_vertical_scrolling(0), _background_horizontal_scrolling(0), 
         _current_scanine(0), _scanline_comparison(0), _background_palette(0), _sprite_palette_0(0), _sprite_palette_1(0), 
         _window_y_position(0), _window_x_position(0), _dma_transfer_control(0), 
         MemoryMappedModule(name, description, start_address, end_address) { }

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
}

// note: access to video RAM will happen transparent to this module currently
//       so currently we only have to handle I/O access
uint8 GBVideo::read_8(uint16 address) {
    // TODO: consider exchanging switch-statement
    switch(address) {
    case 0xFF40: 
        break; // LCDCONT [RW] LCD Control
        
    case 0xFF41: 
        
        break; // LCDSTAT [RW] LCD Status
        
    case 0xFF42: 
        
        break; // SCROLLY [RW] Background Vertical Scrolling
        
    case 0xFF43: 
        
        break; // SCROLLX [RW] Background Horizontal Scrolling
        
    case 0xFF44:
        
        break; // CURLINE [RW] Current Scanline
        
    case 0xFF45: 
        
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
        
        break; // WNDPOSY [RW] Window Y Position
        
    case 0xFF4B: 
        
        break; // WNDPOSX [RW] Window X Position  
        
    default: 
        std::cout << "[Video]: " << (int)address << " access [R] with unknown purpose" << std::endl; 
        break; 
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
        _current_scanine = value; // TODO: check if it is reset to 0 on writing
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
