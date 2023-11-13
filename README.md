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
This  assignment  involves  simulating  a  3-floor  elevator  control  system  usingLEDs, buttons, and a buzzer with Arduino. Through this assignment, I gained experience using button state switching, implementing unlocking techniques, and coordinating multiple components to represent real-world scenarios. The components used in this homework include LEDs  (4:  3  for  the  floors  and  1  for  the  elevator’s  operationalstate), Buttons (At least 3 for floor calls), Buzzer (1). 
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
I tried to implement a stopwatch timer that counts in tenths of a second and has a save lap functionality, similar to most basic stopwatch functions on most phones. The components used in this homework include: 1 7-segment display, 3 buttons, resistors, and wires. The starting value of the 4 digit 7 segment display should be ”000.0”. The buttons should have the following functionalities: Button 1: Start / pause; Button 2: Reset (if in pause mode). Reset saved laps (if in lap
viewing mode); Button 3: Save lap (if in counting mode), cycle through last saved laps (up to 4 laps).


