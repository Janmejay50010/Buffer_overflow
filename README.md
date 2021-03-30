# Buffer_overflow

* Separate folders are created for each exploit.
* Each folder contains a C code `create_badfile.c` which creates `badfile`. That is being fed to the vulnerable file.

### Commands that are used 
	`sudo sysctl -w kernel.randomize_va_space=0`
	`gcc -g stack.c -o stack -z execstack -fno-stack-protector`
	`sudo chown root stack`
	`sudo chmod 4755 stack`