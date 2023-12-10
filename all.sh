#!/bin/bash
# builds the game for all systems

# Z-machine version 5 systems (standard config)
bash c64.sh
bash apple2.sh
bash bbc_acorn.sh
bash speccy.sh
bash amiga.sh
bash plus4.sh
bash macintosh.sh
bash atari_st.sh
bash mega65.sh
bash msx.sh
bash cpc_pcw.sh
bash c128.sh
bash dos.sh
bash sam_coupe.sh
bash a8bit.sh -1
bash trs80_m3.sh -2
bash trs80_m4.sh -2

# Z-machine version 3 only systems (enable if desired)
#bash decrainbow.sh
#bash kaypro.sh
#bash osborne1.sh
#bash trs_coco_dragon64.sh
#bash vic20_pet.sh
#bash oric.sh
#bash ti99.sh