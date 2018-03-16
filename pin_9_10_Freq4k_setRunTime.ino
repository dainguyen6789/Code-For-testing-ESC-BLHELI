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
//Change the ESC firmware to MAIN because they have some bugs (!?) that make the motor fluctuate when PWM is enable
int pwm_1 = 11;           // the PWM pin the pwm_1 is attached to
int pwm_2 = 10;           // the PWM pin the pwm_2 is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount =2;     // how many points to fade the LED by
int num_loop=0;
//
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(pwm_1, OUTPUT);
  //analogWrite(pwm_1, 0);
  setPwmFrequency(pwm_1, 8);           //  3921.16 Hz
  //analogWrite(pwm_1, 0);
  
   // declare pin pwm_2 to be an output:
   pinMode(pwm_2, OUTPUT);
  //analogWrite(pwm_2, 0);
  setPwmFrequency(pwm_2, 8);           //  3921.16 Hz
  //analogWrite(pwm_2, 0);
  analogWrite(pwm_1,0);
  analogWrite(pwm_2,0);

  //analogWrite(9, 0);
  //analogWrite(pwm_2, 0);

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
  // analogWrite(pwm_1,brightness);
  // https://distantorion.com/2014/10/24/motor-control/: how to change motor speed The interface to 
  // command the ESC called PWM, pulse width modulation, where the pulse width will carry the value, 
  // wide pulse means high value, thin pulse means low value
//  delay(3000); 
  while (num_loop<=100)
  {
    analogWrite(pwm_1,brightness);

    analogWrite(pwm_2,brightness);
    brightness = brightness + fadeAmount;
    num_loop++;
    if (brightness <= 0 || brightness >= 100) 
    {
      fadeAmount = -2;      
    }
//    if ( num_loop<=1 )
//    {
//       delay(30);
//    }
//    else
//       delay(10);
  }
  analogWrite(pwm_1,0);
  analogWrite(pwm_2,0);
//  delay(50);  
  delay(4000);
  analogWrite(pwm_1,15);
  analogWrite(pwm_2,15);
  delay(20);    
  analogWrite(pwm_1,25);
  analogWrite(pwm_2,25);
  delay(20);   
  analogWrite(pwm_1,35);
  analogWrite(pwm_2,35);
  delay(20); 
  
  analogWrite(pwm_1,40);
  analogWrite(pwm_2,40);
  delay(20);
  analogWrite(pwm_1,50);
  analogWrite(pwm_2,50);
  delay(20);
//  analogWrite(pwm_1,56);
//  analogWrite(pwm_2,56);  
  delay(20);
  analogWrite(pwm_1,60);
  analogWrite(pwm_2,60); 
  delay(5000);
//  analogWrite(pwm_1,35);
//  analogWrite(pwm_2,35); 
//  delay(5000);
  analogWrite(pwm_1,6);
  analogWrite(pwm_2,6); 
  
  while(1)
  {
   }
    
  // wait for 5000 milliseconds to see the dimming effect
  // delay(3000);
}


