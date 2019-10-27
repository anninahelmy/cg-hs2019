Assignment 5 - Joana Portmann, Ann Kiener

How we solved each exercise:

1. placing the objects in the scene & 2. rendering textured objects:
We did the placing and rendering of the objects at the same time as the exercise sheet suggests. The first planet was the earth. 
We positioned the earth on the circular orbit around the sun and let it rotate around itself. After that we renderd it with it's texture
and followed the example of the sun's rendering with the exception that for the other planets we had to add the translation to the model matrix. 
After realizing that the code works, we implemented all the other planets (also the stars), with the only difference that the moon was placed
around the earth's position.
Since the code for the model matrix does not change from planet to planet for the rendering of the textured objects, 
we decided to create a seperate function (see Solar_viewer::draw_planet) to exclude redundant code. 