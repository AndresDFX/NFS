# Cargar el CSV
n<-read.csv(file="nums.csv",head=TRUE,sep=";")
# mostrar datos leidos
n
# Sacar la 3er columna
z<-n[,3,drop=FALSE]
# Sacar promedio de z
lapply(z,mean)
# Sacar mediana de z
lapply(z,median)
