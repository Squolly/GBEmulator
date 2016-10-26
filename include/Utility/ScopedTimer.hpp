#ifndef SCOPED_TIMER_HPP__
#define SCOPED_TIMER_HPP__

#include <chrono>
#include <string>
#include <map> 
#include <vector>

struct TimeEntry {
    TimeEntry() : duration(0), calls(0) { }
    
    std::chrono::nanoseconds duration; 
    int calls; 
    std::string name; 
}; 

class ScopedTimer {
public: 
    ScopedTimer(const std::string& name); 
    ~ScopedTimer(); 
    
private: 
    void start(); 
    void stop(); 
    void write_timetable(const std::string filename); 
    void write_timeline(const std::string filename); 
    
    std::chrono::high_resolution_clock::time_point _start_time; 
    std::chrono::high_resolution_clock::time_point _end_time; 
    std::string _name; 
    std::map<std::string, TimeEntry>::iterator _it; 
    
    static std::map<std::string, TimeEntry> _timetable; 
    static std::vector<std::map<std::string, TimeEntry> > _timeline; 
    static std::chrono::high_resolution_clock::time_point _begin; 
}; 

#endif