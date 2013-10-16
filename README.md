ArduinoTableTennisRadar
=======================

Arduino based table tennis radar project for DiUS hackday.


# Description #


To construct a radar using an Arduino Uno, Ultrasonic sensor and an LED Display.

# What's needed ? #

1. Arduino boards, I have two, we may be able to borrow a third
2. Download and install the Arduino IDE from [http://arduino.cc/en/main/software](http://arduino.cc/en/main/software)
3. Ultrasonic sensor, LED display and associated hardware.  I have what we need, but on the day we will probably have to break out into two teams, once concentrating on the display the other on the ultrasonic sensor

## Ultrasonic sensor ##

The ulstrasonic sensor will be used to calculate the speeed of the table tennis ball as it travels towards the sensor.

Details on the ultrasonic sensor (HYSRF05) we will be using can be found [here](http://forum.arduino.cc/index.php?topic=89524.0) and [here](http://fabtolab.com/HC-SR05-ultrasonic).  There are also other resources on line and the Arduino IDE has sample ping code which we can leverage

## LED Display ##

The display will be used to show the km/hr of the table tennis ball.  A details write up the LED display can be found at [http://learn.parallax.com/4-digit-7-segment-led-display-arduino-demo](http://learn.parallax.com/4-digit-7-segment-led-display-arduino-demo)

We can leverage this code [https://code.google.com/p/mutiplex7seg/](https://code.google.com/p/mutiplex7seg/) to write to the LED display

# Misc #
If anyone has a soldering iron, bring it along, we *may* need it.


