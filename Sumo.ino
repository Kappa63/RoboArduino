/*
Author: Karim Q.
Date: ~2019
*/
#define interrupt 2
#define IRsideR 10
#define IRsideL 12
#define IRmidR 8
#define IRmidL 7

#define bwR 11
#define bwL 4

#define mtr1R 3
#define mtr2R 5
#define mtr1L 6
#define mtr2L 9

#define Bswitch 13

int orimil = 0;
int searchinterval = 500;
int i = 0;
int count;
int k = 0;

int raiseS = 200;

char flag = "R";

int flag2 = 0;

void setup() {
  pinMode(IRsideR, INPUT); pinMode(IRsideL, INPUT); 
  pinMode(IRmidR, INPUT); pinMode(IRmidL, INPUT);

  pinMode(bwR, INPUT); pinMode(bwL, INPUT);

  pinMode(mtr1R, OUTPUT); pinMode(mtr2R, OUTPUT);
  pinMode(mtr1L, OUTPUT); pinMode(mtr2L, OUTPUT);

  // pinMode(interrupt, INPUT_PULLUP);
  // attachInterrupt (digitalPinToInterrupt (interrupt), interfunc, LOW);

  Serial.begin(9600);
}

void interfunc() {
  digitalWrite(mtr1R, HIGH); analogWrite(mtr2R, 20);
  analogWrite(mtr1L, 20); digitalWrite(mtr2L, HIGH);

  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  //delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  //delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  //delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  //delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  
  stopA();
}

void formove(int right, int left) {
  analogWrite(mtr1R, right); digitalWrite(mtr2R, HIGH);
  analogWrite(mtr1L, left); digitalWrite(mtr2L, HIGH);
}

void stopA() {
  digitalWrite(mtr1R, HIGH); digitalWrite(mtr2R, HIGH);
  digitalWrite(mtr1L, HIGH); digitalWrite(mtr2L, HIGH);
}

void back(int backT) {
  digitalWrite(3, HIGH); analogWrite(5, 20);
  digitalWrite(6, HIGH); analogWrite(9, 20);

  delay(backT);
}

void TurningL(int TurnT) {
  digitalWrite(mtr1R, HIGH);
  analogWrite(mtr2R, 20);
  analogWrite(mtr1L, 20);
  digitalWrite(mtr2L, HIGH);

  delay(TurnT);
}

void TurningR(int TurnT) {
  analogWrite(mtr1R, 20); digitalWrite(mtr2R, HIGH);
  digitalWrite(mtr1L, HIGH); analogWrite(mtr2L, 20);

  delay(TurnT);
}

void search() {
  unsigned long curmil = millis();

  if (curmil - orimil >= searchinterval && flag == 'R') {
    flag = 'L';
    orimil = curmil;
    count = count + 1;
  }

  if (curmil - orimil >= searchinterval && flag == 'L') {
    flag = 'R';
    orimil = curmil;
    count = count + 1;
  }

  if (flag == 'R') {
    formove(200, 20);
  }

  if (flag == 'L') {
    formove(20, 200);
  }

  if (count == 5) {
    TurningR(220);
    orimil = curmil;
    count = 0;
  }
}

void loop() {
  int IRsideRread = digitalRead(IRsideR);
  int IRsideLread = digitalRead(IRsideL);
  int IRmidRread = digitalRead(IRmidR);
  int IRmidLread = digitalRead(IRmidL);

  int Bswitchread = digitalRead(Bswitch);

  int BwRread = digitalRead(bwR);
  int BwLread = digitalRead(bwL);

  Serial.print(BwRread);
  Serial.println(BwLread);

  formove(100,100);

  // if (BwRread && BwLread) {
  //   if (Bswitchread == LOW) {
  //     for (k; k < 2; k++) {
  //       raiseS = millis();
  //     }
  //     unsigned long raisecounter = millis();
  //     if (raisecounter - raiseS >= 500) {
  //       raiseS = raisecounter;
  //       back(300);
  //       stopA();
  //     }
  //   }
  //   else {
  //     k = 0;

  //     if (!IRmidRread || !IRmidLread) {
  //       formove(20, 20);
  //     }

  //     if (IRmidRread && !IRmidLread && IRsideRread && !IRsideLread) {
  //       formove(255, 20);
  //       flag = 'L';
  //     }

  //     if (IRmidRread && IRmidLread && IRsideRread && !IRsideLread) {
  //       TurningR(200);
  //       flag = 'L';
  //     }

  //     if (!IRmidRread && IRmidLread && !IRsideRread && IRsideLread ) {
  //       formove(20, 255);
  //       flag = 'R';
  //     }

  //     if (!IRmidRread && IRmidLread && !IRsideRread && IRsideLread ) {
  //       TurningL(200);
  //       flag = 'R';
  //     }

  //     if (IRmidRread && IRmidLread && IRsideRread && IRsideLread) {
  //       search();
  //     }
  //   }
  // }

  if (BwLread == LOW) {
    stopA();
    delay(700);
    back(400);
    TurningL(350);
  }

  if (BwRread == LOW) {
    stopA();
    delay(700);
    back(400);
    TurningR(350);
  }
}

