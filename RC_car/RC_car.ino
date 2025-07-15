#include <Servo.h>

// THROTTLE PARAMETERS
int min_pulse_th = 1070;
int mid_pulse_th = 1600;
int max_pulse_th = 2137;
int dead_zone_th = 20;
int throttle;
unsigned long pulse_throttle;

// RECEVING CHANNELS - THROTTLE
const int RX_throttle = 5;
const int throttle_pwm_pin = 10;
const int dir_A_throttle = 12;
const int dir_B_throttle = 13;

// STEERING SERVO
Servo servo_motor;
int steering_angle;
const int servo_pwm = 6;  
const int RX_steering = 3;

// STEERING PARAMETERS
int min_pulse_st = 1000;
int mid_pulse_st = 1600;
int max_pulse_st = 2000;
int dead_zone_st = 20;
int steering;
unsigned long pulse_steering;
  


// SETUP FUNCTION
void setup() {

  Serial.begin(9600);

  // THROTTLE PINs SETUP
  pinMode(RX_throttle, INPUT);
  pinMode(throttle_pwm_pin, OUTPUT);
  pinMode(dir_A_throttle, OUTPUT);
  pinMode(dir_B_throttle, OUTPUT);

  // STEERING SERVO PIN SETUP
  servo_motor.attach(servo_pwm);
  
  // STEERING PINs SETUP
  pinMode(RX_steering, INPUT);

  // IC (Initial Conditions)
  digitalWrite(dir_A_throttle, LOW);
  digitalWrite(dir_B_throttle, HIGH);
}

// LOOP FUNCTION
void loop() {

  // THROTTLE CONTROL
  pulse_throttle = pulseIn(RX_throttle, HIGH, 25000); // Timeout after 25ms

  if (pulse_throttle < (mid_pulse_th - dead_zone_th)) {
    throttle = map(pulse_throttle, min_pulse_th, mid_pulse_th, 255, 0);
    analogWrite(throttle_pwm_pin, throttle); // Forward speed
    digitalWrite(dir_A_throttle, LOW);
    digitalWrite(dir_B_throttle, HIGH);
  } else if (pulse_throttle > (mid_pulse_th + dead_zone_th)) {
    throttle = map(pulse_throttle, mid_pulse_th, max_pulse_th, 0, 255);
    analogWrite(throttle_pwm_pin, throttle); // Reverse speed
    digitalWrite(dir_A_throttle, HIGH);
    digitalWrite(dir_B_throttle, LOW);
  } else {
    analogWrite(throttle_pwm_pin, 0); // Neutral
    digitalWrite(dir_A_throttle, HIGH);
    digitalWrite(dir_B_throttle, LOW);
  }

  // STEERING CONTROL
  pulse_steering = pulseIn(RX_steering, HIGH, 25000); // Timeout after 25ms

  if (pulse_steering < (mid_pulse_st - dead_zone_st)) {
    steering_angle = map(pulse_steering, min_pulse_st, mid_pulse_st, 0, 89);
    servo_motor.write(steering_angle);
  } else if (pulse_steering > (mid_pulse_st + dead_zone_st)) {
    steering_angle = map(pulse_steering, mid_pulse_st, max_pulse_st, 91, 180);
    servo_motor.write(steering_angle);
  } else {
    servo_motor.write(90); // Neutral - 90 degrees
  }

  Serial.println("RX throttle pulse: " + String(pulse_throttle) + "// RX steering pulse: " + String(pulse_steering));
}
