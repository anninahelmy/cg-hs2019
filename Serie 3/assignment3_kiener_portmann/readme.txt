Assignment 3

Group Members: Joana Portmann, Ann Kiener

For the vertex normals we basically followed the exercise sheet and the tipps on the slides. We also took advantage of the angleWeights() function in Mesh.cpp
since this computes the weights. Then we implemented the given formula - to each normal of the vertex on the triangle we added the triangle's normals weighted by the opening angle.
We did this for each vertex on the triangle (for-loop). Then we normalized all computed vertex normals.

For the phong shaded objects we just implemented the given formula with the vertex normals of vertices A, B and C (or p0, p1 and p2) and again, normalized the vectors
after interpolating them. Draw_mode_ decides whether the object needs to be flat shaded or phong shaded. 
