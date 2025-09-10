# procedural_snakes
Code from a youtube tutorial on procedural animation using circles.  This implementation attempts to trascribe java/processing to C++/SFML.  I wrote this on osx.

This is the youtube tutorial:
https://youtu.be/wFqSKHLb0lo?si=SpeGTSQuojGkuMPx

On a mac, you can install SFML with homebrew: 

brew install sfml

At the time of this writing, this installs sfml 'somewhere' on the system and then sets up symlinks in /usr/local/include which is what's reference
in the CMake file.  You can just change this line in CMakeLists.txt to where your sfml libs are installed:

include_directories(/usr/local/include)

