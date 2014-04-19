/*
	The main template file.
*/

#include "PolycodeTemplateApp.h"

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) : EventHandler() {
	// initialization
	core = new Win32Core(view, screen_width,screen_height,false, false, 0, 0,60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	// assign GUI parameters
	sprite_scale = new Vector3( sprite_xscale, sprite_yscale, 0 );

	// Create screen
	main_screen = new Screen();

	// add background
	ScreenImage *background = new ScreenImage("Resources/background.png");
	main_screen->addChild( background );

	// initialize fighter/player entity
	ScreenImage *player_sprite = new ScreenImage("Resources/fighter.png");
	player_sprite->setScale( *sprite_scale );
	
	Vector3 *location = new Vector3( float( screen_width/2 ), float( screen_height - ( player_sprite->getHeight() * sprite_yscale + offset ) ), 0 );

	player = new SpaceInvadersEntity( player_sprite, location, initial_HP );
	main_screen->addChild( player->getSprite() );

	// SPAWN a row of aliens
	vector<SpaceInvadersEntity*> *aliens = new vector<SpaceInvadersEntity*>( 0 );
	
	Vector3 start_pos(0, 0, 0);
	const unsigned NUM_ROW_ALIENS = 5;
	for ( unsigned i = 0; i < NUM_ROW_ALIENS; ++i ) {
		// create new alien
		SpaceInvadersEntity *next_alien = createAlien();

		// next position
		Vector3 next_pos(start_pos);
		next_pos += Vector3( i * next_alien->getSprite()->getWidth() * sprite_xscale, 0, 0 );

		next_alien->translate( next_pos );

		main_screen->addChild( next_alien->getSprite() );
		aliens->push_back( next_alien );
	}

	// listen for input
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEDOWN );
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEUP );
}
PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
	return core->updateAndRender();

	// translate the row of aliens
	//...
}

SpaceInvadersEntity * PolycodeTemplateApp::createAlien() {
	//
	ScreenImage * alien_sprite = new ScreenImage("Resources/alien.png");
	alien_sprite->setScale( *sprite_scale );
	
	SpaceInvadersEntity *alien = new SpaceInvadersEntity( alien_sprite, new Vector3(0, 0, 0), initial_HP );

	return alien;
}

void PolycodeTemplateApp::handleEvent( Event *e ) {
	//
	if ( e->getDispatcher() == core->getInput() ) {
		//
		switch ( e->getEventCode() )
		{
		default:
			break;
		case InputEvent::EVENT_MOUSEDOWN:
			main_screen->removeChild( player->getSprite() );
			break;
		case InputEvent::EVENT_MOUSEUP:
			main_screen->addChild( player->getSprite() );
			break;
		}
	}
}