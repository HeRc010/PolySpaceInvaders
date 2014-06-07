#include "Fighter.h"

Fighter::Fighter( ScreenSprite *sprite, Vector3 *position, const unsigned &initial_HP, const int &missile_speed ) : SpaceInvadersEntity( sprite, position, initial_HP )
{
	//
	_sprite->addTag( "fighter" );

	_num_missiles = 0;
	_missile_speed = missile_speed;
}

Fighter::~Fighter()
{
	//

}

void Fighter::update() {
	//
	for ( unsigned i = 0; i < _num_missiles; ++i ) {
		//
		/*if ( _missiles[i]->getHP() == 0 ) {
			//
			_missiles[i]->kill();
		} */

		_missiles[ i ]->translate( Vector3( 0, -_missile_speed, 0 ) );
	}

	//removeDeadMissiles();
}

unsigned Fighter::getNumberOfMissiles() const {
	//
	return _num_missiles;
}

void Fighter::getMissiles( vector<SpaceInvadersEntity*> &list ) const {
	//
	list = _missiles;
}

void Fighter::removeMissile( SpaceInvadersEntity * to_remove ) {
	//
	for ( unsigned i = 0; i < _num_missiles; ++i ) {
		//
		if ( _missiles[i] == to_remove ) {
			//
			_missiles.erase( _missiles.begin() + i );
			break;
		}
	}

	--_num_missiles;
}

void Fighter::removeMissile( const unsigned &index ) {
	//
	_missiles.erase( _missiles.begin() + index );
	--_num_missiles;
}

void Fighter::removeDeadMissiles() {
	if ( _num_missiles > 0 ) return;

	// start from the end and move towards the beginning - to avoid out-of-bounds indexing
	for ( unsigned i = _num_missiles - 1; i >= 0; --i ) {
		//
		if ( !_missiles[i]->stillAlive() ) removeMissile( i );
	}
}

void Fighter::addMissile( SpaceInvadersEntity * new_missile ) {
	//
	++_num_missiles;
	_missiles.push_back( new_missile );
}