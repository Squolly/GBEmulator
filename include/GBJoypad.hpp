#ifndef __GBJOYPAD_HPP__
#define __GBJOYPAD_HPP__

#include "MemoryMappedModule.hpp"

class GBJoypad : public MemoryMappedModule {
public: 
        GBJoypad(uint32 start_address, uint32 end_address, const std::string& name = std::string("Gameboy Joypad Module"), 
                 const std::string& description = std::string("A simple gameboy joypad module"));
        
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void write_8(uint16 address, uint8 value); 
        
        void start(bool pressed = false); 
        void select(bool pressed = false); 
        void up(bool pressed = false); 
        void down(bool pressed = false); 
        void left(bool pressed = false); 
        void right(bool pressed = false); 
        void a(bool pressed = false); 
        void b(bool pressed = false); 
        
private: 
    
    // false == button IS NOT pressed, true == button IS pressed
    bool _button_start; 
    bool _button_select; 
    bool _button_up; 
    bool _button_down; 
    bool _button_left; 
    bool _button_right; 
    bool _button_a; 
    bool _button_b;  
    
    uint8 _chosen_bit; // 5 or 4? 
};

#endif
