#include "input.h"
#include <SDL/SDL.h>

Button btnUp = {0}, btnDown = {0}, btnLeft = {0}, btnRight = {0};
Button btnFaceUp = {0}, btnFaceDown = {0}, btnFaceLeft = {0}, btnFaceRight = {0};
Button btnL = {0}, btnR = {0};
Button btnStart = {0}, btnSelect = {0};
Button btnAccept = {0}, btnDecline = {0};
int axisX = 0, axisY = 0;

int bUp = 0, bDown = 0, bLeft = 0, bRight = 0;
int bFaceUp = 0, bFaceDown = 0, bFaceLeft = 0, bFaceRight = 0;
int bR = 0, bL = 0;
int bStart = 0, bSelect = 0;
int bAccept = 0, bDecline = 0;
int jUp = 0, jDown = 0, jLeft = 0, jRight = 0;
int jFaceUp = 0, jFaceDown = 0, jFaceLeft = 0, jFaceRight = 0;
int jR = 0, jL = 0;
int jStart = 0, jSelect = 0;
int jAccept = 0, jDecline = 0;

SDL_Joystick *joy[4];


int useJoystick = 1;

void Input_InitJoystick()
{
	//set them all to null first
	for(int i = 0; i < 4; i++)
	{
		joy[i] = NULL;
	}
	
	int n = SDL_NumJoysticks();
	for(int i = 0; i < n; i++)
	{
		joy[i] = SDL_JoystickOpen(i);	
		printf("Using %s\n", SDL_JoystickName(i));
	} 
	if(n > 0)
	{
		SDL_JoystickEventState(SDL_ENABLE);
	}
	
	
}

void Input_CloseJoystick()
{
	int n = SDL_NumJoysticks();
	for(int i = 0; i < n; i++)
	{
		if(joy[i])
			SDL_JoystickClose(joy[i]);
		joy[i] = NULL;
	}
}

void Input_KeyEvent(SDL_Event* evt)
{
    int w = (evt->type==SDL_KEYDOWN)?1:0;
    switch(evt->key.keysym.sym)
    {
        case SDLK_UP:       bUp = w; break;
        case SDLK_DOWN:     bDown = w; break;
        case SDLK_LEFT:     bLeft = w; break;
        case SDLK_RIGHT:    bRight = w; break;
#if defined(PANDORA) || defined(PYRA)
        case SDLK_PAGEUP:   bFaceUp = w; break;
        case SDLK_PAGEDOWN: bFaceDown = w; break;
        case SDLK_END:      bFaceLeft = w; break;   // reversing, so (B) is sword
        case SDLK_HOME:     bFaceRight = w; break;
        case SDLK_RCTRL:    bR = w; break;
        case SDLK_RSHIFT:   bL = w; break;
        case SDLK_LCTRL:    bSelect = w; break;
		case SDLK_LALT:     bStart = w; break;
#elif defined(CHIP)
		case SDLK_MINUS:        bFaceUp = w; break;
		case SDLK_o:            bFaceDown = w; break;
		case SDLK_0:            bFaceLeft = w; break;
		case SDLK_EQUALS:       bFaceRight = w; break;
		case SDLK_1:            bR = w; break;
		case SDLK_2:            bL = w; break;
		case SDLK_SPACE:        bSelect = w; break;
		case SDLK_RETURN:       bStart = w; break;
#elif defined(DINGUX)
		case SDLK_LSHIFT:        bFaceUp = w; break;
        case SDLK_LALT:        bFaceDown = w; break;
        case SDLK_LCTRL:        	bFaceLeft = w; break;
		case SDLK_SPACE:       bFaceRight = w; break;
		case SDLK_BACKSPACE:            bR = w; break;
		case SDLK_TAB:            bL = w; break;
		case SDLK_ESCAPE:        bSelect = w; break;
		case SDLK_RETURN:       bStart = w; break;
#else
        case SDLK_e:        bFaceUp = w; break;
        case SDLK_x:        bFaceDown = w; break;
        case SDLK_s:        bFaceLeft = w; break;
        case SDLK_d:        bFaceRight = w; break;
        case SDLK_r:        bR = w; break;
        case SDLK_w:        bL = w; break;
		case SDLK_SPACE:    bSelect = w; break;
		case SDLK_ESCAPE:   bSelect = w; break;
        case SDLK_RETURN:   bStart = w; break;
#endif
    }
}

