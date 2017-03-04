enum action_type {
  FORWARD         = 0x01,
  BACKWARD        = 0x02,
  RIGHT           = 0x04,
  LEFT            = 0x08,
  STOP            = 0x0F,
  
  RIGHT_FORWARD   = RIGHT | FORWARD,
  RIGHT_BACKWARD  = RIGHT | BACKWARD,
  LEFT_FORWARD    = LEFT | FORWARD,
  LEFT_BACKWARD   = LEFT | BACKWARD,
  
  PING            = 0x10,
  ACK             = 0x11,
  NACK            = 0x12,
  ENGINE_SPEED    = 0x13,
};


#define PIN_PWM_ENGINE_1          6
#define PIN_PWM_ENGINE_2          5

#define CODE_FORWARD_ENGINE_1     B00000001
#define CODE_BACKWARD_ENGINE_1    B01000000
#define CODE_FORWARD_ENGINE_2     B00100000
#define CODE_BACKWARD_ENGINE_2    B10000000

#define LATCH_PIN     12
#define CLOCK_PIN     4
#define DATA_PIN      8
#define ENABLE_PIN    7


unsigned char state = STOP;
unsigned char engine_speed = 128;


unsigned char silence_counter = 0;
unsigned char corruption_counter = 0;


namespace engine {  
  inline void forward(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_FORWARD_ENGINE_1 | CODE_FORWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);

    state = FORWARD;
  }

  inline void backward(void) { 
    analogWrite(PIN_PWM_ENGINE_1, engine_speed);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_BACKWARD_ENGINE_1 | CODE_BACKWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);

    state = BACKWARD;
  }

  inline void left(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_FORWARD_ENGINE_1 | CODE_BACKWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);

    state = LEFT;
  }

  inline void left_forward(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed >> 1);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_FORWARD_ENGINE_1 | CODE_FORWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);
    
    state = LEFT_FORWARD;
  }

  inline void left_backward(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed >> 1);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_BACKWARD_ENGINE_1 | CODE_BACKWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);
    
    state = LEFT_BACKWARD;
  }

  inline void right(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_BACKWARD_ENGINE_1 | CODE_FORWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);

    state = RIGHT;
  }

  inline void right_forward(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed >> 1);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_FORWARD_ENGINE_1 | CODE_FORWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);
    
    state = RIGHT_FORWARD;
  }

  inline void right_backward(void) {
    analogWrite(PIN_PWM_ENGINE_1, engine_speed);
    analogWrite(PIN_PWM_ENGINE_2, engine_speed >> 1);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CODE_BACKWARD_ENGINE_1 | CODE_BACKWARD_ENGINE_2);
    digitalWrite(LATCH_PIN, HIGH);
    
    state = RIGHT_BACKWARD;
  }

  inline void stop(void) {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x00);
    digitalWrite(LATCH_PIN, HIGH);

    state = STOP;
  }

  inline void speed(const unsigned char p_speed) {
    engine_speed = p_speed;
  }
}


void setup() {
  pinMode(PIN_PWM_ENGINE_1, OUTPUT);
  pinMode(PIN_PWM_ENGINE_2, OUTPUT);

  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  Serial.begin(9600);
}


void loop() { 
  if (Serial.available() > 0) {
    silence_counter = 0;
    
    // Read received command
    unsigned char rx_byte = Serial.read();
    unsigned char tx_byte = ACK;

    // Handle the command
    switch(rx_byte) {
      case FORWARD:
        engine::forward();
        break;
        
      case BACKWARD:
        engine::backward();
        break;

      case LEFT:
        engine::left();
        break;

      case LEFT_FORWARD:
        engine::left_forward();
        break;

      case LEFT_BACKWARD:
        engine::left_backward();
        break;
      
      case RIGHT:
        engine::right();
        break;

      case RIGHT_FORWARD:
        engine::right_forward();
        break;

      case RIGHT_BACKWARD:
        engine::right_backward();
        break;

      case STOP:
        engine::stop();
        break;

      case ENGINE_SPEED:
        engine::speed(Serial.read());
        break;
      
      default:
        tx_byte = NACK;
        break;
    }

    if (tx_byte != ACK) {
      if (corruption_counter++ > 20) {
        engine::stop();
      }
    }
    else {
      corruption_counter = 0;
    }
    
    Serial.write(rx_byte);
    Serial.write(tx_byte);
  }
  else {
    if ( (state != STOP) && (silence_counter++ > 10) ) {
      engine::stop();
    }
  }

  delay(50);
}

