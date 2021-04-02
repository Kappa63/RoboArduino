int orimil = 0;
int searchinterval = 1000;
int i=0;
int count=0;

char flag ='L';

void setup() {
  pinMode(2, INPUT);
  pinMode(10, INPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
}

void drive(int mtr1Rs, int mtr2Rs, int mtr1Ls, int mtr2Ls) {
  analogWrite(3, mtr1Rs);
  analogWrite(5, mtr2Rs);
  analogWrite(6, mtr1Ls);
  analogWrite(9, mtr2Ls);
}

void autostart() {
  drive(0, 255, 255, 0);
  delay(350);
  drive(255, 0, 112, 0);
  delay(1800);
  drive(255, 0, 0, 255);
  delay(900);
  drive(255, 0, 255, 0);
  delay(1000);
  drive(0,0,0,0);
}

void interfunc() {
  drive(0,255,255,0);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000); delayMicroseconds(16000);
  drive(0,0,0,0);  
}

void loop() {
  if(i==0){
    interfunc();
    i=1;
  }

  // unsigned long curmil = millis();

  // if (curmil - orimil >= searchinterval && flag == 'R') {
  //   flag = 'L';
  //   orimil = curmil;
  //   count=count+1;
  // }

  // if (curmil - orimil >= searchinterval && flag == 'L') {
  //   flag = 'R';
  //   orimil = curmil;
  //   count=count+1;
  // }

  // if (flag == 'R') {
  //   drive(30, 0, 180, 0);
  // }

  // if (flag == 'L') {
  //   drive(180, 0, 30, 0);
  // }

  // if (count == 5) {
  //   drive(0,255,255,0);
  //   delay(500);
  //   orimil=curmil;
  //   count=0;
  // }
}
