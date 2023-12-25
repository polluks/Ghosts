#!/bin/bash
# Puny BuildTools v2.0
# c64.sh - C64 disk builder
# (c) 2023 Stefan Vogt

#read config file 
source config.sh

echo -e "\nc64.sh - C64 disk builder"
echo -e "Puny BuildTools 2.0, (c) 2023 Stefan Vogt\n"

zmachine3()
{
    ${WRAPPER} -3 ${STORY}.inf
    if ! [ -f ${STORY}.z3 ] ; then
        echo -e "Inform 6 compiler error detected, aborting operation."
        echo -e "C64 disk failed to build.\n"
        exit 1;
    fi
}
zmachine5()
{
    ${WRAPPER} -5 ${STORY}.inf
    if ! [ -f ${STORY}.z5 ] ; then
        echo -e "Inform 6 compiler error detected, aborting operation."
        echo -e "C64 disk failed to build.\n"
        exit 1;
    fi
}
while getopts 35h opts
do
	case $opts in
		3) zmachine3
		;;
        5) zmachine5
        ;;
		*) echo -e "\nSynopsis: ./c64.sh -5 for Z-machine version 5\n          ./c64.sh -3 for Z-machine version 3\n"
        exit 0;
		;;
	esac
done
if [ $OPTIND -eq 1 ]; then 
    echo -e "Synopsis: ./c64.sh -5 for Z-machine version 5\n          ./c64.sh -3 for Z-machine version 3\n\nNothing to be done. No options passed.\n"; 
    exit 0;
fi

#cleanup 
if [ -f ${STORY}_c64.d64 ] ; then
    rm ${STORY}_c64.d64
fi

#check for loading screen and arrange resources
LOADSCRFLAG="-i loadpic.kla "
if ! [ -f Resources/loadpic.kla ] ; then
    LOADSCRFLAG=""
else
    cp Resources/loadpic.kla .
fi

#compile
ruby ~/FictionTools/Templates/Interpreters/Ozmoo/make.rb -t:c64 ${LOADSCRFLAG}-dc:2:9 -ss1:"${LABEL}" -ss2:"Interactive Fiction" -ss3:"${SUBTITLE}" -sw:6 ${STORY}.z${ZVERSION}

mv c64_${STORY}.d64 ${STORY}_c64.d64

#post-notification and cleanup
if ! [ -f Resources/loadpic.kla ] ; then
    echo -e "\nNo loadpic.kla found in /Resources dir."
    echo -e "C64 disk without loading screen successfully built.\n"
else
    rm loadpic.kla
    echo -e "\nloadpic.kla found in /Resources dir."
    echo -e "C64 disk with loading screen successfully built.\n"
fi
