#!/bin/bash
# builds Commodore Amiga release

#read config file 
source config.sh

#cleanup
rm ${STORY}_amiga.adf

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 Story.Data

#copy Amiga disk image template
cp Interpreters/amiga_Infocom_z5_pic.adf ./
mv amiga_Infocom_z5_pic.adf ${STORY}_amiga.adf

#add file to Amiga disk image
xdftool ${STORY}_amiga.adf write Story.Data

#post cleanup
rm Story.Data
