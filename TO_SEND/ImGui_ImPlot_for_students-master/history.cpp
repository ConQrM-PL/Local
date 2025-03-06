#include "history.h"

history::history(){
    ;
}

history::history(std::vector<double> xvec, std::vector<double> yvec){
    x = xvec;
    y = yvec;
}

void history::update(double xpoint, double ypoint){
    x.push_back(xpoint);
    y.push_back(ypoint);
}