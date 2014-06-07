/*
	The main template file/runtime file.

	TODO(high level stuffs):
	- add explosion animations for the aliens
	- add different types of aliens per row
		-> need to add different types in general
	- need to fix the occasional problem where rows pretend like the fallen guy on the far side is still alive; in their translation :S
		-> is this still(was ever?) a problem?
	- add missile functionality - and death mechanics
		-> need to get the aliens shooting back; and the player killed if hit
	- general(a lot of it) refactoring; significant redesign of architecture to minimize code in this file :S
	- add lives for the fighter
	- add the red ufo going accross the top
	- sound for when the space invaders move
		-> there also needs to be sound for the red ufo
*/

#include "PolycodeTemplateApp.h"

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) : EventHandler() {
	// initialization
	core = new Win32Core(view, screen_width,screen_height,false, false, 0, 0, 60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	// assign GUI parameters
	alien_width_1 = 168;
	alien_height_1 = 53;

	alien_width_2 = 154;
	alien_height_2 = 52;

	alien_width_2 = 132;
	alien_height_2 = 53;

	alien_sprite_xscale = 1;
	alien_sprite_yscale = 1;
	alien_sprite_scale = new Vector3( alien_sprite_xscale, alien_sprite_yscale, 0 );

	alien_offset = 50;

	cur_alien_frame = 0;

	player_width = 85;
	player_height = 53;
	player_sprite_xscale = 0.5;
	player_sprite_yscale = 0.5;
	player_sprite_scale = new Vector3( player_sprite_xscale, player_sprite_yscale, 0 );

	pmissile_width = 3;
	pmissile_height = 15;
	player_missile_scale = new Vector3( pmissile_sprite_xscale, pmissile_sprite_yscale, 0 );

	player_xoffset = 50;
	player_yoffset = 50;

	// initialize timers/timer parameters
	timer = new Timer( false, 0 );
	weapon_cooldown = new Timer( false, 0 );

	duration = 500;

	// initialize player delta
	player_delta = Vector3( 0, 0, 0 );

	// Create screen
	main_screen = new PhysicsScreen( 10, 50 );

	// add background
	ScreenSprite *background = ScreenSprite::ScreenSpriteFromImageFile("Resources/background.png", Number(screen_width*2), Number(screen_height*2) ); //new ScreenSprite("Resources/background.png");

	main_screen->addChild( background );

	// initialize fighter/player entity
	ScreenSprite *player_sprite = ScreenSprite::ScreenSpriteFromImageFile("Resources/fighter_1.png", Number(player_width*2), Number(player_height*2) ); //new ScreenSprite("Resources/fighter_1.png");
	player_sprite->setScale( *player_sprite_scale );
	
	Vector3 *location = new Vector3( float( screen_width/2 ) - (player_sprite->getWidth() * player_sprite_xscale / 2), float( screen_height - ( (player_sprite->getHeight()/2) * player_sprite_yscale ) ) - player_yoffset, 0 );

	player = new Fighter( player_sprite, location, initial_HP, player_missile_speed );
	main_screen->addCollisionChild( player->getSprite(), PhysicsScreenEntity::ENTITY_RECT );

	// assign current direction
	current_dir = direction::right;

	// test
	//AlienOne *test_alien_one = new AlienOne( new Vector3( 0, 0, 0 ), 100, 600 );

	AlienRow *test_row = new AlienRow( *( new AlienOne( new Vector3( 0, 0, 0 ), 100, 600, *( alien_sprite_scale ) ) ), Vector3( 100, 100, 0 ), 5, 100 );

	const unsigned num_aliens = test_row->getNumAliens();
	vector<Alien*> alien_list;
	test_row->getAliens( alien_list );
	for ( unsigned i = 0; i < num_aliens; ++i ) {
		//
		main_screen->addChild( alien_list[i]->getSprite() );
	}

	aliens.push_back( test_row );

	// spawn aliens and add to screen
	//aliens = createAliens( Vector3( 100, 100, 0 ), 3, 100, 10, 100 );
	//addAliensToScreen( aliens );

	// listen for input
	core->getInput()->addEventListener( this, InputEvent::EVENT_KEYDOWN );
	core->getInput()->addEventListener( this, InputEvent::EVENT_KEYUP );
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEDOWN );
	core->getInput()->addEventListener( this, InputEvent::EVENT_MOUSEUP );

	// listen for collisions
	main_screen->addEventListener( this, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION );
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

/*
	TODO:
	- translation functionality for the alien row
		- need to incorporate a current direction
		- awareness of the left-most/right-most entity for consistency in movement - this might be in there already...
		- if the left-most/right-most entity is at it's respective edge; reverse direction
*/
bool PolycodeTemplateApp::Update() {
	// translate the aliens - if the necessary time has elapsed
	/* if ( (timer->getElapsedf() * 1000) >= duration ) {
		translateAliens( aliens );
		
		// change the current frame
		++cur_alien_frame;
		cur_alien_frame %= 2;
		changeAlienFrame( cur_alien_frame );

		timer->Reset();
	} */

	// update the player
	/* player->update();

	// update the aliens
	vector<Alien*> alien_list;
	aliens[0]->getAliens( alien_list );
	for ( unsigned i = 0; i < aliens[0]->getNumAliens(); ++i ) {
		//
		alien_list[i]->update();
	}

	// process translation input
	processPlayerInput();

	// clean-up player missile list
	cleanPlayerMissiles(); */

	// update player missiles
	//updatePlayerMissles( player_missiles, player_missile_speed );

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
			case KEY_SPACE:
				if ( (weapon_cooldown->getElapsedf() * 1000) >= weapon_cooldown_time ) {
					ScreenSprite * new_missile = ScreenSprite::ScreenSpriteFromImageFile( "Resources/player_missile.png", 3, 15 );
					new_missile->setScale( *( player_missile_scale ) );
					new_missile->Translate( player->getPosition() );

					main_screen->addCollisionChild( new_missile, PhysicsScreenEntity::ENTITY_RECT );

					SpaceInvadersEntity *missile_entitiy = new SpaceInvadersEntity( new_missile, &player->getPosition(), initial_HP );
					player->addMissile( missile_entitiy );
					weapon_cooldown->Reset();
				}
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
	} else if ( e->getDispatcher() == main_screen ) {
		//
		PhysicsScreenEvent * pe = (PhysicsScreenEvent*) e;
		switch ( pe->getEventCode() ) {
		case PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION:
			/* if ( isPlayerMissile( pe->entity1 ) ) {
				removePlayerMissile( pe->entity1 );
			} else if ( isPlayerMissile( pe->entity2 ) ) {
				removePlayerMissile( pe->entity2 );
			}

			if ( isAlien( pe->entity1 ) ) {
				removeAlien( pe->entity1 );

				// display an explosion sprite at the alien's location
				Vector3 loc( pe->entity1->getPosition() );

				ScreenImage *explosion = new ScreenImage("Resources/alien_explosion.png");
				loc.x += -explosion->getImageWidth();
				loc.y += -explosion->getImageHeight();
				explosion->Translate( loc );

				main_screen->addChild( explosion );
				//main_screen->removeChild( explosion );
			} else if ( isAlien( pe->entity2 ) ) {
				removeAlien( pe->entity2 );

				// display an explosion sprite at the alien's location
				Vector3 loc( pe->entity1->getPosition() );

				ScreenImage *explosion = new ScreenImage("Resources/alien_explosion.png");
				loc.x += -explosion->getImageWidth();
				loc.y += -explosion->getImageHeight();
				explosion->Translate( loc );

				main_screen->addChild( explosion );
				//main_screen->removeChild( explosion );
			} */
			break; 
		}
	}
}

