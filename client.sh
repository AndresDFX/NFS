#!/usr/bin/env bash
sudo apt-get update
sudo hostname -I | awk '{print $2}' >> .bashrc #Pone en la pantalla inicial de la maquina la IP
sudo echo "sudo su -" >> .bashrc

#PART2 - Client NFS
sudo apt-get -y install nfs-common
sudo mkdir -p /mnt/sharedfolder_client
sudo chmod 777 /mnt/sharedfolder_client/
sudo mount 192.168.100.5:/mnt/sharedfolder /mnt/sharedfolder_client &

#PART3 - Client MPI (SSH For user Vagrant)
sudo apt-get -y install openmpi-bin openmpi-doc libopenmpi-dev
sudo find /etc/ssh/sshd_config -type f -print0 | xargs -0 sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/g' 
sudo find /etc/ssh/sshd_config -type f -print0 | xargs -0 sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/g' & exit
sudo service ssh restart


