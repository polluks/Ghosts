#!/bin/bash
# builds Tandy TRS-80 Model 4 release

# This script needs a WSL2 environment to work out of the box, which is the
# suggested environment for the Puddle Buildtools anyway. The script executes
# a Windows binary, something perfectly fine in the WSL ecosystem. If you're
# working from a Linux-only environment, you need to install Wine and change
# the 'powershell' lines to 'wine cmd.exe /c' (untested) and you need to 
# alter the paths. Why using a Windows tool? There is literally no program
# available for Linux that allows writing files to TRS80 Model III & 4 disks.
# Well, there is but it's not working. If you are able to point me to a
# working solution for Linux, I'll update this script accordingly.
#
# NOTE FOR WSL2 USERS: The tools I am using here are TRSWRITE and TRSREAD by
# Matthew Reed. These programs are not allowed being redistributed but they
# are freeware and you may grab them from: 
#
# http://www.trs-80emulators.com/trsread-trswrite. 
#
# I stored them in a dedicated folder "FictionTools" on my Windows partition
# (C:/FictionTools). The environment variable $toolswin had been defined in 
# my .bashrc and it points to '/mnt/c/FictionTools' for easy operations.
# Please consider that the path to your Powershell installation might differ.
# I am using Powershell 7 and the script is confirmed to work well with it.

#read config file 
source config.sh

#cleanup
rm ${STORY}_trs80_m4.dsk

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 STORY.DAT

printf "Infocom TRS80 Model4 Disk Creator 1.0 by Stefan Vogt\n" 
printf "%s story file is Z-machine version 5\n\n" ${STORY}

wslopt()
{
    #copy disk template with interpreter
    cp Interpreters/TRS80_M4.dsk $toolswin

    #move story file on Windows partition
    mv STORY.DAT $toolswin

    #write story file on TRS-80 Model 3 (LDOS) disk image
    /mnt/c/Program\ Files/PowerShell/7/pwsh.exe -Command "C:/FictionTools/trswrite.exe -o C:/FictionTools/TRS80_M4.dsk C:/FictionTools/STORY.DAT"
    printf "\n" # only cosmetical
    /mnt/c/Program\ Files/PowerShell/7/pwsh.exe -Command "C:/FictionTools/trsread.exe -v C:/FictionTools/TRS80_M4.dsk"

    #grab prepared image from Windows partition and place it in project directory
    mv $toolswin/TRS80_M4.dsk .

    #post cleanup
    rm $toolswin/STORY.DAT
    mv TRS80_M4.dsk ${STORY}_trs80_m4.dsk
}

wineopt()
{
    #copy disk template with interpreter
    cp Interpreters/TRS80_M4.dsk .

    #write story file on TRS-80 Model 3 (LDOS) disk image
    wine ~/FictionTools/trswrite.exe -o TRS80_M4.dsk STORY.DAT
    printf "\n" # only cosmetical
    wine ~/FictionTools/trsread.exe -v TRS80_M4.dsk

    #post cleanup
    rm STORY.DAT
    mv TRS80_M4.dsk ${STORY}_trs80_m4.dsk
}

while getopts 21h opts
do
	case $opts in
		2) wineopt
		;;
        1) wslopt
        ;;
		*) printf "\nSynopsis: argument -1 for a Windows system with WSL installed\n          argument -2 for a Linux system with Wine installed\n\nWrong argument passed, defaulting to WSL option.\n"
           wslopt
		;;
	esac
done

if [ $OPTIND -eq 1 ]; then printf "Synopsis: argument -1 for a Windows system with WSL installed\n          argument -2 for a Linux system with Wine installed\n\nNo argument passed, defaulting to WSL option.\n"; wslopt; fi