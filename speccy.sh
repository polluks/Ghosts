#!/bin/bash
# speccy.sh - Sinclair ZX Spectrum +3 disk builder
# Puny BuildTools, (c) 2023 Stefan Vogt

#read config file 
source config.sh

echo -e "\nspeccy.sh 2.5 - Sinclair ZX Spectrum +3 disk builder"
echo -e "Puny BuildTools, (c) 2023 Stefan Vogt\n"

#story check / arrangement
if ! [ -f ${STORY}.z${ZVERSION} ] ; then
    echo -e "Story file '${STORY}.z${ZVERSION}' not found. Operation aborted.\n"
    exit 1;
fi 

#cleanup 
if [ -f ${STORY}_speccy.dsk ] ; then
    rm ${STORY}_speccy.dsk
fi

#prepare story 
cp ${STORY}.z${ZVERSION} STORY.DAT

# build disc with or without loading screen
if ! [ -f Resources/SCREEN ] ; then
    mv ${STORY}.dsk ${STORY}_cpc_pcw.dsk
    echo -e "\nNo SCREEN found in /Resources dir."
    echo -e "CPC/PCW disc without loading screen successfully built.\n"
    rm STORY.DAT
else
    cp ~/FictionTools/Templates/Interpreters/DISC .
    idsk ${STORY}.dsk -i DISC
    cp ./Resources/SCREEN .
    idsk ${STORY}.dsk -i SCREEN -t 1 -c c000
    cp ./Resources/PAL .
    idsk ${STORY}.dsk -i PAL -t 1 -c a000
    echo -e "\nSCREEN found in /Resources dir."
    echo -e "CPC/PCW disc with loading screen successfully built.\n"
    mv ${STORY}.dsk ${STORY}_cpc_pcw.dsk
    rm STORY.DAT
    rm DISC
    rm SCREEN
    rm PAL
fi



#copy resources
cp ~FictionTools/Templates/Interpreters/Spec_Vezza_SCR.dsk .
cp Resources/SCRLOAD.COM .
mv Spec_Vezza_SCR.dsk ${STORY}_speccy.dsk

#place story on disk image
idsk ${STORY}_speccy.dsk -i STORY.DAT -t 0
idsk ${STORY}_speccy.dsk -i SCRLOAD.COM -t 0

#post cleanup
rm STORY.DAT
rm SCRLOAD.COM
