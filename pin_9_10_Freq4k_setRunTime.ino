/*
 BLDC motor control

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */
 /*N “electrical revolutions” equates to one mechanical revolution, where N is the number of magnet pairs.*/

int led = 11;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 1;     // how many points to fade the LED by
int num_loop=0;
//
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  //analogWrite(led, 0);
  setPwmFrequency(led, 8);           //  3921.16 Hz
  //analogWrite(led, 0);
  
   // declare pin 10 to be an output:
   pinMode(10, OUTPUT);
  //analogWrite(10, 0);
  setPwmFrequency(10, 8);           //  3921.16 Hz
  //analogWrite(10, 0);
  analogWrite(led,25);
  analogWrite(10,25);

  //analogWrite(9, 0);
  //analogWrite(10, 0);

}
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
  /*    http://playground.arduino.cc/Main/TimerPWMCheatsheet
   *     Setting   Divisor   Frequency
  0x01    1     31372.55
  0x02    8     3921.16
  0x03      64    490.20   <--DEFAULT
  0x04      256     122.55
  0x05    1024    30.64
  TCCR1B = (TCCR1B & 0b11111000) | <setting>; */

    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  // analogWrite(led,brightness);
  // https://distantorion.com/2014/10/24/motor-control/: how to change motor speed The interface to 
  // command the ESC called PWM, pulse width modulation, where the pulse width will carry the value, 
  // wide pulse means high value, thin pulse means low value
  delay(3000); 
  while (num_loop<=500)
  {
    analogWrite(led,brightness);

    analogWrite(10,brightness);
    brightness = brightness + fadeAmount;
    num_loop++;
    if (brightness <= 0 || brightness >= 255) 
    {
      fadeAmount = -1;      
    }
    if ( num_loop<=1 )
    {
       delay(3000);
    }
    else
       delay(5);
  }
//  analogWrite(led,0);
//  analogWrite(10,0);
//  delay(50);  
  
  analogWrite(led,55);
  analogWrite(10,55);
  delay(6000); 
  
//  analogWrite(led,45);
//  analogWrite(10,45);
//  delay(6000);  
//  
//  analogWrite(led,75);
//  analogWrite(10,75);
//  delay(6000); 
//  analogWrite(led,0);
//  analogWrite(10,0);
  while(1)
  {
   }
    
  // wait for 5000 milliseconds to see the dimming effect
  // delay(3000);
}


