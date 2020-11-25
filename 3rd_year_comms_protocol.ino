
char h = HIGH;
char l = LOW;
char i = INPUT;
char o = OUTPUT;

int component_list[100];
int component_read[100];

int sync_comp = 4; // sync end pin is digitil pin 4 PD4
int rx_tx = 2; // rf module pin is digital pin 2 PD2
int power = 7; // power pin is digital pin 7 PD7
int led_1 = 8; // binary 1 is digital pin 8 PB0
int led_0 = 9; // binary 0 is digital pin 9 PB1
int led_sync = 10; // syned comp is digital pin 10 PB2
int led_comp = 11; // sync complete is digital pin 11 PB3

int latching(){
   int latch = 0;
   for(int i=50;i<2000;i++){
      latch = digitalRead(rx_tx);
   }
      if(latch == 1){
   return latch;
      }
   if(latch == 0){
      return 0;
   }
}

void sync(int x){
   for(int i = 0;i<x;i++){
      int read_val = 0;
      read_val = latching();
      if(read_val == 1){
        component_list[i] = i;
        digitalWrite(led_sync, h);
        delay(200);
        digitalWrite(led_sync, l);
      }else{
        i = i-1;
      }
      int sync_val = digitalRead(sync_comp);
      if(sync_val == 1){
        i = x;
         digitalWrite(led_comp, h);
         delay(200);
         digitalWrite(led_comp, l);
         digitalWrite(led_sync, l);
      }
    delay(2000);
   }
}

void rd_trans(int x){
   for(int i=0;i<x;i++){
      int read_val = 0;
      read_val = digitalRead(rx_tx);
      component_read[i] = read_val;
      delay(100);
   }
}

void read_array_clear(int x){
   for(int i = 0;i<x;i++){
      component_read[i] = 0;
   }
}

void pnmode(){
   pinMode(sync_comp, i);
   pinMode(rx_tx, i);
   pinMode(led_0, o);
   pinMode(led_1, o);
   pinMode(power, o);
   pinMode(led_sync, o);
   pinMode(led_comp, o);
}

void led_out(){
   for(int i=0;i<8;i++){
      int val = component_read[i];
      if(val == 1){
      digitalWrite(led_0, l);
   digitalWrite(led_1, h);
      }else if(val == 0){
      digitalWrite(led_1, l);
   digitalWrite(led_0, h);
      }
      delay(1000);
      }
   }

void setup () {
   pnmode();
   sync(8);
   Serial.begin(9600);
}

void loop() {
   for(int i=0;i<8;i++){
      Serial.print(component_list[i]);
   }
   Serial.println("Read Values");
   rd_trans(8);
   for(int i=0;i<8;i++){
      Serial.print(component_read[i]);
   }
   led_out();
   read_array_clear(8);
   Serial.println("________________");
}
