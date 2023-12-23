#!/bin/bash
# builds Tandy TRS-80 Model 3 release

#read config file 
source config.sh

#cleanup
rm ${STORY}_trs80_m3.dsk

#compile
${WRAPPER} -5 ${STORY}.inf

#prepare story 
cp ${STORY}.z5 STORY.DAT

printf "Infocom TRS80 Model3 Disk Creator 1.0 by Stefan Vogt\n" 
printf "%s story file is Z-machine version 5\n\n" ${STORY}

wslopt()
{
    #copy disk template with interpreter
    cp Interpreters/TRS80_M3.dsk $toolswin

    #move story file on Windows partition
    mv STORY.DAT $toolswin

    #write story file on TRS-80 Model 3 (LDOS) disk image
    /mnt/c/Program\ Files/PowerShell/7/pwsh.exe -Command "C:/FictionTools/trswrite.exe -o C:/FictionTools/TRS80_M3.dsk C:/FictionTools/STORY.DAT"
    printf "\n" # only cosmetical
    /mnt/c/Program\ Files/PowerShell/7/pwsh.exe -Command "C:/FictionTools/trsread.exe -v C:/FictionTools/TRS80_M3.dsk"

    #grab prepared image from Windows partition and place it in project directory
    mv $toolswin/TRS80_M3.dsk .

    #post cleanup
    rm $toolswin/STORY.DAT
    mv TRS80_M3.dsk ${STORY}_trs80_m3.dsk
}

wineopt()
{
    #copy disk template with interpreter
    cp Interpreters/TRS80_M3.dsk .

    #write story file on TRS-80 Model 3 (LDOS) disk image
    wine ~/FictionTools/trswrite.exe -o TRS80_M3.dsk STORY.DAT
    printf "\n" # only cosmetical
    wine ~/FictionTools/trsread.exe -v TRS80_M3.dsk

    #post cleanup
    rm STORY.DAT
    mv TRS80_M3.dsk ${STORY}_trs80_m3.dsk
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