#!/bin/sh
if [ ! -d "bin" ]; then
  mkdir bin
fi
echo "compiling Week 11 exercises..."cd ../../
gcc part1.cpp -lglut -lGLU -lGL -o bin/Part1  && echo "--Part1"
gcc part2_1.cpp -lglut -lGLU -lGL -o bin/Part2_1  && echo "--Part2_1"
gcc part2_2.cpp -lglut -lGLU -lGL -o bin/Part2_2  && echo "--Part2_2"
gcc part3.cpp -lglut -lGLU -lGL -o bin/Part3  && echo "--Part3"
echo "...done."
