Assignment 4 - Joana Portmann, Ann Kiener

First of all, we both got the OpenGL assignment code to run.
For the 'special' task we changed an existing wave simulation to this 4d function plotter.

We started by changing the color of the simulation. Then we changed the code such that a static function got plotted. 
Next we added the time parameter t. Up to now the function to plot needed to be hardcoded. 
Next we changed colors again and then we expanded the code such that the user can now input the function that should be plotted.

To execute this program, one will have to click (in Visual Studio at least) on 
Erstellen > 4d-plotter-Eigenschaftseiten > Linker > System > choose Konsole (/SUBSYSTEM:CONSOLE)for Subsystem.
Only then the console will appear to ask you for a function input.
We put an example of that in our folder and a video of the output.

Since this is a project by itself we choose to submit the whole folder to be sure that it will work on someone else's computer if they were to test it.


Problems we encountered:

While developing the project it was hardest to manage some C specific details. 
Because we changed an existing project we bypassed the difficulties of setting up a completely new project.