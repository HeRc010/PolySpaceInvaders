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

	// setup the game variables for the first time
	void setup();

	// initialize the timer provided
	void initializeTimer( Timer * timer );

	// initialize the game state
	void initializeGame();

    bool Update();
	
	void handleEvent( Event *e );

	// process input for player translation
	void processPlayerInput();

	// add aliens to screen
	void addAliensToScreen();

	// remove the aliens from the screen
	void removeAliensFromScreen();

	// update the player's missiles
	void updatePlayerMissiles();

	// update aliens
	void updateAliens();

	// update the aliens' missiles
	void updateAlienMissiles();

	// clear alien and player missiles
	void clearMissiles();

	// get the points associated with killing the given entity
	unsigned getPoints( ScreenEntity * entity ) const;

	// update the score; increment by the parameter
	void updateScore( unsigned inc );

	// remove a life from the lives' label
	void removeLife();

	// draw the life sprites
	void drawLifeSprites( Vector3 base_loc );

	// draw the game over labels
	void drawGameOverLabel();

private:
    Core *core;

	// main screen
	PhysicsScreen * main_screen;

	// has the game been initialized?
	bool _initialized;

	// is the game over?
	bool _game_over;

	// GUI parameters
	static const unsigned screen_width = 1580;
	static const unsigned screen_height = 800;

	// the fighter/player
	Fighter *player;

	// fighter gui offsets
	static const unsigned player_xoffset = 50;
	static const unsigned player_yoffset = 50;

	// the player delta amount when translating
	static const int player_delta_x = 5;

	// the delta vector for the player
	Vector3 player_delta;

	// duration parameter for weapon cooldown - in milliseconds
	//unsigned player_weapon_cooldown;

	// player missile speed
	//static const int player_missile_speed = 5;

	// the offset from both sides of the screen for the alien rows
	static const int alien_xoffset = 150;

	// the amount by which the alien rows lower when they hit the edge of the screen
	static const int alien_yoffset = 15;

	// delta for alien translation
	static const int alien_delta = 15;

	// set of aliens rows
	AlienGroup * aliens;

	// duration parameter between alien row translations - in milliseconds
	unsigned duration;

	// duration parameter for the alien weapon cooldown - in milliseconds
	unsigned alien_weapon_cooldown;

	// timers
	Timer * timer;
	//Timer * player_cooldown;
	Timer * alien_cooldown;

	// sprites for the lives label
	ScreenLabel * lives_label;
	vector<ScreenSprite*> life_sprites;

	// the players score
	int _score;

	// the score label
	ScreenLabel * score_label;

	// game over labels
	ScreenLabel * game_over_label;
	ScreenLabel * replay_label;
};