#!/usr/bin/env bash
sudo apt-get update

#INSTALL VIRTUAL BOX (Ubuntu 18.04+)
sudo apt install virtualbox

#INSTALL VAGRANT
sudo curl -O https://releases.hashicorp.com/vagrant/2.2.6/vagrant_2.2.6_x86_64.deb
sudo apt install ./vagrant_2.2.6_x86_64.deb

#DEPLOY VM
vagrant up