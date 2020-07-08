#pragma once


#define _CRT_SECURE_NO_WARNINGS // To be able work with "unsafe" functions

#define COUNT_OF_BOOl(Array) (_msize(Array))
#define COUNT_OF(Array) (_msize(Array)/4) 
#define SPECIAL_KEY 224 //special key returned on keyArrow-down
#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define ARROW_DOWN 80
#define EVERYWHERE -1
#define BACKSPACE 8
#define ADDITION 43
#define ARROW_UP 72
#define DELETE_ 83 // After ENHANCED_KEY
#define ENTER 13
#define SPACE 32
#define ENTER 13
#define ESC 27

#define PROJECT_NAME "Numerics"
#define NUMBER_INPUT_X 48
#define APP_WIDTH 120
#define APP_HEIGHT 30
#define INPUT_SIZE 7

#define BACKGROUND_COLOR ConsoleColor::DarkGray
#define WINDOW_COLOR ConsoleColor::LightGray

typedef unsigned int ui;

#include <windows.h> // Base
#include <conio.h> // _getch
#include <fstream> // File read/write
#include <vector>
#include <io.h> // File structure


#include "String.h"

#include "Window.h"
#include "Menu.h"

#include "Checkup.h"
#include "Files.h"

#include "Numerics.h"
#include "HillInription.h"
