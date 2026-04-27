# Real-time Scheduler From Scratch

This is my attempt at making a bare-bones real-time task scheduler from scratch.

I tried (and somewhat succeeded) at designing the scheduler to be easily portable
to numerous different architectures.

Currently, I have only written a port for the ARM Cortex-M4 core.

## Project Structure

This project is split into a couple different directories.

The home directory (this directory that the readme is in) has some demo source files
that demo the scheduler, a bug list, an interrupts source file for implementing
interrupts, and a linker script for any STM32F446xx microcontroller.

The `microkernel/` directory has all the source files for the real-time scheduler,
including the hardware port to ARM Cortex-M4.

The `hal/` directory has all the source files for a hardware abstraction layer
for an STM32F446RE microcontroller. This HAL is also written by me, from scratch.
The scheduler does not have any dependencies on the HAL, but the HAL is provided
here for use with the demo projects.

## Building Instructions

If you wish to compile this scheduler, you need:

1. GNU Make
2. The `arm-none-eabi` toolchain

Then, simply run `make` in the home directory for this project. The resulting
object files and binary executables will be placed in `build/`
