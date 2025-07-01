#include <iostream>
#include "App.h"

using namespace std;

const unsigned int WINDOW_WIDTH = 224;
const unsigned int WINDOW_HEIGHT = 288;
const unsigned int ZOOM = 2;


int main(int argc, char* argv[])
{
	App& app = App::Instance();
	if(app.Init(WINDOW_HEIGHT, WINDOW_WIDTH, ZOOM))
	{
		cout << "App initialized successfully!" << endl;
		app.Run();
	}
	else
	{
		cerr << "Failed to initialize the app!" << endl;
		return -1;
	}
	return 0;
}




