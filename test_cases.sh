#!/bin/sh


./a5 -input scene06_bunny_1k.txt  -size 300 300 -output a_2.tga -shadows -bounces 4 -jitter -filter
./a5 -input scene10_sphere.txt  -size 300 300 -output a_4.tga -shadows -bounces 4 -jitter -filter
./a5 -input scene11_cube.txt  -size 300 300 -output a_6.tga -shadows -bounces 4 -jitter -filter
./a5 -input scene12_vase.txt  -size 300 300 -output a_8.tga -shadows -bounces 4 -jitter -filter
./a5soln -input scene06_bunny_1k.txt  -size 300 300 -output a_1.tga -shadows -bounces 4 -bounces 4 -jitter -filter
./a5soln -input scene10_sphere.txt  -size 300 300 -output a_3.tga -shadows -bounces 4 -jitter -filter
./a5soln -input scene11_cube.txt  -size 300 300 -output a_5.tga -shadows -bounces 4 -jitter -filter
./a5soln -input scene12_vase.txt  -size 300 300 -output a_7.tga -shadows -bounces 4 -jitter -filter
./a5 -input scene06_bunny_1k.txt  -size 300 300 -output a_10.tga -shadows -bounces 0 -jitter -filter
./a5soln -input scene06_bunny_1k.txt  -size 300 300 -output a_9.tga -shadows -bounces 0 -jitter -filter
./a5 -input scene12_vase_spotted.txt  -size 300 300 -output a_11.tga -shadows -bounces 4 -jitter -filter
./a5 -input scene12_vase_planet.txt  -size 300 300 -output a_12.tga -shadows -bounces 4 -jitter -filter
./a5 -input scene12_vase_cow.txt  -size 300 300 -output a_13.tga -shadows -bounces 4 -jitter -filter

