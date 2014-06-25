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
int temp2 = 0;

while(O != OMax){
	S = 0;
	while(S != SMax){
		//code start
		OTemp = 0;
		STemp = S;
		
		//STemp= (STemp&85) + ((STemp>>1)&85);
		temp1 = STemp & 85;
		temp2 = STemp >> 1;
		temp2 = temp2 & 85;
		STemp = temp1 + temp2;

		//STemp= (STemp&51) + ((STemp>>2)&51);
		temp1 = STemp & 51;
		temp2 = STemp >> 2;
		temp2 = temp2 & 51;
		STemp = temp1 + temp2;

		//STemp= (STemp + (STemp>>4))&15;
		temp1 = STemp;
		temp2 = STemp >> 4;
		temp2 = temp1 + temp2;
		OTemp = temp2 & 15;

		//code end
		if(O == OTemp){
			OCounter = OCounter + 1;
			goto break1;
		}
		S = S + 1;
	}
	break1 : O = O + 1;
}

if(OCounter == 9){
	printf("reached");
}
}