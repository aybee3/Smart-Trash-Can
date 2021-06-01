/*
   _____________________________________________________________
  |
  | Description
  | -----------
  | - This is a smart trash bin which seperates dry and wet
  |   wet waste.
  |
  |.............................................................
  |
  | Attributes
  | ----------
  | pin_1 : int
  |    -  Servo Motor pin number.
  |
  | pin_2 : int
  |    -  Moisture Sensor pin number.
  |
  | pin_3 : int
  |    - Touch Sensor pin number.
  |
  |............................................................
  |
  | Methods
  | -------
  | dry_waste()
  |       - Lid of the segregator slides towards right side.
  |
  | wet_waste()
  |       - Lid of the segregator slides towards left side
  |
  | neutral_state()
  |       - In which the lid of segregator is in the middle.
  |
  | execute()
  |       - Smart Segregator starts operating.
  |
  |___________________________________________________________
  */
#include <Servo.h>

class Smart_Segregator
{
  public:
     int servo_pin;
     int moisture_sensor_pin;
     int touch_sensor_pin;
     int detect_touch;
		 int moisture_value;
		 float moisture_percentage;
 
     Servo servo;

     Smart_Segregator(int pin_1, int pin_2, int pin_3)
     {
       servo_pin = pin_1;
       moisture_sensor_pin = pin_2;
       touch_sensor_pin = pin_3;

       moisture_value = 0;
       detect_touch = false;
     }

    void init()
    {
      Serial.begin(9600);
      servo.attach(servo_pin);
      servo.write(90);
      
      pinMode(moisture_sensor_pin, INPUT);
      pinMode(touch_sensor_pin, INPUT);

      Serial.println("Your Smart Segregator is ready to Segregate!");
    }

    void dry_waste()
    {
      servo.write(0);
    }

    void wet_waste()
    {
      servo.write(180);
    }

    void neutral_state()
    {
      servo.write(90);
    }
    
    void execute()
    {
      detect_touch = digitalRead(touch_sensor_pin);
			moisture_value = analogRead(moisture_sensor_pin);
      moisture_percentage = ( 100 - ( (moisture_value/1023.00) * 100 ) );

      if (moisture_percentage <= 50.00 && detect_touch == true)
      {
        dry_waste();
      }

      else if (detect_moisture > 50.00 && detect_touch == true)
      {
        wet_waste();
      }

      else 
      {
        neutral_state();
      }
    }
}

segregator = Smart_Segregator(8,A0,7);

void setup() 
{
  segregator.init();
}

void loop() 
{
 segregator.execute();
}
