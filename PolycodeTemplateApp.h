/*
	The main app class
*/

#include "PolycodeView.h"
#include "Polycode.h"
#include "SpaceInvadersEntity.h"
#include "Fighter.h"
#include "AlienRow.h"
#include "AlienOne.h"

// for physics screen
#include "Polycode2DPhysics.h"

using namespace Polycode;

class PolycodeTemplateApp : public EventHandler {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();

	// initialize the GUI paramters
	void initializeGUIParameters();

	//
    bool Update();
	
	//
	void handleEvent( Event *e );

	// process input for player translation
	void processPlayerInput();

	// direction values
	enum direction { left, right };


private:
    Core *core;

	// GUI parameters
	static const unsigned screen_width = 1580;
	static const unsigned screen_height = 800;

	float alien_sprite_xscale;
	float alien_sprite_yscale;
	Vector3 *alien_sprite_scale;
	
	unsigned alien_xoffset;

	// delta for alien translation
	static const int alien_delta = 50;

	float player_sprite_xscale;
	float player_sprite_yscale;
	Vector3 *player_sprite_scale;

	static const unsigned pmissile_sprite_xscale = 1;
	static const unsigned pmissile_sprite_yscale = 1;
	Vector3 *player_missile_scale;

	unsigned player_xoffset;
	unsigned player_yoffset;

	// timers
	Timer *timer;
	Timer *weapon_cooldown;

	// duration parameter between alien row translations - in milliseconds
	unsigned duration;

	// duration parameter for weapon cooldown - in milliseconds
	static const unsigned weapon_cooldown_time = 700;

	// main screen
	PhysicsScreen *main_screen;

	// missile speed
	static const int player_missile_speed = 10;

	// the fighter/player
	Fighter *player;

	// the player delta amount when translating
	static const int player_delta_x = 5;

	// the delta vector for the player
	Vector3 player_delta;

	// a list of the missiles fired by the aliens
	vector<SpaceInvadersEntity*> alien_missles;

	// current direction for row
	direction current_dir;
};