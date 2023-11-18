#!/bin/bash
# builds Commodore 64 tape release SIDE 2

#read config file 
source config.sh

#cleanup
rm minighosts2.prg

#compile
${WRAPPER} -5 minighosts2.inf
ruby Interpreters/Ozmoo/make.rb minighosts2.z5 -P -sp:2 -dc:2:9 -sw:0

c1541 -attach c64_minighosts2.d64 8 -read story minighosts2.prg

rm c64_minighosts2.d64
