/*
	The main template file/runtime file.

	TODO:
	primary:
	- need to empty the alien and player and missile arrays when the player is killed; or when the game ends

	secondary:
	- fix the issue where player missiles can destroy alien missiles
	- animations for the alien missiles
	- add the red ufo going accross the top
	- need to add the barriers too :S
		-> this could be really challenging...
		-> i'm thinking custom sprite sheets
	- sound for when the space invaders move
		-> there also needs to be sound for the red ufo
*/

#include "PolycodeTemplateApp.h"

void PolycodeTemplateApp::setup() {
	// boolean runtime values
	_been_initialized = false;
	_game_over = false;

	// assign GUI parameters
	player_xoffset = 50;
	player_yoffset = 50;

	alien_xoffset = 150;
	alien_yoffset = 15;
	alien_delta = 15;

	// initialize timer parameters; set timer pointers to zero
	timer = 0;
	player_cooldown = 0;
	alien_cooldown = 0;

	duration = 500;
	player_weapon_cooldown = 700;
	alien_weapon_cooldown = 2000;

	// initialize player delta
	player_delta = Vector3( 0, 0, 0 );

	// score label - set to null
	_score = 0;
	score_label = 0;

	// lives' label - set to null
	lives_label = 0;

	// set fighter/player entity to null
	player = 0;

	// initialize aliens' pointer to zero
	aliens = 0;
}

