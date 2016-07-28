# Il comando che dovrete implementare come script shell o programma python e' updatedir. Updatedir prende due directory
# come parametri.
# updatedir dira dirb
# deve copiare in dirb tutti i file regolari che sono in dira e non in dirb. Se un file regolare e' presente con lo stesso nome sia in
# dira sia in dirb, il file deve essere copiato dalla dira alla dirb solo se i contenuti differiscono




import sys, os, filecmp
from shutil import copyfile
dest=sys.argv[2]
src=sys.argv[1]


#è da provare ma non mi va

for root, subdir, files in os.walk(src):
    for filename in files:
        path1 = os.path.join(root, filename)
        n_exist=True
        if (os.path.isfile(path1) :
            for file2 in os.listdir( dest ) :
                if filename == file2 :
                    path2= os.path.join(dest, file2)
                    if (filecmp.cmp(path1, path2)):
                        n_exist=False
                        break

            if n_exist :
                copy2(path1,dest)
