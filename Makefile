all:
	(cd fxGen;make)
	(cd parser;make)
	
clean:
	(cd fxGen;make clean)
	(cd parser;make clean)
	