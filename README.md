PeakOS
======
**PeakOS** is a hobby operating system. [Click here to see current plans for the project on Trello.](https://trello.com/b/5HTUZoXM/peakos)

## Screenshots
![Boot](https://raw.githubusercontent.com/StevenLaabs/PeakOS/master/images/pmm_init.png)

## Download
* [Current](https://github.com/StevenLaabs/PeakOS/archive/master.zip)
* No other versions are available at this time

## Building and running
#### Dependencies
* nasm
* gcc - Note: This project uses a cross-compiled build of gcc. In the future I'll likely add a script to compile one automatically but for now you should follow [this tutorial](http://wiki.osdev.org/GCC_Cross-Compiler) for i686-elf-gcc.
* qemu

```bash
$ git clone https://github.com/StevenLaabs/PeakOS.git
$ ./build.sh
$ ./start.sh
```
## Structure
This section explains the file structure of the project. Explanations of individual source files can be found in the comments of the files themselves.
```
peakos - Includes the README and some useful scripts for building and running
│
└───kernel - Main kernel directory for booting, processes, drivers, etc.
│   │
│   └───arch - Architecture specific implementations
│   │   │
│   │   └───i386 - Implementations for the i386 processor
│   │
│   └───drivers - Driver code for handling certain hardware functionalities
│   │
│   └───hal - hardware abstraction layer for interfacing with hardware components
│   │
│   └───include - global header files for the kernel code
│   │
│   └───libk - Implementation of some useful c library functions for kernel use
│
└───images - screenshots of different parts of the OS
```
