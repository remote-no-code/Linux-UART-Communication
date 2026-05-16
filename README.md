
# Linux UART Communication & Hardware Validation

> I am an undergraduate student actively expanding my skills in Linux system programming and hardware-software interfacing. To ensure a robust and standard implementation, I utilized POSIX `termios` documentation and AI assistance to help structure the boilerplate UART configuration and error handling. However, I have thoroughly reviewed the logic, executed the physical hardware validation myself, and fully understand the underlying data flow.

### Test Execution Results
Below is the terminal output demonstrating successful payload transmission and hardware echo reception from the physical board:

```text
atharv@atharv-InsydeH2O-EFI-BIOS:~/VLSI$ sudo ./uart_test /dev/ttyUSB0
[sudo] password for atharv: 
Sent: LFX Mentorship Test!
Waiting for response...
Received: LFX Mentorship Test!

```

### Build Instructions

Compile the source file using standard GCC:

```bash
$ gcc -Wall -Wextra uart_comm.c -o uart_comm

```

### Execution Instructions

Run the binary by passing the target Linux serial interface path as a command-line argument:

```bash
$ sudo ./uart_comm /dev/ttyUSB0

```

### Hardware Verification Note

To validate this system-level configuration, I verified the application using an indigenous **VSDSquadron Ultra RISC-V development board** (featuring the **THEJAS32 RV32IM SoC**). I flashed a custom firmware to the board's external SPI flash memory using the **VEGA FLASHER** configuration, programming the microcontroller core to act as a hardware UART echo server running in Machine-Mode.

When running this Linux C application, the program successfully opened the virtual port generated via the board's onboard **CP2102N USB-UART bridge**, configured the serial layer to 115200 8N1 standard raw mode parameters, transmitted the payload, and cleanly read back the matched hardware echo response within the allotted `select()` window.

---

### Hardware Loopback Firmware Reference

```cpp
void setup() {
  // Initialize UART0 at 115200 baud to match the Linux host
  Serial.begin(115200); 
}

void loop() {
  // Echo server: immediately transmit any received bytes
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    Serial.write(incomingByte);
  }
}

```
