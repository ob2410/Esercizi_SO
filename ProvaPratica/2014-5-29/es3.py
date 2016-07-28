# Il comando che dovrete implementare come script shell o programma python e' statlen.
# Data una directory statlen fa una statistica sulla lunghezza dei nomi dei file presenti in tutto il sottoalbero con radice nella
# directory passata come parametro.
# es.
# $ statlen /tmp
# 2: 2
# 3: 10
# 5: 4
# ...
# significa che in tmp (e in tutte le sottodir.ectory di /tmp) ci sono 2 file con nome di due caratteri, 10 con nomi di 3 caratteri e
# cosi' via.

#funziona solo che non lo stampa proprio come dice lui, poi si fa un ciclo per stamparli in quel modo volendo ma ora non mi va

import sys,os,string
from collections import Counter

if len(sys.argv) > 1:
    length = {}
    for root, subdir, files in os.walk(sys.argv[1]):
        for filename in files:
            key=len(filename)
            val=length.get(key,0)
            length[key]=val+1
    print str(length)

else:
	print "needed 1 argument"
