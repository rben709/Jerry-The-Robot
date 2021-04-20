#include <IRremote.h> //adds the library for IR remote controller. NOTE: you must have already added this library to the arduino IDE manually

//defines the command code of each button
#define Button_0 22
#define Button_1 12
#define Button_2 24
#define Button_3 94
#define Button_4 8
#define Button_5 28
#define Button_ON 69

//setting the motor control pins to the corresponding pins on the arduino
int LeftMotor1 = 2;
int LeftMotor2 = 3;
int RightMotor1 = 4;
int RightMotor2 = 5;
 
//sets the IR receiver pin to 8
#define IR_RECEIVE_PIN 8

//setting the ultrasonic sensor pins to the corresponding pins on the arduino 
int trigPin = 11;
int echoPin = 12;

//creating variables to store ultrasonic sensor information 
float duration_us, distance_cm;
 
void setup()//start of setup function
{
   Serial.begin(9600);                                    //starts sending data to serial monitor
   Serial.println("IR Receiver Online");                  //tells user IR reciever is on
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); //sets the IR sensor to blink it's LED when a signal is detected

   //setting the ultrasonic sensor trigger to output, and the echo to input
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

   //setting all the motor control pins to outputs
   pinMode(LeftMotor1, OUTPUT);
   pinMode(LeftMotor2, OUTPUT);
   pinMode(RightMotor1, OUTPUT);
   pinMode(RightMotor2, OUTPUT);
 
   //setting the speed control pins to outputs
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
 
} //end of setup
 
void loop()//start of loop function
{
   //detects IR receiver
   if (IrReceiver.decode())//if the IR reciever detects a signal it can decode then...
   {
       Serial.println(IrReceiver.decodedIRData.command); //prints the command code for the button pressed
       IrReceiver.resume();                              //resumes detecting singals
 
       //This switch statement is used to switch between which command to execute based on what input button was pressed.
       switch (IrReceiver.decodedIRData.command)
       {
       case Button_0:     //if button 0 is pressed
           MoveForward(); //executes the function to move the robot forward
           break;         //ends the switch statement
 
       case Button_1:      //if button 1 is pressed
           MoveBackward(); //executes the function to move the robot backward
           break;          //ends the switch statement
 
       case Button_2:     //if button 2 is pressed
           MoveLeft();    //executes the function to move the robot left
           break;         //ends the switch statement
 
       case Button_3:   //if button 3 is pressed
           MoveRight(); //executes the function to move the robot right
           break;       //ends the switch statement

       case Button_4:           //if button 4 is pressed
            analogWrite(9, 0);  //sets speed pin for left wheels to 0
            analogWrite(10, 0); //sets speed pin for right wheels to 0
            break;       //ends the switch statement
            
       case Button_ON:  //if the ON button is pressed
           AutoPilot(); //enters automatic steering mode with Ultrasonic Sensor
           break;       //ends the switch statement
 
       /*The default case tells the program what to do when it gets a case that it doesn't know what to do with.
 If you only define buttons 1-5 and press button 6 it would get sent to the default case*/
       default:
           analogWrite(9, 0);   //sets speed pin for left wheels to 0
           analogWrite(10, 0);  //sets speed pin for right wheels to 0
           break; //ends the switch statement
       }
   }
} //end of loop
 
//functions for each movement operation

void AutoPilot()//start of autopilot function
{
  Serial.println("Auto Pilot Engaged"); //DEBUG
  
  while(2 > 1){ //start of infinite while loop
    
   digitalWrite(trigPin, LOW);  //stops sensor from sending a pulse if one was active
   delayMicroseconds(2);        //waits 2 microseconds
   digitalWrite(trigPin, HIGH); //starts sending an ultrasonic pulse
   delayMicroseconds(10);       //waits 10 microseconds
   digitalWrite(trigPin, LOW);  //stops sending the pulse
 
   duration_us = pulseIn(echoPin, HIGH); //calculates the time taken for the pulse to bounce off an object and return to the sensor
 
   distance_cm = 0.017 * duration_us; //calculates the distance to the obstacle based on the pulse time

   //this checks for input of button 5 which will disegage auto pilot mode and resume manual control
   if (IrReceiver.decode())//if the IR reciever detects a signal it can decode then...
   {
    IrReceiver.resume();
    if(IrReceiver.decodedIRData.command == Button_5){
    analogWrite(9, 0);   //sets speed pin for left wheels to 0
    analogWrite(10, 0);  //sets speed pin for right wheels to 0
    Serial.print("Exit autopilot");
    break;
    }
   }
 
   if (distance_cm < 50)//if the obstacle is less than 50 cm away then...
   {
       analogWrite(9, 0);   //sets speed pin for left wheels to 0
       analogWrite(10, 0);  //sets speed pin for right wheels to 0
       delay(50);           //waits a moment before changing direction
       MoveLeft(); //moves robot left
       delay(100); //waits 100 microseconds
   }
   else
   {
       MoveForward(); //moves forward
       delay(50);     //waits 50 microseconds
   }
   Serial.print("Distance: "); //Prints "Distance: " in the serial monitor
   Serial.print(distance_cm);  //Prints the calculated distance in cm in the serial monitor
   Serial.print('\n');         //Prints a newline for easier readability in the serial monitor
  }
   
}//end of AutoPilot

void MoveForward()//start of MoveForward function
{
   analogWrite(9, 200); //sets speed pin for left wheels to 0
   analogWrite(10, 200); //sets speed pin for right wheels to 0

   //sets left side wheels to move forward         
   digitalWrite(LeftMotor1, HIGH);
   digitalWrite(LeftMotor2, LOW);

   //sets right side wheels to move forward
   digitalWrite(RightMotor1, HIGH);
   digitalWrite(RightMotor2, LOW);
 
   Serial.println("Moving Forward"); //DEBUG
   delay(500);
}//end of MoveForward

void MoveBackward()
{
   analogWrite(9, 200); //sets speed pin for left wheels to 0
   analogWrite(10, 200); //sets speed pin for right wheels to 0

   //sets left side wheels to move backward
   digitalWrite(LeftMotor1, LOW);
   digitalWrite(LeftMotor2, HIGH);

   //sets right side wheels to move backward
   digitalWrite(RightMotor1, LOW);
   digitalWrite(RightMotor2, HIGH);
 
   Serial.println("Moving Backward"); //DEBUG
   delay(500);
}
void MoveLeft()
{
   analogWrite(9, 200); //sets speed pin for left wheels to 0
   analogWrite(10, 200); //sets speed pin for right wheels to 0

   //sets right side wheels to move forward
   digitalWrite(RightMotor1, HIGH);
   digitalWrite(RightMotor2, LOW);

   //sets left side wheels to move backward
   digitalWrite(LeftMotor1, LOW);
   digitalWrite(LeftMotor2, HIGH);
 
   Serial.println("Moving Left"); //DEBUG
   delay(500);
}
void MoveRight()
{
   analogWrite(9, 200); //sets speed pin for left wheels to 0
   analogWrite(10, 200); //sets speed pin for right wheels to 0

   //sets left side wheels to move forward
   digitalWrite(LeftMotor1, HIGH);
   digitalWrite(LeftMotor2, LOW);

   //sets right side wheels to move backward
   digitalWrite(RightMotor1, LOW);
   digitalWrite(RightMotor2, HIGH);
 
   Serial.println("Moving Right"); //DEBUG
   delay(500);
}
