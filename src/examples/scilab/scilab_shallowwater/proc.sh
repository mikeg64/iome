#!/bin/bash

for((i=0; i<10; i++ ))
do
	convert step${i}.tiff -resize 25% step0${i}.gif
done

for((i=10; i<47; i++ ))
do
	convert step${i}.tiff -resize 25% step${i}.gif
done

convert -delay 20 -loop 0 step*.gif shallowwater.gif





 
