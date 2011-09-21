#!/bin/sh
echo "compiling Week 3 exercises..."
gcc Part1.cpp -lglut -lGLU -lGL -o bin/Part1  && echo "--Part1"
gcc 02561-03-03-2011.cpp -lglut -lGLU -lGL -o bin/Part3  && echo "--Part3"
echo "...done."
