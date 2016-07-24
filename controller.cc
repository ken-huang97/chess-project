#include "controller.h"
#include "board.h"

Controller::Controller(Board *board, int player): board{board}, player{player} {}

Controller::~Controller() {}