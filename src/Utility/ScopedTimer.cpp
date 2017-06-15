#include "Utility/ScopedTimer.hpp"

#include <iomanip> 
#include <fstream>
#include <set>

// #define SCOPED_TIMER_ENABLED 
    
#ifdef SCOPED_TIMER_ENABLED

std::map<std::string, TimeEntry> ScopedTimer::_timetable; 
std::vector<std::map<std::string, TimeEntry> > ScopedTimer::_timeline; 
std::chrono::high_resolution_clock::time_point ScopedTimer::_begin = std::chrono::high_resolution_clock::now(); 

ScopedTimer::ScopedTimer(const std::string& name) : _name(name) {
    start(); 
}

ScopedTimer::~ScopedTimer() {
    stop(); 
    if(_name == "main") {
        write_timetable("performance.txt"); 
        write_timeline("timeline.csv"); 
    }
}
    
void ScopedTimer::start() {
    _start_time = std::chrono::high_resolution_clock::now();
    std::pair<std::map<std::string, TimeEntry>::iterator,bool> ret;
    ret = _timetable.insert(std::pair<std::string, TimeEntry>(_name, TimeEntry())); 
    _it = ret.first; 
    _it->second.calls++; 
    _it->second.name = _name; 
}

void ScopedTimer::stop() {
    _end_time = std::chrono::high_resolution_clock::now(); 
    _it->second.duration += std::chrono::duration_cast<std::chrono::nanoseconds>(_end_time - _start_time); 
    
    if(std::chrono::duration_cast<std::chrono::seconds>(_end_time - _begin).count() > 10) { // new timeline entry every 10 seconds
        _timeline.push_back(_timetable); 
        _begin = std::chrono::high_resolution_clock::now(); 
    }
}

void ScopedTimer::write_timetable(const std::string filename) {
    std::ofstream out(filename); 
    for(auto& entry : _timetable) {
        out << std::setw(35) << std::setfill(' ') << entry.second.name << " | "; 
        out << std::setw(20) << std::setfill(' ') << entry.second.calls << " | ";
        out << std::setw(20) << std::setfill(' ') << entry.second.duration.count() << std::endl; 
    }
}

void ScopedTimer::write_timeline(const std::string filename) {
    std::ofstream out(filename); 
    out << "Name,"; 
    for(int i=0; i<_timeline.size(); ++i) {
        out<<(i*10+10)<<","; 
    }
    out << std::endl; 
    
    // gather names
    std::set<std::string> names; 
    for(auto& entry : _timetable) {
        names.insert(entry.first); 
    }
    
    // calls
    for(auto& name : names) {
        out << name << ","; 
        auto& last_tt = _timeline[0]; 
        for(auto& tt : _timeline) {
            out << tt[name].calls -  last_tt[name].calls << ",";  
            last_tt = tt; 
        }
        out << std::endl; 
    }
    out << std::endl; 
    
    // time 
    for(auto& name : names) {
        out << name << ","; 
        auto& last_tt = _timeline[0]; 
        for(auto& tt : _timeline) {
            out << tt[name].duration.count() - last_tt[name].duration.count() << ",";  
            last_tt = tt; 
        }
        out << std::endl; 
    }
}
#endif