#include "Sound/GBSound.hpp"
#include "Memory.hpp"

#include <algorithm> 
#include <iostream>
#include <sstream>
#include <iomanip>

GBSound::GBSound(const std::string& name, const std::string& description) : 
    MemoryMappedModule(name, description, 0x0, 0x0),
     ch1(1),
     ch2(2),
     ch3(3), 
     _nr10_sweep_register(0),
     _nr11_sound_wave(0),
     _nr12_volume_envelope(0),
     _nr13_frequency_lo(0),
     _nr14_frequency_hi(0),
     
     _ch1_sweep_time(0),
     _ch1_sweep_time_in_ms(0),
     _ch1_number_of_sweep_shift(0),
     
     _ch1_wave_pattern_duty(0),
     _ch1_sound_length(0),
     _ch1_sound_length_in_ms(0),
     
     _ch1_initial_volume_envelope(0),
     _ch1_envelope_increase(0),
     _ch1_number_of_envelope_sweep(0),
     _ch1_envelope_step_length_in_ms(0),
     
     _ch1_initial(0),
     _ch1_selection(0),
     
     _ch1_frequency(0), 
     _ch1_frequency_in_hz(0),
     

     _nr21_sound_wave(0),
     _nr22_volume_envelope(0),
     _nr23_frequency_lo_data(0),
     _nr24_frequency_hi_data(0), 
     
     _ch2_wave_pattern_duty(0),
     _ch2_sound_length(0),
     _ch2_sound_length_in_ms(0),
     
     _ch2_initial_volume_envelope(0),
     _ch2_envelope_increase(0),
     _ch2_number_of_envelope_sweep(0),
     _ch2_envelope_step_length_in_ms(0),
     
     _ch2_initial(0),
     _ch2_selection(0),
     
     _ch2_frequency(0),
     _ch2_frequency_in_hz(0),
     
     
     // ==================================
     // Channel 3 Registers
     _nr30_sound_on_off(0),
     _nr31_sound_length(0),
     _nr32_output_level(0),
     _nr33_frequency_lo_data(0),
     _nr34_frequency_hi_data(0),
     
     // Channel 3 Helper 
     _ch3_sound_on(0),
     _ch3_sound_length(0),
     _ch3_sound_length_in_ms(0),
     _ch3_sound_output_level(0),
     
     _ch3_initial(0),
     _ch3_selection(0),
     
     _ch3_frequency(0),
     _ch3_frequency_in_hz(0),
     
     _nr41_sound_length(0),
     _nr42_volume_envelope(0), 
     _nr43_polynomia_counter(0),
     _nr44_counter(0),
     
     _ch4_sound_length(0),
     _ch4_sound_length_in_ms(0),
     
     _ch4_initial_volume_envelope(0),
     _ch4_envelope_increase(0),
     _ch4_number_of_envelope_sweep(0),
     _ch4_envelope_step_length_in_ms(0),
     
     _ch4_shift_clock_frequency(0),
     _ch4_step_width_selection(0),
     _ch4_step_width(0),
     _ch4_div_ratio(0),
     
     _ch4_initial(0),
     _ch4_selection(0),
     
      _ch4_frequency_in_hz(0),
     
     
     
     _nr50_channel_control(0), 
     _nr51_sound_output_selection(0),
     _nr52_sound_on_off(0),
     
     
     _sc_output_to_so2(0),
     _sc_so2_output_level(0),
     _sc_output_to_so1(0),
     _sc_so1_output_level(0),
     
     _sc_ch4_to_so2(0), 
     _sc_ch3_to_so2(0), 
     _sc_ch2_to_so2(0), 
     _sc_ch1_to_so2(0), 
     _sc_ch4_to_so1(0), 
     _sc_ch3_to_so1(0), 
     _sc_ch2_to_so1(0), 
     _sc_ch1_to_so1(0), 
     
     _sc_all_sound_off(0), 
     _sc_ch4_on(0), 
     _sc_ch3_on(0), 
     _sc_ch2_on(0), 
     _sc_ch1_on(0), 
    _verbose(false), 
    _out("sound_debug.txt"), 
    _debug_out(true)
    { 
    }
    
