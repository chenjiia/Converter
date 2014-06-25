#ifndef FXGEN_H
#define FXGEN_H

void printISGT(int bitLength);
void printISLT(int bitLength);
void printISEQUAL(int bitLength);
void printISNOTEQUAL(int bitLength);
void printISGTEQ(int bitLength);
void printISLTEQ(int bitLength);

void printAnd(int bitLength);
void printOr(int bitLength);
void printXor(int bitLength);

void printPlus(int bitLength);
void printMinus(int bitLength);

void printLShift(int bitLength);
void printRShift(int bitLength);

//implement shift and addition/substraction

//currently fx below are internal use only
//both logic shift
void printRShiftOne(int bitLength);
void printLShiftOne(int bitLength);
void printINC(int bitLength);
void printDEC(int bitLength);

void printOneComplement(int bitLength);
#endif
