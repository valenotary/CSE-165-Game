#include "gamewindow.h"
int main(int argc, char** argv) {
	gamewindow* test = new gamewindow(argc, argv);
	test->run();
}