const int SIG = 2; // Pin SIG
const int EN = 7; // Pin EN
const int controlPin[4] = {3, 4, 5, 6}; // Pin kontrol multiplexer
const char* tipeRelay = "HIGH"; // tipe relay posisi COM ON
const char* relayOn;
const char* relayOff;
int waktuDelay = 500;

const int petaBiner[16][4] = {
  // s0, s1, s2, s3     channel
    {0,  0,  0,  0}, // 0
    {1,  0,  0,  0}, // 1
    {0,  1,  0,  0}, // 2
    {1,  1,  0,  0}, // 3
    {0,  0,  1,  0}, // 4
    {1,  0,  1,  0}, // 5
    {0,  1,  1,  0}, // 6
    {1,  1,  1,  0}, // 7
    {0,  0,  0,  1}, // 8
    {1,  0,  0,  1}, // 9
    {0,  1,  0,  1}, // 10
    {1,  1,  0,  1}, // 11
    {0,  0,  1,  1}, // 12
    {1,  0,  1,  1}, // 13
    {0,  1,  1,  1}, // 14
    {1,  1,  1,  1}  // 15
};

void setup() {
  if(strcmp(tipeRelay, "LOW") == 0){
    relayOn = "LOW";
    relayOff = "HIGH"; 
  } else if(strcmp(tipeRelay, "HIGH") == 0){
    relayOn = "HIGH";
    relayOff = "LOW";
  }
  // setel pin kontrol multiplexer dadi output
  for (int i = 0; i < 4; i++) {
    pinMode(controlPin[i], OUTPUT);
    digitalWrite(controlPin[i], relayOff); // Posisi awal Relay 
  }

  // setel pin sinyal (SIG) dadi output
  pinMode(SIG, OUTPUT);
  digitalWrite(SIG, LOW); // Posisi awal SIG Low

  // setel pin EN dadi output
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW); // Low = Murub, High = Mati

  Serial.begin(9600);
}

void loop() {
  Serial.println("Aturan 1 Murub Barengan 4, 5, 7, 8, 9");
  pattern1();
  Serial.println("=================");
  delay(waktuDelay);
  Serial.println("Aturan 2 Murub Ganti-gantian 15, 14, 10, 11");
  pattern2();
  Serial.println("=================");
  delay(waktuDelay);
  Serial.println("Aturan 3 Murub Ganti-gantian 0 - 15");
  pattern3();
  Serial.println("=================");
  delay(waktuDelay);
  Serial.println("Aturan 4 Murub Ganti-gantian 15 - 0");
  pattern4();
  Serial.println("=================");
  delay(waktuDelay);
  Serial.println("Aturan 5 Murub Barengan 1 karo 2");
  pattern5();
  Serial.println("=================");
  delay(2000);
}

void pattern1() {
  // Murub barengan Relay nomor 4, 5, 7, 8, 9
  for (int i = 0; i < 16; i++) {
    channelControl(i);
    if (i == 4 || i == 5 || i == 7 || i == 8 || i == 9) {
      digitalWrite(SIG, relayOn);
    } else {
      digitalWrite(SIG, relayOff);
    }
  }
}

void pattern2() {
  // Murub gantian Relay nomor 15, 14, 10, 11
  for (int i = 0; i < 16; i++) {
    channelControl(i);
    if (i == 15 || i == 14 || i == 10 || i == 11) {
      digitalWrite(SIG, relayOn); 
    } else {
      digitalWrite(SIG, relayOff); 
    }
  }
}

void pattern3() {
  // Relay murub gantian delay 0.5 detik urutane 0 - 15
  for (int i = 0; i < 16; i++) {
    channelControl(i);
    digitalWrite(SIG, relayOn); 
    delay(500); 
    digitalWrite(SIG, relayOff); 
  }
}

void pattern4() {
  // Relay murub gantian delay 0.5 detik urutane 15 - 0
  for (int i = 15; i >= 0; i--) {
    channelControl(i);
    digitalWrite(SIG, relayOn); 
    delay(500); 
    digitalWrite(SIG, relayOff); 
  }
}

void pattern5() {
  // Relay 0 karo 1 murub
  // Pateni Kabeh disit Relay kabehe
  for (int i = 0; i < 16; i++) {
    channelControl(i);
    digitalWrite(SIG, relayOff); //
  }
  
  channelControl(0);
  digitalWrite(SIG, relayOn); 
  
  channelControl(1);
  digitalWrite(SIG, relayOn); 
}


void channelControl(int relayChannel) {
  digitalWrite(controlPin[0], petaBiner[relayChannel][0]);
  digitalWrite(controlPin[1], petaBiner[relayChannel][1]);
  digitalWrite(controlPin[2], petaBiner[relayChannel][2]);
  digitalWrite(controlPin[3], petaBiner[relayChannel][3]); 
}
