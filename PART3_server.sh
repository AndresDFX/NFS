#PART3 - Server MPI (SSH For user Vagrant)
sudo apt-get install -y mpich
sudo sed -i '/PermitRootLogin.*/c\PermitRootLogin yes' /etc/ssh/sshd_config
sudo sed -i '/PasswordAuthentication.*/c\PasswordAuthentication yes' /etc/ssh/sshd_config
sudo service ssh restart
ssh-keygen -t rsa -q -f "/home/vagrant/.ssh/id_rsa" -N ""
chown -R vagrant:vagrant /home/vagrant/.ssh

