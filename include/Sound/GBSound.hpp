#ifndef GBSOUND_HPP__
#define GBSOUND_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"
#include "Sound/SweepSquareWave.hpp" 
#include "Sound/Wave.hpp" 

class Memory; 

class GBSound : public MemoryMappedModule {
public: 
        GBSound(const std::string& name = std::string("Sound"), 
                const std::string& description = std::string("Sound Module"));
        
        ~GBSound() { }
        
        virtual uint8 read_8(uint16 address); 
        virtual void write_8(uint16 address, uint8 value); 
        
        void connect_to_memory(Memory& memory); 
        
        void set_verbose(bool verbose) { _verbose = verbose; }
        bool verbose() { return _verbose; }
        
        virtual void operate(); 
        
        void init(uint32 current_cpu_cycles) { _current_cpu_cycles = _last_cpu_cycles = current_cpu_cycles; }
        uint32 elapsed_cycles() { return _current_cpu_cycles - _last_cpu_cycles; }
        void update_cycles(uint32 current_cpu_cycles) { 
            _last_cpu_cycles = _current_cpu_cycles; 
            _current_cpu_cycles = current_cpu_cycles; 
        }
        
protected: 
        SweepSquareWave ch1; 
        SquareWave ch2;
        Wave ch3; 
        
private: 
        void connect_channel_1(Memory& memory); 
        void connect_channel_2(Memory& memory); 
        void connect_channel_3(Memory& memory); 
        void connect_channel_4(Memory& memory); 
        void connect_status_control_registers(Memory& memory);
        
        std::string describe_nr10(); 
        std::string describe_nr11(); 
        std::string describe_nr12(); 
        std::string describe_nr13(); 
        std::string describe_nr14(); 
        
        std::string describe_nr21(); 
        std::string describe_nr22(); 
        std::string describe_nr23(); 
        std::string describe_nr24(); 
        
        std::string describe_nr30(); 
        std::string describe_nr31(); 
        std::string describe_nr32(); 
        std::string describe_nr33(); 
        std::string describe_nr34(); 
        
        std::string describe_nr41(); 
        std::string describe_nr42(); 
        std::string describe_nr43(); 
        std::string describe_nr44(); 
        
        std::string describe_nr50(); 
        std::string describe_nr51(); 
        std::string describe_nr52(); 
        
        // GBRAM wave_pattern_ram; 
        
        // ==================================
        // Channel 1 Registers
        uint8 _nr10_sweep_register; 
        uint8 _nr11_sound_wave; 
        uint8 _nr12_volume_envelope; 
        uint8 _nr13_frequency_lo; 
        uint8 _nr14_frequency_hi; 
        
        // Channel 1 Helper
        uint8 _ch1_sweep_time; 
        double _ch1_sweep_time_in_ms; 
        bool  _ch1_sweep_decrease; 
        uint8 _ch1_number_of_sweep_shift; 
        
        uint8 _ch1_wave_pattern_duty; 
        uint8 _ch1_sound_length; 
        double _ch1_sound_length_in_ms;
        
        uint8 _ch1_initial_volume_envelope; 
        bool  _ch1_envelope_increase; 
        uint8 _ch1_number_of_envelope_sweep; 
        double _ch1_envelope_step_length_in_ms; 
        
        bool _ch1_initial; // true if sound restart
        bool _ch1_selection; 
        
        uint16 _ch1_frequency; 
        double _ch1_frequency_in_hz; 
        
        
        // ==================================
        // Channel 2 Registers
        uint8 _nr21_sound_wave; 
        uint8 _nr22_volume_envelope; 
        uint8 _nr23_frequency_lo_data; 
        uint8 _nr24_frequency_hi_data; 
        
        // Channel 2 Helper
        uint8 _ch2_wave_pattern_duty; 
        uint8 _ch2_sound_length; 
        double _ch2_sound_length_in_ms; 
        
        uint8 _ch2_initial_volume_envelope; 
        bool _ch2_envelope_increase; 
        uint8 _ch2_number_of_envelope_sweep; 
        double _ch2_envelope_step_length_in_ms; 
        
        bool _ch2_initial; // true if sound restart
        bool _ch2_selection; 
        
        uint16 _ch2_frequency; 
        double _ch2_frequency_in_hz;
        
        
        // ==================================
        // Channel 3 Registers
        uint8 _nr30_sound_on_off; 
        uint8 _nr31_sound_length; 
        uint8 _nr32_output_level; 
        uint8 _nr33_frequency_lo_data; 
        uint8 _nr34_frequency_hi_data;
        
        // Channel 3 Helper 
        bool _ch3_sound_on; 
        uint8 _ch3_sound_length; 
        double _ch3_sound_length_in_ms; 
        uint8 _ch3_sound_output_level; 
        
        bool _ch3_initial; // true if sound restart
        bool _ch3_selection; 
        
        uint16 _ch3_frequency; 
        double _ch3_frequency_in_hz;
        
        // ==================================
        // Channel 4 Registers
        uint8 _nr41_sound_length; 
        uint8 _nr42_volume_envelope; 
        uint8 _nr43_polynomia_counter; 
        uint8 _nr44_counter; 
        
        // Channel 4 Helper 
        uint8 _ch4_sound_length; 
        double _ch4_sound_length_in_ms;
        
        uint8 _ch4_initial_volume_envelope; 
        bool _ch4_envelope_increase; 
        uint8 _ch4_number_of_envelope_sweep; 
        double _ch4_envelope_step_length_in_ms; 
        
        uint8 _ch4_shift_clock_frequency; 
        bool _ch4_step_width_selection; 
        uint8 _ch4_step_width; 
        uint8 _ch4_div_ratio; 
        
        bool _ch4_initial; // true if sound restart
        bool _ch4_selection; 
        
         double _ch4_frequency_in_hz;
         
        // ==================================
        // Sound Control Registers 
        uint8 _nr50_channel_control; 
        uint8 _nr51_sound_output_selection; 
        uint8 _nr52_sound_on_off; 
        
        // Sound Control Helper
        bool _sc_output_to_so2; 
        uint8 _sc_so2_output_level; 
        bool _sc_output_to_so1; 
        uint8 _sc_so1_output_level; 
        
        bool _sc_ch4_to_so2; 
        bool _sc_ch3_to_so2; 
        bool _sc_ch2_to_so2; 
        bool _sc_ch1_to_so2; 
        bool _sc_ch4_to_so1; 
        bool _sc_ch3_to_so1; 
        bool _sc_ch2_to_so1; 
        bool _sc_ch1_to_so1; 
        
        bool _sc_all_sound_off; 
        bool _sc_ch4_on; 
        bool _sc_ch3_on; 
        bool _sc_ch2_on; 
        bool _sc_ch1_on; 
        
        bool _verbose; 
        
        uint32 _current_cpu_cycles; 
        uint32 _last_cpu_cycles; 
};

#endif
