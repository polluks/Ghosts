#!/bin/bash
# builds TI99/4a release

#read config file 
source config.sh

#cleanup
rm ${STORY}_ti99.dsk

#compile
${WRAPPER} ${STORY}.inf

#copy TI99/4a disk image template
cp Interpreters/ti994a.dsk ./
mv ti994a.dsk ${STORY}_ti99.dsk

# define minimum file size
minsize=65536

# get file size of the story file
filesize=$(stat -c%s "${STORY}.z3")

# padd the story file with zeroes if smaller than the minimum value of 65536 bytes
if (( filesize < maxsize )); then
    mv ${STORY}.z3 to ${STORY}_chunk.z3
    dd if=/dev/zero of=${STORY}_temp.z3 ibs=1k count=64
    dd if=${STORY}_chunk.z3 of=${STORY}_temp.z3 conv=notrunc
    mv ${STORY}_temp.z3 to ${STORY}.z3
    rm ${STORY}_chunk.z3
fi

#create TI99/4a story chunks
z3toTI994A ${STORY}.z3

#place files on TI99/4A disk image
tidisk --add=STRY1 ${STORY}_ti99.dsk
tidisk --add=STRY2 ${STORY}_ti99.dsk

#post cleanup
rm STRY1
rm STRY2
