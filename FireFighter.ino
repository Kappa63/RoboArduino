/*
Author: Karim Q.
Date: ~2019
*/
#define RM1 3
#define RM2 5
#define LM1 6
#define LM2 9
#define IRR 2
#define IRL 10
#define fan 11
#define H1 A1
#define H2 A2
#define H3 A3
#define H4 A4
#define H5 A5

void setup() {
  pinMode(RM1, OUTPUT); pinMode(RM2, OUTPUT);
  pinMode(LM1, OUTPUT); pinMode(LM2, OUTPUT);
  pinMode(IRR, INPUT); pinMode(IRL, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(H1, INPUT); pinMode(H2, INPUT);
  pinMode(H3, INPUT);
  pinMode(H4, INPUT); pinMode(H5, INPUT);

  Serial.begin(9600);

  digitalWrite(fan, LOW);
}

void drive(int RM1S, int RM2S, int LM1S, int LM2S) {
  analogWrite(RM2, RM1S); analogWrite(RM1, RM2S);
  analogWrite(LM2, LM1S); analogWrite(LM1, LM2S);
}

void loop() {
  int IRRR = digitalRead(IRR); int IRLR = digitalRead(IRL);
  int H1R = analogRead(H1); int H2R = analogRead(H2);
  int H3R = analogRead(H3);
  int H4R = analogRead(H4); int H5R = analogRead(H5);

  if (H4R > H1R && H4R > H2R && H4R > H3R || H5R > H1R && H5R > H2R && H5R > H3R) {
    drive(200, 0, 0, 200);
    digitalWrite(fan, LOW);
  }

  if (H1R > H3R && H1R > H4R && H1R > H5R || H2R > H3R && H1R > H4R && H1R > H5R) {
    drive(0, 200, 200, 0);
    digitalWrite(fan, LOW);
  }

  if (H3R > H1R && H3R > H2R && H3R > H4R && H3R > H5R) {
    if (H3R > 480) {
      drive(0, 0, 0, 0);
      analogWrite(fan, 100);
    }

    if (H3R < 480) {
      drive(160, 0, 160, 0);
      digitalWrite(fan, LOW);
    }
  }

  if (H1R < 280 && H2R < 280 && H3R < 280 && H4R < 280 && H5R < 280) {
    digitalWrite(fan, LOW);

    if (IRRR && IRLR) {
      drive(180, 0, 180, 0);
    }

    if (IRRR && !IRLR) {
      drive(180, 0, 0, 0);
    }

    if (!IRRR && IRLR) {
      drive(0, 0, 180, 0);
    }
  }
}
