from sys import argv
from httplib import BadStatusLine
from socket import timeout
from ssl import SSLError
import urllib2


def checkurl(url):
    ret=0
    bmurl=url.rstrip()
    bmurl=bmurl.lstrip()
    bmurl=bmurl.rstrip('\r\n')
    print ("%s" % (bmurl))
    # Algunas URLs no aceptan la conexion si no se indica un Agent.
    url=urllib2.Request(bmurl,headers={'User-Agent':'Mozilla/5.0'})
    try:
        ws=urllib2.urlopen(url,timeout=20)
        ret=ws.getcode()
    except urllib2.HTTPError as e1: # Error al acceder (4xx o 5xx)
        ret=e1.code
    except urllib2.URLError as e2:# Error en la URL
        print ("URLError: %s" % e2)
        ret=500
    except BadStatusLine: # Error desconocido.
        print ("BadStatusLine")
        ret=500
    except timeout: # TimeOut.
        print ("TimeOut")
        ret=500
    except SSLError: # Error n SSL
        print ("SSL Error")
        ret=500

    # https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
    if(ret>=100 and ret<200): # Return 1xx
        return(1)
    elif(ret>=200 and ret<300): # Return 2xx
        return(2)
    elif(ret>=300 and ret<400): # Return 3xx
        return(3)
    elif(ret>=400 and ret<500): # Return 4xx
        return(4)
    else: # Return 5xx
        return(5)

def guardar(str,archivo):
  with open(archivo,'a') as of:
    of.write("%s" % str)

def leer(archivo):
  with open(archivo,"r") as f:
    lineas = f.readlines()
  for url in lineas:
    ret=checkurl(url)
    if(ret==1):
     guardar(url,"100.txt")
    elif(ret==2):
     guardar(url,"200.txt")
    elif(ret==3):
     guardar(url,"300.txt")
     print(" Code: %d" % (ret))
    elif(ret==4):
     guardar(url,"400.txt")
     print(" Code: %d" % (ret))
    elif(ret==5):
     guardar(url,"500.txt")
     print(" Code: %d" % (ret))

# print "argumentos: %s " % argv
leer(argv[1])