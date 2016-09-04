#include "SFML_GBVideo.hpp"
#include <iostream> 

const int SCREEN_WIDTH = 160; 
const int SCREEN_HEIGHT = 144; 

const int SCREEN_BUFFER_WIDTH = 256; 
const int SCREEN_BUFFER_HEIGHT = 256; 
SFML_GBVideo::SFML_GBVideo(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description)
    : _screen_pixels(new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4]), _pixels(new sf::Uint8[256 * 256 * 4]), GBVideo(start_address, end_address, name, description), 
    _window(sf::VideoMode(160, 144), "Test Window"), 
    _renderThread(&SFML_GBVideo::render, this), 
    _elapsed(sf::milliseconds(0)), 
    FRAMES_PER_SECOND(60.f), _hold(false) {
    _screen_buffer.create(SCREEN_WIDTH, SCREEN_HEIGHT); 
    _screen.setTexture(_screen_buffer); 
}

SFML_GBVideo::~SFML_GBVideo() {
    _renderThread.terminate(); 
    if(_screen_pixels)
        delete[] _screen_pixels; 
    if(_pixels)
        delete[] _pixels; 
}


void SFML_GBVideo::render() {
    while(_window.isOpen()) {
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
        _window.draw(_screen); 
        _window.display();  
        
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                _renderThread.terminate(); 
                _window.close();
            }
        }
    }
}

void SFML_GBVideo::operate() {
    if(!_hold) {
        GBVideo::operate(); 
        if(_current_pixel_y == 0 && _current_pixel_x == 0)
            _hold = true; 
    }
    if((_clock.getElapsedTime() - _elapsed).asMilliseconds() >= 1/FRAMES_PER_SECOND) {
        _hold = false; 
        _elapsed = _clock.getElapsedTime(); 
    }
        
    static bool once = false; 
    if(!once) {
        once = true; 
        _window.setActive(false); 
        _renderThread.launch(); 
    }
}