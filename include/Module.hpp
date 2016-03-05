#ifndef __MODULE_HPP__
#define __MODULE_HPP__

#include <string>

/*
Standard Module Interface. 
Every component should derive from this class and
specialize for given task.
*/
class Module {
    public:
        Module(const std::string& name, const std::string& description) : _name(name), _description(description) { }; 
        
        const std::string& name() { return _name; }
        const std::string& description() { return _description; }
        
        void execute() { operate(); } // should be called periodically to execute stuff in between (Sound, Video)
        virtual void operate() = 0;
        
    private:
        std::string _name; 
        std::string _description; 
}; 

#endif