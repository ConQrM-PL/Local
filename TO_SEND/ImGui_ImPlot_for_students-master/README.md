Package meant to be used during "Programowanie i metody numeryczne" 

Includes ImGui and ImPlot together with appropriate CMake file.
ImGui is using OpenGL as a backend.
The contex setup has been moved to seprate class in 'ImGUI_custom_bundle/context_setup' to clear the main function.

To use the package:
<ul>
 <li>Create the 'build' directory inside the project directory. You can use 'mkdir build'</li>
 <li> Go to build directory: 'cd ./build'</li>
 <li>Run 'cmake ..' to create necessary configuration files.</li>
 <li>Run 'cmake --build .' to build the project. Note the dot '.' at the end of the command</li>
 <li>Run the project using './Project' </li>