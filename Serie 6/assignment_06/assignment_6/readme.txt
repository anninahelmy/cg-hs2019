
1. We started by implementing the billboard. In the distance calculation we first just just col and row instead of (width/2 - col) and (height/2 - row)
which resulted in a quarter of a circle in the upper left corner. 
(Another mistake we made, was not rendering the billboard we created in the texture.cpp)
In this first iteration of just trying to get some circle on the image we draw the circle completely yellow without thinking about apacity.
Once we had a nice circle we added apacity. We defined a function depending on the distance to calculate the apacity factor (alpha). Starting by just a linear
gradient we tried different types of functions such as quadratic, logarithmic and exponential ones. It was quite hard to get a satisfiying result. 

2. Next we implemented the shader. There it was important to think about the different types of matrices and vectors we had given and had to calculate (vec3/vec4 and mat3/mat4).
We startet with the phong.frag and next set the outgoing vectors in phong.vert. Everything looked wrong. We rechecked every vector we set and the way how we calculate the color but everything looked correct. 
In the end we realised that we hadn't yet calculated the normal matrix in the solar_view.cpp. After calculatin this matrix the shader worked finally in the right way. 

In this exercise we had to think about how shaders work. Which part has to be implemented in which file. 