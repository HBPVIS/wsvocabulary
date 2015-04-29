#include "App.h"

int main(int argc, char **argv)
{
	//setup the basic tutorial object
	App *pApp = new App;

	//initialize basics (you'll not have to have a look at this one)
	if (!pApp->Init(argc, argv))
	{
		delete pApp;
		return -1;
	}

	//finally kick it...
	pApp->Run();


	//clean-up
	delete pApp;

	return 0;
}
