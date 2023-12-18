#!/bin/bash
# builds Amstrad CPC / PCW release

#read config file 
source config.sh

#cleanup
rm ${STORY}_cpc_vezza.dsk

#copy resources
cp ./Interpreters/cpc_vezza.dsk ./
mv cpc_vezza.dsk ${STORY}.dsk

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 STORY.DAT

#place story on disk image
idsk ${STORY}.dsk -i STORY.DAT -t 0

#place loader and resources
cp ./Interpreters/DISC ./
idsk ${STORY}.dsk -i DISC
cp ./Resources/SCREEN ./
idsk ${STORY}.dsk -i SCREEN -t 1 -c c000
cp ./Resources/PAL ./
idsk ${STORY}.dsk -i PAL -t 1 -c a000

#post cleanup
rm STORY.DAT
rm DISC
rm SCREEN
rm PAL
mv ${STORY}.dsk ${STORY}_cpc_pcw.dsk
