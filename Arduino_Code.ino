
#define false 0
#define true 1
#define bool byte


void setup(){
  pinMode(52,INPUT);
  Serial.begin(9600); 
}

bool counting_pulse = false;
int stime = millis();

void loop(){
  if(digitalRead(52)){
    if(counting_pulse){
      pulse(millis() - stime);
      counting_pulse = false;
    }
    else if(millis() - stime > 150){
      pulse(-1);   
      stime = millis();
    }
  } 
  else {
    if(counting_pulse){
      if(millis() - stime > 150){
        pulse(-2); 
        stime = millis();
      }
    }
    else{
      counting_pulse = true;
      stime = millis();
    } 

  }
 // Serial.println(digitalRead(52));
}

int num = -1;
int cha = false;
int hang = true;
void pulse(int time){
  Serial.println(time);
  if(time < 80 && time > 40){
    hang = false;
    if(num == -1){
     num = 1;
     cha = true;
    }else if(num == 9){
     num = 0; 
    }else{
     num++; 
    }
    Serial.print(num);
  }
  if(time == -1 && cha){
    cha = false;
    num = -1;
    Serial.print("c");
  }
  
  if(time == -2 && !hang){
    hang = true;
    num = -1;
    Serial.print("d");
  }
}

