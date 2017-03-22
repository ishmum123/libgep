test: 
	g++ -o TestFunctions Tests/TestRunner.cpp -lcppunit

cleantest:
	rm TestFunctions

clean: 	
	rm FunctionGenerator
