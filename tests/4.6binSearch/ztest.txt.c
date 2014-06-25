#include <stdio.h>
void main(){
//8 bit ver
int S = 0;
int O = 0;

int SMax = 256;
int OMax = 256;

int STemp = 0;
int OTemp = 0;
int OCounter = 0;
int temp1 = 0;

while(O != OMax){
	S = 0;
	while(S != SMax){
		//code start
		OTemp = 0;
		STemp = S;
		
		temp1 = OTemp + 128;
		if(temp1 <= STemp){
			OTemp = OTemp + 128;
		}
		temp1 = OTemp + 64;
		if(temp1 <= STemp){
			OTemp = OTemp + 64;
		}
		temp1 = OTemp + 32;
		if(temp1 <= STemp){
			OTemp = OTemp + 32;
		}
		temp1 = OTemp + 16;
		if(temp1 <= STemp){
			OTemp = OTemp + 16;
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
printf("reached\n");
}
}