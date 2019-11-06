Assignment 6 - Joana Portmann, Ann Kiener

1. We started by implementing the billboard. In the distance calculation we first just used col and row instead of (width/2 - col) and (height/2 - row)
which resulted in a quarter of a circle in the upper left corner. The first mistake here, was that we initially did not render the billboard we created in the texture.cpp.

In this first iteration of just trying to get some circle on the image we drew the circle completely yellow without thinking about opacity.
Once we had a nice circle we added the opacity. We defined a function depending on the distance to calculate the opacity factor (alpha). Starting by just a linear
gradient we tried different types of functions such as quadratic, logarithmic and exponential ones. It was quite hard to get a satisfiying result. 

2. Next we implemented the shader. There it was important to think about the different types of matrices and vectors we had given and had to calculate (vec3/vec4 and mat3/mat4).
We startet with the phong.frag and next set the outgoing vectors in phong.vert. This did not look right. We rechecked every vector we set and the way how we calculated the color 
but we did not find any mistakes. 
In the end we realised that we hadn't calculated the normal matrix in the solar_view.cpp yet. 
After calculating this matrix the shader finally worked in the right way. 

3. Then we went on to shading the earth. Since we already implemented the Phong Lightning Model for the second part of this excerice, this was not much of a challenge.
We computed the two different colors (day and night) and used the tipps in the 'todo'-comments on how to correctly blend them at the border. 


In this exercise we had to think about how shaders work and which part has to be implemented in which file. 