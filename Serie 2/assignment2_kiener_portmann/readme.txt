Assignment 2

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
of the expected results.

