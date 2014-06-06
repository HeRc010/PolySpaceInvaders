/*
	The main template file/runtime file.

	TODO(high level stuffs):
	- ***high priority*** add missile functionality - and death mechanics
		-> for fighter
		-> for aliens
	- clean up fire-by-event process; it's a little finiky(?) if you press two buttons at once...
	- add lives for the fighter
	- add the red ufo going accross the top
	- sound for when the space invaders move
		-> there also needs to be sound for the red ufo that comes accross the top every once in a while
*/

#include "PolycodeTemplateApp.h"

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) : EventHandler() {
	// initialization
	core = new Win32Core(view, screen_width,screen_height,false, false, 0, 0, 60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	// assign GUI parameters
	sprite_scale = new Vector3( sprite_xscale, sprite_yscale, 0 );
	player_missile_scale = new Vector3( pmissile_sprite_xscale, pmissile_sprite_yscale, 0 );

	// initialize timer
	timer = new Timer( false, 0 );

	// initialize player delta
	player_delta = Vector3( 0, 0, 0 );

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
	aliens = createAliens( Vector3( 40, 40, 0 ), 3, 50, 10, 30 );
	addAliensToScreen( aliens );

	// listen for input
	core->getInput()->addEventListener( this, InputEvent::EVENT_KEYDOWN );
	core->getInput()->addEventListener( this, InputEvent::EVENT_KEYUP );
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
*/
bool PolycodeTemplateApp::Update() {
	// translate the aliens - if the necessary time has elapsed
	if ( (timer->getElapsedf() * 1000) >= duration ) {
		translateAliens( aliens );
		timer->Reset();
	}

	// translate player
	player->translate( player_delta );

	// update player missiles
	updatePlayerMissles( player_missiles, player_missile_speed );

	return core->updateAndRender();
}

/*
	TODO:
	- add missile firing functionality for fighter
*/
void PolycodeTemplateApp::handleEvent( Event *e ) {
	//
	
	if ( e->getDispatcher() == core->getInput() ) {
		//
		InputEvent *ie = (InputEvent*) e;
		switch ( e->getEventCode() )
		{
		case InputEvent::EVENT_KEYDOWN:
			switch( ie->keyCode() ) {
			case KEY_a:
				player_delta.x = -player_delta_x;
				break;
			case KEY_d:
				player_delta.x = player_delta_x;
				break;
			case KEY_SPACE:
				playerFireMissile();
				break;
			}
			break;
		case InputEvent::EVENT_KEYUP:
			switch ( ie->keyCode() ) {
			case KEY_a:
				player_delta.x = 0;
				break;
			case KEY_d:
				player_delta.x = 0;
				break;
			}
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

/*
	Memory leak here? not deleting the pointers?... of the sprites?...
*/
SpaceInvadersEntity * PolycodeTemplateApp::createAlien() {
	//
	ScreenImage * alien_sprite = new ScreenImage("Resources/alien.png");
	alien_sprite->setScale( *sprite_scale );

	return new SpaceInvadersEntity( alien_sprite, new Vector3(0, 0, 0), initial_HP );
}

SpaceInvadersEntity * PolycodeTemplateApp::createPlayerMissile() {
	//
	ScreenImage * player_missile_sprite = new ScreenImage("Resources/player_missile.png");
	player_missile_sprite->setScale( *player_missile_scale );

	return new SpaceInvadersEntity( player_missile_sprite, new Vector3(0, 0, 0), initial_HP );
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
	- there currently isn't functionality for all rows(of different lengths) moving in sync
*/
void PolycodeTemplateApp::translateAliens( vector<AlienRow*> &aliens ) {
	//
	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		translateAlienRow( aliens[i] );
	}
}

/*
	fire a missile from the players location; create a missile at the players location and add it to the player-missile array
*/
void PolycodeTemplateApp::playerFireMissile() {
	//
	SpaceInvadersEntity *new_missile = createPlayerMissile();
	new_missile->translate( player->getPosition() );

	main_screen->addChild( new_missile->getSprite() );

	player_missiles.push_back( new_missile );
}

/*
	translate each missile; as long as it is still within the screen - otherwise... DESTROY IT!!!
*/
void PolycodeTemplateApp::updatePlayerMissles( vector<SpaceInvadersEntity*> player_missles, int player_missile_speed ) {
	//
	const unsigned num_missles = player_missles.size();
	for ( unsigned i = 0; i < num_missles; ++i ) {
		//
		player_missles[i]->translate( Vector3( 0, -player_missile_speed, 0 ) );
	}
}