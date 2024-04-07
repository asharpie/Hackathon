#include<NewPing.h>
#include <AFMotor.h>
AF_DCMotor topleftmotor(1);
AF_DCMotor bottomleftmotor(2);
AF_DCMotor bottomrightmotor(4);
AF_DCMotor toprightmotor(3);


//trigpin-output
//echopin-input


//trigger,echo,max_cm_distance
// defines variables
long duration;
int distance;
int speed = 150;

NewPing sonarForward(A0, A1, 1000);
NewPing sonarLeft(A2, A3, 1000);
NewPing sonarRight(A4, A5,1000);
void setup() {
  
  Serial.begin(9600); // Starts the serial communication
  topleftmotor.setSpeed(200);
	topleftmotor.run(RELEASE);
  bottomleftmotor.setSpeed(200);
	bottomleftmotor.run(RELEASE);
  bottomrightmotor.setSpeed(200);
	bottomrightmotor.run(RELEASE);
  toprightmotor.setSpeed(200);
	toprightmotor.run(RELEASE);
}
void loop() {

  int randint = random(2);
  //Serial.print(randint);
  double durationforward = sonarForward.ping_cm(1000);
  double durationleft = sonarLeft.ping(1000);
  double durationright = sonarRight.ping(1000);
  //Serial.println(durationforward);
  // Calculating the distance
  double distanceforward = durationforward * 0.034 / 2;
  double distanceleft = durationleft * 0.034 / 2;
  double distanceright = durationright * 0.034 / 2;
  //Serial.println(distanceforward,distanceleft,distanceright);


  if(distanceforward>=40){
    driveForward(2);
    distanceforward = sonarForward.ping(1000)*0.034/2;
  }


  if(distanceforward<3){
    double ping1 = sonarForward.ping(1000) * 0.034 / 2;
    double ping2 = sonarForward.ping(1000) * 0.034 / 2;
    double ping3 = sonarForward.ping(1000) * 0.034 / 2;
  //  Serial.println(distanceforward, distanceleft, distanceright);
    if(ping1<10&&ping2<10&&ping3<10){
      driveBackward(150);
      
      
    }
    
  }
  durationforward = sonarForward.ping(1000);
  durationleft = sonarLeft.ping(1000);
  durationright = sonarRight.ping(1000);
  // Serial.println(distanceforward, distanceleft, distanceright);
  //Serial.println(durationforward);
  // Calculating the distance
  distanceforward = durationforward * 0.034 / 2;
  distanceleft = durationleft * 0.034 / 2;
  distanceright = durationright * 0.034 / 2;
  if(randint == 1){
        if(distanceright>=50){
          turnRight(150);
        }
        else if(distanceleft>=50){
          turnLeft(150);
        }
        else{
          driveBackward(150);
        }
  }
  else{
    if(distanceleft>=50){
          turnLeft(150);
        }
        else if(distanceright>=50){
          turnRight(150);
        }
        else{
          driveBackward(150);
        }
  }
  durationforward = sonarForward.ping(1000);
  durationleft = sonarLeft.ping(1000);
  durationright = sonarRight.ping(1000);
  //Serial.println(durationforward, );
  // Calculating the distance
  distanceforward = durationforward * 0.034 / 2;
  distanceleft = durationleft * 0.034 / 2;
  distanceright = durationright * 0.034 / 2;
  
  
  if(distanceleft<20){
    if(distanceright>50){
      //turn right
      turnRight(100);
    }
    
  }
  if(distanceright<20){
    if(distanceleft>50){
      //turn left
      turnLeft(100);
    }
    
  }
  
  
}

void turnLeft(int i){
      topleftmotor.setSpeed(speed);
      toprightmotor.setSpeed(speed);
      bottomrightmotor.setSpeed(speed);
      bottomleftmotor.setSpeed(speed);
      topleftmotor.run(BACKWARD);
      toprightmotor.run(FORWARD);
      bottomrightmotor.run(FORWARD);
      bottomleftmotor.run(BACKWARD);
      delay(i);
}
void turnRight(int i){
      topleftmotor.setSpeed(speed);
      toprightmotor.setSpeed(speed);
      bottomrightmotor.setSpeed(speed);
      bottomleftmotor.setSpeed(speed);
      topleftmotor.run(FORWARD);
      toprightmotor.run(BACKWARD);
      bottomrightmotor.run(BACKWARD);
      bottomleftmotor.run(FORWARD);
      delay(i);
}
void driveForward(int i){
    topleftmotor.setSpeed(speed);
    toprightmotor.setSpeed(speed);
    bottomrightmotor.setSpeed(speed);
    bottomleftmotor.setSpeed(speed);
    topleftmotor.run(FORWARD);
    toprightmotor.run(FORWARD);
    bottomrightmotor.run(FORWARD);
    bottomleftmotor.run(FORWARD);
    delay(i);
}
void driveBackward(int i){
      topleftmotor.setSpeed(speed);
      toprightmotor.setSpeed(speed);
      bottomrightmotor.setSpeed(speed);
      bottomleftmotor.setSpeed(speed);
      topleftmotor.run(BACKWARD);
      toprightmotor.run(BACKWARD);
      bottomrightmotor.run(BACKWARD);
      bottomleftmotor.run(BACKWARD);
      delay(i);
}
  