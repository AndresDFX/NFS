#!/usr/bin/env bash
sudo apt-get update

#INSTALL VIRTUAL BOX 
sudo add-apt-repository 'deb [arch=amd64] https://download.virtualbox.org/virtualbox/debian xenial contrib'
wget -q https://www.virtualbox.org/download/oracle_vbox_2016.asc -O- | sudo apt-key add -
sudo apt-get update
sudo apt-get -y install virtualbox-6.1 &

#INSTALL VAGRANT
sudo curl -O https://releases.hashicorp.com/vagrant/2.2.6/vagrant_2.2.6_x86_64.deb
sudo apt install ./vagrant_2.2.6_x86_64.deb
vagrant plugin install vagrant-env

#DEPLOY VM
vagrant up