void PolycodeTemplateApp::processPlayerInput() {
	//
	bool key_a = core->getInput()->getKeyState( KEY_a );
	bool key_d = core->getInput()->getKeyState( KEY_d );

	if ( key_a ) {
		//
		if ( player->getPosition().x >= (player_xoffset) ) player->translate( Vector3( -player_delta_x, 0, 0 ) );
	}
	if ( key_d ) {
		if ( player->getPosition().x <= (screen_width - player_xoffset) ) player->translate( Vector3( player_delta_x, 0, 0 ) );
	}
}

/* void PolycodeTemplateApp::cleanPlayerMissiles() {
	//
	const unsigned num_missiles = player->getNumberOfMissiles();
	vector<SpaceInvadersEntity*> missile_list;
	player->getMissiles( missile_list );
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		Vector3 pos( missile_list[i]->getPosition() );
		if ( (pos.y <= 0) ) { //|| (pos.y >= screen_height) ) {
			//
			player->removeMissile( i );
			main_screen->removeChild( missile_list[i]->getSprite() );
		}
	}
} */

/*
	Memory leak here? not deleting the pointers?... of the sprites?...
*/
/* SpaceInvadersEntity * PolycodeTemplateApp::createAlienOne() {
	// only take half the width; the other half is the second anim. frame
	ScreenSprite * alien_sprite = ScreenSprite::ScreenSpriteFromImageFile( "Resources/Alien_1.png", Number(alien_width_1/2), Number(alien_height_1) );
	alien_sprite->setScale( *alien_sprite_scale );

	// add animations
	alien_sprite->addAnimation( "frame_0", "0", 1 );
	alien_sprite->addAnimation( "frame_1", "1", 1 );
	alien_sprite->playAnimation( "frame_1", 0, false );

	return new SpaceInvadersEntity( alien_sprite, new Vector3(0, 0, 0), initial_HP );
}

SpaceInvadersEntity * PolycodeTemplateApp::createPlayerMissile() {
	//
	ScreenSprite * player_missile_sprite = ScreenSprite::ScreenSpriteFromImageFile( "Resources/alien_1.png", pmissile_width*2, pmissile_height*2 );
	player_missile_sprite->setScale( *player_missile_scale );

	return new SpaceInvadersEntity( player_missile_sprite, new Vector3(0, 0, 0), initial_HP );
}

AlienRow * PolycodeTemplateApp::createAlienRow( Vector3 &start_pos, unsigned num_aliens, unsigned spacing ) {
	//
	return new AlienRow( *( createAlienOne() ), start_pos, num_aliens, spacing );
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

void PolycodeTemplateApp::addAlienRowToScreen( AlienRow * row ) {
	//
	const unsigned num_aliens = row->getNumAliens();
	vector<SpaceInvadersEntity*> aliens;
	row->getAliens( aliens );
	for ( unsigned i = 0; i < num_aliens; ++i ) {
		//
		main_screen->addCollisionChild( aliens[i]->getSprite(), PhysicsScreenEntity::ENTITY_RECT );
		//main_screen->addChild( aliens[i]->getSprite() );
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

void PolycodeTemplateApp::changeAlienFrame( unsigned next_frame ) {
	// make sure the frame is either 0 or 1
	assert( next_frame < 2 );

	// create the frame string
	Polycode::String str = "frame_";
	char temp[256];

	itoa(next_frame, temp, 10);
	Polycode::String *val = new String(temp);
	
	Polycode::String res = str + *val;
	str = res;

	//
	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		const unsigned num_aliens = aliens[i]->getNumAliens();
		vector<SpaceInvadersEntity*> alien_list;
		aliens[i]->getAliens( alien_list );
		for ( unsigned i = 0; i < num_aliens; ++i ) {
			//
			alien_list[i]->getSprite()->playAnimation( str, next_frame, false );
		}
	}
}

void PolycodeTemplateApp::translateAlienRow( AlienRow *row ) {
	// if there are now aliens in the row; return
	if ( row->getNumAliens() == 0 ) return;
	
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
	if ( ( next_position.x > (screen_width - alien_offset) ) || ( next_position.x < alien_offset ) ) {
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


void PolycodeTemplateApp::translateAliens( vector<AlienRow*> &aliens ) {
	//
	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		translateAlienRow( aliens[i] );
	}
}

// Issue: adding the sprite as a collision child shifts it's position slightly; in a manner not see when adding as a normal child
void PolycodeTemplateApp::playerFireMissile() {
	//
	SpaceInvadersEntity *new_missile = createPlayerMissile();
	new_missile->translate( player->getPosition() + Vector3( -(new_missile->getSprite()->getWidth() * pmissile_sprite_xscale / 2), -( ((player->getSprite()->getHeight()/2) * player_sprite_yscale) + (new_missile->getSprite()->getHeight() * pmissile_sprite_yscale) ), 0 ) );

	main_screen->addCollisionChild( new_missile->getSprite(), PhysicsScreenEntity::ENTITY_RECT );
	
	// see issue above
	//main_screen->addChild( new_missile->getSprite() );

	player_missiles.push_back( new_missile );
}

void PolycodeTemplateApp::updatePlayerMissles( vector<SpaceInvadersEntity*> player_missles, int player_missile_speed ) {
	//
	unsigned num_missiles = player_missles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		player_missles[i]->translate( Vector3( 0, -player_missile_speed, 0 ) );

		if ( player_missiles[i]->getSprite()->getPosition().y < 0 ) {
			// remove from the screen
			main_screen->removeChild( player_missiles[i]->getSprite() );

			player_missiles.erase( player_missiles.begin() + i );
			--num_missiles;
		}
	}
}

bool PolycodeTemplateApp::isPlayerMissile( ScreenEntity * entity  ) {
	//
	const unsigned num_missiles = player_missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		if ( player_missiles[i]->getSprite() == entity  ) {
			return true;
		}
	}

	return false;
}

void PolycodeTemplateApp::removePlayerMissile( ScreenEntity * to_remove ) {
	//
	main_screen->removeChild( to_remove );

	const unsigned num_missiles = player_missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		if ( to_remove == player_missiles[i]->getSprite() ) {
			player_missiles.erase( player_missiles.begin() + i );
			break;
		}
	}
}

bool PolycodeTemplateApp::isAlien( ScreenEntity * entity ) {
	//
	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		if ( aliens[i]->containsAlien( entity ) ) return true;
	}

	return false;
}

void PolycodeTemplateApp::removeAlien( ScreenEntity * to_remove ) {
	//
	assert( isAlien( to_remove ) );

	main_screen->removeChild( to_remove );

	const unsigned num_rows = aliens.size();
	for ( unsigned i = 0; i < num_rows; ++i ) {
		//
		if ( aliens[i]->containsAlien( to_remove ) ) {
			aliens[i]->removeAlien( to_remove );
			break;
		}
	}
} */