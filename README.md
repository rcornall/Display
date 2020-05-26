On linux:
$ g++ -std=c++11 src/*cpp  -Iinc/display -o test -lsfml-graphics -lsfml-window -lsfml-system

Or standard cmake:
$ cmake ..
$ make
and run with ./display

Requires SFML 2.4.2 lib, and if using cmake, copy FindSFML.cmake into /user/share/cmake/Modules/.

![fireworks](fireworks.gif)
