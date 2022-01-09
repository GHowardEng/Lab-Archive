#pragma once
#include <string>

using namespace std;

enum TYPE { DIGITAL = 0, ANALOG, SERVO };

#define LED 18
#define	B0	17
#define SM0 27
#define SERVO_MAX 2500
#define SERVO_MIN 700

#define STAT 22
#define PASS_BUTTON 17
#define REJ 18

#define STAT_LED 23
#define P_LED	24
#define R_LED 	25

class CControlPi
{
private:
	int lastval[5];  ///< Stores previous button state for de-bouncing
	
public:
	CControlPi();
	bool open(string com);
	bool get_data(int type, int channel, int &value);
	bool set_data(int type, int channel, int value);
	int get_button(int channel, int index);
	int get_analog(int channel, int &value);
	void print_menu(void);
	
};
