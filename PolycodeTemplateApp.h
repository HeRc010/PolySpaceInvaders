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
#include "RedUfo.h"
#include "Barrier.h"

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

	// update the red ufo
	void updateRedUfo();

	// add the given barrier to the screen
	void addBarrierToScreen( Barrier * to_add );

	// remove the given barrier from the screen
	void removeBarrierFromScreen( Barrier * to_remove );

	// remove the given block from the barrier which contains it
	void hitBlock( ScreenEntity * to_remove );

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

	// if the game paused
	bool _paused;

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

	// the offset from both sides of the screen for the alien rows
	static const int alien_xoffset = 150;

	// the amount by which the alien rows lower when they hit the edge of the screen
	static const int alien_yoffset = 15;

	// delta for alien translation
	static const int alien_delta = 15;

	// set of aliens rows
	AlienGroup * aliens;

	// duration parameters:
	
	// how ofter the aliens increase speed - in milliseconds
	float alien_acceleration;

	// initial alien row translations - in milliseconds
	static const unsigned alien_shift_pause_initial = 500;

	// alien row translations - in milliseconds
	float alien_shift_pause;

	// alien weapon cooldown - in milliseconds
	float alien_weapon_cooldown;

	// the red ufo that goes accross the top every once in a while
	RedUfo * red_ufo;

	// duration parameter to control how often the red ufo appears - in milliseconds
	float _red_ufo_duration;

	// the set of barriers
	vector<Barrier*> _barriers;

	// timers
	Timer * alien_shift_timer;
	Timer * alien_acceleration_timer;
	Timer * alien_cooldown;
	Timer * red_ufo_timer;

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

	// audio
	Sound * player_shoot;
	Sound * player_explosion;
	Sound * alien_explosion;
	Sound * red_ufo_audio;
};