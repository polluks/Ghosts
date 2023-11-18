#!/bin/bash
# builds Commodore 64 tape release SIDE 1

#read config file 
source config.sh

#cleanup
rm minighosts1.prg

#compile
${WRAPPER} -5 minighosts1.inf
ruby Interpreters/Ozmoo/make.rb minighosts1.z5 -P -sp:2 -dc:2:9 -sw:0

c1541 -attach c64_minighosts1.d64 8 -read story minighosts1.prg

rm c64_minighosts1.d64
