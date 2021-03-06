#!/bin/bash
echo "Generate built-in functions."
./fxGen/fxGen $2 &> "fxGen.out"

echo "Append parsed statements."
./parser/parser $1 $2 >> "fxGen.out"

mv fxGen.out ${1}.bp
echo "Done."

