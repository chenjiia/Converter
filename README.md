<h1>Converter for Getafix</h1>
The Converter is a tool that translates C-style code into boolean programs. Specifically the style required by Getafix.

Link to Getafix:

http://www.cs.uiuc.edu/~madhu/getafix/ 

<h2>Dependency</h2>
flex
bison
pkg-config
glib-2.0

<h2>How to build</h2>
make

in the root directory.

<h2>How to run</h2>
./run.sh input_file_name bit_length

Like

./run.sh ./tests/4.1sanityCheck/ztest.txt 7

<h2>Where are the examples</h2>
./tests

Jia Chen, 2014