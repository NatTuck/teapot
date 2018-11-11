#include <Servo.h>

Servo turn;
Servo velo;

int turn_pos = 90;
int velo_pos = 90;

/* Serial protocol:
 *  - Line oriented
 *  - Line is command char, space, argument.
 *  - Commands are:
 *    - 't': Set turn
 *    - 'v': Set velocity
 */

char buff[20];
char bptr = 0;

void read_serial() {
  buff[bptr++] = Serial.read();
  if (buff[bptr-1] == '\n') {
    buff[bptr] = 0;

    String temp = String(buff + 2);
    int value = temp.toInt();
    
    switch (buff[0]) {
    case 't':
      turn_pos = value;
      Serial.print("set turn: ");
      Serial.println(value);
      break;
    case 'v':
      velo_pos = value; 
      Serial.print("set velo: ");
      Serial.println(value);
      break;
    default:
      Serial.println("unknown command");
    }
    
    bptr = 0;
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  turn.attach(2);
  velo.attach(3);
}

void loop() {
  if (Serial.available() > 0) {
    read_serial();
  }

  turn.write(turn_pos);
  velo.write(velo_pos); 
  
  delay(100);
}
