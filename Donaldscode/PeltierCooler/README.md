# PID Controlled Peltier Cooler

## Overview
This is a project I worked on at Lawrence Berkeley National Laboratory. The intent was to create a cost effective
temperature PID controller with an Arduino.

## Prerequisites
The current setup is:
- Arduino Mega 2526
- TMP 102 temperature sensor
- Sparkfun Mosfet Power Control Kit.
- CPU cooler.
- Thermoelectric cooler (Peltier).
- Two power supplies, one for the fan, and another for the Mosfet.

You must have the latest version of Arduino installed, and the PID library. Processing is optional to output serial data.

## Operating
- Set Power supply for fan to 12v, .5A
- Set Power supply for Mosfet to 8V, 2.5A (Depending on operation, this may change -- trace width on the pcb only supports
< 3A)
- Make sure pin 4 (PWM) is applied to gate of Mosfet.

