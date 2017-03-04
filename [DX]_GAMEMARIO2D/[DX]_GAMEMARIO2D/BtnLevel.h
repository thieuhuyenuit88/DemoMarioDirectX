#include "MyButton.h"
#include "DXFont.h"

template <class cInstance>
class BtnLevel: public MyButton<cInstance>{
private:

	int level;
	DXFont* gameFont;

public:

	BtnLevel(void):MyButton<cInstance>(void){

	}

	BtnLevel()
};