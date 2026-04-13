const int IRleft = 8;
const int IRright = 7;
void go_left();
void go_right();
void go_forward(int);
void operate_movement();
const int DIR1 = 4;
const int DIR2 = 2;
const int PWM1 = 3;
const int PWM2 = 5;
const int buttonpin = 12;
int gradual_speed = 100;
void brake();
/* Motor 1 (ie PWM1,DIR1) is the left Motor for me and Motor 2 is the right motor, 
and they are coded according to my motor placement, 
their poles facing inwards and each other. It may be different 
for everyone depending on the way you have placed your motors on the chassis!*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IRleft, INPUT);
  pinMode(IRright, INPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(buttonpin, INPUT);


}

void loop() {

  operate_movement();
  
}

void operate_movement(){

   int left_instructions = digitalRead(IRleft);
   int right_instructions = digitalRead(IRright);
   if (!((left_instructions ==  LOW) && (right_instructions == LOW) )){   
    /*checking whether one of the sensors senses something different*/
     brake();
     
     gradual_speed = 100;
     if (left_instructions == LOW) {

      go_left();
      Serial.println("left");
     }
      
      /*checking if the left sensor sees black, so we need to follow along by turning left*/
     if (right_instructions == LOW){

      go_right();
      Serial.println("right");
     }   
      /*checking if the right sensor sees black, so we need to follow along by turning right*/
   }
   else
   { 
     if (gradual_speed < 220){
      
      gradual_speed += 1;
      
     }

     go_forward(gradual_speed);
     Serial.println("forward");

   }
     /*delay(100); */
    /*just take notice of this! This is intended to send an output of HIGH if it scans black. May be the other way and may vary on the sensor.*/

}

void go_left(){
 digitalWrite(DIR1, HIGH);  /*Left means that the left motor should go opposite/slower than the right motor to make a turn, 
                             take the go_forward directions as reference! */
  digitalWrite(DIR2, HIGH); 
  analogWrite(PWM1, 110); 
  analogWrite(PWM2, 110);
 /* delay(150);*/
}

void go_right(){
  digitalWrite(DIR1, LOW); /*Same logic used at right turns! Right motor should go opposite/slower than the right motor! :)*/
  digitalWrite(DIR2, LOW); 
  analogWrite(PWM1, 110);
  analogWrite(PWM2, 110);
 /* delay(150); */


}
void go_forward(int speed){
  
  digitalWrite(DIR1, HIGH); /*Use this as reference for directions! Here, the left motor goes forward if placed with the poles facing inwards.*/
  digitalWrite(DIR2, LOW); /*Right motor goes forward if placed with the poles facing inwards*/
  analogWrite(PWM1, speed);
  analogWrite(PWM2, speed);

}

void brake(){
   digitalWrite(DIR1, LOW);
   digitalWrite(DIR2, HIGH);
   analogWrite(PWM1, 70);
   analogWrite(PWM2, 70);
   

}
