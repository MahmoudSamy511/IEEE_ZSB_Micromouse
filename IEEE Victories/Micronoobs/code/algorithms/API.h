#ifndef API_H_
#define API_H_
#include <string>
#include <NewPing.h>
// Pin definitions
/*****************Motors**************/
// Right
#define ENA             32
#define IN1             33
#define IN2             25
// Left     
#define ENB             19
#define IN3             5
#define IN4             18
/*****************UltraSonic**************/
#define  S_RIGHT          0
#define  S_MIDDLE         1
#define  S_LEFT           2

#define MAX_DISTANCE    250 
#define AVG_NUM         5

#define ECHO_R          5
#define TRIGGER_R       12
#define ECHO_M          6
#define TRIGGER_M       13
#define ECHO_L          25
#define TRIGGER_L       26
/*****************Encoders**************/
#define  encoderResolution  7 

#define encoderRight_A  25 
#define encoderRight_B  26 
#define encoderLeft_A   23
#define encoderLeft_B   22

/*******************APIs****************/
int orientation(int orient, char turning);
void updateCoordinates(int orient, int *new_x, int *new_y);
bool wallFront();
bool wallRight();
bool wallLeft();
void moveForward();
void turnRight();
void turnLeft();
// Motors APIs
void Forward(void);
void Stop(void);
void Right(void);
void Left(void);
void EncoderRightHandler();
void EncoderLeftHandler();
uint16_t getDistance(NewPing sonar);

#endif