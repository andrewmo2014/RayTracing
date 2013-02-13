README.txt
==========================================================================================
Author:		Andrew Moran	|
Date:		12/05/2012	|
6.837 Computer Graphics		|
Assignment 5			|
=================================
__________________________________________________________________________________________
Compiling Instructions
==========================================================================================
	When I completed the assignment, I managed to run Linux through my Macbook Pro laptop with a Virtual Machine called VirtualBox.  I also tested on the campus Athena computer to make sure that it worked correctly.  Here are instructions
	1.	Unzip submission on Stellar and extract all files to designated directory
	2.	In terminal, cd to directory containing "assn4" folder
	3.	command make
	4.	if images not already in folder:
		command sh test_cases.sh
		This should reproduce the images generated from this assignment ranging from names a_1-13
		a_1-a_8 : Comparing my images to solution
		a_9-a_10 : Comparing bunny zero bounce to solution
		a_11-a_13 : Showing new spotted noise on vase
	5.	"assn5" folder contains all necessary files including updated 
		files, classes, subclasses, etc.
	6.	Note, in this assignment, I made it so you have to call -jitter -filter together or none at all
		(I did not implement them separately)

__________________________________________________________________________________________
Collaboration
==========================================================================================
	I had no further assitance other than the help I received from Professor/TAs at office hours.

__________________________________________________________________________________________
References
==========================================================================================
	⁃	6.837 Lecture Notes (Very Helpful)
        -	http://www.cplusplus.com/reference/
	- 	http://www.d.umn.edu/~ddunham/cs5721f07/schedule/resources/lab_opengl07.html

__________________________________________________________________________________________
Problems
==========================================================================================
	Currently, my code is functioning properly.  It took some time debugging, but should be a good solution.  My main problem was normalizing the normals.  Also, I think I accounted for an extra bounc that was hard to figure out.  Luckily the updated executable allowed me to separate between refraction and reflection.  Now, All my solution images have a correct image except for the bunny in scene 6.  I think my shadow/reflection may be off by a bit (due to not-normalizing properly?) and is a very minor discrepancy.

__________________________________________________________________________________________
Extra Credit
==========================================================================================
	Here are some added features to the assignment:
	•	***In Addition to Extra Credit from before*** (refer to previous assignment 4 for pics/documentation) 
	•	New Noise (Spotted)
		Attempted to make wood texture but created this nice looking pstted texture.  Applied it to different colors.
		This required adding a new parameter to noise and type variable (is marble or is spotted)
	•	Attempted to put in Stadford Dragon to the scene
		Did not work.  tried to copy obj file from "http://www.d.umn.edu/~ddunham/cs5721f07/schedule/resources/models/dragon.obj", but indices too large.  Did not follow through trying to figure it out.  However, I will still try to do it.
	

__________________________________________________________________________________________
Comments
==========================================================================================
	I felt very guided on this assignment by the lecture notes.  By following the slides and implementing the correst formulas and constraints, I saw progress fast.  The only thing that threw me off was normalizing normals.  I am still confused when I should/should not normalize vectors (for both normals and directions).  This resulted in very small discepancies in lighting/shadows on my pictures.  After realizing that I didn't normalize (or normalized when I shouldn't have), I was able to fix my mistakes.  Also, I managed to find out that I was accounting for an extra bounce when I shouldn't off. Ironiccaly my refraction algorithm worked first and I had to debug reflection/shadows.  Luckily the new executable allowed me to see between the two while debugging.  They may be some discrepany due to jitter/blurring/ray slightly off, however, the overall product looks correct.  If I didn't spend so much time debugging, I would have nejoyed working on Extra Credit.  To be honest, I thought thislast assignment would be very intense, however, it was just an extension from our previous assignemnt 4.  I had a lot of fun in the course and learned a lot.  I am glad I took it and appreciate all the help/guidance 6.837 had provided me.  Thanks

 
