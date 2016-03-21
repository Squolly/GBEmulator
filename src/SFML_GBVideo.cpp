#include "SFML_GBVideo.hpp"

#include <iostream> 

const int SCREEN_WIDTH = 160; 
const int SCREEN_HEIGHT = 144; 

const int SCREEN_BUFFER_WIDTH = 256; 
const int SCREEN_BUFFER_HEIGHT = 256; 
SFML_GBVideo::SFML_GBVideo(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description)
    : _screen_pixels(new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4]), _pixels(new sf::Uint8[256 * 256 * 4]), GBVideo(start_address, end_address, name, description) {
    _screen_buffer.create(SCREEN_WIDTH, SCREEN_HEIGHT); 
    _screen.setTexture(_screen_buffer); 
}

SFML_GBVideo::~SFML_GBVideo() {
    if(_screen_pixels)
        delete[] _screen_pixels; 
    if(_pixels)
        delete[] _pixels; 
}

void SFML_GBVideo::operate() {
    GBVideo::operate(); 
    
    static int counter = 0; 
    static bool init_done = false; 
    static sf::RenderWindow window(sf::VideoMode(160, 144), "Test Window"); 
    
    if(!init_done) {
        
    }
    
    if(counter % 3000 == 0) {
       // window.clear(sf::Color::Green); 

        // copy display from GBVideo
        for(int y=0; y<144; ++y) {
            for(int x=0; x<160; ++x) {
                uint8 color = GBVideo::_display[x + y * 160]; 
                uint8 r, g, b, a; 
                a = 255; 
                r = g = b = (color * 70); 
                // if(color != 0) 
                //     std::cout << (int)color << std::endl; 
                _screen_pixels[(x + y * 160) * 4 + 0] = r; 
                _screen_pixels[(x + y * 160) * 4 + 1] = g; 
                _screen_pixels[(x + y * 160) * 4 + 2] = b; 
                _screen_pixels[(x + y * 160) * 4 + 3] = a; 
            }
        }
        /* 
        for(int y=0; y<256; ++y) {
            for(int x=0; x<256; ++x) {
                uint8 color = GBVideo::_screen_buffer[x + y * 256]; 
                uint8 r, g, b, a; 
                a = 255; 
                r = g = b = (color * 70); 
                // if(color != 0) 
                //     std::cout << (int)color << std::endl; 
                _screen_pixels[(x + y * 256) * 4 + 0] = r; 
                _screen_pixels[(x + y * 256) * 4 + 1] = g; 
                _screen_pixels[(x + y * 256) * 4 + 2] = b; 
                _screen_pixels[(x + y * 256) * 4 + 3] = a; 
            }
        }
        */
        _screen_buffer.update(_screen_pixels); 
        window.draw(_screen); 
        window.display(); 
        
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    counter++; 
}