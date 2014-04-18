#include "PolycodeView.h"
#include "Polycode.h"

//
#include "Fighter.h"

using namespace Polycode;

class PolycodeTemplateApp : public EventHandler {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();
    
	// data
	Screen *main_screen;
	Fighter *player;

	// functions
    bool Update();
	void handleEvent( Event *e );
    
private:
    Core *core;
};