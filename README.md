# Kernel Modules to list all processes and their states

## Objective
To develop and use kernel modules and character devices. And learn how the Linux OS maintains list of processes and their execution states.

## Part A: Learn how to write and execute a Linux kernel module.
### Usage and How To Run?
The files hello_world.c has initialization and cleanup functions that are invoked upon loading and unloading the kernel module.  
The second file hello_world_n.c is similar, except that it takes command-line arguments with insmod command to print a custom message.

1. Compile the kernel module by running `make` in `Part A` directory.
2. Run below command to insert/load .ko files to kernel.
    ```sh
	sudo insmod hello_world.ko
    sudo insmod hello_world_n.ko whom=class howmany=10
	```  
	If the module was successfully inserted, you will see `Banu: Hello World!` message in kernel log.

3. Use commands `dmesg` or `cat /var/log/kern.log` to see the kernel log messages.
4.  Run below commands to remove/unload moduels from kernel.
    ```sh
	sudo rmmod hello_world
    sudo rmmod hello_world_n
	```
	Upon removing the kernel module, check if kernel log prints the message `Banu: %d: Goodbye, cruel %s!!`
	
## Part B: Learn how to write a miscellaneous character device driver
### Usage and How To Run?
1. Run `make` in `Part B` directory.
2. Run below command to insert .ko file to kernel.
    ```sh
	sudo insmod misc_dd.ko
	```
3. Run compile command on file user_space.c
    ```sh
	gcc -o user_space user_space.c
	```
4. do below,
    ```sh
	sudo ./user_space
	```
5. You should see `Hello World!` printed.

## Part C: Write a kernel module to return list of processes to user space via a character device & Write a user space program to retrieve the list of processes from the kernel module
### Usage and How To Run?

Implemented a kernel module that creates a /dev/process_list character device. The character device supports the read() operation. When the read() system call is invoked on the character device from a user space process, kernel module will return the following information about all currently running processes:

a. process ID  
b. parent process ID  
c. the CPU on which the process is running  
d. its current state.  

> Beware that bugs in kernel code may either crash your kernel immediately or may have no immediate visible effect, but may have a delayed effect. Therefore, you cannot assume that the thing you did most recently is necessarily the cause of a crash.

Also, Implemented a user-space C program that opens character device and outputs the list of processes retrieved from the character device.

1. Run `make` in `Part C` directory.
2. Run below command to insert .ko file to kernel.
    ```sh
	sudo insmod process_list.ko
	```
3. Run compile command on file user.c
    ```sh
	gcc -o user user.c
	```
4. do below,
    ```sh
	sudo ./user
	```
5. You should see list of all processes and its state.