#!/usr/bin/env bash
sudo apt-get update

#INSTALL VIRTUAL BOX (Ubuntu 18.04+)
sudo apt install virtualbox

#INSTALL VAGRANT
sudo curl -O https://releases.hashicorp.com/vagrant/2.2.6/vagrant_2.2.6_x86_64.deb
sudo apt install ./vagrant_2.2.6_x86_64.deb
vagrant plugin install vagrant-env

#DEPLOY VM
echo BOX_NAME=ubuntu/xenial64 > .env
echo IP_SERVER=192.168.100.5 >> .env
echo IP_CLIENT1=192.168.100.4 >> .env
echo IP_CLIENT2=192.168.100.3 >> .env
vagrant up