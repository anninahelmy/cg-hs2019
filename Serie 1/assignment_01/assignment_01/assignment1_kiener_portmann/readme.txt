Assignment 1

We solved the exercise pretty much in the 'order' that was suggested.

We started with the Ray-plane intersection:

The implementation was straight forward. We understood the equations from the lecture and started implementing the intersect function for the plane as the one for the sphere.
Then we created a scene (sphere.scn) to see if our implementation was correct. It looked strange. We changed the sphere.scn to understand what went wrong. 
The pictures that we got are the screenshots 'first_ray_plane_intersection_wrong'. 
Our mistake was that we accidentally transferred our calculations wrong into the code. We kind of did the 'origin - center'-substraction twice.
After changing the code we got pictures like the screenshot 'ray-plane-intersection'.
To receive this image we did change the sphere.scn to understand, what our plane intersection method does. 
We removed the changes in sphere.scn after we believed that our function works correctly.


After that we would solve the theory exercise for the Ray-cylinder intersection and implemented it:

The main part and problem here was to really understand by "pen and paper" what was going on. 
We struggled really imagining this intersection and had many attempts in drawing the figure and the vectors and how they connect.
The programming itself turned out to be 'simple' compared to the derivations. For the implementation we were inspired by the 'Ray-sphere intersection'-Code.
For the ideas and derivation of the theory exercise refer to the theory exercise scan.  

The final part was the cylinder normal implementation:

Again, problems only arose when deciphering everything on paper. We were also unsure if we had the right solution or if maybe somewhere we put 
a wrong 'minus' where none should be. When implementing our solution, the picture would be correct, but still, we were worried that it only
'looked' correct but our calculations were not quite correct. However, this again, took a lot of thinking, imagining and drawing cylinders on papers.

