#!/usr/bin/env bash
sudo apt-get update
sudo apt-get -y install openmpi-bin openmpi-doc libopenmpi-dev build-essential git
cp /vagrant/Makefile /vagrant/machinefile /vagrant/mpiExample.c /home/vagrant
echo "-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-"
echo "Para probar la instalacion ejecute 'make'"
echo "-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-"

