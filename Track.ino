/*
Author: Karim Q.
Date: ~2019
*/
void setup() {
  pinMode(4,INPUT); //right ps  
  pinMode(7,INPUT); //left ps
  pinMode(A3,INPUT); //bw
  pinMode(3,OUTPUT); //mtr 1 r
  pinMode(5,OUTPUT); //mtr 1 r
  pinMode(9,OUTPUT); //mtr 2 l
  pinMode(10,OUTPUT); //mtr 2 l
}

void loop() {
  static int psr,psl,bw;
  static int ACC=185;

  static bool tf1=true;
  static bool tf2=false;
  static bool tf3=false;

  psr=digitalRead(4);
  psl=digitalRead(7);
  bw=analogRead(A3);

  if(psr==HIGH && psr==HIGH) {
    analogWrite(3,ACC); analogWrite(5,0);
    analogWrite(9,ACC); analogWrite(10,0);
  }

  if(psr==LOW && psr==HIGH) {
    analogWrite(3,180); analogWrite(5,0);
    analogWrite(9,0); analogWrite(10,0);

    ACC=185;
  }

  if(psr==HIGH && psr==LOW) {
    analogWrite(3,0); analogWrite(5,0);
    analogWrite(9,180); analogWrite(10,0);

    ACC=185;
  }    

  //CHALLENGES BEGIN 
  // if(bw==1023 && tf1==true && tf2==false && tf3==false) {
  //   analogWrite(3,0); analogWrite(5,0);
  //   analogWrite(9,0); analogWrite(10,0);

  //   delay(5000);

  //   tf1==false;tf2==true;

  //   ACC=185;
  // } 

  // if(bw==1023 && tf1==false && tf2==true && tf3==false) {
  //   analogWrite(3,ACC); analogWrite(5,0);
  //   analogWrite(9,ACC); analogWrite(10,0);

  //   tf2==false; tf3==true;
  // }

  // if(bw==1023 && tf1==false && tf2==false && tf3==true) {
  //   analogWrite(3,0); analogWrite(5,0);
  //   analogWrite(9,0); analogWrite(10,0);

  //   delay(3000);

  //   tf3==false;

  //   ACC=185;
  // }
  //CHALLENGES END

  if(ACC<256){
    ACC=ACC+10;
  }
}
