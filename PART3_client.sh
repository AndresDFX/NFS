#PART3 - Client MPI (SSH For user Vagrant)
sudo apt-get install -y mpich
sudo sed -i '/PermitRootLogin.*/c\PermitRootLogin yes' /etc/ssh/sshd_config
sudo sed -i '/PasswordAuthentication.*/c\PasswordAuthentication yes' /etc/ssh/sshd_config
sudo service ssh restart