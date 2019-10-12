Assignment 3

Group Members: Joana Portmann, Ann Kiener

1. We started by implementing a draft of the vertex normal calculation function by just taking any normal of an adjacent triangle. 
Next, to get some feedback we implemented a first draft of the triangle intersection function by always just taking the triangle's normal. 
=> The image was wrong (which means the code wasn't correct) and imageprocessing was extremly slow. We made the image smaller to make the rendering faster (debug_office).
The image lokked not completely wrong. Something was wrong with the light.

2. Before finding the mistake in the existing code we quickly implemented the box intersection function to speed up the rendering process. 

Having now implemented the box intersection we could correct our mistakes in the functions for the normals ans intersection. In the determinant calculation we had a copy-paste-error.
This (corrected) draft gave us already quite nice images (toon_faces0) so we knew that our ideas and understanding of the situation were correct. 

3. Next we the fine tuning:

For the vertex normals we basically followed the exercise sheet and the tipps on the slides. We also took advantage of the angleWeights() function in Mesh.cpp
since this computes the weights. Then we implemented the given formula - to each normal of the vertex on the triangle we added the triangle's normals weighted by the opening angle.
We did this for each vertex on the triangle (for-loop). Then we normalized all computed vertex normals.

For the phong shaded objects we just implemented the given formula with the vertex normals of vertices A, B and C (or p0, p1 and p2) and again, normalized the vectors
after interpolating them. Draw_mode_ decides whether the object needs to be flat shaded or phong shaded. 

4. After havin done this everything looked OK but the toon_faces. We had some weird black strips. Debugging this was quite hard. 
We changed the scene.sce file many times to better understand the error (-> toon_faces_debug).
The stripes had exactly the color of the background. 
After playing around with the scene.sce we got the impression that something's wrong with the shadow (see toon_faces_debug_[...]). 
So we changed the scene.cpp file in a way that we trace the shadow to see where it's coming from (which color it has)(toon_faces_debug_traced-shadows).
Having this idea we checked the code from exercise 3 (lightning) line after line. We had one condition implemented wrong. 
