#include "PolycodeView.h"
#include "Polycode.h"
#include "SpaceInvadersEntity.h"
#include "AlienRow.h"

// for physics screen
#include "Polycode2DPhysics.h"

using namespace Polycode;

class PolycodeTemplateApp : public EventHandler {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();

	//
    bool Update();
	
	//
	void handleEvent( Event *e );
    
	// create a particular alien, more or less hard-coded right now
	SpaceInvadersEntity * createAlien();

	// create a player missile
	SpaceInvadersEntity * createPlayerMissile();

	// create a row of aliens
	AlienRow * createAlienRow( Vector3 &start_pos, unsigned num_aliens, unsigned spacing );

	// create the group of aliens; constitutes multiple alien rows
	vector<AlienRow*> createAliens( Vector3 &start_pos, unsigned num_rows, unsigned row_spacing, unsigned num_aliens_per_row, unsigned sprite_spacing );

	// add the sprites from a row of aliens to the main screen
	void addAlienRowToScreen( AlienRow * row );

	// add the aliens to the main screen
	void addAliensToScreen( vector<AlienRow*> aliens );

	// direction values
	enum direction { left, right };

	// translate a row of aliens in a particluar direction
	void translateAlienRow( AlienRow *row );

	// translate all the alien rows
	void translateAliens( vector<AlienRow*> &aliens );

	// fire a missile from the player
	void playerFireMissile();

	// update the player's missiles
	void updatePlayerMissles( vector<SpaceInvadersEntity*> missiles, int missile_speed );

	// is the sprite one of the player missiles?
	bool isPlayerMissile( ScreenEntity * entity );

	// remove a player missile from the screen and the array
	void removePlayerMissile( ScreenEntity * to_remove );

	// is the entity and alien?
	bool isAlien( ScreenEntity * entity );

	// remove an alien from the screen and the array
	void removeAlien( ScreenEntity * to_remove );


private:
    Core *core;

	// GUI parameters
	static const unsigned screen_width = 640;
	static const unsigned screen_height = 480;

	static const unsigned sprite_xscale = 2;
	static const unsigned sprite_yscale = 2;
	Vector3 *sprite_scale;
	
	static const unsigned pmissile_sprite_xscale = 1;
	static const unsigned pmissile_sprite_yscale = 1;
	Vector3 *player_missile_scale;

	static const unsigned offset = 10;

	// timer
	Timer *timer;

	// main screen
	PhysicsScreen *main_screen;
	
	// entity initial HP
	static const unsigned initial_HP = 100;

	// missile speed
	static const int player_missile_speed = 10;

	// the fighter/player
	SpaceInvadersEntity *player;

	// the player delta amount when translating
	static const int player_delta_x = 5;

	// the delta vector for the player
	Vector3 player_delta;

	// a list of the players missiles
	vector<SpaceInvadersEntity*> player_missiles;

	// the set of aliens
	vector<AlienRow*> aliens;

	// row of aliens
	AlienRow *alien_row;

	// delta for alien translation
	static const int delta = 50;

	// duration parameter between alien row translations - in milliseconds
	static const unsigned duration = 1000;

	// a list of the missiles fired by the aliens
	vector<SpaceInvadersEntity*> alien_missles;

	// current direction for row
	direction current_dir;
};