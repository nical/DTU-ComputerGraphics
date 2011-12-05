#!/bin/sh
if [ ! -d "bin" ]; then
  mkdir bin
fi
echo "compiling Week 3 exercises..."
gcc Part1.cpp -lglut -lGLU -lGL -o bin/Part1  && echo "--Part1"
gcc Part2.cpp -lglut -lGLU -lGL -o bin/Part2  && echo "--Part2"
gcc Part5.cpp -lglut -lGLU -lGL -o bin/Part5  && echo "--Part5"
echo "...done."
