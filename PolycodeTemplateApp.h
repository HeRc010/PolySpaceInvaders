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

	// direction values
	enum direction { left, right };

	// translate a row of aliens in a particluar direction
	void translateAliens( vector<SpaceInvadersEntity*> *alien_list );

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

	// row of aliens
	vector<SpaceInvadersEntity*> *aliens;

	// delta for alien translation
	static const int delta = 50;

	// current direction for row
	direction current_dir;
};