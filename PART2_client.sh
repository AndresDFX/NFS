#PART2 - Client NFS
sudo apt-get -y install nfs-common
sudo apt-get -y install cifs-utils
sudo mkdir -p /shared
sudo chmod 1777 /shared
sudo mount server:/shared /shared &
