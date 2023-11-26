#!/bin/bash
# builds Atari ST release

#read config file 
source config.sh

#cleanup
rm ${STORY}_atarist.st

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 STORY.DAT

#copy interpreter
cp Interpreters/ATARIST.PRG ./
mv ATARIST.PRG PLAY.PRG

#copy artviewer and artwork
cp Interpreters/Tools/ARTVIEW.APP ./
cp Resources/ART.PI1 ./

#create ATARI disk image
zip -v ${STORY}.zip PLAY.PRG PLAY.PRG
zip -rv ${STORY}.zip STORY.DAT STORY.DAT
zip -rv ${STORY}.zip ARTVIEW.APP ARTVIEW.APP
zip -rv ${STORY}.zip ART.PI1 ART.PI1
zip2st ${STORY}.zip ${STORY}.st

#post cleanup
rm STORY.DAT
rm PLAY.PRG
rm ${STORY}.zip
rm ARTVIEW.APP
rm ART.PI1
mv ${STORY}.st ${STORY}_atarist.st
