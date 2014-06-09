/*
	The main app class
*/

#include "PolycodeView.h"
#include "Polycode.h"

// for physics screen
#include "Polycode2DPhysics.h"

// project files
#include "SpaceInvadersEntity.h"
#include "Fighter.h"
#include "AlienGroup.h"

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

	// add aliens to screen
	void addAliensToScreen();

	// fire player missile
	void firePlayerMissile();

	// update the player's missiles
	void updatePlayerMissiles();

	// update aliens
	void updateAliens();

	// update the aliens' missiles
	void updateAlienMissiles();

	// get the points associated with killing the given entity
	unsigned getPoints( ScreenEntity * entity ) const;

	// update the score; increment by the parameter
	void updateScore( unsigned inc );

	// remove a life from the lives' label
	void removeLife();

	// game over function
	void gameOver();

private:
    Core *core;

	// main screen
	PhysicsScreen *main_screen;

	// GUI parameters
	static const unsigned screen_width = 1580;
	static const unsigned screen_height = 800;

	float alien_sprite_xscale;
	float alien_sprite_yscale;
	Vector3 *alien_sprite_scale;
	
	int alien_xoffset;

	// delta for alien translation
	static const int alien_delta = 50;

	// set of aliens rows
	AlienGroup * aliens;

	float player_sprite_xscale;
	float player_sprite_yscale;
	Vector3 *player_sprite_scale;

	static const unsigned pmissile_sprite_xscale = 1;
	static const unsigned pmissile_sprite_yscale = 1;
	Vector3 *player_missile_scale;

	unsigned player_xoffset;
	unsigned player_yoffset;

	// timers
	Timer * timer;
	Timer * player_cooldown;
	Timer * alien_cooldown;

	// duration parameter between alien row translations - in milliseconds
	unsigned duration;

	// duration parameter for weapon cooldown - in milliseconds
	unsigned player_weapon_cooldown;

	// duration parameter for the alien weapon cooldown - in milliseconds
	unsigned alien_weapon_cooldown;

	// missile speeds
	static const int player_missile_speed = 10;
	static const int alien_missile_speed = 5;

	// the fighter/player
	Fighter *player;

	// the player delta amount when translating
	static const int player_delta_x = 5;

	// the delta vector for the player
	Vector3 player_delta;

	// the number of lives the player has
	unsigned _num_lives;

	// sprites for the lives label
	vector<ScreenSprite*> life_sprites;

	// the players score
	unsigned _score;

	// the score label
	ScreenLabel * score_label;

	ScreenLabel * game_over_label;

	// a list of the missiles fired by the player
	vector<ScreenSprite*> player_missiles;

	// a list of the missiles fired by the aliens
	vector<ScreenSprite*> alien_missiles;
};