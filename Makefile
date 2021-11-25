app:
	make clearCache; make clean; make compile; make execute;

clean:
	cd src/build; make clean; cd ../../build; make clean;

compile:
	cd src/build; cmake ..; make; cd ../../build; cmake ..; make;

execute:
	cd build/; ./COVID_PREDICTIONS;

clearCache:
	cd src/build; rm CMakeCache.txt; cd ../../build; rm CMakeCache.txt;
