#include "PolycodeTemplateApp.h"

//
#include "Fighter.h"

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
	// GUI parameters
	int screen_width = 640;
	int screen_height = 480;

	float sprite_xscale = 2;
	float sprite_yscale = 2;
	Vector3 sprite_scale( sprite_xscale, sprite_yscale, 0 );

	// initialization
	core = new Win32Core(view, screen_width,screen_height,false, false, 0, 0,60);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	// Create screen
	Screen *main_screen = new Screen();

	// add background
	ScreenImage *background = new ScreenImage("Resources/background.png");
	main_screen->addChild( background );

	// initialize fighter
	ScreenImage *player_sprite = new ScreenImage("Resources/fighter.png");

	// adjust accordingly
	player_sprite->setScale( sprite_scale );
	
	float offset = 10;
	Vector3 location( float( screen_width/2 ), float( screen_height - ( player_sprite->getHeight() * sprite_yscale + offset ) ), 0 );
	player_sprite->setPosition( location );

	Fighter *player = new Fighter( player_sprite );
	main_screen->addChild( player->fighter_sprite );
}
PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
	return core->updateAndRender();
}