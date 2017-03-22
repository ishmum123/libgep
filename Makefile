all: Bismillah.cpp
	g++ -o FunctionGenerator -c -Wall Bismillah.cpp 

test: 
	g++ -o TestFunctions Tests/HelpMeYaAllah.cpp -lcppunit

cleantest:
	rm TestFunctions

clean: 	
	rm FunctionGenerator
