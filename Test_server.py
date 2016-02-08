#author:Wang Yan
#Data:2016/02/06
#Introduce:Build a simple tcp server,send msg to web server use MOTT.
import socket
import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import threading
import time
import Data_transfrom
#import re


def tcplink(sock, addr):
	print 'Accpt new connect form %s:%s...'% addr
	sock.send('Welcome!')
        mq = mqtt.Client("python_test")
        mq.connect("120.25.218.92",1883,60)
	while True:
		data = sock.recv(1024)
		time.sleep(1)
                print data
                if(data[1] != 'E'):
                    data = Data_transfrom.data_transform(data)
                #print data
                    mq.publish("/test",data,2)
                    publish.single("/test",data,hostname = "120.25.218.92")
                print "publish ok!"
		if data == 'exit' or not data:
			break
		#sock.send('hello')
	sock.close()
	print 'connect closed from %s:%s... ' % addr

if __name__ == '__main__':
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind(('120.25.218.92',9919))
	s.listen(100)
	print 'Wait for connect!'
	
	while True:
		sock, addr = s.accept()
		t = threading.Thread(target = tcplink, args = (sock,addr))
		t.start()
		


	
