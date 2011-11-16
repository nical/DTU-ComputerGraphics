#!/bin/sh
if [ ! -d "bin" ]; then
  mkdir bin
fi
echo "compiling Week 11 exercises..."
gcc 02561-11-00-2011.cpp -lglut -lGLU -lGL -o bin/Part1  && echo "--Part1"
echo "...done."
