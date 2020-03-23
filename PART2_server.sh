#PART2 - Server NFS
sudo apt install -y nfs-kernel-server
sudo mkdir -p /shared
sudo chown nobody:nogroup /shared && sudo chmod 1777 /shared
sudo echo "/shared *(rw,sync,no_subtree_check)" > /etc/exports 
sudo exportfs -a
sudo service nfs-kernel-server restart

