int levels[48] = {
  127,  144,  160,  176,  191,  205,  217,  228,  237,  
  245,  250,  253,  255,  253,  250,  245, 237,  228,  
  217,  205,  191,  176,  160,  144,  127,  110,   94,   
  78,   63,   49,   37,   26, 17,    9,    4,    1,    
  0,    1,    4,    9,   17,   26,   37,   49,   63,   
  78,   94,  110};
// These are the pins used to drive the motor. 
int pinA = 9; 
int pinB = 10; 
int pinC = 11; 
int step = 0;               
// Keeps track of what pulse width to use 
unsigned long lastTime = 0; // the time in micros since last 
int period = 3000;          // set motor speed by defining time between steps 

void setup() {   
  // Set pins as digital outputs   
  pinMode(pinA, OUTPUT);   
  pinMode(pinB, OUTPUT);   
  pinMode(pinC, OUTPUT);   // Set all the pins LOW   
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW); 
} 

void loop() {   // Check if it is time for the next step   
  if ((micros() - lastTime) >= period)   {     
    // Next three lines send pulse width value for this step.     
    analogWrite(pinA, levels[step]);     
    analogWrite(pinB, levels[(step + 16) % 48]);     
    analogWrite(pinC, levels[(step + 32) % 48]);     
    // Add one to set (% 48 rolls step back to 0 after it fits 47)     
    step = (step + 1) % 48;     // make note of current time     
    lastTime = micros();     // ramps up the speed     
    if (period > 200)     
    {       
      period -= 1; 
      // make speed faster (the period between steps smalled)   
    }   
  } 
} 
