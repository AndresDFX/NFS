# Cargar el CSV
n<-read.csv(file="nums.csv",head=TRUE,sep=";")
# mostrar datos leidos
n
# Sacar la 1er columna
x<-n[,1,drop=FALSE]
# Sacar promedio de x
lapply(x,mean)
# Sacar mediana de x
lapply(x,median)
