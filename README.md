<div align="justify">
<u><h1>Definiciones</u></h1>

**Socket UDP:** Los sockets UDP son sockets no orientados a conexión. Esto quiere decir que un programa puede abrir un socket y ponerse a escribir mensajes en él o leer, sin necesidad de esperar a que alguien se conecte en el otro extremo del socket. El protocolo UDP, al no ser orientado a conexión, no garantiza que el mensaje llegue a su destino. Parece claro que si mi programa envía un mensaje y no hay nadie escuchando, ese mensaje se pierde. De todas formas, aunque haya alguien escuchando, el protocolo tampoco garantiza que el mensaje llegue. Lo único que garantiza es, que si llega, llega sin errores.


**NFS:** Network File System es un protocolo de sistema de archivos distribuido, creado originalmente pero Sun Microsystems. A través de NFS, puede permitir que un sistema comparta directorios y archivos con otros en una red. En el uso compartido de archivos NFS, los usuarios e incluso los programas pueden acceder a la información en sistemas remotos casi como si residieran en una máquina local.

**OpenMPI:** Message Passing Interface es un protocolo de comunicación entre computadoras. Es el estándar para la comunicación entre los nodos que ejecutan un programa en un sistema de memoria distribuida. Las implementaciones en MPI consisten en un conjunto de bibliotecas de rutinas que pueden ser utilizadas en programas escritos en los lenguajes de programación C, C++, Fortran y Ada. La ventaja de MPI sobre otras bibliotecas de paso de mensajes, es que los programas que utilizan la biblioteca son portables (dado que MPI ha sido implementado para casi toda arquitectura de memoria distribuida), y rápidos, (porque cada implementación de la biblioteca ha sido optimizada para el hardware en la cual se ejecuta).

---
<u><h2> Parte 1 - Socket UDP</u></h2>

La documentacion completa como realizar este ejercicio se encuentra en el archivo [Despliegue de Servicios de Red.docx](./docs/Despliegue%20Servicios%20de%20Red%20-%20Usando%20Vagrant.docx).

Para esta practica hay dos programas escritos en Python, un código es cliente y el otro es servidor. Estos códigos se comunican a través del protocolo UDP. Ejecute el programa cliente (que correrá en el `host`) y el servidor que correrá en la máquina virtual `server_nfs`.

Bastara solo con ejecutar el archivo [Vagrantfile](./Vagrantfile) mediante el comando `vagrant up server` en este punto el servidor estara en linea.

---
<u><h3> 1.1) Validando</u></h3>

Iniciar el cliente en el `host` en el directorio [scripts](/PART1/scripts_socket/client-udp.py) mediante el comando `python client-udp.py --port 5678` esto devolvera un mensaje informando que el mensaje se envio y la conexion por socket se cerro.

Es importante considerar que tanto el cliente como el servidor a la hora de ser programados en el [Vagrantfile](./Vagrantfile) se les debe asignar puertos por encima de 1024 y por debajo de 65535 y pasar como argumentos “--port nnn” donde nnn es el puerto configurado en el *portafowarding udp* en el archivo [Vagrantfile](./Vagrantfile) para el `host` y `guest` respectivamente.

---
<u><h2> Parte 2 - NFS</u></h2>

La documentacion completa como realizar este ejercicio se encuentra en el archivo [CreandoTuPropioCluster.docx](./docs/CreandoTuPropioCluster.docx).

Para llevar a cabo esta demostración se crearán tres máquinas virtuales con la siguiente configuración. 

* Servidor: 1 procesador, 782 MB de RAM
* Clientes (2): 1 procesador, 386 MB de RAM

La definición de estas máquinas se da en el siguiente [Vagrantfile](./Vagrantfile).

```
# -*- mode: ruby -*-
# vi: set ft=ruby :

N = 2

Vagrant.configure("2") do |config|
  config.env.enable  
  config.vm.box = ENV['BOX_NAME']
  
  config.vm.define "server" do |server|
    server.vm.network "private_network", ip: ENV['IP_BASE'] + "1"  
    server.vm.provision "shell", path: "general.sh"
    server.vm.provision "shell", path: "PART1_server.sh"
    #server.vm.provision "shell", path: "PART2_server.sh"
    #server.vm.provision "shell", path: "PART3_server.sh"
    server.vm.provision "file", source: "PART1/scripts_socket/server-udp.py", destination: "$HOME/server-udp.py"
    server.vm.network "forwarded_port", guest: ENV['TCP_PORT'] , host: ENV['TCP_PORT'] , protocol: "tcp"
    server.vm.network "forwarded_port", guest: ENV['UDP_PORT'] , host: ENV['UDP_PORT'] , protocol: "udp"
    server.vm.synced_folder "./shared", "/shared" 
    server.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--name', ENV['MASTER_NAME'] ]
      vb.customize [ 'modifyvm', :id, '--memory', '782' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
    end
  end
  
  (1..N).each do |i|
    config.vm.define "client0#{i}" do |client|
        client.vm.network "private_network", ip: ENV['IP_BASE']+"#{i + 1}"
        client.vm.provision "shell", path: "general.sh"
        #client.vm.provision "shell", path: "PART2_client.sh"
        #client.vm.provision "shell", path: "PART3_client.sh"
        client.vm.hostname = ENV['NODE_NAME']+"-#{i}"
        client.vm.provider :virtualbox do |vb|
          vb.customize [ 'modifyvm', :id, '--memory', '386' ]
          vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
          vb.customize [ 'modifyvm', :id, '--name', ENV['NODE_NAME']+"-#{i}" ]
        end
    end
  end
end 

```

Para desplegar las máquinas se puede hacer con el comando:

```
vagrant up
```

O se pueden gestionar cada una de las máquinas por sus nombres:

* `server`
* `client01`
* `client02`

Para crear una máquina en particular `vagrant up server`.
Para acceder a una máquina en especial via `ssh`, `vagrant ssh client01`.
Para destruir una máquina `vagrant destroy client02 -f`.

--- 
<u><h3> 2.1) Validando</u></h3>

Ingresar al `server` y ejecutar el siguiente comando:

```
touch /shared/demo
```
Ingresar a `client01`. Estando allí validar que el archivo existe:

```
ls -l /shared/demo
```
El archivo debería estar disponible también en `client01`.

--- 
<u><h2> Parte 3 - OpenMPI</u></h2>

La documentacion completa como realizar este ejercicio se encuentra en el archivo [CreandoTuPropioCluster.docx](./docs/CreandoTuPropioCluster.docx).

Para llevar acabo esta parte es necesario que la maquina `server` pueda acceder por SSH a las maquinas `client01` y `client02` por medio de una clave publica RSA (Sin contraseña) esto ya se encuentra configurado en el archivo [Vagrantfile](./Vagrantfile)

--- 
<u><h3> 3.1) Validando</u></h3>

Para probar la conexion SSH por parte del servidor a los clientes, ingresamos en el *host* el comando 
```
vagrant ssh server
```

Ejecutar los siguientes comandos:
```
ssh-copy-id -i ~/.ssh/id_rsa.pub vagrant@node1 # type 'vagrant' as passwd
ssh-copy-id -i ~/.ssh/id_rsa.pub vagrant@node2 # type 'vagrant' as passwd
```

Posteriormente dentro de la maquina virtual ejecutamos el comando 
```
ssh vagrant@client01 
``` 

Este comando nos permitira conectarnos al `client01` por medio de SSH sin necesidad de contraseña. Para conectarnos al `client02` replicamos el comando pero cambiamos la ip por *client02*.



</div>
