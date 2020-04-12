#!/bin/bash
# Colocar archivos de entrada en las carpetas esperadas por el Job.
for((i=0;i<4;++i));
 do
  mkdir run_${i}
  cp checkBM.py urlsC_${i}.txt run_${i}
 done
