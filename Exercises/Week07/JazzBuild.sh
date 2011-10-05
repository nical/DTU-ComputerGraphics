#!/bin/sh
if [ ! -d "bin" ]; then
  mkdir bin
fi
echo "Compiling Week 7 exercises..."
for i in `seq -w 5`
do
  if [ -f "Ex-07-0$i.cpp" ]
  then
    gcc "Ex-07-0$i.cpp" -lglut -lGLU -lGL -o "bin/Ex-07-0$i"  && echo "\t --Excercise $i"
  else
    echo "\t --Excercise $i still not done. Keep it up!"
  fi
done

echo "...done."
