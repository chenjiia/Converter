#!/bin/bash
echo "Generate builtin functions."
./fxGen/fxGen.exe $2 &> "fxGen.out"

echo "Append parsed statements."
./parser/parser.exe $1 $2 >> "fxGen.out"

mv fxGen.out ${1}.bp
echo "Done."

