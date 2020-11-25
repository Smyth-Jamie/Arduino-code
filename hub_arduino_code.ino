//#include <LiquidCrystal.h>

//LiquidCrystal lcd(14,12,2,4,7,8);
char h = HIGH;
char l = LOW;
char i = INPUT;
char o = OUTPUT;

int component_list[100];
int component_read[100];

int sync_comp = 4; // sync end pin is digitil pin 4 PD4
int rx_tx = 0; // rf module pin is digital pin 2 PD2
int trans = 1; // transmit pin
int led1 = 2; // led binary 1
int led0 = 3; // led binary 0
int led_comp = 5; // led sync comp
int keep_val = 0;

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
      while(read_val == 0){
        read_val = latching();
      }
      if(read_val == 1){
        component_list[i] = i;
        for(int a=0;a<i-1;a++){
          component_list[a] = 0;
        }
          for(int b=0;b<x;b++){
            if(component_list[b] == 1){
              digitalWrite(trans, h);
              delay(10);
            }else{
              delay(10);
            }
          }
      }
      int sync_val = digitalRead(sync_comp);
      if(sync_val == 1){
        i = x;
      }
    delay(2000);
   }
  keep_val = 0;
  digitalWrite(led_comp,h);
  delay(1000);
  digitalWrite(led_comp,l);
}

void rd_trans(int x){
    int read_val = 0;
   for(int i=0;i<x;i++){
      read_val = 0;
      read_val = digitalRead(rx_tx);
      component_read[i] = read_val;
      delay(100);
   }
   for(int i=0;i<x;i++){
    if(component_read[i] == "1"){
     // lcd.print("error!");
     digitalWrite(led1,h);
     digitalWrite(led0,l);
    }else{
      //lcd.print("All good");
      digitalWrite(led1,l);
      digitalWrite(led0,h);
    }
    delay(1000);
   // lcd.clear();
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
   pinMode(trans, o);
   pinMode(led0,o);
   pinMode(led1,o);
}

void setup () {
   pnmode();
   keep_val = 1;
   while(keep_val == 1){
   sync(8);
   }
   Serial.begin(9600);
  // lcd.begin(16,2);
  // lcd.print("Hello_world!");
   delay(1000);
   //lcd.clear();
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
   read_array_clear(8);
   Serial.println("________________");
}
