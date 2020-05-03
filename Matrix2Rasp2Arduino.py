import RPi.GPIO as GPIO
from time import sleep, strftime
from datetime import datetime

from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.core.virtual import viewport
from luma.led_matrix.device import max7219
from luma.core.legacy import text, show_message
from luma.core.legacy.font import proportional, CP437_FONT, LCD_FONT

from smbus import SMBus

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial, width=16, height=8, block_orientation=0)
device.contrast(5)
virtual = viewport(device, width=32, height=16)

addr = 0x0 
bus = SMBus(1) # indicates /dev/ic2-1

option = 0


def writeMessage(addr, msg)):
	 data = split(msg)
	 bus.write_i2c_block_data(addr, 0, data)

def displayMessage(addr):
	msg = bus.read_i2c_block_data(addr, 0, 20) # reads the message of that address
	show_message(device, msg, fill="white", font=proportional(LCD_FONT), scroll_delay=0.08)

def split(word): 
    return list(word)  
	
print("Welcome! Enter the option you want")
print("[1]: Write a message")
print("[2]: Display a message")
print("[3]: Exit")

while option != 3:
	if option == 1:
		print("Write the message you want to save")
		msg = input()
		writeMessage(addr, msg)
		print("Do you want to enter another option?")
	if option == 2:
		print("Write the number of the message you want to display")
		nMessage = input()
		selectMessage(nMessage)						
		displayMessage(addr)
		print("Do you want to enter another option?")

