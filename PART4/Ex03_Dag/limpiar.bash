#!/bin/bash
# Guardar argumento 1
fIn=$1
# Quitar la extension .txt del nombre de archivo
fName=${fIn%\.txt}
fOut=${fName}C.txt
# Eliminar URLs repetidas y guardar resultado en fOut
sort -n ${fIn} | uniq > ${fOut}
