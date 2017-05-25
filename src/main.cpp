#include <iostream>
#include <sstream>

#include "LR35902.hpp"
#include "GBROM.hpp" 
#include "GBCartridge.hpp"
#include "Cartridge/GBMBC1.hpp"
#include "GBInterruptEnable.hpp" 
#include "GBInterruptFlag.hpp"
#include "GBJoypad.hpp"
#include "GBSerialTransfer.hpp"
#include "GBTimer.hpp"
#include "SFML_GBVideo.hpp"
#include "Sound/SFML_GBSound.hpp"

#include "Instruction.hpp"

#include "Utility/ScopedTimer.hpp"

#include <fstream>
#include <cstdlib> 
#include <limits>
#include <iomanip>


std::string show_bcd(uint8 v) {
    std::stringstream ss; 
    ss << (int)((v >> 4)&0xF) << (int)((v)&0xF); 
    return ss.str(); 
}

int main() {
	try {
		ScopedTimer st("main");

		LR35902 cpu;
		cpu.memory.set_boot(true);
		GBROM  rom(0x0000, 0x0100);             rom.init(rom.size());
		GBRAM  zero_page_ram(0xFF80, 0xFFFF);   zero_page_ram.init(zero_page_ram.size());
		GBRAM  internal_ram(0xC000, 0xFE00);    internal_ram.init(internal_ram.size());
		GBRAM  switchable_ram(0xA000, 0xC000);   switchable_ram.init(switchable_ram.size());
		GBJoypad joypad(0xFF00, 0xFF01);
		GBSerialTransfer serialTransfer(0xFF01, 0xFF03);
		GBInterruptEnable ie(0xFFFF, 0x10000);
		GBInterruptFlag iff(0xFF0F, 0xFF10);
		SFML_GBSound sound;
		sound.play();
		GBTimer timer(0xFF04, 0xFF08);
		timer.set_verbose(false);
		cpu.ie = &ie;
		cpu.iff = &iff;
		ie.set_verbose(false);


		SFML_GBVideo video(0x8000, 0xA000);
		cpu.memory.connect(&zero_page_ram);
		cpu.memory.connect(&internal_ram);
		cpu.memory.connect(&timer);
		cpu.memory.connect(&switchable_ram); 
		video.init();
		video.connect_to_memory(cpu.memory);
		video.set_verbose(false);

		sound.connect_to_memory(cpu.memory);
		sound.set_verbose(false);

		// fill rom with boot info
		std::fstream in("data\\DMG_ROM.bin", std::ios::in | std::ios::binary);
		if (!in.is_open()) {
			std::cout << "Not able to find Boot ROM. Please change your path" << std::endl;
			return 1;
		}
		uint16 addr = 0x0000;
		std::cout << "reading" << std::endl;
		std::vector<uint8> data;
		uint8 value;
		while (in.get((char&)value)) {
			rom.write_8_rom(addr, value & 0xFF);
			addr++;
		}

		std::cout << "Read " << addr << " bytes." << std::endl;
		char g;
		//  std::cin >> g; 

		 // read cartridge
		GBMBC1 gbc(0x0000, 0x8000);
		//GBCartridge gbc(0x0000, 0x8000);
		gbc.read_file("data\\Bounce.gb");
		cpu.memory.connect(&gbc);

		// map cartridge to memory
		// now printing dissassembly // rom will overwrite gbc entries
		cpu.memory.connect(&rom);
		cpu.disassemble();
		cpu.init();


		// current debug info: 
		// 0x508: call to 0x90A

		int a = 0;
		bool once = false;
		bool use_breakpoint = true;
		bool verbose_instruction = false;
		cpu.memory.set_verbose(false);
		bool switched = false;
		uint16 execute_until = 0x100;

		cpu.memory.connect(&joypad);
		cpu.memory.connect(&serialTransfer);
		cpu.memory.connect(&ie);
		cpu.memory.connect(&iff);

		cpu.init_timer();
		sound.init(cpu.cycle_counter);
		video.update_cycles(cpu.cycle_counter);
		timer.init(cpu.cycle_counter);
		timer.update_cycles(cpu.cycle_counter);
		for (int i = 0; i < 100000000; ++i) {
			if (!cpu.debug_hold) {
				cpu.single_step(verbose_instruction);

				// system("sleep 0.0001");
				if (use_breakpoint) {
					if (!once && cpu.registers.PC >= execute_until) { // 0xe60
						once = true;
						cpu.memory.dump();
						verbose_instruction = true;
						break;
					}
					//    if(once) 
						 //   std::cin >> a; 
				}
				if (!switched && cpu.registers.PC >= 0xff) {
					std::cout << "Connecting rom..." << std::endl;
					cpu.memory.connect(&gbc);
					switched = true;
				}
			}
			else break;
			video.update_cycles(cpu.cycle_counter);
			video.execute();

			// forward interrupts
			if (video.vblank_interrupt_request()) {
				iff.set_interrupt(Interrupt::VBlank);
				video.clear_vblank_interrupt_request();
			}
			if (video.lcdc_interrupt_request()) {
				iff.set_interrupt(Interrupt::LCDC);
				video.clear_lcdc_interrupt_request();
			}


			timer.update_cycles(cpu.cycle_counter);
			timer.execute();
			if (timer.timer_interrupt_request()) {
				iff.set_interrupt(Interrupt::Timer);
				timer.clear_timer_interrupt();
			}

			sound.update_cycles(cpu.cycle_counter);
			sound.execute();

			// handle dma
			if (video.dma_request()) {
				std::cout << "dma requested." << std::endl;
				uint16 dma_transfer_address = video.dma_transfer_value() << 8;
				std::cout << "address: " << dma_transfer_address << std::endl;
				video.clear_dma_request();
				for (int dma_i = 0; dma_i < 0xA0; ++dma_i) {
					uint8 value = cpu.memory.read_8(dma_transfer_address + dma_i);
					cpu.memory.write_8(0xFE00 + dma_i, value);
				}
			}
		}
		cpu.memory.connect(&gbc);
		
		// cpu.memory.connect(&gbc, 0xA000, 0xC000);
		cpu.memory.set_boot(false);
		std::string input;

		bool done = false;
		use_breakpoint = false;
		uint16 breakpoint = 0;

		std::cout << "Bootstrap done. Now ROM execution..." << std::endl;
		verbose_instruction = false;
		// use_breakpoint = true; 
		breakpoint = -1;
		while (!done) {
			// std::cout << "CPU cycles: " << cpu.cycle_counter << std::endl; 
			if (video.break_request()) {
				use_breakpoint = false;
				video.set_break_request(false);
			}
			if (!use_breakpoint) {
				std::getline(std::cin, input);
				std::cout << "Eingabe war: " << input << std::endl;
				switch (input[0]) {
				case 'q': // quit
					done = true;
					break;

				case 'f':
				{
					std::stringstream ss(input);
					std::string filename;
					int entries = 100;
					ss >> filename >> filename >> entries;
					std::cout << "Saving trace (" << entries << ") to file " << filename << std::endl;

					std::ofstream tracefile(filename.c_str());
					tracefile << std::hex;
					for (int i = std::max(0, (int)cpu.trace.size() - entries), iEnd = cpu.trace.size(); i != iEnd; ++i) {
						cpu.print_state(cpu.trace[i].registers_before, tracefile);
						tracefile << "Instruction: " << cpu.trace[i].instruction->alt_name << std::endl;
					}
					cpu.print_state(cpu.trace.back().registers_after, tracefile);
				}
				break;

				case 't': // show trace
				{
					std::cout << "Instruction Trace: " << cpu.trace.size() << " entries." << std::endl;
					std::cout << "Printing last 20 instructions and states: " << std::endl;
					for (int i = std::max(0, (int)cpu.trace.size() - 20), iEnd = cpu.trace.size(); i != iEnd; ++i) {
						cpu.print_state(cpu.trace[i].registers_before);
						std::cout << "Instruction: " << cpu.trace[i].instruction->alt_name << std::endl;
					}
					cpu.print_state(cpu.trace.back().registers_after);
				}
				break;

				case 'p': // press button 
				{
					std::cout << "Press button ";
					std::stringstream ss(input);
					std::string button;
					ss >> button >> button;
					std::cout << button << std::endl;
					if (button == "start" || button == "st") { joypad.start(!joypad.start_pressed()); }
					else if (button == "select" || button == "se") joypad.select(!joypad.select_pressed());
					else if (button == "up" || button == "u")      joypad.up(!joypad.up_pressed());
					else if (button == "down" || button == "d")    joypad.down(!joypad.down_pressed());
					else if (button == "left" || button == "l")    joypad.left(!joypad.left_pressed());
					else if (button == "right" || button == "r")   joypad.right(!joypad.right_pressed());
					else if (button == "a")                        joypad.a(!joypad.a_pressed());
					else if (button == "b")                        joypad.b(!joypad.b_pressed());
				}
				break;

				case 'b': // set next breakpoint 
				{
					use_breakpoint = true;
					std::stringstream ss(input);
					std::string tmp;
					ss >> tmp >> std::hex >> breakpoint;
				}
				break;

				case 'r': // release button
				{
					std::stringstream ss(input);
					std::string button;
					ss >> button >> button;
					if (button == "start" || button == "st")       joypad.start();
					else if (button == "select" || button == "se") joypad.select();
					else if (button == "up" || button == "u")      joypad.up();
					else if (button == "down" || button == "d")    joypad.down();
					else if (button == "left" || button == "l")    joypad.left();
					else if (button == "right" || button == "r")   joypad.right();
					else if (button == "a")                        joypad.a();
					else if (button == "b")                        joypad.b();
				}
				break;

				case 's': // step 
				{
					cpu.single_step(verbose_instruction);
					cpu.print_state();
				}
				break;

				case 'v':
					verbose_instruction = !verbose_instruction;
					break;

				case 'd': { // dump background_maps
					{
						std::ofstream out("bgmap1.txt");
						for (int y = 0; y < 32; ++y) {
							for (int x = 0; x < 32; ++x) {
								int offset = x + y * 32;
								out << std::setw(5) << std::setfill(' ') << (int)cpu.memory.read_8(0x9800 + offset) << " ";
							}
							out << std::endl;
						}
					}
					{
						std::ofstream out("bgmap2.txt");
						for (int y = 0; y < 32; ++y) {
							for (int x = 0; x < 32; ++x) {
								int offset = x + y * 32;
								out << std::setw(5) << std::setfill(' ') << (int)cpu.memory.read_8(0x9C00 + offset) << " ";
							}
							out << std::endl;
						}
					}

				}
						  break;

				default:
					std::cout << "Unknown option." << std::endl;
					break;
				}
			}
			else {
				if (cpu.registers.PC == breakpoint) {
					use_breakpoint = false;
				}
				else {
					cpu.single_step(verbose_instruction);
					// if(cpu.calls() >= 69856675)
					//     done = true; 
					video.update_cycles(cpu.cycle_counter);
					video.execute();

					// forward interrupts
					if (video.vblank_interrupt_request()) {
						iff.set_interrupt(Interrupt::VBlank);
						video.clear_vblank_interrupt_request();
					}
					if (video.lcdc_interrupt_request()) {
						iff.set_interrupt(Interrupt::LCDC);
						video.clear_lcdc_interrupt_request();
					}

					timer.update_cycles(cpu.cycle_counter);
					timer.execute();
					if (timer.timer_interrupt_request()) {
						iff.set_interrupt(Interrupt::Timer);
						timer.clear_timer_interrupt();
					}

					sound.update_cycles(cpu.cycle_counter);
					sound.execute();

					// handle dma
					if (video.dma_request()) {
						// std::cout << "dma requested." << std::endl; 
						uint16 dma_transfer_address = video.dma_transfer_value() << 8;
						// std::cout << "address: " << dma_transfer_address << std::endl; 
						video.clear_dma_request();
						// cpu.memory.set_verbose(true); 
						for (int dma_i = 0; dma_i < 0xA0; ++dma_i) {
							uint8 value = cpu.memory.read_8(dma_transfer_address + dma_i);
							cpu.memory.write_8(0xFE00 + dma_i, value);
						}
						// cpu.memory.set_verbose(false); 
					}

					// hack to have input
					if (video.buttons_changed()) {
						video.clear_button_changed();
						joypad.start(video.button_start());
						joypad.select(video.button_select());
						joypad.up(video.button_up());
						joypad.down(video.button_down());
						joypad.left(video.button_left());
						joypad.right(video.button_right());
						joypad.a(video.button_a());
						joypad.b(video.button_b());
						iff.set_interrupt(Interrupt::Joystick);
					}
				}
			}
		}
	}
	catch (...) {
	}
	std::cin.get(); 
	
}
