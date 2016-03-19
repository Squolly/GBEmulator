#include "GBVideo.hpp"

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

uint8 GBVideo::read_8(uint16 address) {
    
}

void  GBVideo::write_8(uint16 address, uint8 value) {
    
}
