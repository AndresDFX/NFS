#!/usr/bin/env bash
sudo apt-get update
sudo hostname -I | awk '{print $2}' > .bashrc
#sudo echo "sudo su -" >> .bashrc
sudo cat hosts >> /etc/hosts



