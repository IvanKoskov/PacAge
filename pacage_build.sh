#!/bin/bash

echo "BUILDING"
make
echo "DONE WITH COMPILATION!"

# Prompt user to move executable
echo "Do you want to move the executable to /usr/local/bin? (y/n)"
read option

if [ "$option" = "y" ]; then
    echo "This may ask for password!"
    sudo mv pacage /usr/local/bin/
    echo "'pacage' has been moved to /usr/local/bin"
else
    echo "Executable not moved."
    echo "finishing"
fi

