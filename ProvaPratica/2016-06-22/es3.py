# La directory /home/students contiene le home directory di tutti gli studenti. Scrivere un programma bash o python
# che considerando solo i nomi del Directory Service centralizzato del tipo (nome.cognome) mostri la classifica dei

#import operator

#x = {1: 2, 3: 4, 4: 3, 2: 1, 0: 0}
#sorted_x = sorted(x.items(), key=operator.itemgetter(1))

import sys,os,string,operator,re



names={}

for dirName, subdirList, fileList in os.walk("./"):
    if (dirName=="./"):
        continue
    print (dirName)
    name=dirName[2:]
    name_with_namber=name.split(".")
    print name_with_namber
    key=re.sub("[0-9]", "" , name_with_namber[0])
    val=names.get(key,0)
    names[key]=val+1

print str(names)
#se la roba sopra funziona quello dovrebbe farmi un dizionario nome-numero persono con il nome
sorted_names = sorted(names.items(), key=operator.itemgetter(1))

for x in sorted_names:
    print (x[0])
