
This is a project with the aim of making an N body simulator and experimenting with different forms of calculation and optimisation.

For performance, computation is planned to take place in cpp and saved in a txt file for a python program to display.

First goal: save a multitude of gravitational objects

Log:
Created vector objects for both 2D and 3D vectors and populated with operator functions

Notes to self:
Compile command: g++ -o ./main ./main.cpp
Compile command: g++ -o ./test ./test.cpp

Profiler compile command $ g++ -o ./main ./main.cpp -lprofiler -ltcmalloc -ggdb3 -Wall
Profiler run command $ env CPUPROFILE=/tmp/prof.out ./main                
Profiler show command $ ~/go/bin/pprof --web ./main /tmp/prof.out
