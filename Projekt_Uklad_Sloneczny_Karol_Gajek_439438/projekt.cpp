#include "main.h"

// krok czasu
#define DT 10*(24*60*60)
// Maksymalny czas
#define TMAX 1000*((long int)DT)
// czestotliwosc generowania grafik (co ile okresow)
#define CZESTOSC 50

using namespace std;

int main (){
    Uklad_Sloneczny solar(DT);
    solar.read();
    while(solar.get_t()<=TMAX){
        solar.save_step();
        if (!((long int) solar.get_t()%(long int) (CZESTOSC*DT))) solar.draw();
        solar.step();
    }
    return 0;
}