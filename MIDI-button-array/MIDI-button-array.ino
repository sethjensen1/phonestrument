//#include <frequencyToNote.h>
//#include <MIDIUSB.h>
//#include <pitchToNote.h>

const int channel = 1;

int numrows = 4;
int numcols = 3;
int fpin = 2;
int lpin = 8;
int trig = 0;
int lasttrig = 0;
int lasty = 0;
int note = 0;


void setup() {
  Serial.begin(9600);

  for(int i = fpin; i <= lpin;i++){
    if (i <= (fpin + (numrows - 1))){
      pinMode(i,INPUT_PULLUP); 
    }
    if (i >= (lpin - (numcols - 1))){
      pinMode(i,OUTPUT);
      digitalWrite(i,LOW);
    }
  }
}
    
void loop() {
  /*Serial.print(digitalRead(2));
  Serial.print("      ");
  Serial.print(digitalRead(3));
  Serial.println();*/
  Trigger(fpin,lpin,numrows,numcols);
  delay(1);
  if( trig != lasttrig){
    Serial.println(trig);
    if(trig == 32){
      note = 60;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig == 28){
      note = 61;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig == 24){
      note = 62;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==72){
      note = 63;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==63){
      note = 64;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==54){
      note = 65;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==128){
      note = 66;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==112){
      note = 67;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==96){
      note = 68;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==200){
      note = 69;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==175){
      note = 70;
      usbMIDI.sendNoteOn(note,99,channel);
    }
    if(trig==150){
      note = 71;
      usbMIDI.sendNoteOn(note,99,channel);
    }
  }
  if(trig==0){
      usbMIDI.sendNoteOff(note,0,channel);
    }
  lasttrig = trig;
  trig = 0;
  /*if (lastx != trig[0] || lasty != trig[1]){
    Serial.print("(");
    Serial.print(trig[0]);
    Serial.print(",");
    Serial.print(trig[1]);
    Serial.print(")");
    Serial.println();
    delay(5);
  }
  //lastx = trig[0];
  //lasty = trig[1];*/
}



int Trigger(int fpin, int lpin, int numrows, int numcols) {

  for(int k = (lpin - (numcols - 1)); k <= lpin; k++){
        digitalWrite(k, LOW);
      } 
  for(int i = fpin; i <= (fpin + (numrows - 1)); i++){
    if (digitalRead(i) == LOW){
      for(int n = (lpin - (numcols - 1)); n <= lpin; n++){
        digitalWrite(n, HIGH);
      }
      for(int j = (lpin - (numcols - 1)); j <= lpin ; j++){
        digitalWrite(j, LOW);
        if (digitalRead(i) == LOW){
          trig = i * i * j;
        }
        digitalWrite(j,HIGH);
      }
    }
  }
}
