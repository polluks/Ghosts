#!/bin/bash
# Puny BuildTools - MacOS testing environment
# builds z5 version and launches Fizmo in current Terminal
# install Fizmo with homebrew https://brew.sh/

#read config file 
source config.sh

#cleanup
rm ${STORY}.z5

#compile
${WRAPPER} -5 ${STORY}.inf
read -n 1 -p "Press ANY KEY to launch Fizmo..."

#run Fizmo with the freshly generated Z-file
fizmo-ncursesw -nc ${STORY}.z5
