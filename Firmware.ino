
// Include Libraries
#include "DCMDriverL298.h"
#include "NewPing.h"


// Pin Definitions
//FRONT
#define senorFront_PIN_TRIG	8
#define senorFront_PIN_ECHO	9
//LEFT
#define senorLeft_PIN_TRIG	7
#define senorLeft_PIN_ECHO	6
//RIGHT
#define senorRight_PIN_TRIG	4
#define senorRight_PIN_ECHO	5

#define motors_PIN_INT1	13
#define motors_PIN_INT2	12
#define motors_PIN_ENA	10

#define motors_PIN_INT3	2
#define motors_PIN_INT4	3
#define motors_PIN_ENB	11
#define speed1s 55
#define speed2s 50
#define wallL 30
#define wallR 30
#define wallF 10
#define max 300

// Global variables and defines
int speed1 = speed1s;
int speed2 = speed2s;
int key = 0;
int rightArr[3] = {110, 10, 11};
int leftArr[5] = {110, 10, 0, 1, 100};
int isTurning = 0;


// object initialization
NewPing senorFront(senorFront_PIN_TRIG, senorFront_PIN_ECHO, max);
NewPing senorLeft(senorLeft_PIN_TRIG, senorLeft_PIN_ECHO, max);
NewPing senorRight(senorRight_PIN_TRIG, senorRight_PIN_ECHO, max);

DCMDriverL298 motors(motors_PIN_ENA,motors_PIN_INT1,motors_PIN_INT2,motors_PIN_ENB,motors_PIN_INT3,motors_PIN_INT4);

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(115200);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
}


void loop() 
{
    // int senorFrontDist = senorFront.ping_cm(); //c
    // int senorRightDist = senorRight.ping_cm(); //r
    // int slowSpeed1 = speed1/2 + 10;
    // int slowSpeed2 = speed2/2 + 10;
    // Serial.println(isLeft());
    // Serial.println(isRight());
    // Serial.println(isFront());
    key = genKey();
    isTurning = 0;
    isTurning += motorLeftOn(key);
    isTurning += motorRightOn(key);
    if (isTurning == 1)
    {
      delay(500);
      motors.setMotorA(speed1, 0);
      motors.setMotorB(speed2, 0);
      delay(1000);     
    }
    Serial.println(key);
}
int genKey()
{
  int key = 0;
  if (isLeft())
    key += 10;
  if (isRight())
    key += 100;
  if (isFront())
    key += 1;
  return key;
}

int motorLeftOn(int key)
{
  int flag = 0;

  for (int i = 0; i < 5; i++)
  {
    if (key == leftArr[i])
    {
      flag = 1;
    }
  }

  if (flag == 1)
  {
    // Serial.println("LEFT");
    motors.setMotorA(speed1, 0);
  }
  else
    motors.stopMotorA();

  return flag;    
}

int motorRightOn(int key)
{
  int flag = 0;

  for (int i = 0; i < 3; i++)
  {
    if (key == rightArr[i])
    {
      Serial.println(key);
      flag = 1;
    }
  }
  
  if (flag == 1)
  {
    // Serial.println("RIGHT");
    motors.setMotorB(speed2, 0);
  }
  else
    motors.stopMotorB();
  return flag;
}

bool isLeft()
{
  int senorLeftDist = senorLeft.ping_cm();
  if (senorLeftDist < wallL)
  {
    return true;
  }
  return false;
}

bool isRight()
{
  int senorRightDist = senorRight.ping_cm();;
  if (senorRightDist < wallR)
  {
    return true;
  }
  return false;
}

bool isFront()
{
  int senorFrontDist = senorFront.ping_cm();
  if (senorFrontDist < wallF)
  {
    return true;
  }
  return false;
}