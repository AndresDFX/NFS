#!/usr/bin/env bash
sudo apt-get update

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
#sudo systemctl restart nfs-kernel-server &

#PART3 - SSH Keygen (For user Vagrant)
ssh-keygen -t rsa -f ~/.ssh/id_rsa -C "" -N ""
ssh-copy-id -i ~/.ssh/id_rsa.pub vagrant@192.168.100.4
ssh-copy-id -i ~/.ssh/id_rsa.pub vagrant@192.168.100.3

#sudo ssh-copy-id -i ~/.ssh/id_rsa.pub vagrant@$(sudo hostname -I | awk '{print $2}')
#sudo ssh -l vagrant 192.168.100.4   #probando conexion
#sudo ssh -l vagrant 192.168.100.3   #probando conexion
#sudo ssh -o StrictHostKeyChecking=no root@$(sudo hostname -I | awk '{print $2}')
#ssh -o StrictHostKeyChecking=no root@192.168.100.5
                                                


