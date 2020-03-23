#PART1 - Server Python UDP
sudo apt-get -y install apache2 ; apt-get -y install python
sudo fuser -k -n udp 5678 
python /home/vagrant/PART1/server-udp.py --port 5678 &