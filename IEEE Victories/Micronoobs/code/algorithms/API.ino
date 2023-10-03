#include "API.h"

float distancePerPulse = 0.1; 
volatile long encoderCountRight = 0,encoderCountLeft = 0; 
float distanceLeft = 0.0,distanceRight = 0.0;

NewPing sonar[3] = {NewPing(TRIGGER_R, ECHO_R, MAX_DISTANCE),
                     NewPing(TRIGGER_M, ECHO_M, MAX_DISTANCE),
                     NewPing(TRIGGER_L, ECHO_L, MAX_DISTANCE)};

void Forward(void)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 
}
void Stop(void)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Right(void)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void Left(void)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

bool wallFront() {
  if( (getDistance(sonar[S_MIDDLE])) < 20)
    return 1;
  else
    return 0;
}

bool wallRight() {
  if( (getDistance(sonar[S_RIGHT])) < 20)
    return 1;
  else
    return 0;
}


bool wallLeft() {
  if( (getDistance(sonar[S_LEFT])) < 20)
    return 1;
  else
    return 0;
}

// Using encoders
void moveForward() {
  //Reset counter
  encoderCountLeft = encoderCountRight = 0;

  distanceLeft = encoderCountLeft * distancePerPulse;
  distanceRight = encoderCountRight * distancePerPulse;
  while((distanceLeft < 9) || (distanceRight < 9)){
    Forward();
  distanceLeft = encoderCountLeft * distancePerPulse;
  distanceRight = encoderCountRight * distancePerPulse;
  }
  Stop();
}

void turnRight() {
    Right();
    delay(100);
}

void turnLeft() {
    Left();
    delay(100);
}
int orientation(int orient, char turning)
{
  if (turning== 'L'){
    orient-=1;
    if (orient==-1)
      orient=3;
  }else if(turning== 'R'){
    orient+=1;
    if (orient==4)
      orient=0;
  }else if(turning== 'B'){
    if (orient==0)
      orient=2;
    else if(orient==1)
      orient=3;
    else if(orient==2)
      orient=0;
    else if (orient==3)
      orient=1;
  }
    return orient;
}
void updateCoordinates(int orient, int *new_x, int *new_y)
{

  if(orient == 0)
    *new_y += 1;
  else if(orient == 1)
    *new_x += 1;
  else if(orient == 2)
    *new_y -= 1;
  else if(orient == 3)
    *new_x -= 1;
}
void EncoderLeftHandler() {
  // Read the state of channel A and B
  uint8_t stateA = digitalRead(encoderLeft_A);
  uint8_t stateB = digitalRead(encoderLeft_B);
  // Determine the direction of rotation
  if (stateA == stateB) {
    encoderCountLeft++; // Clockwise rotation
  } else {
    encoderCountLeft--; // Counterclockwise rotation
  }
}
void EncoderRightHandler() {
  // Read the state of channel A and B
  uint8_t stateA = digitalRead(encoderRight_A);
  uint8_t stateB = digitalRead(encoderRight_B);
  // Determine the direction of rotation
  if (stateA == stateB) {
    encoderCountRight++; // Clockwise rotation
  } else {
    encoderCountRight--; // Counterclockwise rotation
  }
}
uint16_t getDistance(NewPing sonar){
  uint32_t sum = 0;
  for(uint8_t i = 0 ;i<AVG_NUM;i++){
    sum += sonar.ping_cm();
    delay(30);                    
  }
  return (sum/AVG_NUM);
}