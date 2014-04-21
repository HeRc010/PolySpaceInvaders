/*
	The main template file/runtime file.
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
	/* aliens = new vector<SpaceInvadersEntity*>( 0 );
	
	Vector3 start_pos(offset, float(screen_height/2), 0);
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
	} */

	// assign current direction
	//current_dir = PolycodeTemplateApp::direction::right;

	// spawn row of aliens
	AlienRow *test_row = new AlienRow( *( createAlien() ), Vector3( 40, 40, 0 ), 10, 30 );

	// add the aliens to the screen
	vector<SpaceInvadersEntity*> list;
	test_row->getAliens( list );
	for ( int i = 0; i < list.size(); ++i ) {
		//
		main_screen->addChild( list[i]->getSprite() );
	}

	// listen for input
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEDOWN );
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEUP );
}
PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
	// translate the row of aliens - to the right to test
	//translateAliens( aliens );

	return core->updateAndRender();
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

SpaceInvadersEntity * PolycodeTemplateApp::createAlien() {
	//
	ScreenImage * alien_sprite = new ScreenImage("Resources/alien.png");
	alien_sprite->setScale( *sprite_scale );
	
	SpaceInvadersEntity *alien = new SpaceInvadersEntity( alien_sprite, new Vector3(0, 0, 0), initial_HP );

	return alien;
}

void PolycodeTemplateApp::translateAliens( AlienRow *row ) { //vector<SpaceInvadersEntity*> *alien_list ) {
	// factor to reverse the delta direction if need be
	int reverse = 1;

	// list reference
	vector<SpaceInvadersEntity*> *alien_list;
	row->getAliens( *( alien_list ) );

	// a pointer to the entity at the front of the list
	// with respect to the direction the row is moving
	SpaceInvadersEntity *front_entity;

	// alter parameters based on direction
	switch( current_dir ) {
	default:
		break;
	case PolycodeTemplateApp::direction::left:
		reverse *= -1;
		front_entity = alien_list->at(0);
		break;
	case PolycodeTemplateApp::direction::right:
		front_entity = alien_list->at( alien_list->size() - 1 );
		break;
	}

	// delta vector
	Vector3 *delta_vec = new Vector3( delta * reverse, 0, 0 );

	// check if the front element will escape the bound(s) if incremented
	// by the offset, if so, reverse the direction
	Vector3 next_position = front_entity->getPosition() + *delta_vec;
	if ( ( next_position.x > (screen_width - offset) ) || ( next_position.x < offset ) ) {
		reverse *= -1;

		switch( current_dir ) {
		default:
			break;
		case PolycodeTemplateApp::direction::right:
			current_dir = left;
			front_entity = alien_list->at(0);
			break;
		case PolycodeTemplateApp::direction::left:
			current_dir = right;
			front_entity = alien_list->at( alien_list->size() - 1 );
			break;
		}
	}

	// translate
	row->translate( Vector3( delta * reverse, 0, 0 ) );
}