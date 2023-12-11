# IntroductionToRobotics(2023-2024)

Welcome to my repository "Introduction to Robotics" course. I am a third-year student at the Faculty of Mathematics and Computer Science, University of Bucharest, specializing in Computer Science and Information Technology. In this repository you will find my assignments for this course.

**Thank you for visiting! :)**

## Homework1 - RGB_LED
This assignment focuses on controlling each channel (Red, Green, and Blue) of an RGB LED using individual potentiometers. The components used in this homework include an RGB LED (1), potentiometers (3), as well as resistors and wires as needed. I utilized a separate potentiometer to control each color of the RGB LED: red, green, and blue. This control utilizes digital electronics. I read the potentiometer values with the Arduino and then wrote the corresponding values to the LED pins.

### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/WhatsApp%20Image%202023-10-21%20at%2021.38.51.jpeg?raw=true" alt="A photo of my setup" width="500" height="300">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/S05PshwinNo)](https://consent.youtube.com/m?continue=https%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3DS05PshwinNo%26ab_channel%3DDiana-CristianaOjoc%26cbrd%3D1&gl=RO&m=0&pc=yt&cm=4&hl=en&src=1)

## Homework2 - Elevator simulator wannabe
This  assignment  involves  simulating  a  3-floor  elevator  control  system  usingLEDs, buttons, and a buzzer with Arduino. Through this assignment, I gained experience using button state switching, implementing unlocking techniques, and coordinating multiple components to represent real-world scenarios. 

The components used in this homework include LEDs  (4:  3  for  the  floors  and  1  for  the  elevator’s  operationalstate), Buttons (At least 3 for floor calls), Buzzer (1). 
Each of the 3 LEDs should represent one of the 3 floors. The LED corresponding to the current floor should light up. Additionally, another LED should represent the elevator's operational state. It should blink when the elevator is moving and remain static when stationary. 

Implement 3 buttons that represent the call buttons from the 3 floors. When pressed, the elevator should simulate movement towards the floor after a short interval (2-3 seconds).
If the elevator is already at the desired floor, pressing the button for that floor should have no effect. Otherwise, after a button press, the elevator should "wait for the doors to close" and then "move" to the corresponding floor.

### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/Elevator%20simulator%20wannabe.jpeg?raw=true" alt="A photo of my setup" width="500" height="350">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/JMy4mJVvdsM?t=5)](https://www.youtube.com/watch?v=JMy4mJVvdsM&ab_channel=Diana-CristianaOjoc)

## Homework3 - 7 segment display drawing
I used the joystick to control the position of the segment and "draw" on the display. Movement between segments should be natural, that is, it should jump from the current position only to neighbors, but without passing through "walls". The components used in this homework include:  1  7-segment  display,  1  joystick,  resistors  and  wires. 

### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/7segment%20display.jpg?raw=true" alt="A photo of my setup" width="500" height="350">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/adp_y_hMdd4)](https://www.youtube.com/watch?v=adp_y_hMdd4&ab_channel=Diana-CristianaOjoc)

## Homework4 - Stopwatch timer
I tried to implement a stopwatch timer that counts in tenths of a second and has a save lap functionality, similar to most basic stopwatch functions on most phones. The components used in this homework include: 1 7-segment display, 3 buttons, resistors, and wires. The starting value of the 4 digit 7 segment display should be ”000.0”. 

The buttons should have the following functionalities: Button 1: Start / pause; Button 2: Reset (if in pause mode). Reset saved laps (if in lap
viewing mode); Button 3: Save lap (if in counting mode), cycle through last saved laps (up to 4 laps).

### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/Stopwatch_timer.jpg?raw=true" alt="A photo of my setup" width="500" height="350">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/9RFk5uDwGFI)](https://www.youtube.com/watch?v=9RFk5uDwGFI&ab_channel=Diana-CristianaOjoc)

## Homework5 - Pseudo-smart environment monitor and logger
I tried to develop a  ”Smart Environment Monitor and Logger” using Arduino.  This system will utilize various sensors to gather environmental data, log this data into EEPROM, and provide both visual feedback via an RGB LED and user interaction through a Serial Menu.  The project focuses on integrating sensor readings, memory management, Serial Communication and the general objective of building a menu.  

