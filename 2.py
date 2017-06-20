# -*- coding:utf-8 -*-
from socket import *  
import time
HOST = '10.0.0.164'  
PORT = 8000  
BUFSIZ = 128  
ADDR = (HOST, PORT)  
  
#创建客户端UDP套接字  
udpClient = socket(AF_INET, SOCK_DGRAM)  



data='232222211100'

udpClient.sendto(data,ADDR)
# time.sleep(3)


# while True:  
#     data = raw_input('>')  
#     if not data:  
#         break  
# #向服务器端发送数据  
#     udpClient.sendto(data,ADDR)  
