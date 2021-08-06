# Car-Robot-Control-Using-Devo-10
using ROS Serial Arduino
https://youtu.be/3BBNV1cGiQg

devo10 value is ros topic /cmd_vel
Car Robot Subscribe /cmd_vel topic and saves /cmd_vel topic value at steering, car_speed variable(not include in this post) 
Next send data using i2c(arduino mega <-> raspberry pi4)
We can see data at Oled display(arduino)
https://youtu.be/x8bkPSdArxU
