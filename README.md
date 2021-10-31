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

## Part C: Write a kernel module to return list of processes to user space via a character device & Write a user space program to retrieve the list of processes from the kernel module