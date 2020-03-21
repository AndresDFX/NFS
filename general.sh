#!/usr/bin/env bash
sudo apt-get update -y
sudo hostname -I | awk '{print $2}' > .bashrc
cat /vagrant/hosts >> /etc/hosts
cp -r /vagrant/PART1/ /home/vagrant/
cp -r /vagrant/PART3/ /home/vagrant/
cp -r /vagrant/PART4/ /home/vagrant/
sudo chown nobody:nogroup /home/vagrant/PART1/ && sudo chmod -R 1777 /home/vagrant/PART1/ 
sudo chown nobody:nogroup /home/vagrant/PART3/ && sudo chmod -R 1777 /home/vagrant/PART3/ 
sudo chown nobody:nogroup /home/vagrant/PART4/ && sudo chmod -R 1777 /home/vagrant/PART4/ 
#sudo echo "sudo su -" >> .bashrc



