#!/usr/bin/env bash
# builds Commodore 128 release

#read config file 
source config.sh

#cleanup
rm ${STORY}_c128.d71

#compile
${WRAPPER} -5 ${STORY}.inf
cp ${STORY}.z5 ${STORY}_c128.z5
ruby Interpreters/Ozmoo/make.rb -t:c128 -dc:2:9 -ss1:"${LABEL}" -ss2:"Interactive Fiction" -ss3:"${SUBTITLE}" -sw:6 ${STORY}_c128.z5

mv c128_${STORY}_c128.d71 ${STORY}_c128.d71

#remove obsolete files
rm ${STORY}_c128.z5
