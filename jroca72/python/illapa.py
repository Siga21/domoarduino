#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests  #es necesario instalar la libreria requests
import MySQLdb
import serial, time

DB_HOST = 'localhost'
DB_USER = 'root'
DB_PASS = 'password'
DB_NAME = 'domotica'   #nombre de la base  


def run_query(query):
    datos = [DB_HOST, DB_USER, DB_PASS, DB_NAME]

    conn = MySQLdb.connect(*datos)
    cursor = conn.cursor()
    cursor.execute(query)

    data = cursor.fetchall()

    cursor.close()
    conn.close()

    return data

# configuro comunicacion serial con arduino 
arduino = serial.Serial("COM4", 9600)
# recupero la temperatura del sensor 1 
response = requests.get("http://192.168.1.135/Python")
fvalor = float(response.text)      #convierto el valor de la temperatura a float otra vez

# recupero la temperatura de corte del sensor 1 de la base de datos
texto = "select temperatura, nombre from temperaturas where sensor = 1"
registros = run_query(texto)

# guardo el valor y nombre de sensor 1
for i in range(len(registros)):
    valor_sensor_1 = registros[i][0]
    nombre_sensor_1 = registros[i][1]
    print 'temperatura de corte de ' +  registros[i][1] + ' -- ' + str(registros[i][0])



print 'temperatura en ' + nombre_sensor_1 + ' : ' + str(fvalor)
# comparo el valor leido con el de corte y actuo en consecuencia
# si supera la temp de corte apaga el led, si no lo enciende
if valor_sensor_1 > fvalor:
    time.sleep(2)   
    arduino.write(b'e')
    arduino.close()
else:
    time.sleep(2)
    arduino.write(b'a')
    arduino.close()


