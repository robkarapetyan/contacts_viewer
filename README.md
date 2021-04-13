# Contact Viewer
 A simple program to view, edit and save information from .json file containing
 name, surname, number formated data. Name and surname are stored in string format
 but number is decimal, program itself won't check for inserted
 data correctness for number and if no way to convert it to decimalit will save as "0".
 Number also can take maximum 19 digits of decimal number.

# Build Dependencies
To successfully build on debian based OS:<br>

sudo apt-get install qt5-default qt5-qmake gdb <br>

To successfully build on macOS:<br>

brew update<br>
brew install qt5<br>
export PATH=$(brew --prefix)/opt/qt5/bin:$PATH<br>

To successfully build on windows (install Qt & MSVC):

# Build Instructions

cd ~/your_project_folder/ <br>
qmake -project <br>
qmake <br>
make

# Development Tools Versions
Qt 5.13.2 / 
QtCreator 5.14.2 <br>
MSVC17

# Tests
/test.json is provided for testing purposes,wich contains cntacts list.
