# Arduino-C++ compatibiliy

This library is made to create some compatibility between c++ and arduino, this way you can compile your arduino program by just including the library once compiled.

## Installation

For now I only distribute source code, here is an extract from the make file I used when developing:

```makefile
all: libarddebug.a

libarddebug.a: registers.o test_env.o test_api.o
	ar rcs build/libarddebug.a build/test_env.o build/test_api.o build/registers.o

registers.o:
	g++ -c registers.cpp -o build/registers.o -Wall

test_env.o: lib/test_env.cpp test_api.o
	g++ -c test_env.cpp -o build/test_env.o -Wall

test_api.o: lib/test_api.cpp
	g++ -c test_api.cpp -o build/test_api.o -Wall
```

## use

Once you compiled the code into a static library, you can simply import the header provided "libarddebug.hpp", if you compiled the library under a different name, you should rename the provided header. You can find the library documentation [here](https://awing-ding.github.io/arduino-cpp-compatibility/html/index.html) you should add ``using namespace arduinoTest`` at the top of your file.

## Development

This project is still under active development, but the key features as compatibility with basic arduino functions and the logging of variables are here. Here is the list of modification I plan to do:

- Rework the log() function to accept more than char * (will affect Serial print and println method)
- Implement more functions from [arduino](https://www.arduino.cc/reference/en/) as for now only a few parts (Time, Digital I/O) are fully supported

If you want to add your participation, want me to add some functionnality in priority, feel free to contact me/add pull request/add issues

## License

This project is under the BSD 2 clause license, see LICENSE for more details.
