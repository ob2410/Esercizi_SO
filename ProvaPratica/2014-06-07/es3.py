# Il comando che dovrete implementare come script shell o programma python e' maxfreq.
# Maxfreq ha come parametro un carattere alfanumerico e una directory.
# Es:
# maxfreq q mydir
# Cerca in tutto il sottoalbero del file system originato da mydir il file che ha la maggior frequenza della lettera indicata (in
# questo caso la maggior frequenza di 'q'). Fornisce in output il nome del file e la frequenza in percentuale.


import sys,os,string
from collections import Counter

if len(sys.argv)>2 :

    rootDir = str(sys.argv[2])
    x=sys.argv[1]
    maxx=0
    filemax=""
    for dirName, subdirList, fileList in os.walk(rootDir):
        print('Found directory: %s' % dirName)
        n=len(dirName)
        for name in fileList:
            print('\t%s' % name)
            fname=dirName[:n]+"/"+name
            text = open(fname).read()
            # Filter all characters that are not letters.
            text = filter(lambda x: x in string.letters, text.lower())
            c = Counter(text)
            frequency= c[x]*100/(sum(c.values()))
            print (c[x], sum(c.values()), frequency)



            if frequency > maxx :
                maxx=frequency
                filemax=name

    print (str(maxx) + "% " + filemax)
