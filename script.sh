#!/usr/bin/env bash

sudo apt-get update
sudo apt-get -y install apache2
sudo apt-get -y install python
sudo fuser -k -n udp 5678
#python server-udp.py --port 5678 --> Para ejecutar el servidor en el guest


