#PART2 - Server NFS
sudo apt-get -y install nfs-kernel-server
sudo mkdir -p /shared
sudo chown nobody:nogroup /shared && chmod 1777 /shared 
sudo echo "/shared *(rw,sync,no_subtree_check)" > /etc/exports 
sudo exportfs -a
sudo systemctl start nfs-kernel-server