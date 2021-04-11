/*
Author: Karim Q.
Date: ~2019
*/
#define motorright1 3
#define motorright2 5
#define motorleft1 6
#define motorleft2 9
#define proxrightright 11
#define proxleftleft 12

int proxrightright2, proxleftleft2;

void setup() {
  pinMode(motorright1, OUTPUT); pinMode(motorright2, OUTPUT);
  pinMode(motorleft1, OUTPUT); pinMode(motorleft2, OUTPUT);
  pinMode(proxrightright, INPUT); pinMode(proxleftleft, INPUT);

  Serial.begin(9600);
}

void drive(int rightspeed1, int rightspeed2, int leftspeed1, int leftspeed2) {
  analogWrite(motorright1, rightspeed1); analogWrite(motorright2, rightspeed2);
  analogWrite(motorleft1, leftspeed1); analogWrite(motorleft2, leftspeed2);
}

void loop() {
  proxrightright2 = digitalRead(proxrightright);
  proxleftleft2 = digitalRead(proxleftleft);

  drive(255,0,255,0);

  if(proxleftleft2==LOW && proxrightright2==HIGH) {
    drive(0,0,255,0);
  }

  if(proxleftleft2==HIGH && !proxrightright==LOW) {
    drive(255,0,0,0);
  }
}
