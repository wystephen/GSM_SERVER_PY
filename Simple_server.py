#author:Wang Yan
#Data:2016/01/29
#Introduce:Build a simple tcp server.
import socket

import threading
import time

def tcplink(sock, addr):
	print 'Accpt new connect form %s:%s...'% addr
	sock.send('Welcome!')
	while True:
		data = sock.recv(1024)
		time.sleep(1)
                print data
		if data == 'exit' or not data:
			break
		#sock.send('hello')
	sock.close()
	print 'connect closed from %s:%s... ' % addr

if __name__ == '__main__':
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind(('120.25.218.92',9919))
	s.listen(10)
	print 'Wait for connect!'
	
	while True:
		sock, addr = s.accept()
		t = threading.Thread(target = tcplink, args = (sock,addr))
		t.start()
		


	
