# Il comando che dovrete implementare come script shell o programma python e' linkdir. linkdir prende due directory come
# parametri.
# linkdir dira dirb
# e deve creare in dirb un link fisico (non simbolico) a tutti i file regolari che sono in dira e non in dirb. Se un file regolare e'
# presente con lo stesso nome sia in dira sia in dirb, nella directory dirb deve rimanere il file originariamente presente se e' piu'
# recente di quello in dira altrimenti un link al file di dira con lo stesso nome.


import sys, os

dest=sys.argv[2]
src=sys.argv[1]





for root, subdir, files in os.walk(src):
    for filename in files:
        path1 = os.path.join(root, filename)
        n_exist=True
        if (os.path.isfile(path1) :
            for file2 in os.listdir( dest ) :
                if filename == file2 :
                    n_exist=False
                    path2= os.path.join(dest, file2)
                    time1=os.path.getmtime(path1)
                    time2=os.path.getmtime(path2)
                    if time1-time2 > 0:
                        os.link(dest,path1)
                        break

            if n_exist :
                os.link(dest,path1)
