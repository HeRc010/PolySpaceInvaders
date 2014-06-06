/*
	The main template file/runtime file.

	TODO(high level stuffs):
	- ***high priority*** add multiple rows of aliens & get translation mech. down :)
	- add lives for the fighter
	- general death-by-missle mechanics
	- add the red ufo going accross the top
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

	// assign current direction
	current_dir = PolycodeTemplateApp::direction::right;

	// spawn aliens and add to screen
	aliens = createAliens( Vector3( 40, 40, 0 ), 3, 100, 10, 30 );
	addAliensToScreen( aliens );

	// listen for input
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEDOWN );
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEUP );
}
PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

/*
	TODO:
	- translation functionality for the alien row
		- need to incorporate a current direction
		- awareness of the left-most/right-most entity for consistency in movement
		- if the left-most/right-most entity is at it's respective edge; reverse direction
	- add timer to control how long it takes before the row shifts
	- sound for when the space invaders move
		-> there also needs to be sound for the red ufo that comes accross the top every once in a while
*/
bool PolycodeTemplateApp::Update() {
	// translate the row of aliens - to the right to test
	translateAliens( aliens );

	return core->updateAndRender();
}

/*
	TODO:
	- add translation functionality for the fighter
*/
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

AlienRow * PolycodeTemplateApp::createAlienRow( Vector3 &start_pos, unsigned num_aliens, unsigned spacing ) {
	//
	return new AlienRow( *( createAlien() ), start_pos, num_aliens, spacing );
}

void PolycodeTemplateApp::addAlienRowToScreen( AlienRow * row ) {
	//
	const unsigned num_aliens = row->numAliens();
	vector<SpaceInvadersEntity*> aliens;
	row->getAliens( aliens );
	for ( unsigned i = 0; i < num_aliens; ++i ) {
		//
		main_screen->addChild( aliens[i]->getSprite() );
	}
}

void PolycodeTemplateApp::addAliensToScreen( vector<AlienRow*> aliens ) {
	//
	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		addAlienRowToScreen( aliens[i] );
	}
}

vector<AlienRow*> PolycodeTemplateApp::createAliens( Vector3 &start_pos, unsigned num_rows, unsigned row_spacing, unsigned num_aliens_per_row, unsigned sprite_spacing ) {
	//
	vector<AlienRow*> result;
	Vector3 row_offset( start_pos );
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		result.push_back( createAlienRow( row_offset, num_aliens_per_row, sprite_spacing ) );

		row_offset += Vector3( 0, row_spacing, 0 );
	}

	return result;
}

void PolycodeTemplateApp::translateAlienRow( AlienRow *row ) {
	// variable to reverse the delta direction if need be
	int reverse = 1;

	// list for retrieval
	vector<SpaceInvadersEntity*> alien_list;
	row->getAliens( alien_list );

	// a pointer to the entity at the front of the list
	// with respect to the direction the row is moving
	SpaceInvadersEntity *front_entity;

	// alter parameters based on direction
	switch( current_dir ) {
	default:
		break;
	case PolycodeTemplateApp::direction::left:
		reverse *= -1;
		front_entity = alien_list.at(0);
		break;
	case PolycodeTemplateApp::direction::right:
		front_entity = alien_list.at( alien_list.size() - 1 );
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
			front_entity = alien_list.at(0);
			break;
		case PolycodeTemplateApp::direction::left:
			current_dir = right;
			front_entity = alien_list.at( alien_list.size() - 1 );
			break;
		}
	}

	// translate
	row->translate( Vector3( delta * reverse, 0, 0 ) );
}

/*
	Translate all the alien rows. Continue until the left-most/right-most element is at the edge of the screen.

	TODO:
	- get it working...
*/
void PolycodeTemplateApp::translateAliens( vector<AlienRow*> &aliens ) {
	//
	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		translateAlienRow( aliens[i] );
	}
}