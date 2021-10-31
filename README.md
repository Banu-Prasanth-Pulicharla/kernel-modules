# Kernel Modules to list all processes and their states

## Objective
To develop and use kernel modules and character devices. And learn how the Linux OS maintains list of processes and their execution states.

## Part A: Learn how to write and execute a Linux kernel module.
### How To Run?
1. Run `make` in "Part A" directory.
2. Run below command to insert .ko files to kernel.
    ```sh  
	sudo insmod hello_world.ko
    sudo insmod hello_world_n.ko whom=class howmany=10
	```  
3. Check using `dmesg` if the prints are happening properly.
4.  Run below commands to remove moduels from kernel.
    ```sh
	sudo rmmod hello_world
    sudo rmmod hello_world_n
	```
### Usage
Kernel modules allow the code to be dynamically added to the kernel, dynamically.

## Part B: Learn how to write a miscellaneous character device driver

## Part C: Write a kernel module to return list of processes to user space via a character device & Write a user space program to retrieve the list of processes from the kernel module