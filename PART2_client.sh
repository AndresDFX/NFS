#PART2 - Client NFS
sudo apt-get -y install nfs-common
sudo mkdir -p /shared
sudo chmod 1777 /shared
sudo mount 192.168.100.1:/shared /shared