void PolycodeTemplateApp::initializeGame() {
	// initialize timers/timer parameters
	if ( !timer ) {
		timer = new Timer( false, 0 );
	} else {
		timer->Reset();
	}
	
	if ( !player_cooldown ) {
		player_cooldown = new Timer( false, 0 );
	} else {
		player_cooldown->Reset();
	}

	if ( !alien_cooldown ) {
		alien_cooldown = new Timer( false, 0 );
	} else {
		alien_cooldown->Reset();
	}

	// initialize fighter/player entity
	if ( !player ) {
		player = new Fighter();
		player->setScale( Vector3( 0.75, 0.75, 0 ) );
		player->Translate( Vector3( screen_width / 2, screen_height - player_yoffset, 0 ) );

		main_screen->addCollisionChild( player, PhysicsScreenEntity::ENTITY_RECT );
	} else if ( _game_over ) {
		if ( player->getState() != SpaceInvadersEntity::EntityState::alive ) {
			player->revive();
			player->restoreLives();
		}
	
		player->Translate( Vector3( screen_width / 2, screen_height - player_yoffset, 0 ) - player->getPosition() );
	}

	// initilize aliens
	if ( !aliens ) {
		aliens = new AlienGroup( Vector3( 100, 100, 0 ), 5, 75, 11, 75, alien_delta );
		addAliensToScreen();
	} else {
		// remove the aliens from the screen if there are any
		if ( aliens->getNumberOfAliens() != 0 ) removeAliensFromScreen();

		delete aliens;

		aliens = new AlienGroup( Vector3( 100, 100, 0 ), 5, 75, 11, 75, alien_delta );
		addAliensToScreen();
	}

	// initialize the score label
	if ( !score_label ) {
		char buffer[256];
		itoa( _score, buffer, 10 );

		score_label = new ScreenLabel( "Score: " + String( buffer ), 30 );
		score_label->setPosition( Vector3( 200, 10, 0 ) );

		main_screen->addChild( score_label );
	} else if( _game_over ) {
		// reset score to zero
		updateScore( -_score );
	}

	// initialize the lives' label
	if ( !lives_label ) {
		// base location
		Vector3 base_loc( 500, 10, 0 );

		ScreenLabel * lives_label = new ScreenLabel( "Lives: ", 30 );
		lives_label->setPosition( base_loc );

		main_screen->addChild( lives_label );

		base_loc += Vector3( 150, 25, 0 );
		for ( unsigned i = 0; i < player->getNumLives(); ++i ) {
			//
			ScreenSprite * new_sprite = new ScreenSprite( "Resources/fighter_1.png", 85, 53 );
			new_sprite->setScale( Vector3( 0.5, 0.5, 0 ) );
			new_sprite->setPosition( base_loc );

			main_screen->addChild( new_sprite );
		
			life_sprites.push_back( new_sprite );
			base_loc += Vector3( 50, 0, 0 );
		}
	} else if ( _game_over ) {
		// remove the existing sprites
		unsigned num_sprites = life_sprites.size();
		for ( unsigned i = 0; i < num_sprites; ++i ) {
			//
			main_screen->removeChild( life_sprites[i] );
			life_sprites.erase( life_sprites.begin() + i );
		}

		// base location
		Vector3 base_loc( 500, 10, 0 );
		base_loc += Vector3( 150, 25, 0 );
		for ( unsigned i = 0; i < player->getNumLives(); ++i ) {
			//
			ScreenSprite * new_sprite = new ScreenSprite( "Resources/fighter_1.png", 85, 53 );
			new_sprite->setScale( Vector3( 0.5, 0.5, 0 ) );
			new_sprite->setPosition( base_loc );

			main_screen->addChild( new_sprite );
		
			life_sprites.push_back( new_sprite );
			base_loc += Vector3( 50, 0, 0 );
		}
	}

	// set game over labels to null
	game_over_label = 0;
	replay_label = 0;

	// clear the missiles
	clearMissiles();

	_been_initialized = true;
}

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) : EventHandler() {
	// initialization
	core = new Win32Core(view, screen_width,screen_height,false, false, 0, 0, 60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	// Create screen
	main_screen = new PhysicsScreen( 10, 50 );

	// add background
	ScreenSprite *background = ScreenSprite::ScreenSpriteFromImageFile("Resources/background.png", Number(screen_width*2), Number(screen_height*2) );

	main_screen->addChild( background );

	setup();

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
	// if the game hasn't been initialized do so
	if ( !_been_initialized ) {
		//
		initializeGame();
	} else if ( aliens->getNumberOfAliens() == 0 ) {
		// WON! YAY! - keep going
		_been_initialized = false;
	} else if ( !_game_over ) {
		// check if the player is still alive
		if ( player->getState() != SpaceInvadersEntity::EntityState::alive ) {
			// decrement the players lives(if there are any left) if the player has died
			if ( player->getState() == SpaceInvadersEntity::EntityState::dead ) {
				//
				if ( player->getNumLives() != 0 ) {
					//
					player->revive();

					// remove a life from the lives' label
					removeLife();
				} else {
					// game over
					_game_over = true;
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
			aliens->shift();
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
	} else {
		//
		drawGameOverLabel();
	}

	return core->updateAndRender();
}

void PolycodeTemplateApp::handleEvent( Event *e ) {
	//
	int temp = 0;
	if ( e->getDispatcher() == core->getInput() ) {
		//
		InputEvent *ie = (InputEvent*) e;
		switch ( e->getEventCode() )
		{
		case InputEvent::EVENT_KEYDOWN:
			switch( ie->keyCode() ) {
			case KEY_BACKSLASH:
				// this is for debugging
				temp = 1;
				break;
			case KEY_RETURN:
				if ( _game_over ) {
					// delete the game over labels
					main_screen->removeChild( game_over_label );
					main_screen->removeChild( replay_label );

					delete game_over_label;
					delete replay_label;

					initializeGame();
					_game_over = false;
				}
				break;
			case KEY_k:
				// cheat; use to kill all the aliens
				removeAliensFromScreen();
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

				// increment score
				updateScore( getPoints( pe->entity1 ) );
			} else if ( pe->entity2->hasTag("alien") ) {
				//
				aliens->killAlien( pe->entity2 );

				// increment score
				updateScore( getPoints( pe->entity2 ) );
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

				// empty the missile arrays
				clearMissiles();
			} else if ( pe->entity2->hasTag("fighter") ) {
				player->kill();
				// empty the missile arrays
				clearMissiles();				
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
void PolycodeTemplateApp::removeAliensFromScreen() {
	//
	vector<Alien*> alien_list;
	aliens->getAliens( alien_list );

	const unsigned num_aliens = alien_list.size();
	for ( unsigned i = 0; i < num_aliens; ++i ) {
		//
		main_screen->removeChild( alien_list[i] );
		
		aliens->removeAlien( alien_list[i] );
	}
}


void PolycodeTemplateApp::firePlayerMissile() {
	//
	ScreenSprite * new_missile = ScreenSprite::ScreenSpriteFromImageFile( "Resources/player_missile.png", 3, 15 );
	new_missile->setScale( Vector3( 1, 1, 0 ) );
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
			aliens->translate( Vector3( 0, alien_yoffset, 0 ) );
		}
		break;
	case AlienGroup::Direction::right:
		bound_alien = aliens->getRightMostAlien();

		if ( !bound_alien ) break;

		if ( bound_alien->getPosition().x > (screen_width - alien_xoffset) ) {
			//
			aliens->reverseDirection();
			aliens->translate( Vector3( 0, alien_yoffset, 0 ) );
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

void PolycodeTemplateApp::clearMissiles() {
	// player missiles
	const unsigned num_player_missiles = player_missiles.size();
	for ( unsigned i = 0; i < num_player_missiles; ++i ) {
		//
		main_screen->removeChild( player_missiles[i] );
		player_missiles.erase( player_missiles.begin() + i );
	}

	// alien missiles
	const unsigned num_alien_missiles = alien_missiles.size();
	for ( unsigned i = 0; i < num_alien_missiles; ++i ) {
		//
		main_screen->removeChild( alien_missiles[i] );
		alien_missiles.erase( alien_missiles.begin() + i );
	}
}

unsigned PolycodeTemplateApp::getPoints( ScreenEntity * entity ) const {
	//
	if ( entity->hasTag( "alien_one" ) ) {
		//
		return 10;
	} else if ( entity->hasTag( "alien_two" ) ) {
		//
		return 20;
	} else if ( entity->hasTag( "alien_three" )  ) {
		//
		return 40;
	} else {
		return 0;	
	}
}

void PolycodeTemplateApp::updateScore( unsigned inc ) {
	// increase the value
	_score += inc; 

	// update the label
	char buffer[ 256 ];
	itoa( _score, buffer, 10 );

	score_label->setText( "Score: " + String( buffer ) );
}

void PolycodeTemplateApp::removeLife() {
	//
	const unsigned idx = life_sprites.size() - 1;

	main_screen->removeChild( life_sprites[idx] );
	life_sprites.erase( life_sprites.begin() + idx );
}

void PolycodeTemplateApp::drawGameOverLabel() {
	//
	if ( !game_over_label ) {
		game_over_label = new ScreenLabel( "GAME OVER", 50 );
		game_over_label->setPosition( Vector3( (screen_width / 2) - (game_over_label->getWidth() / 2), (screen_height / 2) - (game_over_label->getHeight() / 2), 0 ) );

		main_screen->addChild( game_over_label );
	}

	if ( !replay_label ) {
		//
		replay_label = new ScreenLabel( "Press enter to play again", 50 );
		replay_label->setPosition( Vector3( (screen_width / 2) - (replay_label->getWidth() / 2), (screen_height / 2) - (replay_label->getHeight() / 2) + (100), 0 ) );

		main_screen->addChild( replay_label );
	}
}