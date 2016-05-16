//#include <frequencyToNote.h>
//#include <MIDIUSB.h>
//#include <pitchToNote.h>

int numrows = 2;
int numcols = 2;
int fpin = 2;
int lpin = 5;
int trig = 0;
int lasttrig = 0;


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

void Trigger(int fpin, int lpin, int numrows, int numcols) {
  for(int i = fpin; i <= (fpin + (numrows - 1)); i++){
    if (digitalRead(i) == LOW){
      delay(5);
      for(int n = (lpin - (numcols - 1)); n <= lpin; n++){
        pinMode(n, INPUT_PULLUP);
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
        if (digitalRead(n) == LOW){
          trig = i * n;
        }
        pinMode(n, OUTPUT);
        digitalWrite(n, LOW);
        pinMode(i, INPUT_PULLUP);
      }
    }
  }
}
    
void loop() {
  Trigger(fpin,lpin,numrows,numcols);
  if( trig != lasttrig){
    Serial.println(trig); 
    //SEND MIDI HERE!  
  }
  lasttrig = trig;
  trig = 0;
  delay(5);
}






