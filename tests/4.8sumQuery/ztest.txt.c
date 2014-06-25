#include <stdio.h>
//BDD: longbman
void main(){
int S1 = 0;
int S2 = 0;
int S3 = 0;
int O = 0;

int SMax = 10;
int OMax = 50;

int OTemp = 0;
int OCounter = 0;

while(O != OMax){
	S1 = 0;
	while(S1 != SMax){
		S2 = 0;
		while(S2 != SMax){
			S3 = 0;
			while(S3 != SMax){
				OTemp = S1 + S2;
				OTemp = OTemp + S3;
				//code end
				if(O == OTemp){
					OCounter = OCounter + 1;
					goto break1;
				}
				S3 = S3 + 1;
			}
			S2 = S2 + 1;
		}
		S1 = S1 + 1;
	}
	break1 : O = O + 1;
}

if(OCounter == 28){
	printf("reached\n");
}
}