void GBSound::operate() { 
    int elapsed = elapsed_cycles(); 
    ch1.tick(elapsed);
    ch2.tick(elapsed); 
    ch3.tick(elapsed); 
}

void GBSound::connect_channel_1(Memory& memory) {
    memory.connect(this, 0xFF10); // NR10 - Channel 1 Sweep Register (R/W)
    memory.connect(this, 0xFF11); // NR11 - Channel 1 Sound Length/Wave Pattern Duty
    memory.connect(this, 0xFF12); // NR12 - Channel 1 Volume Envelope (R/W)
    memory.connect(this, 0xFF13); // NR13 - Channel 1 Frequency lo (W)
    memory.connect(this, 0xFF14); // NR14 - Channel 1 Frequency hi (R/W)
    std::cout << "[Sound] Channel 1 connected." << std::endl; 
    if(_debug_out) _out << std::setw(10) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] Channel 1 connected." << std::endl; 
}

void GBSound::connect_channel_2(Memory& memory) {
    memory.connect(this, 0xFF15); // NR20 - Unused
    memory.connect(this, 0xFF16); // NR21 - Channel 2 Sound Length/Wave Pattern Duty (R/W partly)
    memory.connect(this, 0xFF17); // NR22 - Channel 2 Volume Envelope (R/W)
    memory.connect(this, 0xFF18); // NR23 - Channel 2 Frequency lo data (W)
    memory.connect(this, 0xFF19); // NR24 - Channel 2 Frequency hi data (R/W)
    std::cout << "[Sound] Channel 2 connected." << std::endl; 
    if(_debug_out) _out << std::setw(10) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] Channel 2 connected." << std::endl; 
}

void GBSound::connect_channel_3(Memory& memory) {
    memory.connect(this, 0xFF1A); // NR30 - Channel 3 Sound on/off (R/W)
    memory.connect(this, 0xFF1B); // NR31 - Channel 3 Sound Length
    memory.connect(this, 0xFF1C); // NR32 - Channel 3 Select output level (R/W)
    memory.connect(this, 0xFF1D); // NR33 - Channel 3 Frequency's lower data (W)
    memory.connect(this, 0xFF1E); // NR34 - Channel 3 Frequency's higher data (R/W)
    memory.connect(&(ch3.wave_ram())); // 0xFF30 - 0xFF3F
    std::cout << "[Sound] Channel 3 connected." << std::endl; 
    if(_debug_out) _out << std::setw(10) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] Channel 3 connected." << std::endl; 
}

void GBSound::connect_channel_4(Memory& memory) {
    memory.connect(this, 0xFF19); // NR40 - Unused
    memory.connect(this, 0xFF20); // NR41 - Channel 4 Sound Length (R/W)
    memory.connect(this, 0xFF21); // NR42 - Channel 4 Volume Envelope (R/W)
    memory.connect(this, 0xFF22); // NR43 - Channel 4 Polynomial Counter (R/W)
    memory.connect(this, 0xFF23); // NR44 - Channel 4 Counter/consecutive; Initial (R/W)
    std::cout << "[Sound] Channel 4 connected." << std::endl;
    if(_debug_out) _out << std::setw(10) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] Channel 4 connected." << std::endl; 
    
}

