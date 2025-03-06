#pragma once

// minimalny i maksymalny promień generrowanych ciał
// zalecam dać minimalny promień >= 10, bo inaczej niektóre kolizjie mogą zostać niewykryte)
// dodatkowo, minimalny promień musi być większy niż 0 (promień znajduje się w mianownikach ułamków)
#define MIN_RADIUS 10
#define MAX_RADIUS 100

// minimalna i maksymalna masa generowanych ciał
#define MIN_MASS 1e3
#define MAX_MASS 1e4

// maksymalna prędkość początkowa wygenerowanego ciała
//(to znaczy prędość v = (vx, vy), np. dla wartości 10, vx oraz vy mają wrtości z przediału [-10, 10])
#define MAX_INIT_VELOCITY 10

// maksymalna wartość początkowej pozycji wygenerowanego ciała
// (podobnie jak dla prędkości)
#define MAX_INIT_POSITION 10000

// wartość stałej grawitacyjnej
#define G_CONSTANT 1e3

// wartość epsilon - program uznaje liczby mniejsze za równe 0
#define EPSILON 1e-5

// wartość kroku czasowego
#define DT 1e-2

// rozdzielczość generowanych okręgów
// (to znaczy, z ilu punktów składają się wyświetlane okręgi) 
// min wartość: 3
#define CIRCLE_RESOLUTION 16