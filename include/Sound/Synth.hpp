#ifndef SYNTH_HPP__
#define SYNTH_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"

#include <array>
#include <queue> 
#include <mutex>
#include <iostream>
#include <iomanip> 

/* 
 * Class for sound synthesis given signal (for one channel) 
 */
class Synth {
public: 
    
    static const int SAMPLE_WINDOW_SIZE = 256; 
    static const int BUFFER_SIZE = 8192*2; 
    
    Synth() : _last_idx(0), _time_next(4194304. / 44100.), _time_passed(0), _current_buffer_idx(0) {
        _sample_window.fill(0); 
        _current_buffer.fill(0); 
        _default_buffer.fill(0); 
    }
    ~Synth() { }
    
    void out(int volume) { // at emulated CPU speed
        _sample_window[_last_idx++] = volume * (30000 / 15); 
        if(_last_idx >= SAMPLE_WINDOW_SIZE) 
            _last_idx = 0; 
        
        _time_passed += 1.; 
        if(_time_passed >= _time_next) { // sample 44100 Hz 
            _time_passed -= _time_next; 
            // insert into current buffer
            insert_avg_sample_to_current_buffer(); 
        }
    }
    
    void insert_avg_sample_to_current_buffer() {
        // moving average filter
        int avg = 0; 
        for(int i=0; i<SAMPLE_WINDOW_SIZE; ++i) 
            avg += _sample_window [i]; 
        avg /= SAMPLE_WINDOW_SIZE; 
        _current_buffer[_current_buffer_idx++] = avg; 
        
        if(_current_buffer_idx >= BUFFER_SIZE) {
            _current_buffer_idx = 0; 
            append_to_ready_buffer(); 
        }
    }
    
    void append_to_ready_buffer() {
        std::lock_guard<std::mutex> lg(_buffer_mutex); 
        if(_ready_buffer.size() > 128) 
            return; 
        _ready_buffer.push(_current_buffer); 
    }
    
    std::array<int, BUFFER_SIZE> get_buffer() {
        std::lock_guard<std::mutex> lg(_buffer_mutex); 
        if(_ready_buffer.size() != 0) {
            std::array<int, BUFFER_SIZE> val = _ready_buffer.front(); 
            _ready_buffer.pop(); 
            return val; 
        }
        return _default_buffer; 
    }
    
    std::queue<std::array<int, BUFFER_SIZE> > get_queue() {
        std::lock_guard<std::mutex> lg(_buffer_mutex); 
        std::queue<std::array<int, BUFFER_SIZE> > ret = _ready_buffer; 
        while(!_ready_buffer.empty()) 
            _ready_buffer.pop(); 
        return ret; 
    }
    
private: 
    std::mutex _buffer_mutex; 
    
    // real sample rate is CPU frequency (4194304 Hz / 44100 Hz ~ 95.1089342404)
    std::array<int, SAMPLE_WINDOW_SIZE> _sample_window; 
    int _last_idx; 
    const double _time_next; 
    double _time_passed; 
    int _current_buffer_idx; 
    
    std::array<int, BUFFER_SIZE> _default_buffer;
    std::array<int, BUFFER_SIZE> _current_buffer;            // current buffer to fill with 44.1kHz sampes
    std::queue<std::array<int, BUFFER_SIZE> > _ready_buffer; // ready to go buffers
}; 

#endif