void GBSound::connect_status_control_registers(Memory& memory) {
    memory.connect(this, 0xFF24); // NR50 - Channel control / ON-OFF / Volume (R/W)
    memory.connect(this, 0xFF25); // NR51 - Selection of Sound output terminal (R/W)
    memory.connect(this, 0xFF26); // NR52 - Sound on/off
    std::cout << "[Sound] Sound Control Registers connected." << std::endl; 
    if(_debug_out) _out << std::setw(10) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] Sound Control Registers connected." << std::endl; 
}

        
void GBSound::connect_to_memory(Memory& memory) {
    connect_channel_1(memory);
    connect_channel_2(memory); 
    connect_channel_3(memory); 
    connect_channel_4(memory); 
    connect_status_control_registers(memory); 
    std::cout << "[Sound] Sound Module connected." << std::endl; 
    if(_debug_out) _out << std::setw(10) << std::setfill(' ') << _current_cpu_cycles << "[Sound] Sound Module connected." << std::endl; 
}


uint8 GBSound::read_8(uint16 address) {
    if(_debug_out) _out << std::setw(8) << std::setfill(' ') << _current_cpu_cycles << "[Sound] Reading Address " << std::hex << "0x" << address << std::dec <<"." << std::endl; 
    switch(address) {
        // Channel 1 Registers
        case 0xFF10: 
            debug_out("Reading Sweep Register NR10 ", _nr10_sweep_register | 0x80); 
            return _nr10_sweep_register | 0x80; 
            
        case 0xFF11: 
            debug_out("Reading Sound Wave NR11 ", _nr11_sound_wave | 0x3F); 
            return _nr11_sound_wave | 0x3F; 
        
        case 0xFF12: 
            debug_out("Reading Volume Envelope NR12 ", _nr12_volume_envelope); 
            return _nr12_volume_envelope;  
            
        case 0xFF13: 
            debug_out("Reading constant ", 0xFF);  
            return 0xFF; // write only
            
        case 0xFF14:
            debug_out("Reading Frequency Hi NR14 ", _nr14_frequency_hi | 0xBF); // TODO: Check: 0xBF appears weird, should be 7F
            return _nr14_frequency_hi | 0xBF; 
            
        // Channel 2 Registers
            
        case 0xFF15: // TODO: check this
            debug_out("Reading constant ", 0xFF); 
            return 0xFF; 
            
        case 0xFF16:
            debug_out("Reading Sound Wave NR21 ", _nr21_sound_wave | 0x3F); 
            return _nr21_sound_wave | 0x3F; 
            
        case 0xFF17:
            debug_out("Reading Volume Envelope NR22 ", _nr22_volume_envelope); 
            return _nr22_volume_envelope;  
            
        case 0xFF18:
            debug_out("Reading constant ", 0xFF); 
            return 0xFF; // write only
            
        case 0xFF19:
            debug_out("Reading Frequency Hi Data NR24 ", _nr24_frequency_hi_data | 0xBF); // TODO: 0x7F?
            return _nr24_frequency_hi_data | 0xBF; 
            
        // Channel 3 Registers
        case 0xFF1A: 
            debug_out("Reading Sound On Off NR30 ", _nr30_sound_on_off | 0x7F);
            return _nr30_sound_on_off | 0x7F; 
            
        case 0xFF1B:
            debug_out("Reading Sound Length NR31 ", _nr31_sound_length | 0xFF); 
            return _nr31_sound_length | 0xFF; 
            
        case 0xFF1C:
            debug_out("Reading Output Level NR32 ", _nr32_output_level | 0x9F); 
            return _nr32_output_level | 0x9F; 
            
        case 0xFF1D:
            debug_out("Reading constant ", 0xFF); 
            return 0xFF; // write only
            
        case 0xFF1E:
            debug_out("Reading Frequency Hi Data NR34 ", _nr34_frequency_hi_data | 0xBF); 
            return _nr34_frequency_hi_data | 0xBF; 
            
        // Channel 4 Registers
            
        case 0xFF1F: // TODO: Check this
            debug_out("Reading constant ", 0xFF); 
            return 0xFF; 
            
        case 0xFF20: 
            debug_out("Reading Sound Length NR41 ", _nr41_sound_length | 0xFF); 
            return _nr41_sound_length | 0xFF; 
            
        case 0xFF21:
            debug_out("Reading Volume Envelope NR42 ", _nr42_volume_envelope); 
            return _nr42_volume_envelope; 
            
        case 0xFF22:
            debug_out("Reading Polynomial Counter NR43 ", _nr43_polynomia_counter); 
            return _nr43_polynomia_counter; 
            
        case 0xFF23:
            debug_out("Reading Counter NR44 ", _nr44_counter | 0xBF); 
            return _nr44_counter | 0xBF; 
            
        // Sound Control Registers
        case 0xFF24:
            debug_out("Reading Channel Control NR50 ", _nr50_channel_control); 
            return _nr50_channel_control; 
            
        case 0xFF25:
            debug_out("Reading Sound Output Selection NR51 ", _nr51_sound_output_selection); 
            return _nr51_sound_output_selection; 
            
        case 0xFF26:
            debug_out("Reading Sound On Off NR52 ", _nr52_sound_on_off | 0x70); 
            return _nr52_sound_on_off | 0x70; 
    }
    
    
    return 0; 
}
void GBSound::write_8(uint16 address, uint8 value) {
    switch(address) {
        // Channel 1 Registers
        case 0xFF10: 
            std::cout << "Sweep" << std::endl; 
            _ch1_sweep_time     = (value >> 4) & 0x7; 
            _ch1_sweep_decrease = (value & 8); 
            _ch1_number_of_sweep_shift = (value & 7); 
            _ch1_sweep_time_in_ms = _ch1_sweep_time / 128.; 
            _nr10_sweep_register = value; 
            
            ch1.set_sweep_time(_ch1_sweep_time);
            ch1.set_sweep_increase(!_ch1_sweep_decrease);
            ch1.set_sweep_shift(_ch1_number_of_sweep_shift);
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr10() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr10() << std::endl; 
            break;  
            
        case 0xFF11: 
            _ch1_wave_pattern_duty = (value >> 6) & 3; 
            _ch1_sound_length      = (value & 0x3F); 
            _ch1_sound_length_in_ms = (64 - _ch1_sound_length) * (1000. / 256.); 
            _nr11_sound_wave       = value; 
            
            // Control channel 
            ch1.set_wave_duty(_ch1_wave_pattern_duty); 
            ch1.set_sound_length(_ch1_sound_length);
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr11() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr11() << std::endl; 
            break; 
        
        case 0xFF12: 
            _ch1_initial_volume_envelope = (value >> 4) & 0xF; 
            _ch1_envelope_increase       = (value & 8); 
            _ch1_number_of_envelope_sweep= (value & 7); 
            _ch1_envelope_step_length_in_ms = _ch1_number_of_envelope_sweep / 64. * 1000.; 
            _nr12_volume_envelope = value; 
            
            ch1.set_initial_volume(_ch1_initial_volume_envelope);
  
            ch1.set_volume_env_initial(_ch1_initial_volume_envelope);
            ch1.set_volume_env_sweep(_ch1_number_of_envelope_sweep);
            ch1.set_volume_env_increase(_ch1_envelope_increase);
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr12() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr12() << std::endl; 
            break; 
            
        case 0xFF13: 
            _ch1_frequency &= (~(uint16)0xFF); 
            _ch1_frequency |= value; 
            _nr13_frequency_lo = value; 
            _ch1_frequency_in_hz = 131072. / (2048 - _ch1_frequency); 
            
            ch1.set_rate(_ch1_frequency); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr13() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr13() << std::endl; 
            break; 
            
        case 0xFF14:
            _ch1_initial        = (value & 0x80); 
            _ch1_selection      = (value & 0x40); 
            _ch1_frequency &= 0xFF; 
            _ch1_frequency |= (value & 7) << 8; 
            _ch1_frequency_in_hz = 131072. / (2048 - _ch1_frequency); 
            _nr14_frequency_hi  = value; 
            
            ch1.set_counter(_ch1_selection);
            ch1.set_initial(_ch1_initial);
            ch1.set_rate(_ch1_frequency); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr14() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr14() << std::endl; 
            break; 
            
            
        // Channel 2 Registers
        case 0xFF16: 
            _ch2_wave_pattern_duty = (value >> 6) & 3; 
            _ch2_sound_length      = (value & 0x3F); 
            _ch2_sound_length_in_ms= (64-_ch2_sound_length) / 256. * 1000.; 
            _nr21_sound_wave = value; 
            
            ch2.set_wave_duty(_ch2_wave_pattern_duty); 
            ch2.set_sound_length(_ch2_sound_length);
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr21() << std::endl;  }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr21() << std::endl; 
            break; 
            
        case 0xFF17:
            _ch2_initial_volume_envelope = (value >> 4) & 0xF; 
            _ch2_envelope_increase = (value & 8); 
            _ch2_number_of_envelope_sweep= (value & 7); 
            _ch2_envelope_step_length_in_ms = _ch2_number_of_envelope_sweep / 64. * 1000.; 
            _nr22_volume_envelope = value; 
            
            ch2.set_initial_volume(_ch2_initial_volume_envelope);
            ch2.set_volume_env_initial(_ch2_initial_volume_envelope);
            ch2.set_volume_env_sweep(_ch2_number_of_envelope_sweep);
            ch2.set_volume_env_increase(_ch2_envelope_increase);
            if(_verbose) { std::cout << "[Sound] " << describe_nr22() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr22() << std::endl; 
            break; 
            
        case 0xFF18: 
            _ch2_frequency &= (~0xFF); 
            _ch2_frequency |= value; 
            _nr23_frequency_lo_data = value; 
            _ch2_frequency_in_hz = 131072. / (2048 - _ch2_frequency); 
            
            ch2.set_rate(_ch2_frequency); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr23() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr23() << std::endl; 
            break;
            
        case 0xFF19: 
            _ch2_initial        = (value & 0x80); 
            _ch2_selection      = (value & 0x40); 
            _ch2_frequency &= 0xFF; 
            _ch2_frequency |= (value & 7) << 8; 
            _ch2_frequency_in_hz = 131072. / (2048 - _ch2_frequency); 
            _nr24_frequency_hi_data  = value; 
            
            ch2.set_counter(_ch2_selection);
            ch2.set_initial(_ch2_initial); 
            ch2.set_rate(_ch2_frequency); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr24() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr24() << std::endl; 
            break; 
            
        // Channel 3 Registers
        case 0xFF1A: 
            _ch3_sound_on = (value & 0x80); 
            _nr30_sound_on_off = value; 
            
            ch3.set_on(_ch3_sound_on); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr30() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr30() << std::endl; 
            break; 
            
        case 0xFF1B: 
            _ch3_sound_length = value; 
            _ch3_sound_length_in_ms = (256-_ch3_sound_length) / 256. * 1000.; 
            _nr31_sound_length = value; 
            
            ch3.set_sound_length(_ch3_sound_length); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr31() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr31() << std::endl; 
            break; 
            
        case 0xFF1C: 
            _ch3_sound_output_level = (value >> 5) & 3; 
            _nr32_output_level = value; 
            
            ch3.set_output_level(_ch3_sound_output_level); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr32() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr32() << std::endl; 
            break;
            
        case 0xFF1D: 
            _ch3_frequency &= (~0xFF); 
            _ch3_frequency |= value; 
            _nr33_frequency_lo_data = value; 
            _ch3_frequency_in_hz = 65536. / (2048 - _ch3_frequency); 
            
            ch3.set_rate(_ch3_frequency); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr33() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr33() << std::endl; 
            break;
            
        case 0xFF1E: 
            _ch3_initial        = (value & 0x80); 
            _ch3_selection      = (value & 0x40); 
            _ch3_frequency &= 0xFF; 
            _ch3_frequency |= (value & 7) << 8; 
            _ch3_frequency_in_hz = 65536. / (2048 - _ch3_frequency); 
            _nr34_frequency_hi_data  = value; 

            ch3.set_rate(_ch3_frequency);
            ch3.set_initial(_ch3_initial); 
            ch3.set_counter(_ch3_selection); 
            
            if(_verbose) { std::cout << "[Sound] " << describe_nr34() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr34() << std::endl; 
            break; 
            
        // Channel 4 Registers
        case 0xFF20: 
            _ch4_sound_length = (value & 0x3F); 
            _ch4_sound_length_in_ms = (64-_ch4_sound_length) / 256. * 1000.; 
            _nr41_sound_length = value; 
            if(_verbose) { std::cout << "[Sound] " << describe_nr41() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr41() << std::endl; 
            break; 
           
        case 0xFF21: 
            _ch4_initial_volume_envelope = (value >> 4) & 0xF; 
            _ch4_envelope_increase = (value & 8); 
            _ch4_number_of_envelope_sweep= (value & 3); 
            _ch4_envelope_step_length_in_ms = _ch4_number_of_envelope_sweep / 64. * 1000.; 
            _nr42_volume_envelope = value; 
            if(_verbose) { std::cout << "[Sound] " << describe_nr42() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr42() << std::endl; 
            break; 
            
        case 0xFF22: 
            _ch4_shift_clock_frequency = (value >> 4) & 0xF; 
            _ch4_step_width_selection = (value & 8); 
            _ch4_step_width = (_ch4_step_width_selection ? 7 : 15); 
            _ch4_div_ratio = (value & 7); 
            _ch4_frequency_in_hz = 524288. / (_ch4_div_ratio ? _ch4_div_ratio : 0.5)  / std::pow(2., _ch4_shift_clock_frequency+1); 
            _nr43_polynomia_counter = value; 
            if(_verbose) { std::cout << "[Sound] " << describe_nr43() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr43() << std::endl; 
            break; 
            
        case 0xFF23: 
            _ch4_initial        = (value & 0x80); 
            _ch4_selection      = (value & 0x40); 
            _nr44_counter = value; 
            if(_verbose) { std::cout << "[Sound] " << describe_nr44() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr44() << std::endl; 
            break; 
            
        // Sound Control Registers
        case 0xFF24: 
            _sc_output_to_so2 = (value & 0x80); 
            _sc_so2_output_level = (value >> 4) & 7; 
            _sc_output_to_so1 = (value & 0x08); 
            _sc_so1_output_level = (value) & 7;
            _nr50_channel_control = value; 
            if(_verbose) { std::cout << "[Sound] " << describe_nr50() << std::endl; }
            if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr50() << std::endl; 
            break; 
            
        case 0xFF25:
            _sc_ch4_to_so2 = (value & 0x80); 
            _sc_ch3_to_so2 = (value & 0x40); 
            _sc_ch2_to_so2 = (value & 0x20); 
            _sc_ch1_to_so2 = (value & 0x10); 
            _sc_ch4_to_so1 = (value & 0x08); 
            _sc_ch3_to_so1 = (value & 0x04); 
            _sc_ch2_to_so1 = (value & 0x02); 
            _sc_ch1_to_so1 = (value & 0x01); 
            _nr51_sound_output_selection = value; 
             if(_verbose) { std::cout << "[Sound] " << describe_nr51() << std::endl; }
             if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr51() << std::endl; 
            break; 
            
        case 0xFF26:
            _nr52_sound_on_off = (_nr52_sound_on_off & 0x7F) | (value & 0x80); // only bit 
             if(_verbose) { std::cout << "[Sound] " << describe_nr52() << std::endl; }
             if(_debug_out) _out << std::setw(16) << std::setfill(' ') << std::left << _current_cpu_cycles << "[Sound] " << describe_nr52() << std::endl; 
            break; 
    }
}

std::string GBSound::describe_nr10() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR10 Info (" << (int)_nr10_sweep_register << "): " << std::endl; ss << std::dec; 
    ss << "    Channel 1 Sweep Time     : " << (int)_ch1_sweep_time << " (" << _ch1_sweep_time_in_ms << "ms)" << std::endl;
    ss << "    Channel 1 Sweep Descrease: " << (_ch1_sweep_decrease ? "Descrease" : "Increase") << std::endl; 
    ss << "    Channel 1 Nr. Sweep Shift: " << (int)_ch1_number_of_sweep_shift << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr11() {
    std::stringstream ss; ss << std::hex;  
    ss << "NR11 Info (" << (int)_nr11_sound_wave << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 1 Wave Pattern Duty: " << (int)_ch1_wave_pattern_duty << std::endl; 
    ss << "    Channel 1 Sound Length     : " << (int)_ch1_sound_length << " (" << _ch1_sound_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr12() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR12 Info (" << (int)_nr12_volume_envelope << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 1 Initial Volume Env: " << (int)_ch1_initial_volume_envelope << std::endl; 
    ss << "    Channel 1 Envelope Increase : " << (_ch1_envelope_increase ? "Increase" : "Decrease") << std::endl; 
    ss << "    Channel 1 Number of Env Swee: " << (int)_ch1_number_of_envelope_sweep << " (Step Length: " << _ch1_envelope_step_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr13() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR13 Info (" << (int)_nr13_frequency_lo << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 1 Frequency: " << _ch1_frequency << " (" << _ch1_frequency_in_hz << " Hz)"  << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr14() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR14 Info (" << (int)_nr14_frequency_hi << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 1 Frequency: " << _ch1_frequency << " (" << _ch1_frequency_in_hz << " Hz)"  << std::endl; 
    ss << "    Channel 1 Initial  : " << _ch1_initial << std::endl; 
    ss << "    Channel 1 Selection: " << _ch1_selection << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr21() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR21 Info (" << (int)_nr11_sound_wave << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 2 Wave Pattern Duty: " << (int)_ch2_wave_pattern_duty << std::endl; 
    ss << "    Channel 2 Sound Length     : " << (int)_ch2_sound_length << " (" << _ch2_sound_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr22() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR22 Info (" << (int)_nr22_volume_envelope << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 2 Initial Volume Env: " << (int)_ch2_initial_volume_envelope << std::endl; 
    ss << "    Channel 2 Envelope Increase : " << (_ch2_envelope_increase ? "Increase" : "Decrease") << std::endl; 
    ss << "    Channel 2 Number of Env Swee: " << (int)_ch2_number_of_envelope_sweep << " (Step Length: " << _ch2_envelope_step_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr23() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR23 Info (" << (int)_nr23_frequency_lo_data << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 2 Frequency: " << _ch2_frequency << " (" << _ch2_frequency_in_hz << " Hz)"  << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr24() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR24 Info (" << (int)_nr24_frequency_hi_data << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 2 Frequency: " << _ch2_frequency << " (" << _ch2_frequency_in_hz << " Hz)"  << std::endl; 
    ss << "    Channel 2 Initial  : " << _ch2_initial << std::endl; 
    ss << "    Channel 2 Selection: " << _ch2_selection << std::endl; 
    return ss.str(); 
}


std::string GBSound::describe_nr30() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR30 Info (" << (int)_nr30_sound_on_off << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 3 On/Off: " << (_ch3_sound_on ? "On" : "Off") << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr31() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR31 Info (" << (int)_nr31_sound_length << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 3 Sound Length: " << (int)_ch3_sound_length << " (" << _ch3_sound_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr32() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR32 Info (" << (int)_nr32_output_level << "): " << std::endl;  ss << std::dec; 
    ss << "    Channel 3 Output Level: " << (int)_ch3_sound_output_level << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr33() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR33 Info (" << (int)_nr33_frequency_lo_data << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 3 Frequency: " << _ch3_frequency << " (" << _ch3_frequency_in_hz << " Hz)"  << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr34() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR34 Info (" << (int)_nr34_frequency_hi_data << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 3 Frequency: " << _ch3_frequency << " (" << _ch3_frequency_in_hz << " Hz)"  << std::endl; 
    ss << "    Channel 3 Initial  : " << _ch3_initial << std::endl; 
    ss << "    Channel 3 Selection: " << _ch3_selection << std::endl; 
    return ss.str(); 
}


std::string GBSound::describe_nr41() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR41 Info (" << (int)_nr41_sound_length << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 4 Sound Length: " << (int)_ch4_sound_length << " (" << _ch4_sound_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr42() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR42 Info (" << (int)_nr42_volume_envelope << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 4 Initial Volume Env: " << (int)_ch4_initial_volume_envelope << std::endl; 
    ss << "    Channel 4 Envelope Increase : " << (_ch4_envelope_increase ? "Increase" : "Decrease") << std::endl; 
    ss << "    Channel 4 Number of Env Swee: " << (int)_ch4_number_of_envelope_sweep << " (Step Length: " << _ch2_envelope_step_length_in_ms << "ms)" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr43() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR43 Info (" << (int)_nr43_polynomia_counter << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 4 Shift Clock Freq.: " << (int)_ch4_shift_clock_frequency << std::endl; 
    ss << "    Channel 4 Step Width Select: " << (int)_ch4_step_width_selection << " ("
       << (int)_ch4_step_width << ")" << std::endl; 
    ss << "    Channel 4 Div Ratio        : " << (int)_ch4_div_ratio << std::endl; 
    ss << "    channel 4 Frequency        : " << _ch4_frequency_in_hz << " Hz" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr44() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR44 Info (" << (int)_nr44_counter << "): " << std::endl; ss << std::dec;  
    ss << "    Channel 4 Initial  : " << _ch4_initial << std::endl; 
    ss << "    Channel 4 Selection : " << _ch4_selection << std::endl; 
    return ss.str(); 
}


std::string GBSound::describe_nr50() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR50 Info (" << (int)_nr50_channel_control << "): " << std::endl; ss << std::dec;  
    ss << "    Sound Control SO2  : " << _sc_output_to_so2 << " (Vol: " << (int)_sc_so2_output_level << ")" << std::endl; 
    ss << "    Sound Control SO1  : " << _sc_output_to_so1 << " (Vol: " << (int)_sc_so1_output_level << ")" << std::endl; 
    return ss.str(); 
}

std::string GBSound::describe_nr51() {
    auto onOff = [](bool v){ return (v ? "On" : "Off"); }; 
    
    std::stringstream ss; ss << std::hex; 
    ss << "NR51 Info (" << (int)_nr51_sound_output_selection << "): " << std::endl; 
    ss << "        Ch4 Ch3 Ch2 Ch1" << std::endl; 
    ss << std::setfill(' '); 
    ss << "    SO2 " << std::setw(3) << onOff(_sc_ch4_to_so2) << " " << std::setw(3) << onOff(_sc_ch3_to_so2) << " " << std::setw(3) << onOff(_sc_ch2_to_so2) << " " << std::setw(3) << onOff(_sc_ch1_to_so2) << std::endl; 
    ss << "    SO1 " << std::setw(3) << onOff(_sc_ch4_to_so1) << " " << std::setw(3) << onOff(_sc_ch3_to_so1) << " " << std::setw(3) << onOff(_sc_ch2_to_so1) << " " << std::setw(3) << onOff(_sc_ch1_to_so1) << std::endl;
    return ss.str();
}

std::string GBSound::describe_nr52() {
    std::stringstream ss; ss << std::hex; 
    ss << "NR52 Info (" << (int)_nr52_sound_on_off << ") " << std::endl; 
    return ss.str(); 
}
