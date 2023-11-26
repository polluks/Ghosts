#!/bin/bash
# builds Apple II release

#read config file 
source config.sh

# #cleanup
# rm ${STORY}_apple2.dsk

# # #compile
# ${WRAPPER} ${STORY}.inf

# # #create disk image
# interlz3 ./Interpreters/info3k.bin ${STORY}.z3 ${STORY}_apple2.dsk

#cleanup
rm ${STORY}_apple2_s1.dsk
rm ${STORY}_apple2_s2.dsk

#compile
${WRAPPER} -5 ${STORY}.inf

#create disk image
interlz5 ./Interpreters/info5a.bin ${STORY}.z5 ${STORY}_apple2_s1.dsk
interlz5 ./Interpreters/info5a.bin ${STORY}.z5 ${STORY}_apple2_s1.dsk ${STORY}_apple2_s2.nib
