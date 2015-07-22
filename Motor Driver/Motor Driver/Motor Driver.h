
#ifndef MOTOR	// include guard so functions aren't included twice
#define MOTOR	// MOTOR is just arbitrary word to check for so fns aren't included twice

void motor_setup();
void motor_set_mode(int val);

void timersetup(void);

void left_motor_CW();
void left_motor_CCW();
void right_motor_CW();
void right_motor_CCW();

void left_motor_stop();
void right_motor_stop();

void RANGER_ON(int u);		//Ranger setup
double GETRANGE(void);

#endif