void Input_JoyAxisEvent(SDL_Event* evt) {
	//if(evt->jaxis.which!=0)
		//return;
	#define DEADZONE 32
	if(evt->jaxis.axis==0) {
		int v = (evt->jaxis.value)/256;
		if(v>-DEADZONE & v<DEADZONE) axisX = 0;
		else if(v<0) axisX = -1;
		else axisX = +1;
	}
	if(evt->jaxis.axis==1) {
		int v = (evt->jaxis.value)/256;
		if(v>-DEADZONE & v<DEADZONE) axisY = 0;
		else if(v<0) axisY = -1;
		else axisY = +1;
	}
}

void Input_JoyEvent(SDL_Event* evt) {
	//if(evt->jbutton.which!=0)
		//return;
	int w = (evt->type==SDL_JOYBUTTONDOWN)?1:0;
/* XBox 360 based mapping here,
	(would be better to switch to SDL2.0)
	btn 		SDL1.2	SDL2.0
	---------------------------
	A			0		10
	B			1		11
	X			2		12
	Y			3		13
	Home		N/A	14
	LB			4		8
	RB			5		9
	LT			N/A		N/A (axis)
	RT			N/A		N/A (axis)
	Select		6		5
	Start		7		4
	L3			9		6
	R3			10		7
	DPad Up		N/A		0
	DPad Down	N/A		1
	DPad Left	N/A		2
	DPad Right	N/A		3
*/
	switch(evt->jbutton.button)
	{
		case 2: jFaceDown = w; break;
		case 1: jFaceLeft = w; break;
		case 0: jFaceRight = w; break;
		case 3: jFaceUp = w; break;
		case 4: jL = w; break;
		case 5: jR = w; break;
		case 8: jSelect = w; break;
		case 9: jStart = w; break;
		/*case 12:jUp = w; break;
		case 13:jDown = w; break;
		case 14:jLeft = w; break;
		case 15:jRight = w; break;*/
	}
}

void Input_JoyHatEvent(SDL_Event* evt) {
	if(evt->jhat.which!=0)
		return;
	if(evt->jhat.hat!=0)
		return;
	int v=evt->jhat.value;
	jUp = v&SDL_HAT_UP;
	jDown = v&SDL_HAT_DOWN;
	jLeft = v&SDL_HAT_LEFT;
	jRight = v&SDL_HAT_RIGHT;
}

void updateKey(Button* btn, int state)
{
	if (state) {
		if (btn->held == 1) {
			btn->pressed = 0;
		}else{
			btn->pressed = 1;
		}
		btn->held = 1;
		btn->released = 0;
	}else{
		if (btn->held == 1) {
			btn->released = 1;
		}else{
			btn->released = 0;
		}
		btn->held = 0;
		btn->pressed = 0;
	}
}

void PHL_ScanInput()
{
	updateKey(&btnUp, bUp|jUp|(axisY<0));
	updateKey(&btnDown, bDown|jDown|(axisY>0));
	updateKey(&btnLeft, bLeft|jLeft|(axisX<0));
	updateKey(&btnRight, bRight|jRight|(axisX>0));
	
	updateKey(&btnStart, bStart|jStart);
	updateKey(&btnSelect, bSelect|jSelect);
	
	updateKey(&btnL, bL|jL);
	updateKey(&btnR, bR|jR);
	
	updateKey(&btnFaceLeft, bFaceLeft|jFaceLeft);
	updateKey(&btnFaceDown, bFaceDown|jFaceDown);
	updateKey(&btnFaceRight, bFaceRight|jFaceRight);
	
	updateKey(&btnAccept, bFaceLeft|jFaceLeft);
	updateKey(&btnDecline, bFaceDown|jFaceDown);
}
