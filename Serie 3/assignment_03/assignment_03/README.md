Ray Tracer
==========

We are using a couple of modern C++ features, so please ensure that you use a recent C++ compiler (GCC 8, Clang 7, Visual Studio 2017 are tested).
You will need [CMake](https://www.cmake.org) for setting up the build environment.


Building with QtCreator or CLion
--------------------------------

It should be sufficient to open the CMakeLists.txt as a project, then using the
build button.

Building under Linux/macOS (Commandline)
----------------------------------------

Inside the exercise's top-level directory, execute the following commands:

    mkdir build
    cd build
    cmake ..
    make

The last command -- i.e. `make` -- compiles the application. Rerun it whenever you have added/changed code in order to recompile.
You can use `make -j8` to compile with 8 cores (choose an appropriate number).

To build a pretty documentation use:

    make doc

and open the `index.html` in the html folder with your favourite browser. To build the documentation, you must install Doxygen.


Building with XCode (macOS)
---------------------------

If you wish, you can use the CMake build system to generate an XCode project.
Inside the exercise's top-level directory, execute the following commands:

    mkdir xcode
    cd xcode
    cmake -G Xcode ..
    open RayTracing.xcodeproj


Building under Microsoft Windows (Visual Studio)
------------------------------------------------

* Start the CMake-GUI.
* Open the RayTracing top-level directory as source directory.
* Create and select a subfolder "build" of the raytracing folder as *build directory*
* Click on configure and select Visual Studio as generator.
* Click generate to create the Visual Studio project files.
* Open the Visual Studio solution file that is in the build directory you chose in CMake.


Running the Ray Tracer (commandline)
-------------------------------------

The program expects two command line arguments: an input scene (`*.sce`) and an output image (`*.tga`). To render the scene with the three spheres, while inside the `build` directory, type in your shell:

    ./raytrace ../scenes/spheres/spheres.sce output.tga

If you have finished all exercise tasks, use

    ./raytrace 0

to render all scenes at once.

On Windows, this would be

    .\raytrace.exe ../scenes/spheres/spheres.sce output.tga


Make sure (e.g. with `ls`) that you are specifing the correct path to the input file.
The output file will be saved in the current working directory of the program, i.e. the directory you started it from.

If `raytrace 0` does not find the input files, you may have to adjust them in `raytrace.cpp`.


Running the Ray Tracer (IDEs)
-------------------------------------

To set the command line parameters in IDEs MSVC or Xcode, please refer to the documentation of these programs (or use the command line...).


Assignment 3: Triangle Meshes
-----------------------------
In this assignment you will need to edit the Mesh.cpp file.

- Compute vertex normals weighted by opening angles in Mesh::compute_normals().
- Compute the ray-triangle intersection with barycentric coordinates using Cramer's rule within Mesh::intersect_triangle() function. For intersections normals use triangle normals when flat shading or interpolate vertex normals when Phong shading.
- To improve the computation time use the axis-aligned bounding box test for triangle meshes. Implement the ray-box intersection within Mesh::intersect_bounding_box().
- (not graded) To parallelize your computation, install TBB or make sure OpenMP works with your compiler.

For more details, please refer to the assignment handout and lecture+exercise slides.


