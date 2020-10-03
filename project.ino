int button = 4;
int buzzer = 3;
int red_led = 7;
int green_led = 6;
int button_state = 0;
int lastStateButton = 1;
int ldr1 = A0;
int ldr2 = A1;
int ldr1_value = 0;
int ldr2_value = 0;
int personCounter = 0;


void setup()
{
 pinMode(button, INPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(red_led, OUTPUT);
 pinMode(green_led, OUTPUT);
 pinMode(A0, INPUT);
 pinMode(A1, INPUT); 
 Serial.begin(9600);
}

void loop()
{
  
  button_state = digitalRead(button);
  if (button_state != lastStateButton)      //here to check the button is pressed once
  {
    if (button_state == HIGH)
  {
    while (true)
    {
      //here to check if he will enter the room by the right LDR
      ldr2_value = analogRead(A0);
      ldr2_value = map(ldr2_value, 0, 1023, 0, 255);
      
      if (ldr2_value < 10 )
      {
       digitalWrite(green_led, HIGH);
        digitalWrite(buzzer, HIGH);
       delay(500);
       digitalWrite(green_led, LOW);
       digitalWrite(buzzer, LOW);
       personCounter +=1;
       if(personCounter >= 6 ){
               Serial.println("More than 5 persons in the room");
       }
       else{
       Serial.println(personCounter);
       }
        break;
      }
      //here to check if he will exit the room by the left LDR
      ldr1_value = analogRead(A1);
      ldr1_value = map( ldr1_value, 0, 1023, 0, 255);
      if (ldr1_value  < 10)
      {
       personCounter -=1;
        if (personCounter <= 0)       //to make sure the counter still zero not minus (-)
        {
          personCounter = 0;
        }
        Serial.println(personCounter);
       digitalWrite(red_led, HIGH);
        digitalWrite(buzzer, HIGH);
       delay(500);
       digitalWrite(red_led, LOW);
       digitalWrite(buzzer, LOW);
        break;
      }
    }
  }
    
  }
  //here to turn on the buzzer
  if( personCounter > 5)
  {
    digitalWrite(buzzer, HIGH);
  }
  else{
    digitalWrite(buzzer, LOW);
  }
  lastStateButton = button_state;
  delay(50);
}
