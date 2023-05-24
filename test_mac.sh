#!/bin/bash
# Puny BuildTools - MacOS testing environment
# builds z5 version and launches Fizmo in current Terminal
# install Frotz with homebrew https://brew.sh/

#read config file 
source config.sh

#cleanup
rm ${STORY}.z5

#compile
${WRAPPER} -5 ${STORY}.inf
read -n 1 -p "Press ANY KEY to launch Frotz..."

#run Frotz with the freshly generated Z-file
#frotz -d ${STORY}.z5
frotz ${STORY}.z5
