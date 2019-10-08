Assignment 2

Ambient contribution:
for the ambient contribution we followed exactly the description from the lecture: We multiplied the ambient-material factor with the ambient light.
This was quite easy to achieve.

Diffuse contribution: 
We first set the diffuse color part to zero and then add with a for loop for every lightsource (stored in the lights array) the diffuse component.

Specular contribution:
For the specular contribution we did the same as for the ambient and diffuse contribution and followed the information on the slides.
The biggest challenge here was to describe the r-vector, but we figured it out eventually since this is also provided on the slides. 
With googling we also figured out how to implement the exponent 'shininess' with the pow-function. 


Shadows:
For the shadows we had to think about how to figure out if a light source is blocked by an object, so we would know when to discard the 
diffuse and specular contribution so that there's only the ambient contribution. We worked with the tipps on the slides and moved the intersection point away, so 
we added a little bit of the direction-vector. Then we checked if an intersection occurred (if an object is blocking the light source) and if we should add up the
diffuse and specular contribution. However, the number we added is just a wild guess and it seems as if it has more of an impact than anticipated.
The picture that resulted does not quite seem correct, but it is hard to tell, since we do have some shadows but they're not exactly like in the picture
of the expected results. The reason therefore was that we had a multiplication with the materialfactor at the wrong place in the loop so we multiplied to much. 
That resulted in the second light being cancelled out. So there was only one light to produce the shadow, what is exactly what we have seen in the wrong picture. 


Reflections: 
We recursively calculated the additional reflection part of the actual color. 
At first glace we forgot to shift the reflection_ray origin and we had the ray direction inverted. This resulted in the screenshot reflect_floatingPointUngenauigkeit_reflectionrayInvertiert. We first just corrected the floating point thing which didn't really gave us the expected result:
See screenshot reflection2_floating_correct_ray_inverse. There were still no mirror effects to detect. After studying why this could be we found the direction error of the ray. Correcting this led us to the expected results. 
At last to really understand our code we had some fun changing the scene.sce file by making the spheres to perfect mirrors. Because in the original code after a finite number of reflections the loop stops and the color is set to 0 0 0 (=black)
we should expect the spheres to be black and this is exactly what happened (see screenshot perfect_mirror_spheres)