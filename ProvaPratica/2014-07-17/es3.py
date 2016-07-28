# Il comando che dovrete implementare come script shell o programma python e' mytx.
# Tale comando elenca tutti i file di una directory.
# mytx ddd ddd.tx
# Ogni riga del file di output (secondo parametro) deve contenere la lunghezza, uno spazio e il nume del file. Dopo l'ultima riga
# deve inserire una riga bianca.
# ddd.t2 deve contenere l'elenco dei file regolari. Il primo campo e' un numero intero seguito da uno spazio, tutto cio' che segue
# fino alla fine riga e' il nome del file.
# es.
# 12 file1
# 235 file di prova


import sys
import os

#print "Nome della directory" , (str(sys.argv[1]))
#print "Nome del file" , (str(sys.argv[2]))
if len(sys.argv) > 2:

    path=str(sys.argv[1])
    n=len(path)

# Open a file
    dirs = os.listdir( path )


    fd=open(sys.argv[2], "w")

# This would print all the files and directories
    for file in dirs:
        path=path[:n]+file
        size=os.path.getsize(path)
    #print str(size) + " " + path
        fd.write(str(size) + " " + file + "\n")

    fd.write("\n")

    fd.close

else:
    print "ci vogliono 2 argomenti"
