all: workitems dividearrays fileutil

workitems: workitems.c
	$(CC) -g -O0 -o $@ $< -lpthread
dividearrays: dividearrays.cpp
	$(CXX) -g -O0 -o $@ $<
fileutil: fileutil.cpp
	$(CXX) -g -O0 -o $@ $<
run: fileutil
	./fileutil
	diff -u bible.txt copy.txt
