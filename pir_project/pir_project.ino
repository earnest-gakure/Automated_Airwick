/*Automated Airwick project */
//STEP 1 :making 5 counts each with an interval of 5sec
//STEP 2 :making the counts in 3min else count = 0 
#define COUNT 5

const int interval = 2000;
const int min_counter = 60000;
// Set GPIOs for LED and PIR Motion Sensor
const int led = 2;
const int motionSensor = 27;

// Timer: Auxiliary variables

long int current_time;
long int previous_trigger= 0;
long int three_min_counter = 0;
int motion_count = 0;
int state ;
//function to turn on and of the LED 
void led_on(){
  if(motion_count >= COUNT &&  (current_time - three_min_counter < min_counter )){
      digitalWrite(led,HIGH);
       Serial.println("Detected Motion");
        motion_count = 0;
        three_min_counter = millis();
  }
 else if(current_time - three_min_counter > min_counter ){
  motion_count = 0;
  three_min_counter = millis();
    Serial.println(" Counter took longer than 1 minute ");
 }
}
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor,INPUT_PULLUP);

  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  current_time = millis();
 state = digitalRead(motionSensor);
 if(state == HIGH){
   if(state == HIGH && (current_time - previous_trigger>= interval)){
    motion_count ++;
     previous_trigger = millis();
     
       led_on();
    } 

 }else{
  digitalWrite(led ,LOW);
  Serial.println("Motion stoped");
 }
}
