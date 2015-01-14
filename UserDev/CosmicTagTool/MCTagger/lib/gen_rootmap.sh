#!/bin/bash

temp=make_rootmap.$$.temp

rootlibmap() {
 ROOTMAP=$1
 SOFILE=$2
 LINKDEF=$3
 shift 3
 DEPS=$*
 if [[ -e $SOFILE && -e $LINKDEF ]]; then
     rlibmap -f -o $ROOTMAP -l $SOFILE -d $DEPS -c $LINKDEF 2>> $temp
     rm -f $temp
 fi
}

######################################################
# MCTagger
rootlibmap libCosmicTagTool_MCTagger.rootmap libCosmicTagTool_MCTagger.so $LARLITE_USERDEVDIR/CosmicTagTool/MCTagger/LinkDef.h \
    libLArLite_Analysis.so libBasicTool_GeoAlgo.so













