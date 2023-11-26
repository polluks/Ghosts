#!/bin/bash
# builds SAM Coupe release

#read config file 
source config.sh

#cleanup
rm ${STORY}_sam_coupe.cpm

#copy resources
cp ./Interpreters/SAM_Vezza.cpm ./
mv SAM_Vezza.cpm ${STORY}_sam_coupe.cpm

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 story.dat

#place story on disk image
cpmcp -f prodos ${STORY}_sam_coupe.cpm story.dat 0:story.dat
cpmls -f prodos ${STORY}_sam_coupe.cpm

#post cleanup
rm story.dat
