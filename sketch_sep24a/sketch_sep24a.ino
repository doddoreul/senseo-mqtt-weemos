int in1 = 7;
int in2 = 8;
int pushButton = 2;

int brew = 0;
int k;
int prev_k;
int is_brewing;
int is_pumping;

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:    

  pinMode(in1, OUTPUT);
  digitalWrite(in1, HIGH);
 
  pinMode(in2, OUTPUT);
  digitalWrite(in2, HIGH);

  pinMode(2, INPUT_PULLUP);

}
void loop() {
  k = !watchOrder();


  if (k != prev_k && k){ // run process
    brew = !brew;
    letsBrew(brew);
    prev_k = k; // store K to compare it and see if status has changed
    Serial.println(brew);
  } 
  
  Serial.print("is_brewing ");
  Serial.println(is_brewing);

  delay(500);
  
}

int watchOrder(){
  int val = digitalRead(pushButton);  // read input value
  return val;
}

void letsBrew(int status){
  
  if (status){ // brew coffee
    is_brewing = 1;
    
    heat(true);

    if (is_brewing){
      int temperature = (getTemp() >= 68);
      heat(temperature);

      if (temperature){
        pump(true);
      }
    }
    
  } else { // stop brewing
    is_brewing = 0;
    prev_k = 0;
    k = 0;
    if (is_brewing){
      //heat(false);
      //pump(false);
    }
    Serial.print("##");
    Serial.println(is_brewing);
  }
  
}

int getTemp(){
  return 68;
}

void heat(int status){
  if (status){ // heat water
      Serial.println("Heating...");
  } else { // stop heating
      Serial.println("Stop heating");
  }
}
  

void pump(int status){
  if (status){
    Serial.println("Pumping water");
    delay(5000);
    Serial.println("Pumping done");
  } else {
    Serial.println("stop pump");  
  }
  
  letsBrew(false); // coffee done, stop the process
}

