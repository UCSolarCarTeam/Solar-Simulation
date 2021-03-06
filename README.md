# Solar-Simulator

This program takes in a 3D-Model of a car from Solidworks, the program then simulates solar intensity on the model from different angles to determine the efficiency of the solar cell arrangement.

## Meshlab Instructions 

Meshlab is used to convert STL files to OBJ files.

Install meshlab on ubuntu using the following command:
	`sudo apt-get install meshlab`

Type this in command line to convert from .stl to .obj:
	`meshlabserver -i [inputlocation] -o [outputlocation]`

Example:
	`meshlabserver -i ./Materials/box.STL -o ./test.obj`

## Note 

Make sure that glm and glew libraries have been installed in /usr/local/include/


## Set up tests

Testing the CCS Test Tool is done with googletest and googlemock, the gmock and gtest header files need to be in /usr/local/include.
You must compile the library that has the definitions yourself. 
Meaning you need a `libgmock.a` archive file in the test directory in order to compile the tests. 

To create a `libgmock.a` file follow these instructions in an arbitrary dir.

1. Get the googletest and googlemock source code:
	`git clone https://github.com/google/googletest.git`

2. Go into the cloned directory 
	`cd googletest/`

3. Compile googletest:	
	`g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googletest/src/gtest-all.cc`

4. Compile googlemock:
	`g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googlemock/src/gmock-all.cc`

5. Collect both the resulting .o files into an archive file:
	`ar -rv libgmock.a gtest-all.o gmock-all.o`

Congratulations! You now have a `libgmock.a` archive file, now include it in the `Solar-Simulator/test/` directory and you should be good to go, run `make` in the test directory to check if you can compile the tests.
