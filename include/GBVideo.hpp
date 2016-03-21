#ifndef __GB_VIDEO_HPP__
#define __GB_VIDEO_HPP__

#include "MemoryMappedModule.hpp"
#include "Memory.hpp"
#include "GBRAM.hpp"

class GBVideo : public MemoryMappedModule {
    public: 
        GBVideo(uint32 start_address, uint32 end_address, 
                const std::string& name = std::string("First Video Module"), 
                const std::string& description = std::string("This Video Module should be used for testing.")); 
                
        ~GBVideo(); 
        
        void connect_to_memory(Memory& memory); 
        
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void  write_8(uint16 address, uint8 value); 
        virtual void  init(); 
        
        virtual void next_render_step(); 
        virtual void put_pixel(uint8 x, uint8 y, uint8 color); 
        
    protected: 
        GBRAM _character_ram; 
        GBRAM _background_map_1_ram; 
        GBRAM _background_map_2_ram; 
        GBRAM _oam_ram; 
        
        uint8 _lcd_control; 
        uint8 _lcd_status;  
        uint8 _background_vertical_scrolling; 
        uint8 _background_horizontal_scrolling;
        uint8 _current_scanline; 
        uint8 _scanline_comparison; 
        uint8 _background_palette; 
        uint8 _sprite_palette_0; 
        uint8 _sprite_palette_1; 
        uint8 _window_y_position; 
        uint8 _window_x_position; 
        uint8 _dma_transfer_control; 
        
        uint8 _current_pixel_x; 
        uint8 _current_pixel_y; 
        uint8* _screen_buffer; 
        uint8* _display; 
}; 
    
#endif