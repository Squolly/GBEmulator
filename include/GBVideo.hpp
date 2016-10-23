#ifndef __GB_VIDEO_HPP__
#define __GB_VIDEO_HPP__

#include "MemoryMappedModule.hpp"
#include "Memory.hpp"
#include "GBRAM.hpp"

#include <mutex>

enum class GPUMode {
    HBlank = 0, 
    VBlank = 1, 
    OAM    = 2, 
    VRAM   = 3
}; 

class GBVideo : public MemoryMappedModule {
    public: 
        GBVideo(uint32 start_address, uint32 end_address, 
                const std::string& name = std::string("First Video Module"), 
                const std::string& description = std::string("This Video Module should be used for testing.")); 
                
        virtual ~GBVideo(); 
        
        void connect_to_memory(Memory& memory); 
        
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void  write_8(uint16 address, uint8 value); 
        virtual void  init(); 
        
        bool refresh() { return _refresh; }
        void refreshed() { _refresh = false; }
        
        uint32 elapsed_cycles() { return _current_cpu_cycles - _last_cpu_cycles; }
        void update_cycles(uint32 current_cpu_cycles) { 
            _last_cpu_cycles = _current_cpu_cycles; 
            _current_cpu_cycles = current_cpu_cycles; 
        }
        
        void update_mode_cycles() { _mode_cycles += elapsed_cycles(); }
        
        // for now keep old and new ones 
        
        // new render functions 
        void render_scanline(); 
        void render_image(); 
        uint8 get_background_pixel(uint8 x, uint8 y); // returns color of background at (WINX + x, WINY + y)
        void update_tile(uint16 address, uint8 value); 
        
        // old render functions
        virtual void next_render_step(); // deprecated
        virtual void put_pixel(uint8 x, uint8 y, uint8 color); // deprecated
        
        std::vector<uint8> get_vram_visualization(int& width, int& height); 
        std::vector<uint8> get_display() { std::lock_guard<std::mutex> lg(_display_mutex); std::vector<uint8> res = _display; return res; }
        
        void set_bit(uint8& r, int bit, bool value); 
        void set_coincidence_interrupt(bool enable) { set_bit(_lcd_status, 6, enable); } 
        void set_oam_interrupt(bool enable) { set_bit(_lcd_status, 5, enable); }
        void set_vblank_interrupt(bool enable) { set_bit(_lcd_status, 4, enable); }
        void set_hblank_interrupt(bool enable) { set_bit(_lcd_status, 3, enable); }
        void set_coincidence_flag(bool enable) { set_bit(_lcd_status, 2, enable); }
        void set_mode_flag(GPUMode mode) { 
            set_bit(_lcd_status, 1, static_cast<int>(mode) & 0x2); 
            set_bit(_lcd_status, 0, static_cast<int>(mode) & 0x1); 
        }
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
        
        // new 
        // still use "display" 
        std::vector<std::vector<std::vector<uint8> > > _tileset; 
        
        // old
        std::vector<uint8> _screen_buffer; 
        std::vector<uint8> _offscreen_display;
        std::vector<uint8> _display;
        
        std::mutex _display_mutex; 
        
        uint32 _mode_cycles; 
        uint32 _current_cpu_cycles; 
        uint32 _last_cpu_cycles; 
        GPUMode _current_mode; 
        
        bool _refresh; 
}; 
    
#endif