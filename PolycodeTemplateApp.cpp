/*
	The main template file/runtime file.

	TODO:
	primary:
	- add barriers
	- accelerate aliens' speed
	- add... something...

	secondary:
	- sound for when the space invaders move
		-> there also needs to be sound for the red ufo
	- should pause the timers when the game is paused
*/

#include "PolycodeTemplateApp.h"

void PolycodeTemplateApp::setup() {
	// boolean runtime values
	_initialized = false;
	_game_over = false;
	_paused = false;

	// set fighter/player entity to null
	player = 0;

	// initialize player delta
	player_delta = Vector3( 0, 0, 0 );

	// initialize aliens' pointer to zero
	aliens = 0;

	// initialize the red ufo pointer to zero
	red_ufo = 0;

	// initialize timer parameters; set timer pointers to zero
	alien_shift_timer = 0;
	alien_cooldown = 0;
	red_ufo_timer = 0;

	alien_shift_pause = 500;
	alien_weapon_cooldown = 2000;
	_red_ufo_duration = 10000;

	// score label - set to null
	_score = 0;
	score_label = 0;

	// lives' label - set to null
	lives_label = 0;
}

void PolycodeTemplateApp::initializeGame() {
	// initialize timers/timer parameters
	if ( !alien_shift_timer ) {
		alien_shift_timer = new Timer( false, 0 );
	} else {
		alien_shift_timer->Reset();
	}

	if ( !alien_cooldown ) {
		alien_cooldown = new Timer( false, 0 );
	} else {
		alien_cooldown->Reset();
	}

	if ( !red_ufo_timer ) {
		red_ufo_timer = new Timer( false, 0 );
	} else {
		red_ufo_timer->Reset();
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
	if ( aliens ) {
		// remove the aliens from the screen if there are any
		if ( aliens->getNumberOfAliens() != 0 ) removeAliensFromScreen();
		delete aliens;
	}

	aliens = new AlienGroup( Vector3( 100, 150, 0 ), 5, 75, 11, 75, alien_delta, 5 );
	addAliensToScreen();

	// if the red_ufo's pointer is not zero; set to zero
	if ( red_ufo ) {
		main_screen->removeChild( red_ufo );

		delete red_ufo;
		red_ufo = 0;
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
	
	// base location
	Vector3 base_loc( 500, 10, 0 );
	if ( !lives_label ) {
		//
		lives_label = new ScreenLabel( "Lives: ", 30 );
		lives_label->setPosition( base_loc );

		main_screen->addChild( lives_label );

		drawLifeSprites( base_loc );
	} else if ( _game_over ) {
		// remove the existing sprites
		unsigned num_sprites = life_sprites.size();
		for ( unsigned i = 0; i < num_sprites; ++i ) {
			//
			main_screen->removeChild( life_sprites[i] );
			life_sprites.erase( life_sprites.begin() + i );
		}

		drawLifeSprites( base_loc );
	}

	// set game over labels to null
	game_over_label = 0;
	replay_label = 0;

	_initialized = true;
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

	// test
	Barrier * test = new Barrier( Vector3( 250, 250, 0 ), 12, 4 );
	addBarrierToScreen( test );

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
	if ( _paused ) { 
		return core->updateAndRender();
	} else if( !_initialized ) {
		//
		initializeGame();
	} else if ( aliens->getNumberOfAliens() == 0 ) {
		// WON! YAY! - keep going
		clearMissiles();
		_initialized = false;
	} else if ( !_game_over ) {
		// check if the player is still alive
		if ( player->getState() != SpaceInvadersEntity::EntityState::alive ) {
			// pause the red ufo if not paused
			if ( red_ufo ) {
				if ( !red_ufo->isPaused() )  red_ufo->togglePause();
			}

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
		if ( (alien_shift_timer->getElapsedf() * 1000) >= alien_shift_pause ) {
			// change the current frame/translate the rows
			aliens->shift();
			aliens->changeAnimationFrame();

			alien_shift_timer->Reset();
		}

		// update the aliens
		aliens->update();

		if ( (alien_cooldown->getElapsedf() * 1000) >= alien_weapon_cooldown ) {
			//
			ScreenSprite * new_missile = aliens->fireMissile();
		
			if ( new_missile ) {
				main_screen->addCollisionChild( new_missile, PhysicsScreenEntity::ENTITY_RECT );

				alien_cooldown->Reset();
			}
		}

		// update aliens
		updateAliens();

		// update the alien missiles
		updateAlienMissiles();

		// spawn a new red ufo if there isn't one already and the timer permits
		if ( !red_ufo && ( (red_ufo_timer->getElapsedf() * 1000) >= _red_ufo_duration ) ) {
			//
			red_ufo = new RedUfo( screen_width );
			main_screen->addCollisionChild( red_ufo, PhysicsScreenEntity::ENTITY_RECT );

			red_ufo_timer->Reset();
		} else if ( red_ufo ) {
			//
			if ( red_ufo->isPaused() ) red_ufo->togglePause();

			updateRedUfo();
		}
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
			case KEY_p:
				// pause the game
				_paused = !_paused;
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

			if ( pe->entity1->hasTag("a_missile") ) {
				if ( !pe->entity2->hasTag("p_missile") ) main_screen->removeChild( pe->entity1 );
			} else if ( pe->entity2->hasTag("a_missile") ) {
				if ( !pe->entity1->hasTag("p_missile") ) main_screen->removeChild( pe->entity2 );
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

			if ( pe->entity1->hasTag("p_missile") ) {
				if ( !pe->entity2->hasTag("a_missile") ) main_screen->removeChild( pe->entity1 );
			} else if ( pe->entity2->hasTag("p_missile") ) {
				if ( !pe->entity1->hasTag("a_missile") ) main_screen->removeChild( pe->entity2 );
			}

			if ( pe->entity1->hasTag("redUFO")  ) {
				//
				main_screen->removeChild( pe->entity1 );

				// increment score
				updateScore( getPoints( pe->entity1 ) );

				delete red_ufo;
				red_ufo = 0;
			} else if ( pe->entity2->hasTag("redUFO") ) {
				main_screen->removeChild( pe->entity2 );

				// increment score
				updateScore( getPoints( pe->entity2 ) );

				delete red_ufo;
				red_ufo = 0;
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
		ScreenSprite * new_missile = player->fireMissile();

		if ( new_missile ) main_screen->addCollisionChild( new_missile, PhysicsScreenEntity::ENTITY_RECT );
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

void PolycodeTemplateApp::updatePlayerMissiles() {
	//
	vector<ScreenSprite*> missiles = player->getMissiles();
	
	for ( int i = missiles.size() - 1; i >= 0; --i ) {
		//
		if ( missiles[i]->getPosition().y < 0 ) {
			//
			main_screen->removeChild( missiles[i] );
			player->removeMissile( missiles[i] );
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
	vector<ScreenSprite*> missiles = aliens->getMissiles();
	
	for ( int i = missiles.size() - 1; i >= 0; --i ) {
		//
		if ( missiles[i]->getPosition().y > screen_height ) {
			//
			main_screen->removeChild( missiles[i] );		
			aliens->removeMissile( missiles[i] );
		}
	}
}

void PolycodeTemplateApp::clearMissiles() {
	//
	vector<ScreenSprite*> missiles = player->getMissiles();

	// player missiles
	unsigned num_missiles = missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		main_screen->removeChild( missiles[i] );
		player->removeMissile( missiles[i] );
	}

	// alien missiles
	missiles = aliens->getMissiles();

	num_missiles = missiles.size();
	for ( unsigned i = 0; i < num_missiles; ++i ) {
		//
		main_screen->removeChild( missiles[i] );
		aliens->removeMissile( missiles[i] );
	}
}

void PolycodeTemplateApp::updateRedUfo() {
	// ensure the red ufo does not go outside the bounds of the screen
	unsigned x_pos = red_ufo->getPosition().x;
	if ( (x_pos > screen_width) || (x_pos < 0) ) {
		//
		main_screen->removeChild( red_ufo );

		delete red_ufo;
		red_ufo = 0;
	}
}

void PolycodeTemplateApp::addBarrierToScreen( Barrier * to_add ) {
	//
	vector<Block*> blocks = to_add->getBlocks();
	const unsigned num_blocks = to_add->getNumBlocks();
	for ( unsigned i = 0; i < num_blocks; ++i ) {
		//
		main_screen->addCollisionChild( blocks[i], PhysicsScreenEntity::ENTITY_RECT );
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
	} else if ( entity->hasTag( "redUFO" )  ) {
		// 50, 100, or 150
		return (rand() % 3) * 50;
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

void PolycodeTemplateApp::drawLifeSprites( Vector3 base_loc ) {
	//
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