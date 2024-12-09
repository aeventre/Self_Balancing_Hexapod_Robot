# Hardware Design

## Table of Contents
- [**Hardware Design**](#hardware-design)
  - [Overview](#overview)
  - [Structure](#structure)
  - [Electronics](#electronics)
  - [Setting the I2C Address of the PCA9685](#setting-the-i2c-address-of-the-pca9685)
  - [PCB Layout](#pcb-layout)


## Overview
One of the main goals I had for the initial design is to try and keep this robot as modular as possible so that I can mess around with a bunch of different 
things and not be constrained to just the inital configuration. As such the GPIO of the ras pi is still accessible so wires or another PCB could be added. There are also 4 extra PWM outputs from the PCA9685 chips on the PCB that can be used to add additional servos or anything else that could be PWM controlled.

## Structure
All CAD models currently being used are from "Robs Tech Workbench" and can be found at https://github.com/robs-tech-workbench/hexapod_spiderbot_model\  

Since this project is using slightly different hardware to his and additional sensors might be placed on it in the future,some parts of the central body will eventually be modified and that CAD will be uploaded here.

## Electronics

For this project a custom PCB was designed to rest on top of a Raspberry pi 4b in order to make the wiring for everything neater and because PCB design is fun.  

The main chips on the board are:  
- **PCA9685** - Used to create PWM outputs to control the servos, recieves commands from the pi over the I2C bus
- **LSM6DSO32TR** - IMU for sending attitude data to the pi over the I2C bus
- **LM393** - Op-amp that compares the battery voltage to the 5V line and will light up an LED and send a 0 to a GPIO pin when the batteries voltage gets too low

The rest of the chips are for reducing the voltage from the battery to a 5V 3 amp max line and a 6V 20 amp max line. The 6V line is for powering the servos which tend to draw a lot of current. I do not expect 20 amps to ever get drawn on that line, it's about 3 just standing, and then I'd imagine 10 amps max when walking, but better safe then sorry.

## Setting the I2C Address of the PCA9685  
The I2C address of the PCA chips is determined by certain pin  

From datasheet:  
![image](https://github.com/user-attachments/assets/077c3241-b36b-435b-8d50-6b18a9e48571)

JP1-JP6 on the back of the PCB correlates to A0-A5 for chip 1 (left side) and JP7-JP12 correlates to chip 2 (right side). Placing a
jumper on the pin will bring it high and change the I2C address accordingly.  

Currently the code is configured for a jumper placed on JP7. The address can be edited in the servo_control packages code.

## PCB Layout
Front:   
![image](https://github.com/user-attachments/assets/dfdeaa73-c6c8-46eb-a4a2-f4136d9daac4)
  
Back:  
![image](https://github.com/user-attachments/assets/7bdfb4ab-2f1f-43e5-bcb4-fd6b4d70a6b0)
