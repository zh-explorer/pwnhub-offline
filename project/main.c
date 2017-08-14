#include <stdio.h>
#include <stdlib.h>

int ReadDecode(char *Buf,int MaxLen, int DelimChar) {
	int len;
	int TotalLen = 0;
	int i;
	char ch;
	int bit_tmp;
	int state = 0;
	int Delim = DelimChar;
	if (!Buf) {
		return(0);
	}
	while (1) {
		len = read(&ch, 1);
		if(len == -1){
			exit(1);
		}
		if(len == 0){
			wait();
			continue;
		}

		if(state == 0) {
			if(ch == Delim){
				Buf[TotalLen] = '\0';
				return (TotalLen);
			}
			if(ch>='A' && ch<='Z') {
				ch = ch - 'A';	
			}else if(ch>='a' && ch<='z') {
				ch = ch - 'a' + 26;
			}else if(ch>='0' && ch<='9'){
				ch = ch - '0' + 52;
			}else if(ch == '+'){
				ch = 62;
			}else if(ch == '/'){
				ch = 63;
			}else {
				exit(1);
			}

			bit_tmp = ch;
			bit_tmp = bit_tmp << 3;
			state = 1;
		}else if(state == 1){
			if(ch>='A' && ch<='Z') {
				ch = ch - 'A';	
			}else if(ch>='a' && ch<='z') {
				ch = ch - 'a' + 26;
			}else if(ch>='0' && ch<='9'){
				ch = ch - '0' + 52;
			}else if(ch == '+'){
				ch = 62;
			}else if(ch == '/'){
				ch = 63;
			}else {
				exit(1);
			}
			bit_tmp |= ch>>3;
			Buf[TotalLen] = (char) bit_tmp;
			bit_tmp = ch&0x7;
			TotalLen += 1;
			state = 2;
		}else if(state == 2){
			if(ch == '='){
				Buf[TotalLen] = '\0';
				return (TotalLen);
			}
			if(ch>='A' && ch<='Z') {
				ch = ch - 'A';	
			}else if(ch>='a' && ch<='z') {
				ch = ch - 'a' + 26;
			}else if(ch>='0' && ch<='9'){
				ch = ch - '0' + 52;
			}else if(ch == '+'){
				ch = 62;
			}else if(ch == '/'){
				ch = 63;
			}else {
				exit(0);
			}
			if(TotalLen >= MaxLen-1){
				exit(1);
			}
			bit_tmp = bit_tmp<<6 | ch;
			Buf[TotalLen] = (char) bit_tmp;
			TotalLen += 1;
			if(TotalLen >= MaxLen-1) {
				Buf[MaxLen-1] = '\0';
				return (MaxLen-1);
			}
			state=0;
		}
	}
}

void decode(){
	char buf[0x20];
	ReadDecode(buf, 0x80, '\n');
	puts(buf);
	fflush(stdout);
}

int main(){
	int buf[0x20];
	decode();
	return 0;
}
