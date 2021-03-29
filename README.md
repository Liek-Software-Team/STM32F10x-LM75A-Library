# STM32F10x-LM75A-Library
LM75A temperature sensor library that you can use with STM32F10x series microcontrollers. 

# Launching the LM75A sensor in your algorithm
First, integrate libraries. Then call the function Lm75a_Config (). In this function, enter 0 or 1 according to the solder condition of your A0, A1 and A2 pins. Enter the value 1 if you soldered the pins to the VCC, 0 if you soldered them to GND. 

# Reading the temperature data
The library allows you to read as celcius and fahrenheit. If you want to read in Celsius value, assign the data returned by the get_temperature_c () function to a variable you define as float or double. In the data you want to read as fahrenheit, assign the data returned from the get_temperature_f () function to the same variable.

# Notes
The library provides you with the delay function. You can call this function by typing LM75a_Delay (). It also receives data in milliseconds as input.
