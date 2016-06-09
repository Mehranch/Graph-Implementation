all: CreateGraphAndTest FindPaths TestRandomGraph

CreateGraphAndTest:
	g++ CreateGraphAndTest.cpp -o CreateGraphAndTest

FindPaths:
	g++ FindPaths.cpp -o FindPaths

TestRandomGraph:
	g++ TestRandomGraph.cpp -o TestRandomPaths

clean:
	rm CreateGraphAndTest FindPaths TestRandomPaths
