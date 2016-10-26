#ifndef __SFML_GB_VIDEO_HPP__
#define __SFML_GB_VIDEO_HPP__

#include "GBVideo.hpp"
#include <SFML/Graphics.hpp>

class SFML_GBVideo : public GBVideo {
public: 
    SFML_GBVideo(uint32 start_address, uint32 end_address, 
            const std::string& name = std::string("SFML Video Module"), 
            const std::string& description = std::string("This Video Module should be used for testing.")); 
    virtual ~SFML_GBVideo(); 
    
    virtual void operate();
    virtual void render(); 
    
    bool break_request() { return _break_request; }
    void set_break_request(bool request) { _break_request = request; }
    
    const float FRAMES_PER_SECOND; 
    
    
    bool button_start() { return _button_start; };  
    bool button_select() { return _button_select; }; 
    bool button_up() { return _button_up; };  
    bool button_down() { return _button_down; }; 
    bool button_left() { return _button_left; }; 
    bool button_right() { return _button_right; }; 
    bool button_a() { return _button_a; }; 
    bool button_b() { return _button_b; }; 
    bool buttons_changed() { return _buttons_changed; }; 
    bool clear_button_changed() { _buttons_changed = false; }
    
private: 
    bool _hold; // to make video module 60 fps for render stuff
    
    // SFML Related
    sf::RenderWindow _window; 
    sf::Thread       _renderThread; 
    sf::Clock        _clock; 
    sf::Time         _elapsed; 
    
    sf::Uint8*  _pixels; 
    sf::Uint8*  _screen_pixels; 
    sf::Texture _screen_buffer; 
    sf::Sprite  _screen; 
    
    bool _break_request; 
    
    bool _button_start; 
    bool _button_select; 
    bool _button_up; 
    bool _button_down; 
    bool _button_left; 
    bool _button_right; 
    bool _button_a; 
    bool _button_b; 
    bool _buttons_changed; 
}; 

#endif