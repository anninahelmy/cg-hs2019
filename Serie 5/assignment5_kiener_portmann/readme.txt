Assignment 5 - Joana Portmann, Ann Kiener

How we solved each exercise:

1. Placing the objects in the scene (update_body_positions)
We set all positions relative to the sun, except the moon's. For the moon we have to be careful to place it relative to the earth (and not just relative to the sun as all other planets). 
(The order of the matrices isn't important here. First rotate and then scale or first scale and then rotate will give the same results). 

2. Rendering objects (planets, moon, space ship)
We define the matrices for the model, view, modelview and modelview-projection transformation. 
Important was to think about the order in which we multiply the matrices (first multiplication comes the rightest). 
To define the m_matrix (for model transformation) it doesn't matter if we first scale the planets up or rotate around their "own" angle. But it is important to do the "own" rotation before translate the planets to its orbit.
To define the other matrices we followed the sun's example. 
Since the code for the model matrix does not change from planet to planet for the rendering of the textured objects, 
we decided to create a seperate function (see Solar_viewer::draw_planet) to exclude redundant code.

3. Implement the paint-method
This method sets the camera to the right position. We started with the " not in ship" case. For the "in ship" case we had to add to the rotation angle the ships angle. 
To have a better view we rotate a little bit around the x-axis and doubled the ships radius for the eye positioning. 

4. Add the functions for key 8 and 9
We decided to always change the dist factor by adding +/- 0.5. Then we set the condition to not come to close or go away to far by a simple 
if-statement (dist_factor_ >= 3.0) to improve performance by not having to calculate (in another step) a minimum or maximum of two numbers. 


Problems we encountered:

 - We first didn't clearly seperate setting the position in update_body_positions and then calculate the matrices for the transformations. We started by directly do everything where we defined the m_matrix.
 - Another problem was to imagine all the transformations. Especially for setting the camera (paint-method) it was hard to clearly think everything through.
 
