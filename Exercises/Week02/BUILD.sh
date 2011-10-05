#!/bin/sh
if [ ! -d "bin" ]; then
  mkdir bin
fi
echo "compiling Week 2 exercises..."
gcc Part1.cpp -lglut -lGLU -lGL -o bin/Part1 && echo "-- Part1"
gcc Part2.cpp -lglut -lGLU -lGL -o bin/Part2 && echo "-- Part2"
gcc Part2b.cpp -lglut -lGLU -lGL -o bin/Part2b && echo "-- Part2b"
gcc Part3.cpp -lglut -lGLU -lGL -o bin/Part3 && echo "-- Part3"
gcc Part4.cpp -lglut -lGLU -lGL -o bin/Part4 && echo "-- Part4"
echo "...done."
