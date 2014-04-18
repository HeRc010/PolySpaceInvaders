#include "PolycodeTemplateApp.h"

//
#include "Fighter.h"

PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
	core = new Win32Core(view, 640,480,false, false, 0, 0,60);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	// Create screen
	Screen *main_screen = new Screen();

	// add background
	ScreenImage *background = new ScreenImage("Resources/background.png");
	main_screen->addChild( background );

	// initialize fighter
	Fighter *player = new Fighter( new ScreenImage("Resources/fighter.png") );
	main_screen->addChild( player->fighter_sprite );
}
PolycodeTemplateApp::~PolycodeTemplateApp() {
    
}

bool PolycodeTemplateApp::Update() {
	return core->updateAndRender();
}