#pragma once
//Modify constants in the program

//epsilon - smallest value the program will not treat as = 0
#define EPSILON 1e-8

//value of dt
#define TIME_DIFFERENTIAL 1e-3

//initial position of particles
#define INIT_POSITION_RANGE_X_MIN -1.0
#define INIT_POSITION_RANGE_X_MAX 1.0
#define INIT_POSITION_RANGE_Y_MIN -1.0
#define INIT_POSITION_RANGE_Y_MAX 1.0

//initial velocity of particles
#define INIT_VELOCITY_RANGE_X_MIN -.1
#define INIT_VELOCITY_RANGE_X_MAX .1
#define INIT_VELOCITY_RANGE_Y_MIN -.1
#define INIT_VELOCITY_RANGE_Y_MAX 0.1

//particle radius (obsolete)
//#define PARTICLE_RADIUS 1e-5

//functions defining the default container
#define FUNCTION_WALL_UP 5.0
#define FUNCTION_WALL_DOWN -5.0
#define FUNCTION_WALL_RIGHT 5.0
#define FUNCTION_WALL_LEFT -5.0

#define WALL_UP_RANGE_MIN -5.0
#define WALL_UP_RANGE_MAX 5.0
#define WALL_DOWN_RANGE_MIN -5.0
#define WALL_DOWN_RANGE_MAX 5.0
#define WALL_RIGHT_RANGE_MIN -5.0
#define WALL_RIGHT_RANGE_MAX 5.0
#define WALL_LEFT_RANGE_MIN -5.0
#define WALL_LEFT_RANGE_MAX 5.0

// range of collision detection
#define WALL_THICKNESS 1e-1
#define PARTICLE_THICKNESS 1e-2

//mass variance
#define DEFAULT_MASS 1.0
#define MASS_VARIATION 0.01

// graphic resolution
#define WALL_RESOLUTION 5 // > 1
