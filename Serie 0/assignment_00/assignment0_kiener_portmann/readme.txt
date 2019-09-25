While changing the color in the solid_color.sce was not really difficult, 
compiling the provided raytracer framework was much more of a challenge than anticipated.
The main problems consisted in 'finding the right directory'. 
While following the provided README we always questioned what exactly we should put as the directory 
(e.g. when generating the files with the CMake-GUI, where to put the 'build'-folder, etc.). 

After that we struggled with actually 'running' the raytracer in Visual Studio so that it generates an .exe-file,
which was crucial to have for the program to actually work.
We managed to generate the program and got a 'Debug'-folder in our 'build'-folder where the raytracer.exe application was, 
typed the command from the provided README into Powershell (in the right directory, of course) and got a '.tga'-output-image!
Working with powershell was fine - the only problem was finding the right path where the '.sce'-files were.

We repeated this process with the changed solid_color.sce file. 

In the .zip-folder we included the .tga-file and also a screenshot of the actual output (in IrfanView).