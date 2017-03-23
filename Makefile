all: src/main.cpp src/MoveListGenerator.cpp
	g++ -o RunFile src/main.cpp src/MoveListGenerator.cpp
test: 
	g++ -o TestFunctions Tests/TestRunner.cpp -lcppunit

cleantest:
	rm TestFunctions

clean: 	
	rm RunFile
