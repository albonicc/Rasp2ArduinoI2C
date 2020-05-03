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
show_message(device, 'Raspberry Pi MAX7219', fill="white", font=proportional(LCD_FONT), scroll_delay=0.08)


addresses = [0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9] # bus addresses
addr = 0 # starts addresses in addr 0x0
bus = SMBus(1) # indicates /dev/ic2-1

option = 0


def writeMessage(addresses, addr, msg)):
	bus.write_byte(addresses[addr], msg) # writes the message in the address

def displayMessage(addresses, addr):
	bus.write_byte(addresses[addr]) # reads the message of that address
	
def selectMessage(nMessage):
	if nMessage = 1:
		addr = 0
	if nMessage = 2:
		addr = 0
	if nMessage = 3:
		addr = 0
	if nMessage = 4:
		addr = 0
	if nMessage = 5:
		addr = 0
	if nMessage = 6:
		addr = 0
	if nMessage = 7:
		addr = 0
	if nMessage = 8:
		addr = 0
	if nMessage = 9:
		addr = 0
	if nMessage = 10:
		addr = 0	
	

print("Welcome! Enter the option you want")
print("[1]: Write a message")
print("[2]: Display a message")
print("[3]: Exit")

while option != 3:
	if option == 1:
		print("Write the message you want to save")
		msg = input()
		writeMessage(addresses, addr, msg)
	if option == 2:
		print("Write the number of the message you want to display")
		nMessage = input()
									
		displayMessage(addresses, addr)
		
		
	




print ("Enter 1 for ON or 0 for OFF")
while numb == 1:

	ledstate = input(">>>>   ")

	if ledstate == "1":
		bus.write_byte(addr, 0x1) # switch it on
	elif ledstate == "0":
		bus.write_byte(addr, 0x0) # switch it on
	else:
		numb = 0

