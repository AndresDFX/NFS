<div align="justify">
<u><h1>NFS - Network File System </u></h1>

NFS o Network File System es un protocolo de sistema de archivos distribuido, creado originalmente pero Sun Microsystems. A través de NFS, puede permitir que un sistema comparta directorios y archivos con otros en una red. En el uso compartido de archivos NFS, los usuarios e incluso los programas pueden acceder a la información en sistemas remotos casi como si residieran en una máquina local.

NFS se opera en un entorno *cliente-servidor* donde el servidor es responsable de administrar la autenticación, autorización y administración del cliente, así como todos los datos compartidos dentro de un sistema de archivos específico. Tras la autorización, cualquier número de clientes puede acceder a los datos compartidos como si estuvieran presentes en su almacenamiento interno. Configurar un servidor NFS en su sistema Ubuntu es muy simple. Todo lo que necesita hacer es realizar algunas instalaciones y configuraciones necesarias, tanto en el servidor como en las máquinas cliente, y ya está.

---
<u><h2> Parte 1 - Socket UDP</u></h2>

Para esta practica hay dos programas escritos en Python, un código es cliente y el otro es servidor. Estos códigos se comunican a través del protocolo UDP. Ejecute el programa cliente (que correrá en el `host`) y el servidor que correrá en la máquina virtual `server_nfs`.

Bastara solo con ejecutar el archivo [Vagrantfile](./Vagrantfile) mediante el comando `vagrant up server_nfs` en este punto el servidor estara en linea.

---
<u><h3> 1.1) Validando</u></h3>

Iniciar el cliente en el `host` en el directorio [scripts](scripts/client-udp.py) mediante el comando `python client-udp.py --port 5678` esto devolvera un mensaje informando que el mensaje se envio y la conexion por socket se cerro.

Es importante considerar que tanto el cliente como el servidor a la hora de ser programados en el [Vagrantfile](./Vagrantfile) se les debe asignar puertos por encima de 1024 y por debajo de 65535 y pasar como argumentos “--port nnn” donde nnn es el puerto configurado en el *portafowarding udp* en el archivo [Vagrantfile](./Vagrantfile) para el `host` y `guest` respectivamente.

---
<u><h2> Parte 2 - NFS Cluster</u></h2>

Para llevar a cabo esta demostración se crearán tres máquinas virtuales con la siguiente configuración. 

* Servidor: 1 procesador, 782 MB de RAM
* Clientes (2): 1 procesador, 386 MB de RAM

La definición de estas máquinas se da en el siguiente [Vagrantfile](./Vagrantfile).

```
# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
    config.vm.box = "ubuntu/xenial64"
    config.vm.define "server_nfs" do |web|
      web.vm.network "private_network", ip: "192.168.100.5"
      web.vm.provision "file", source: "scripts/server-udp.py", destination: "$HOME/server-udp.py"
      web.vm.provision "shell", path: "server.sh"
      web.vm.network "forwarded_port", guest: 1234, host: 1234, protocol: "tcp"
      web.vm.network "forwarded_port", guest: 5678, host: 5678, protocol: "udp"
      web.vm.synced_folder "./shared", "/mnt/sharedfolder" 
      web.vm.provider :virtualbox do |vb|
        vb.customize [ 'modifyvm', :id, '--name', 'server_nfs' ]
        vb.customize [ 'modifyvm', :id, '--memory', '782' ]
        vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      end
    end

  config.vm.define "client01" do |web|
    web.vm.network "private_network", ip: "192.168.100.4"
    web.vm.provision "shell", path: "client.sh"
    web.vm.synced_folder "./shared", "/mnt/sharedfolder_client" 
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'client01' ]
    end
  end

  config.vm.define "client02" do |web|
    web.vm.network "private_network", ip: "192.168.100.3"
    web.vm.provision "shell", path: "client.sh"
    web.vm.synced_folder "./shared", "/mnt/sharedfolder_client" 
    web.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'client02' ]
    end
  end
end 

```

Para desplegar las máquinas se puede hacer con el comando:

```
vagrant up
```

O se pueden gestionar cada una de las máquinas por sus nombres:

* `server_nfs`
* `client01`
* `client02`

Para crear una máquina en particular `vagrant up server_nfs`.
Para acceder a una máquina en especial via `ssh`, `vagrant ssh client01`.
Para destruir una máquina `vagrant destroy client02 -f`.

--- 
<u><h3> 2.1) Validando</u></h3>

Ingresar al `server_nfs` y ejecutar el siguiente comando:

```
touch /mnt/sharedfolder/demo
```
Salir del `server_nfs` e ingresar a `client01`. Estando allí validar que el archivo existe:

```
ls -l /mnt/sharedfolder_client/demo
```
El archivo debería estar disponible también en `client01`.

</div>
