# Jerry-The-Robot
Jerry the K-12 educational robot

##About
	Jerry is the name of our educational robot, meant to teach young children basics of robotics assembly and basic programming skills. The robot is a small remote controlled, 4-wheeled assembly with 2 attatchable and detechable arms that the children can play with upon proper assembly. The robot also features an autopilot mode where it will drive automatically and avoid colliding with any walls or obstacles. 
  
#GETTING STARTED
  To get started, you are going to want to clear the number values for all of the variables that have them. You are going to need to replace these with the variables that correspond to your assembly. To get the values for each button, start by plugging in the IR sensor and assign the value of IR_RECEIVE_PIN to the pin of the arduino it is connected to. Note that you only want the number for the controlling pin, the other 2 wires for the IR sensor should be connected to GRD(ground), and 5V, so do not include these. Next you can run the program and begin pressing buttons on the IR remote to determine what command code corresponds to each button. These numbers will be printed in the Serial Monitor of the arduino IDE. You may rename the button_0 through button_ON variables, just ensure the number printed corresponds to the name of the button you want it to. After that connect your motor controller to the arduino and set the motor control pin variables to the appropriate pins. Finally, connect the ultrasonic sensor and assign the trig and echo pins to the appropriate values. Now you may connect everything together and test the robot.
  
#TROUBLESHOOTING
  There are several debug tools written into the program so plug the arduino into your PC and test the components there first, with the serial monitor open. 
  For the IR sensor, it should blink when a signal is being recieved, so if you don't see a blink when pressing a button it is either incorrectly installed, or the battery in the remote is dead.
  
#CONTACT
  For questions and concerns over the program feel free to contact me at rabennett@usf.edu
  
  For legal questions or concerns, you may reach our boss at theboss@email.com
