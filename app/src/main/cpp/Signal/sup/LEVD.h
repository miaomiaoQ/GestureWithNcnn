//
// Created by lisi on 2017/9/22.
//

#ifndef MYDEMO_7_11_LEVD_H
#define MYDEMO_7_11_LEVD_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include "Peak.h"

class LEVD {
    public: bool flag ;       //是否找到第一个极值对
    double Thr;
    bool first;
    double *last;
    double last_SI;
    double *levd_SI;
    double last_Pks;
    bool last_type;
    double *levd_out;
    LEVD();
    bool levd(double *in);

};


#endif //MYDEMO_7_11_LEVD_H
