#include <Servo.h>
#include <NewPing.h>


enum action_type {
  FORWARD          = 0x01,
  BACKWARD         = 0x02,
  RIGHT            = 0x04,
  LEFT             = 0x08,
  STOP             = 0x0F,
  
  RIGHT_FORWARD    = RIGHT | FORWARD,
  RIGHT_BACKWARD   = RIGHT | BACKWARD,
  LEFT_FORWARD     = LEFT | FORWARD,
  LEFT_BACKWARD    = LEFT | BACKWARD,
  
  PING             = 0x10,
  ENGINE_SPEED     = 0x11,
  MEASUREMENT_REQ  = 0x12,
  SERVO_STOP       = 0x13,
  SERVO_START      = 0x14,

  ACK              = 0x80,
  NACK             = 0x81,
  MEASUREMENT_RESP = 0x82
};


enum servo_state_t {
  SERVO_MOVE_FORWARD,
  SERVO_MOVE_BACKWARD
};


/* Define pins that control left and right engines */
#define PIN_PWM_ENGINE_1        6
#define PIN_PWM_ENGINE_2        5

/* Define pin that control servo for radar */
#define SERVO_RADAR_PIN         10

/* Defines pins to control shift register to control engines */
#define LATCH_PIN               12
#define CLOCK_PIN               4
#define DATA_PIN                8
#define ENABLE_PIN              7

/* Define pins that control back and front rangefinder */
#define RADAR_ECHO_BACK_PIN     9
#define RADAR_TRIG_BACK_PIN     4
#define RADAR_ECHO_FRONT_PIN    3
#define RADAR_TRIG_FRONT_PIN    2

/* Defines codes to control engines via shift register to reduce pin usage */
#define CODE_FORWARD_ENGINE_1     B00000001
#define CODE_BACKWARD_ENGINE_1    B01000000
#define CODE_FORWARD_ENGINE_2     B00100000
#define CODE_BACKWARD_ENGINE_2    B10000000


unsigned char state = STOP;
unsigned char engine_speed = 128;


unsigned char silence_counter = 0;
unsigned char corruption_counter = 0;

NewPing         radar_front(RADAR_TRIG_FRONT_PIN, RADAR_ECHO_FRONT_PIN, 100);
NewPing         radar_back(RADAR_TRIG_BACK_PIN, RADAR_ECHO_BACK_PIN, 100);

Servo           servo_radar;
servo_state_t   servo_state = SERVO_MOVE_FORWARD;
bool            g_servo_enable = true;

struct robot_measurement {
  long m_range_front = 0;
  long m_range_back  = 0;
  int  m_servo_angle = 0;
};

robot_measurement g_measurement;

char * g_response_buffer[64];
unsigned char g_response_size = 0;


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

void read_sensors(void) {
  g_measurement.m_range_front = radar_front.ping_cm();
  g_measurement.m_range_back = radar_back.ping_cm();
}


void move_servo_radar(void) {
  switch(servo_state) {
    case SERVO_MOVE_FORWARD:
      g_measurement.m_servo_angle += 5;
      if (g_measurement.m_servo_angle >= 180) {
        servo_state = SERVO_MOVE_BACKWARD;
      }
      break;

    case SERVO_MOVE_BACKWARD:
      g_measurement.m_servo_angle -= 5;
      if (g_measurement.m_servo_angle <= 0) {
        servo_state = SERVO_MOVE_FORWARD;
      }
      break;
  }

  servo_radar.write(g_measurement.m_servo_angle);
}


void setup() {
  /* Initialize engines */
  pinMode(PIN_PWM_ENGINE_1, OUTPUT);
  pinMode(PIN_PWM_ENGINE_2, OUTPUT);

  /* Initialize shift register to control engine */
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  /* Initialize radar */
  pinMode(RADAR_TRIG_FRONT_PIN, OUTPUT);
  pinMode(RADAR_ECHO_FRONT_PIN, INPUT);
  pinMode(RADAR_TRIG_BACK_PIN, OUTPUT);
  pinMode(RADAR_ECHO_BACK_PIN, INPUT);

  /* Initialize servo */
  servo_radar.attach(SERVO_RADAR_PIN);
  servo_radar.writeMicroseconds(1500);

  /* Initialize radio channel */
  Serial.begin(9600);
}


void loop() { 
  if (Serial.available() > 0) {
    silence_counter = 0;
    
    // Read received command
    unsigned char rx_byte = Serial.read();

    g_response_buffer[0] = (char) ACK;
    g_response_size = 1;

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

      case MEASUREMENT_REQ:
        read_sensors();

        g_response_buffer[0] = (char) MEASUREMENT_RESP;
        memcpy(g_response_buffer + 1, (void *) &g_measurement, sizeof(robot_measurement));
        g_response_size = sizeof(g_measurement);
        
        break;

      case SERVO_START:
        g_servo_enable = true;
        break;

      case SERVO_STOP:
        g_servo_enable = false;
        break;
      
      default:
        g_response_buffer[0] = (char) NACK;
        break;
    }

#if 1
    read_sensors();
    Serial.print("Front (cm): ");
    Serial.print(g_measurement.m_range_front);
    Serial.print("\n");

    Serial.print("Back (cm): ");
    Serial.print(g_measurement.m_range_back);
    Serial.print("\n");
#else
    Serial.write((char *) g_response_buffer, g_response_size);
#endif

    if (g_response_buffer[0] != (char) ACK) {
      if (corruption_counter++ > 20) {
        engine::stop();
      }
    }
    else {
      corruption_counter = 0;
    }
  }
  else {
    if ( (state != STOP) && (silence_counter++ > 10) ) {
      engine::stop();
    }
  }

  /* Move servo */
  if (g_servo_enable) {
    move_servo_radar();
  }

  delay(50);
}