The components used in this homework include: Arduino Uno Board, Ultrasonic Sensor (HC-SR04), LDR (Light-Dependent Resistor) aka Photocell aka Photoresistor aka LightSensor, RGB LED, Resistors as needed, Breadboard and connecting wires. 


**Menu Structure**

  **1. Sensor Settings**// Go to submenu

   **1.1 Sensors Sampling Interval.** 

Here you should be prompted for a value between 1 and 10 seconds.  Use this value as a sampling rate for the sensors.  You can read a separate value for each or have the same for both.

  **1.2 Ultrasonic Alert Threshold.**

Here you should be prompted for a threshold value for the ultrasonic sensor. When sensor value exceeds the threshold value,  an alert should be given.  This can be in the form of a message.  If the LED is set to Automatic Mode (see section 4.2), it should also turn red if any of the sensors are outside the value.

  **1.3 LDR Alert Threshold.**

Here you should be prompted for a threshold  value  for  the  LDR  sensor. When sensor value exceeds the threshold value,  an alert should be given.  This can be in the form of a message.  If the LED is set to Automatic Mode (see section 4.2), it should also turn red if any of the sensors are outside the value.

  **1.4 Back** // Return to main menu

**2. Reset Logger Data.**
Should  print  a  message,  promting  if  you  to confirm to delete all  data. You can reset both sensor data at the same time.

**2.1 Yes.**

**2.2 No.**

**3. System Status** // Check current status and health

**3.1 Current Sensor Readings.** 

Continuously print sensor readings at the set sampling rate, from all sensors.

**3.2 Current Sensor Settings.**

Displays  the  sampling  rate  and threshold value for all sensors.

**3.3 Display Logged Data.**

Displays last 10 sensor readings for all sensors. 

**3.4 Back.** //Return to Main menu.
  
**4. RGB LED Control** // Go to submenu

**4.1 Manual Color Control.**

Set the RGB colors manually.

**4.2 LED: Toggle Automatic ON/OFF.** 

If  automatic  mode  is ON, then the led color should be GREEN when all sensors value do not exceed threshold values (aka no alert) and RED when there is an alert (aka ANY sensor value exceeds the threshold). When automatic mode is OFF, then the LED should use the last saved RGB values.

**4.3 Back** // Return to main menu

### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/Pseudo-smart%20environment%20monitor%20and%20logger.jpeg?raw=true" alt="A photo of my setup" width="500" height="350">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/7pNTpUT4WCs)](https://www.youtube.com/watch?v=7pNTpUT4WCs&ab_channel=Diana-CristianaOjoc)


## Homework6 - Mini Matrix Game
I tried to develop a small game on the 8x8 matrix. The game must have at least 3 types of elements: player (blinks slowly), bombs/bullets (blinks fast), wall (doesn't blink). The basic idea is that I generate walls on the map (50% - 75% of the map) and then you move with the player and destroy them. The player and the bombs need to blinkat  different  rates.   The  player  should  blink  slowly  and  the  bomb/bulletshould blink fast.  The wall should not blink at all.

The components used in this homework include: Arduino Uno Board, Joystick, 8x8 LED Matrix, MAX7219, Resistors and capacitors, Breadboard and connecting wires.


### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/Mini%20Matrix%20Game.jpeg?raw=true" alt="A photo of my setup" width="500" height="350">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/w9cDfYQvrYI)](https://www.youtube.com/watch?v=w9cDfYQvrYI&ab_channel=Diana-CristianaOjoc)


## Homework7 - Matrix Checkpoint

The following functionality for this checkpoint:

**1.Intro Message** - When  powering  up  the  project,  a  greeting  messageshould be shown for a few moments.

**2.Menu**:

**(a)Start game**, starts the initial level of

**(b)Settings**. ** LCD  brightness  control.**   Save  value  to  EEPROM  and  load  itupon system start,  **Matrix brightness control** .

**(c)About**: include details about the creator of the game.  Atleast game name, author and github link

**3.End Message**

- When the game ends, add a message.
  
### Picture of the setup
<img src="https://github.com/CristianaOD/IntroductionToRobotics/blob/main/Homeworks/Matrix%20Checkpoint.jpeg?raw=true" alt="A photo of my setup" width="500" height="350">

### Video
[![A link to a video showcasing functionality ](https://youtu.be/vldVTkVOfkE)](https://www.youtube.com/watch?v=vldVTkVOfkE&ab_channel=Diana-CristianaOjoc)
