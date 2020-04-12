# Cargar el CSV
n<-read.csv(file="nums.csv",head=TRUE,sep=";")
# mostrar datos leidos
n
# Sacar la 2a columna
y<-n[,2,drop=FALSE]
# Sacar promedio de y
lapply(y,mean)
# Sacar mediana de y
lapply(y,median)
