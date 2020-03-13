#!/usr/bin/env bash
sudo apt-get update

#PART2 - Client NFS
sudo apt -y install nfs-common
sudo apt -y install cifs-utils
sudo mkdir -p /mnt/sharedfolder_client
sudo chmod 777 /mnt/sharedfolder_client/
sudo mount 192.168.100.5:/mnt/sharedfolder /mnt/sharedfolder_client &

#PART3 - Client SSH (For user Vagrant)
sudo apt -y install openmpi-bin openmpi-doc libopenmpi-dev
#sudo su
#sudo chown nobody:nogroup -R /etc/ssh/ && chmod -R 1777 /etc/ssh/
sudo find /etc/ssh/sshd_config -type f -print0 | xargs -0 sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/g' 
sudo find /etc/ssh/sshd_config -type f -print0 | xargs -0 sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/g' 
sudo service ssh restart




