/*Automated Airwick project */
//STEP 1 :making 5 counts each with an interval of 5sec
//STEP 2 :making the counts in 3min else count = 0 
//STEP 3 :take care of not more than two consecutive spraying in lesss than 20 min
#define COUNT 5
#define SPRAY_MAX 2
const int interval = 2000;      //interval for before next trigger 
const unsigned int min_counter = 60000;  //interval for max time up to which the 5 counts should be achieved 
const unsigned long int spray_interval = 180000 ;  //20 min counter 
// Set GPIOs for LED and PIR Motion Sensor
const int led = 2;               
const int motionSensor = 27;       //PIR pin 

// Timer: Auxiliary variables

long int current_time;
long int previous_trigger= 0;        //keep tack of time when last trigger happend 
long int three_min_counter = 0;
long int twenty_min_counter = 0;    
int motion_count = 0;                //keep track of no of motion detected 
int spray_count = 0;                //keep track of no of spraying done
int state ;
//function to turn on and of the LED 
void led_on(){
  if(motion_count > COUNT &&  (current_time - three_min_counter < min_counter )){
       Serial.println("Detected Motion");
        motion_count = 0;
        three_min_counter = millis();
        
        if(spray_count < SPRAY_MAX && (current_time - twenty_min_counter  < spray_interval)){
          digitalWrite(led , HIGH);
          spray_count ++ ;
          twenty_min_counter = millis();
        } else if( current_time - twenty_min_counter > spray_interval){
          spray_count = 0 ;
          twenty_min_counter = millis();
        }
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
