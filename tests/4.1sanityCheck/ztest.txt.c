#include <stdio.h>

void main(){
int S = 0;
int O = 0;

int SMax = 128;
int OMax = 128;

int STemp = 0;
int OTemp = 0;
int OCounter = 0;

int base = 4;

while(O != OMax){
	S = 0;
	while(S != SMax){
		//code start
		OTemp = 0;
		STemp = S;
		if(STemp < 16){
			OTemp = base+ STemp;
		}
		else{
			OTemp = base;
		}
		//code end
		if(O == OTemp){
			OCounter = OCounter + 1;
			goto break1;
		}
		S = S + 1;
	}
	break1 : O = O + 1;
}

if(OCounter == 16){
	printf("reached");
}
}