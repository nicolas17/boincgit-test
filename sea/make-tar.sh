#!/bin/sh

rm -fr BOINC/.CVS
mkdir BOINC
mkdir BOINC/locale
find ../locale/client -name '*.mo' | cut -d '/' -f 4 | awk '{print "BOINC/locale/"$0}' | xargs mkdir
find ../locale/client -name '*.mo' | cut -d '/' -f 4,5 | awk '{print "cp \"../locale/client/"$0"\" \"BOINC/locale/"$0"\""}' | bash
tar cvvf sea.tar BOINC/

