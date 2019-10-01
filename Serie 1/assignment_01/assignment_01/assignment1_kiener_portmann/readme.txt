Serie 1

Ray-plane intersection: 
The implementation was straight forward. We understood the equations from the lecture and started implement the intersect function for the plane as the one for the sphere.
Then we created a scene (sphere.scn) to see if our implementation was correct. It looked strange. We changed the sphere.scn to understand what went wrong. 
We achieved pictures as you can see in the first_ray_plane_intersection_wrong. 
Our mistake was that we accidentally transfered our calculations wrong in the code. We did the origin - center substraction kind of twice.
After changing the code we got pictures like ray-plane-intersection. To receive this image we did change the sphere.scn to understand, what our plane intersection method does. We removed the changes in sphere.scn after we believed that our function works correctly.


Ray-cylinder intersection: 
The main part & problem here was to really understand by "pen and paper" whats going on (what was the theory exercise). 
The implementation then was straight forward as we did the code as it is done by the sphere-ray intersection.
For the ideas and derivation of the theory exercise see theory exercise scan.  
