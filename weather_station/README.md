# Weather station

Sensors used can measure humidity, pressure, gas(which I do not use yet), temperature and luminosity.

So this is an initial version, I basically just read measure, and write them as CSV format.
After that, I tell the Arduino to sleep for at least 16 seconds to save power.
I save energy because it will be used outside and powered on batteries.
I will move it around and I want to check it once in a while, so I need the batteries to keep it up for a long time.

I use different librairies :
- [RTC](https://github.com/Seeed-Studio/RTC_DS1307)
- [BME680](https://github.com/Seeed-Studio/Seeed_BME680)
- [TSL2561](https://github.com/Seeed-Studio/Grove_Digital_Light_Sensor/)
- [LowPower](https://github.com/rocketscream/Low-Power/blob/master/LowPower.h)

As well as built-in libraries :
- [SD](https://www.arduino.cc/en/Reference/SD)