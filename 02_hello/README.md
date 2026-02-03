# Linux Kernel Module Development

This repository contains Linux kernel modules developed on Debian
(Raspberry Pi) for learning and BSP-level driver development.

## Modules
- 02_hello: Better hello-world kernel module

## Build
```bash
make
sudo insmod hello.ko
sudo rmmod hello
sudo dmesg
sudo dmesg | tail
sudo dmesg -w




pi@pi:~/Programming/kernel_modules/02_hello $ sudo modprobe hello
modprobe: FATAL: Module hello not found in directory /lib/modules/6.12.62+rpt-rpi-v8
pi@pi:~/Programming/kernel_modules/02_hello $ sudo modprobe industialio
modprobe: FATAL: Module industialio not found in directory /lib/modules/6.12.62+rpt-rpi-v8
