
// THROTTLE PARAMETERS
int min_pulse_th = 1000;
int mid_pulse_th = 1600;
int max_pulse_th = 2000;
int dead_zone_th = 20;
int throttle;
unsigned long pulse_throttle;

// STEERING PARAMETERS
int min_pulse_st = 1000;
int mid_pulse_st = 1600;
int max_pulse_st = 2000;
int dead_zone_st = 20;
int steering;
unsigned long pulse_steering;

// RECEVING CHANNELS
const int RX_throttle = 5;
const int RX_steering = 6;
const int throttle_pwm_pin = 10;
const int steering_pwm_pin = 11;
const int dir_A_throttle = 12;
const int dir_B_throttle = 13;
const int dir_A_steering = 3;
const int dir_B_steering = 4;
void setup() {

  Serial.begin(9600);

  // THROTTLE PINs SETUP
  pinMode(RX_throttle, INPUT);
  pinMode(throttle_pwm_pin, OUTPUT);
  pinMode(dir_A_throttle, OUTPUT);
  pinMode(dir_B_throttle, OUTPUT);
  
  // STEERING PINs SETUP
  pinMode(RX_steering, INPUT);
  pinMode(steering_pwm_pin, OUTPUT);
  pinMode(dir_A_steering, OUTPUT);
  pinMode(dir_B_steering, OUTPUT);

  // IC
  digitalWrite(dir_A_throttle, LOW);
  digitalWrite(dir_B_throttle, HIGH);
  digitalWrite(dir_A_steering, LOW);
  digitalWrite(dir_B_steering, HIGH);
}

void loop() {

  // THROTTLE
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

  // STEERING
  pulse_steering = pulseIn(RX_steering, HIGH, 25000); // Timeout after 25ms


  delay(10); // Read every 100ms
}
