#!/bin/bash
# Puny BuildTools v2.0
# dos.sh - MS-DOS release builder
# (c) 2023 Stefan Vogt

#read config file 
source config.sh

echo -e "\ndos.sh - MS-DOS release builder"
echo -e "Puny BuildTools 2.0, (c) 2023 Stefan Vogt\n"

zmachine3()
{
    ${WRAPPER} -3 ${STORY}.inf
    if ! [ -f ${STORY}.z3 ] ; then
        echo -e "Inform 6 compiler error detected, aborting operation."
        echo -e "MS-DOS release failed to build.\n"
        exit 1;
    fi
    cp ${STORY}.z3 STORY.DAT
}
zmachine5()
{
    ${WRAPPER} -5 ${STORY}.inf
    if ! [ -f ${STORY}.z5 ] ; then
        echo -e "Inform 6 compiler error detected, aborting operation."
        echo -e "MS-DOS release failed to build.\n"
        exit 1;
    fi
    cp ${STORY}.z5 STORY.DAT
}
while getopts 35h opts
do
	case $opts in
		2) zmachine3
		;;
        5) zmachine5
        ;;
		*) echo -e "\nSynopsis: ./dos.sh -3 for Z-machine version 3\n          ./dos.sh -5 for Z-machine version 5\n"
        exit 0;
		;;
	esac
done
if [ $OPTIND -eq 1 ]; then 
    echo -e "Synopsis: ./dos.sh -3 for Z-machine version 3\n          ./dos.sh -5 for Z-machine version 5\n\nNothing to be done. No options passed.\n"; 
    exit 0;
fi

#cleanup
rm -rf Releases/DOS

#copy resources
cp Interpreters/FROTZ.EXE Interpreters/DOSTEMP/MOONM.EXE

#place story in temporary directory
mv STORY.DAT Interpreters/DOSTEMP

#copy content to Release directory
cp -r Interpreters/DOSTEMP Releases/DOS

#check for loading screen and arrange resources
if ! [ -f Resources/SCREEN.PNG ] ; then
    rm Releases/DOS/PLAY.BAT
    rm Releases/DOS/PICTVIEW.CFG
    rm Releases/DOS/VIEWER.EXE
    mv Releases/DOS/PLAYONLY.BAT Releases/DOS/PLAY.BAT
    echo "No SCREEN.PNG found in /Resources dir."
    echo -e "MS-DOS release without loading screen successfully built.\n"
else
    cp Resources/SCREEN.PNG Releases/DOS
    rm Releases/DOS/PLAYONLY.BAT
    echo "SCREEN.PNG found in /Resources dir."
    echo -e "MS-DOS release with loading screen successfully built.\n"
fi
