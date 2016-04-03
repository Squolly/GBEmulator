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
    
    const float FRAMES_PER_SECOND; 
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
}; 

#endif