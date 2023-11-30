#!/bin/bash
# builds Apple II release

#read config file 
source config.sh

#cleanup
rm ${STORY}_apple2_s1.dsk
rm ${STORY}_apple2_s2.dsk

#copy resources
cp Interpreters/apple2_boot.dsk .
cp Interpreters/apple2_template.dsk .

#compile
${WRAPPER} -5 ${STORY}.inf

#add files to disk
cpmcp -f apple-do apple2_template.dsk ${STORY}.z5 0:story.dat

#apply naming scheme
mv apple2_boot.dsk ${STORY}_apple2_s1.dsk
mv apple2_template.dsk ${STORY}_apple2_s2.dsk

# show disk contents
cpmls -f apple-do ${STORY}_apple2_s2.dsk
