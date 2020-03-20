#PART3 - Server MPI (SSH For user Vagrant)
sudo apt-get -y install openmpi-bin openmpi-doc libopenmpi-dev build-essential git
sudo sed -i '/PermitRootLogin.*/c\PermitRootLogin yes' /etc/ssh/sshd_config
sudo sed -i '/PasswordAuthentication.*/c\PasswordAuthentication yes' /etc/ssh/sshd_config
sudo service ssh restart
ssh-keygen -t rsa -f /home/vagrant/.ssh/id_rsa -C "" -N ""

