//
// Created by lisi on 2017/9/22.
//

#ifndef MYDEMO_7_11_PEAK_H
#define MYDEMO_7_11_PEAK_H


class Peak {
public:
        int* Locs;
        double* Value;
        bool* type;     //type = true + ; false -
        int Length;         //节点个数
        int size;           //空间大小
Peak(int Size)
        {
            size = Size;
            Locs = new int[size];
            Value = new double[size];
            type = new bool[size];
            Length = 0;
        }
    void setLength(int length) {
            Length = length;
        }
    void setLocs(int* locs) {
            Locs = locs;
        }
    void setValue(double* value) {
            Value = value;
        }
    int getLength() {
            return Length;
        }
    int* getLocs() {
            return Locs;
        }
    double* getValue() {
            return Value;
        }

};



#endif //MYDEMO_7_11_PEAK_H
