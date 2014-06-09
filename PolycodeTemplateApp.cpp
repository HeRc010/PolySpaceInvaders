/*
	The main template file/runtime file.

	TODO(high level stuffs):
	primary:
	- add missile death mechanics - missiles for the aliens; death for the player

	secondary:
	- add lives for the fighter
	- add score mechanics
		-> win/lose conditions
	- add the red ufo going accross the top
	- need to add the barriers too :S
		-> this could be really challenging...
	- sound for when the space invaders move
		-> there also needs to be sound for the red ufo
*/

#include "PolycodeTemplateApp.h"

void PolycodeTemplateApp::initializeGUIParameters() {
	// assign GUI parameters
	alien_sprite_xscale = 1;
	alien_sprite_yscale = 1;
	alien_sprite_scale = new Vector3( alien_sprite_xscale, alien_sprite_yscale, 0 );

	alien_xoffset = 100;

	player_sprite_xscale = 0.5;
	player_sprite_yscale = 0.5;
	player_sprite_scale = new Vector3( player_sprite_xscale, player_sprite_yscale, 0 );

	player_missile_scale = new Vector3( pmissile_sprite_xscale, pmissile_sprite_yscale, 0 );

	player_xoffset = 50;
	player_yoffset = 50;

	// initialize timers/timer parameters
	timer = new Timer( false, 0 );
	player_cooldown = new Timer( false, 0 );
	alien_cooldown = new Timer( false, 0 );

	duration = 500;
	player_weapon_cooldown = 700;
	alien_weapon_cooldown = 2000;

	// initialize player delta
	player_delta = Vector3( 0, 0, 0 );
}

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) : EventHandler() {
	// initialization
	core = new Win32Core(view, screen_width,screen_height,false, false, 0, 0, 60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	initializeGUIParameters();

	// Create screen
	main_screen = new PhysicsScreen( 10, 50 );

	// add background
	ScreenSprite *background = ScreenSprite::ScreenSpriteFromImageFile("Resources/background.png", Number(screen_width*2), Number(screen_height*2) );

	main_screen->addChild( background );

	// initialize fighter/player entity
	player = new Fighter();
	player->setScale( Vector3( 0.75, 0.75, 0 ) );
	player->Translate( Vector3( screen_width / 2, screen_height - player_yoffset, 0 ) );

	main_screen->addCollisionChild( player, PhysicsScreenEntity::ENTITY_RECT );

	// set the number of lives the player has
	_num_lives = 2;

	// initialize aliens
	aliens = new AlienGroup( Vector3( 100, 100, 0 ), 5, 75, 11, 75, alien_delta );
	addAliensToScreen();

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

bool PolycodeTemplateApp::Update() {
	// check if the player is still alive
	if ( player->getState() != SpaceInvadersEntity::EntityState::alive ) {
		// decrement the players lives(if there are any left) if the player has died
		if ( player->getState() == SpaceInvadersEntity::EntityState::dead ) {
			//
			if ( _num_lives != 0 ) {
				//
				--_num_lives;
				player->revive();
			} else {
				// game over

			}
		}

		return core->updateAndRender();
	}

	// process translation input
	processPlayerInput();

	// update the player missiles
	updatePlayerMissiles();

	// translate the aliens - if the necessary time has elapsed
	if ( (timer->getElapsedf() * 1000) >= duration ) {
		// change the current frame/translate the rows
		aliens->translate();
		aliens->changeAnimationFrame();

		timer->Reset();
	}

	if ( (alien_cooldown->getElapsedf() * 1000) >= alien_weapon_cooldown ) {
		//
		ScreenSprite * new_missile = aliens->fireMissile();
		
		if ( new_missile ) {
			main_screen->addCollisionChild( new_missile, PhysicsScreenEntity::ENTITY_RECT );

			alien_missiles.push_back( new_missile );
			alien_cooldown->Reset();
		}
	}

	// update aliens
	updateAliens();

	// update the alien missiles
	updateAlienMissiles();

	return core->updateAndRender();
}

void PolycodeTemplateApp::handleEvent( Event *e ) {
	//
	
	if ( e->getDispatcher() == core->getInput() ) {
		//
		InputEvent *ie = (InputEvent*) e;
		switch ( e->getEventCode() )
		{
		case InputEvent::EVENT_KEYDOWN:
			switch( ie->keyCode() ) {
			case KEY_BACKSLASH:
				// this is for debugging
				int temp = 10;
				break;
			}
			break;
		case InputEvent::EVENT_MOUSEDOWN:
			main_screen->removeChild( player );
			break;
		case InputEvent::EVENT_MOUSEUP:
			main_screen->addChild( player );
			break;
		}
	} else if ( e->getDispatcher() == main_screen ) {
		//
		PhysicsScreenEvent * pe = (PhysicsScreenEvent*) e;
		switch ( pe->getEventCode() ) {
		case PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION:
			if ( pe->entity1->hasTag("alien") ) {
				//
				aliens->killAlien( pe->entity1 );
			} else if ( pe->entity2->hasTag("alien") ) {
				//
				aliens->killAlien( pe->entity2 );
			}

			if ( pe->entity1->hasTag("p_missile") ) {
				main_screen->removeChild( pe->entity1 );
			} else if ( pe->entity2->hasTag("p_missile") ) {
				main_screen->removeChild( pe->entity2 );
			}

			if ( pe->entity1->hasTag("a_missile") ) {
				main_screen->removeChild( pe->entity1 );
			} else if ( pe->entity2->hasTag("a_missile") ) {
				main_screen->removeChild( pe->entity2 );
			}

			if ( pe->entity1->hasTag("fighter") ) {
				player->kill();
			} else if ( pe->entity2->hasTag("fighter") ) {
				player->kill();
			}
			break; 
		}
	}
}

void PolycodeTemplateApp::processPlayerInput() {
	//
	bool key_a = core->getInput()->getKeyState( KEY_a );
	bool key_d = core->getInput()->getKeyState( KEY_d );
	bool key_space = core->getInput()->getKeyState( KEY_SPACE );

	if ( key_a ) {
		//
		if ( player->getPosition().x >= (player_xoffset) ) player->Translate( Vector3( -player_delta_x, 0, 0 ) );
	}
	if ( key_d ) {
		if ( player->getPosition().x <= (screen_width - player_xoffset) ) player->Translate( Vector3( player_delta_x, 0, 0 ) );
	}
	if ( key_space ) {
		//
		if ( (player_cooldown->getElapsedf() * 1000) >= player_weapon_cooldown ) {
			firePlayerMissile();
			player_cooldown->Reset();
		}
	}
}

void PolycodeTemplateApp::addAliensToScreen() {
	//
	vector<Alien*> alien_list;
	aliens->getAliens( alien_list );

	const unsigned num_aliens = alien_list.size();
	for ( unsigned i = 0; i < num_aliens; ++i ) {
		//
		main_screen->addCollisionChild( alien_list[i], PhysicsScreenEntity::ENTITY_RECT );
	}
}

void PolycodeTemplateApp::firePlayerMissile() {
	//
	ScreenSprite * new_missile = ScreenSprite::ScreenSpriteFromImageFile( "Resources/player_missile.png", 3, 15 );
	new_missile->setScale( *( player_missile_scale ) );
	new_missile->Translate( player->getPosition() + Vector3( 0, - ( (new_missile->getHeight()*2) * new_missile->getScale().y ), 0 ) );
	new_missile->addTag("p_missile");

	main_screen->addCollisionChild( new_missile, PhysicsScreenEntity::ENTITY_RECT );
	player_missiles.push_back( new_missile );
}

void PolycodeTemplateApp::updatePlayerMissiles() {
	//
	const int num_missiles = player_missiles.size();
	for ( int i = num_missiles - 1; i >= 0; --i ) {
		//
		player_missiles[i]->Translate( Vector3( 0, -player_missile_speed, 0 ) );

		if ( player_missiles[i]->getPosition().y < 0 ) {
			//
			main_screen->removeChild( player_missiles[i] );
			player_missiles.erase( player_missiles.begin() + i );
		}
	}
}

void PolycodeTemplateApp::updateAliens() {
	// ensure the alien group does not exit the screen bounds
	Alien * bound_alien = 0;
	switch ( aliens->getCurrentDirection() ) {
	case AlienGroup::Direction::left:
		bound_alien = aliens->getLeftMostAlien();

		if ( !bound_alien ) break;

		if ( bound_alien->getPosition().x < (50 + alien_xoffset) ) {
			//
			aliens->reverseDirection();
		}
		break;
	case AlienGroup::Direction::right:
		bound_alien = aliens->getRightMostAlien();

		if ( !bound_alien ) break;

		if ( bound_alien->getPosition().x > (screen_width - alien_xoffset) ) {
			//
			aliens->reverseDirection();
		}
		break;
	}

	// get the dead aliens; remove screen and alien group
	vector<Alien*> dead_aliens = aliens->getDeadAliens();

	const unsigned num_aliens = dead_aliens.size();
	if ( num_aliens == 0 ) return;

	for ( unsigned i = 0; i < num_aliens; ++i ) {
		//
		main_screen->removeChild( dead_aliens[i] );
		aliens->removeAlien( dead_aliens[i] );
	}
}

void PolycodeTemplateApp::updateAlienMissiles() {
	//
	const int num_missiles = alien_missiles.size();
	for ( int i = num_missiles - 1; i >= 0; --i ) {
		//
		unsigned y_pos = alien_missiles[i]->getPosition().y;
		if ( (y_pos > 0) && (y_pos < screen_height) ) {
			//
			alien_missiles[i]->Translate( Vector3( 0, alien_missile_speed, 0 ) );
		} else {
			// remove the missile
			main_screen->removeChild( alien_missiles[i] );
			alien_missiles.erase( alien_missiles.begin() + i );
		}
	}
}

void PolycodeTemplateApp::gameOver() {
	//

}