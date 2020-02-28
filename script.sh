#!/usr/bin/env bash

apt-get update
apt-get -y install apache2
apt-get -y install python
python /home/vagrant/server-udp.py