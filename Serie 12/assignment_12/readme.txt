Assignment 12 - Joana Portmann, Ann Kiener

1. We started by implementing the missing code in the bezier file. (Following the order how the exercise suggests)

First, we forgot to change the default parameters for the tangent calculation. 
While writing the code for the eval_piecewise_bezier_curve(float t) const {} we first handled the last segment wrongly (setting parameter t not to 1) 
and had a > instead of a >= which leads the bezier_pts vector to be filled by some strange default values (really big values). This made the control polygon to have an edge going to "infinity" at the end. 


2. Next we started filling in the missing code in the solar_viewer.cpp. 

The part we "wasted" the most time was understanding how to fill in the code from the previous exercises (incl. the shader code). We tried to do this manually; in the end we used 
a merging tool for ordner and file comparison between assignement 6 and assignement 12. 
