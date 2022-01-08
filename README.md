This is a blinky for STM32F411CE microcontroller programmed from blank including the make files, linker and the startup code.

Before Building
---------------
Edit CMakelists.txt to specify path to toolchain file.

Build
-----
In the project directory:
> mkdir build && cd build
> cmake .. -G "MinGW Makefiles"
> cmake --build .

Upload and debug
----------------
Start OpenOCD GDB Server after connecting ST-Link v2:
> openocd -f "...\openocd-0.11.0-1\scripts\interface\stlink.cfg" -f "...\openocd-0.11.0-1\scripts\target\stm32f4x.cfg"

Connect GDB to OpenOCD GDB Server
> arm-none-eabi-gdb "STM32F411CE-bare.elf"
(gdb) target remote localhost:3333

Reset chip, halt it
(gdb) monitor reset halt

Finally flash it...
(gdb) load

...and run the program
(gdb) continue

This section can be built into cmake in the future.

Dependencies
------------
 - ARM-none-eabi C++ cross compiler compiler (C++17)
 - cmake, mingw32-make(or alternative)
 - OpenOCD
 - ST-Link Debugger/Programmer
 - ST-Link Driver