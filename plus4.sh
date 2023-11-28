#!/bin/bash
# builds Commodore Plus/4 release

#read config file 
source config.sh

#cleanup
rm ${STORY}_plus4.d64

#copy resources
cp Resources/picplus4.mb .

#compile
${WRAPPER} -5 ${STORY}.inf
cp ${STORY}.z5 ${STORY}_plus4.z5
ruby Interpreters/Ozmoo/make.rb -t:plus4 -i picplus4.mb -dc:2:9 -ss1:"${LABEL}" -ss2:"Interactive Fiction" -ss3:"${SUBTITLE}" -sw:6 ${STORY}_plus4.z5

mv plus4_${STORY}_plus4.d64 ${STORY}_plus4.d64

#remove obsolete files
rm ${STORY}_plus4.z5
rm picplus4.mb
