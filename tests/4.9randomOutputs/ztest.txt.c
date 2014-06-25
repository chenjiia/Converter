#include <stdio.h>
void main(){
//BDD: longbman
int S = 0;
int O = 0;

int SMax = 16;
int OMax = 16;

int STemp = 0;
int OTemp = 0;
int OCounter = 0;

while(O != OMax){
	S = 0;
	while(S != SMax){
		//code start
		OTemp = 0;
		STemp = S;
		
		if(STemp == 4){
			OTemp = 4;
		}else{
			if(STemp == 2){
				OTemp = 2;
			}else{
				OTemp = 7;
			}
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

if(OCounter == 3){
printf("reached");
}
}