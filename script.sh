#!/usr/bin/env bash

sudo apt-get update
sudo apt-get -y install apache2
sudo apt-get -y install python
sudo fuser -k -n udp 5678
sudo python server-udp.py --port 5678 &


