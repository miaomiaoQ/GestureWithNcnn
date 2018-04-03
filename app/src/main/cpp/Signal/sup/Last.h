//
// Created by lisi on 2017/9/26.
//

#ifndef MYDEMO_7_11_LAST_H
#define MYDEMO_7_11_LAST_H


class Last {
public:
    double lastDist;
    double lastPhase;

Last(){
        lastDist = 0;
        lastPhase = 0;
    }

void setLastDist(double LastDist) {
        lastDist = LastDist;
    }

void setLastPhase(double LastPhase) {
        lastPhase = LastPhase;
    }
};

#endif //MYDEMO_7_11_LAST_H
