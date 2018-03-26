#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial, time

arduino = serial.Serial("COM4", 9600)

time.sleep(2)
arduino.write(b'a')
arduino.close()
