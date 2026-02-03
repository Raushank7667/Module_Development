# Linux Kernel Module Development

This repository contains Linux kernel modules developed on Debian
(Raspberry Pi) for learning and BSP-level driver development.

## Modules
- 01_hello: Basic hello-world kernel module

## Build
```bash
make
sudo insmod hello.ko
sudo rmmod hello

