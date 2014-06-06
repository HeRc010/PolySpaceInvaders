#include "PolycodeView.h"
#include "Polycode.h"
#include "SpaceInvadersEntity.h"
#include "AlienRow.h"

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

private:
    Core *core;

	// GUI parameters
	static const unsigned screen_width = 640;
	static const unsigned screen_height = 480;

	static const unsigned sprite_xscale = 2;
	static const unsigned sprite_yscale = 2;
	Vector3 *sprite_scale;

	static const unsigned offset = 10;

	// main screen
	Screen *main_screen;
	
	// the fighter/player
	SpaceInvadersEntity *player;

	// player initial HP
	static const unsigned initial_HP = 100;

	// the set of aliens
	vector<AlienRow*> aliens;

	// row of aliens
	AlienRow *alien_row;

	// delta for alien translation
	static const int delta = 50;

	// duration parameter between alien row translations
	unsigned duration;

	// current direction for row
	direction current_dir;
};