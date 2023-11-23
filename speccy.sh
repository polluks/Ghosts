#!/bin/bash
# builds ZX Spectrum +3 release

#read config file 
source config.sh

#cleanup
rm ${STORY}_speccy.dsk

#copy resources
cp ./Interpreters/Spec_Vezza_SCR.dsk ./
mv Spec_Vezza_SCR.dsk ${STORY}_speccy.dsk

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 STORY.DAT

#place story on disk image
idsk ${STORY}_speccy.dsk -i STORY.DAT -t 0

#post cleanup
rm STORY.DAT
