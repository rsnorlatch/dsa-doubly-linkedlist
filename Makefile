default: clean build run

run:
	@./build/main.exe

build:
	mkdir build
	mkdir plist
	clang++ --analyze main.cpp -o plist/main.plist
	clang++ main.cpp -o ./build/main.exe 

clean: 
	@rm -rf ./build ./plist
