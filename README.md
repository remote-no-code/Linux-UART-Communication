# Linux-UART-Communication

### Build Instructions
Compile the source file using standard GCC:
```
$ gcc -Wall -Wextra uart_comm.c -o uart_comm
```

### Execution Instructions
Run the binary by passing the target Linux serial interface path as a command-line argument:
```
$ sudo ./uart_comm /dev/ttyUSB0
```

### Hardware Verification Note:
To validate this system-level configuration, I verified the application using an indigenous VSDSquadron Ultra RISC-V development board (featuring the THEJAS32 RV32IM SoC). I flashed a custom firmware to the board's external SPI flash memory using the VEGA FLASHER configuration, programming the microcontroller core to act as a hardware UART echo server running in Machine-Mode.  
When running this Linux C application, the program successfully opened the virtual port generated via the board's onboard CP2102N USB-UART bridge, configured the serial layer to 115200 8N1 standard raw mode parameters, transmitted the payload, and cleanly read back the matched hardware echo response within the allotted select() window."
