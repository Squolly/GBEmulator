#include "SFML_GBVideo.hpp"
#include <iostream> 

const int SCREEN_WIDTH = 160; 
const int SCREEN_HEIGHT = 144; 

const int SCREEN_BUFFER_WIDTH = 256; 
const int SCREEN_BUFFER_HEIGHT = 256; 
SFML_GBVideo::SFML_GBVideo(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description)
    : _screen_pixels(new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4]), _pixels(new sf::Uint8[256 * 256 * 4]), GBVideo(start_address, end_address, name, description),  
    _renderThread(&SFML_GBVideo::render, this), 
    _elapsed(sf::milliseconds(0)), 
    FRAMES_PER_SECOND(60.f), _hold(false), _break_request(false) {
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
	static bool window_initialized = false; 

	if (!window_initialized) {
		_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(160, 144), "Test Window");
		_window->setActive(false);
		window_initialized = true; 
	}

    while(_window->isOpen()) {
        // copy display from GBVideo
        static sf::RenderWindow vram_window(sf::VideoMode(16*8, 16*8), "VRAM Window"); 
        
        if(refresh()) {
            refreshed(); 
            const std::vector<uint8> display = get_display(); 
            for(int y=0; y<144; ++y) {
                for(int x=0; x<160; ++x) {
                    uint8 color = display[x + y * 160]; 
                    uint8 r, g, b, a; 
                    a = 255; 
                    r = g = b = ((3-color) * 70); 
                    // if(color != 0) 
                    //     std::cout << (int)color << std::endl; 
                    _screen_pixels[(x + y * 160) * 4 + 0] = r; 
                    _screen_pixels[(x + y * 160) * 4 + 1] = g; 
                    _screen_pixels[(x + y * 160) * 4 + 2] = b; 
                    _screen_pixels[(x + y * 160) * 4 + 3] = a; 
                }
            }
            _screen_buffer.update(_screen_pixels); 
            _window->draw(_screen); 
            _window->display(); 
            
            int vram_vis_width = 0, vram_vis_height = 0; 
            auto vram_vis = get_vram_visualization(vram_vis_width, vram_vis_height); 
            
            
            static sf::Uint8 vram_screen_pixels[16 * 8 * 16 * 8 * 4]; 
            static sf::Texture vram_screen_buffer; 
            static sf::Sprite  vram_screen; 
            
            static bool vram_first = false; 
            if(!vram_first) {
                vram_screen_buffer.create(16 * 8, 16 * 8);
                vram_screen.setTexture(vram_screen_buffer); 
                vram_window.setActive(false); 
                vram_first = true; 
            }

            
            for(int y=0; y<16*8; ++y) {
                for(int x=0; x<16*8; ++x) {
                    uint8 color = vram_vis[x + y * 16*8]; 
                    uint8 r, g, b, a; 
                    a = 255; 
                    r = g = b = (color * 70); 
                    // if(color != 0) 
                    //     std::cout << (int)color << std::endl; 
                    vram_screen_pixels[(x + y * 16*8) * 4 + 0] = r; 
                    vram_screen_pixels[(x + y * 16*8) * 4 + 1] = g; 
                    vram_screen_pixels[(x + y * 16*8) * 4 + 2] = b; 
                    vram_screen_pixels[(x + y * 16*8) * 4 + 3] = a; 
                }
            }
            vram_screen_buffer.update(vram_screen_pixels); 
            vram_window.draw(vram_screen); 
            vram_window.display();
			sf::Event event;
			while (vram_window.pollEvent(event));
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

        sf::Event event;
	
        while (_window->pollEvent(event))
        {
            int set_keys = -1; 
            if (event.type == sf::Event::KeyPressed)
            {
                set_keys = 1; 
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                set_keys = 0; 
            }
            
            if(set_keys == 0 || set_keys == 1) {
                switch(event.key.code) {
                    case sf::Keyboard::W: 
                        _break_request = set_keys; 
                        std::cout << "Break request! " << std::endl; 
                        break; 
                    
                    case sf::Keyboard::Up: 
                        _button_up = set_keys; 
                        break; 
                        
                    case sf::Keyboard::Down: 
                        _button_down = set_keys; 
                        break; 
                        
                    case sf::Keyboard::Left: 
                        _button_left = set_keys; 
                        break; 
                        
                    case sf::Keyboard::Right: 
                        _button_right = set_keys; 
                        break; 

                    case sf::Keyboard::Y: 
                        _button_a = set_keys; 
                        break; 
                        
                    case sf::Keyboard::X: 
                        _button_b = set_keys; 
                        break; 
                    
                    case sf::Keyboard::A: 
                        _button_start = set_keys; 
                        break;
                        
                    case sf::Keyboard::S: 
                        _button_select = set_keys; 
                        break; 
                }
                _buttons_changed = true; 
            }
            
            if (event.type == sf::Event::Closed) {
                _renderThread.terminate(); 
                _window->close();
                vram_window.close(); 
            }
        }
    }
    
}

void SFML_GBVideo::operate() {
   //  if(!_hold) {
        GBVideo::operate(); 
   //  }
        /*
    if((_clock.getElapsedTime() - _elapsed).asMilliseconds() >= 1/FRAMES_PER_SECOND) {
        _hold = false; 
        _elapsed = _clock.getElapsedTime(); 
    }
    else
        _hold = true; 
        */
    
    static bool once = false; 
    if(!once) {
        once = true; 
        _renderThread.launch(); 
    }
}