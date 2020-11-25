int in_port = 1;
int out_port = 2;
int sync_btn = 3;
int read_val = 0; // sensor
int t_delay = 10;
int len_components = 10;
int keep_val = 0;

int bytes[100];

int location = 0;

char h = HIGH;
char l = LOW;
char i = INPUT;
char o = OUTPUT;

void transmit(){
  int val = digitalRead(read_val);
  delay(t_delay*location);
  if(val == 1){
  digitalWrite(out_port, h);
  delay(t_delay/2);
  digitalWrite(out_port, l);
  }
  delay(t_delay*len_components);
}

void sync(int x){
    int val = 0;
    int val_1 = 0;
    val = digitalRead(sync_btn);
    while(val == 0){
      }
    if(val == 1){
      for(int i=0;i<x;i++){
        int aa = digitalRead(in_port);
        bytes[x-i] = aa;
      }
    }
    for(int i=0;i<x;i++){
      int bb = bytes[i];
      if(bb == 1){
        location = i;
      }
    }
    keep_val = 0;
  }

void pnmd(){
  pinMode(in_port,i);
  pinMode(out_port,o);
  pinMode(sync_btn,i);
  pinMode(read_val,i);
}

void setup() {
  // put your setup code here, to run once:
  pnmd();
  keep_val = 1;
  while(keep_val == 1){
  sync(len_components);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  transmit();
}
