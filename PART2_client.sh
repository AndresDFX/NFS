#PART2 - Client NFS
sudo apt-get -y install nfs-common
sudo mkdir /shared
sudo mount master:/shared /shared