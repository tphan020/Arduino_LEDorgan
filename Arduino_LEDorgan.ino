/*
 * LED ORGAN -> Red Green Blue LED's
 */
 
int analogPin=0;       
int strobePin=2;      
int resetPin=3;       
int ledred=9;         //RED LED
int ledgreen=10;      //GREEN LED
int ledblue=11;       //BLUE LED
int spectrumValue[7]; //Integer variable to store the 10bit values of the frequency bands
int filter=80;        //Noise filter

void setup(){  
  
  Serial.begin(9600);         
  pinMode(analogPin, INPUT);  
  pinMode(strobePin, OUTPUT); 
  pinMode(resetPin, OUTPUT);  
  pinMode(ledred, OUTPUT);    
  pinMode(ledblue, OUTPUT);   
  pinMode(ledgreen, OUTPUT);  
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop(){
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);              //change from high to low starts the output of the mutliplexer from the beginning 
  for (int i=0;i<7;i++){                    //for loop goes through this cycle 7 times to get the values for each frequency band
    digitalWrite(strobePin, LOW);           //puts strobe pin low to output the frequency band
    delayMicroseconds(100);                  //wait until output value of MSGEQ7 can be measured
    spectrumValue[i]=analogRead(analogPin); //put analog DC value in the spectrumValue variable
    if (spectrumValue[i]<filter){ 
      spectrumValue[i]=0;}                  //if the received value is below the filter value it will get set to 0
    spectrumValue[i]=map(spectrumValue[i], 0,1023,0,255); //transform the 10bit analog input value to a suitable 8bit PWM value
    Serial.print(spectrumValue[i]);         //outputs the PWM value -> Serial Monitor
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);          //puts the strobe pin high to get ready for the next cycle
  }
  Serial.println();
  analogWrite(ledred,spectrumValue[0]);   //outputs the 63Hz  Value for the RED LED
  analogWrite(ledred,spectrumValue[1]);   //outputs the 160Hz PWM ValuePWM for the RED LED
  analogWrite(ledgreen,spectrumValue[3]); //outputs the 1kHz PWM Value for the GREEN LED
  analogWrite(ledgreen,spectrumValue[4]); //outputs the 2.5kHz PWM Value for the GREEN LED
  analogWrite(ledblue,spectrumValue[5]);  //outputs the 6.25kHz PWM Value for the BLUE LED
  analogWrite(ledblue,spectrumValue[6]);  //outputs the 16kHz PWM Value for the BLUE LED
}


