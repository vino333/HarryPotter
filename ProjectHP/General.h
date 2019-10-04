#pragma once
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#else
#error "Unrecognized configuration!"
#endif

//=============================================================================

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>
#include <string>
#include <math.h>
#include <queue>

//=============================================================================

using std::vector;
using std::string;
using std::queue;
using std::shared_ptr;
using std::make_shared;
using std::pair;
using std::find;
using std::min;
using std::max;
using std::any_of;
using std::for_each;
using std::abs;
using std::to_string;
using std::swap;

//=============================================================================

const int PLAY = 0;
const int EXIT = 1;
const int RESUME = 2;
const int HELP = 3;
const int NOTHING = 4;

//=============================================================================

enum Direction { DOWN = 0, UP, RIGHT, LEFT, STAND, ATTACK, WEAPON};
enum GameState { WALK = 0, SHOOTATTAK, SWORDATTAK, WANDATTAK, WHITEWANDATTACK,BROWNWANDATTACK};

//=============================================================================

const int NUM_OF_LEVELS = 4;
const int HEIGHT = 17;
const int WIDTH = 170;
const int SQUARE_SIZE = 40;

//=============================================================================
