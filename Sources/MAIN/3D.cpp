#include "Controller.h"

int main() {
	Controller *controller = new Controller();
	controller->launch();
	delete controller;
	controller = NULL;
	
	return 0;
}