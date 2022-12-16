output: mainFile.cpp function.h
	g++ -o output mainFile.cpp
clean:
	rm -rf *.o output