#!/bin/bash
# Puny BuildTools - Linux testing script
# builds z5 version and launches Frotz in current Terminal

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
