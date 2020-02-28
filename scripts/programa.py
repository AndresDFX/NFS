#/usr/bin/python
# Complete el codigo, en la seccion que dice COMPLETE de acuerdo al enunciado
# dado en este enlace https://goo.gl/1uQqiB, item 'socket-http-client'
#
import socket
import sys

try: # esta estructura permite capturar comportamientos anomalos
     # COMPLETE (1)
     s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      
except socket.error, msg: # si es del tipo socket.error
	print "Failed to create socket. Error code: " + str(msg[0]) + ", error message: " + msg[1] 
	sys.exit()

print "Socket created"

host = "www.google.com"
# defina una variable port y almacene alli el numero 80
# COMPLETE (2)
port = '80'

try:
	# COMPLETE (3)
	remote_ip = socket.gethostbyname(host)
	
except socket.gaierror:
	print "Hostname could not be resolved. Exiting"
	sys.exit()

# COMPLETE (4)
print "La direccion ip de " + host + " es " + remote_ip 

#########################################################
try:
	host = 'localhost'
	port = 8080
	remote_ip = socket.gethostbyname(host)
	
except socket.gaierror:
	print "Hostname could not be resolved. Exiting"
	sys.exit()

#########################################################

# COMPLETE (5)
endpoint = (remote_ip, port)

# COMPLETE (6)
s.connect(endpoint)

print "Socket connected to " + host + " on ip " + remote_ip

# Datos a enviarse
message = "GET / HTTP/1.1\r\n\r\n"

try:
	# COMPLETE (7)
	s.send(message)
	
except socket.error:
	print "Send failed"
	sys.exit()

print "Message send successfullly"

# Recibiendo datos
# COMPLETE (8)
reply = s.recv(1024)

print reply
s.close()
