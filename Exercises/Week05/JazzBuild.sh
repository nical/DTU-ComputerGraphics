#!/bin/sh
if [ ! -d "bin" ]; then
  mkdir bin
fi
echo "Compiling Week 5 exercises..."
for i in `seq -w 6`
do
  if [ -f "Ex-05-0$i.cpp" ]
  then
    gcc "Ex-05-0$i.cpp" -lglut -lGLU -lGL -o "bin/Ex-05-0$i"  && echo "\t --Excercise $i"
  else
    echo "\t --Excercise $i still not done. Keep it up!"
  fi
done

echo "...done."
