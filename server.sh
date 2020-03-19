#!/usr/bin/env bash
sudo apt-get update
sudo hostname -I | awk '{print $2}' >> .bashrc #Pone en la pantalla inicial de la maquina la IP
sudo echo "sudo su -" >> .bashrc

#PART1 - Server Python UDP
sudo apt-get -y install apache2 ; apt-get -y install python
sudo fuser -k -n udp 5678 ; python server-udp.py --port 5678 &

#PART2 - Server NFS
sudo apt-get -y install nfs-kernel-server
sudo mkdir -p /mnt/sharedfolder
sudo chown nobody:nogroup /mnt/sharedfolder && chmod 1777 /mnt/sharedfolder 
sudo echo "/mnt/sharedfolder *(rw,sync,no_subtree_check)" >> /etc/exports 
sudo ufw allow from 192.168.100.5/24 to any port nfs 
sudo systemctl restart nfs-kernel-server 
sudo exportfs -a
sudo systemctl restart nfs-kernel-server &

#PART3 - Server MPI (SSH For user vagrant)
sudo apt-get -y install openmpi-bin openmpi-doc libopenmpi-dev
sudo find /etc/ssh/sshd_config -type f -print0 | xargs -0 sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/g' 
sudo find /etc/ssh/sshd_config -type f -print0 | xargs -0 sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/g' 
sudo service ssh restart
ssh-keygen -t rsa -f /home/vagrant/.ssh/id_rsa -C "" -N ""
#ssh-copy-id -i /home/vagrant/.ssh/id_rsa.pub vagrant@192.168.100.4     --->Copiar IP de client01
#ssh-copy-id -i /home/vagrant/.ssh/id_rsa.pub vagrant@192.168.100.3     --->Copiar IP de client02
#ssh vagrant@192.168.100.4                                              --->Probando conexion
#ssh vagrant@192.168.100.3                                              --->Probando conexion

#BONUS - Virtualization Active in VM
#sudo add-apt-repository 'deb [arch=amd64] https://download.virtualbox.org/virtualbox/debian xenial contrib'
#wget -q https://www.virtualbox.org/download/oracle_vbox_2016.asc -O- | sudo apt-key add -
#sudo apt-get update
#sudo apt-get -y install virtualbox-6.1 &
