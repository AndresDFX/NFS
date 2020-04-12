#!/bin/bash
# Guardar argumento 1
fIn=$1
# Quitar la extension .txt del nombre de archivo
fName=${fIn%\.txt}
lineas=$(wc -l ${fIn} | cut -d\  -f1)
linesxfile=$(expr ${lineas} \/ 4)
linesxfile=$((linesxfile+1))
# Partir fIn en 4 partes semiiguales.
split -a1 --lines=${linesxfile} -d ${fIn} ${fName}_
# Anexar extension .txt a los archivos resultantes
for i in $(ls -1 ${fName}_*); do
 mv $i $i.txt
done
