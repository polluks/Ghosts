#!/bin/bash
# builds Mega65 release

#read config file 
source config.sh

#cleanup
rm ${STORY}_mega65.d81

#compile
${WRAPPER} -5 ${STORY}.inf
cp ${STORY}.z5 ./Interpreters/Ozmoo/
cd Interpreters/Ozmoo
ruby make.rb -t:mega65 -dc:2:9 -ss1:"${LABEL}" -ss2:"Interactive Fiction" -ss3:"${SUBTITLE}" -sw:6 ${STORY}.z5

# nuke obsolete files 
rm ${STORY}.z5
mv mega65_${STORY}.d81 ${STORY}_mega65.d81
mv ${STORY}_mega65.d81 ../../
