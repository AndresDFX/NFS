#!/usr/bin/env bash
sudo apt-get update

#PART2 - Client NFS
sudo apt-get -y install nfs-common
sudo apt-get -y install cifs-utils
sudo mkdir -p /mnt/sharedfolder_client
sudo chmod 777 /mnt/sharedfolder_client/
sudo mount 192.168.100.5:/mnt/sharedfolder /mnt/sharedfolder_client &
