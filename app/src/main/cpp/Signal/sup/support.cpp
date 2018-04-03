//
// Created by lisi on 2017/9/22.
//


#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "../mycic/MyCic.h"
#include "LEVD.h"
#include "Last.h"
#include "../ADist/ADist.h"

#define recBufSize 4400*2			//定义录音片长度

#define numfre 8
#define Deci 40
#define CutLength  4400           //切片长度
#define LastLength 2200        //窗口长度
#define PassLength LastLength/Deci        //丢弃长度
#define Short_Max_Value 32767

int  Freqarrary[] = {17500,17850,18200,18550,18900,19250,19600,19950,20300,20650}	;	//设置播放频率

#define IQ_Length 110

#define TAG    "myjni-test" // 这个是自定义的LOG的标识
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义//LOGW类型

class newdemo{
private:
public:
    newdemo()
    {
        lastL = new Last();
        lastR = new Last();
        now = 0;
        lastRecordL = new short[LastLength];
        lastRecordR = new short[LastLength];
    }
    ~newdemo()
    {
        delete []lastRecordL;
        delete []lastRecordR;
    }
    Last *lastL;
    Last *lastR;
    int now;
    short *lastRecordL;
    short *lastRecordR;
    LEVD levdIL[numfre];
    LEVD levdQL[numfre];
    LEVD levdIR[numfre];
    LEVD levdQR[numfre];
};



int* Ichange(short *in,int fre,int now)
{
    int *out = new int[CutLength+LastLength];
    double x = fre*2.0* M_PI/44100.0;
    for(int i=1;i<=CutLength+LastLength;i++) {
        out[i-1] = (int)(in[i-1] *((cos((i+(2*now-1)*2200) * x))*Short_Max_Value));
    }
    return out;
}

int* Qchange(short *in,int fre,int now)
{
    int *out = new int[CutLength+LastLength];
    double x = fre*2.0* M_PI/44100.0;
    for(int i=1;i<=CutLength+LastLength;i++) {
        out[i-1] = (int)(in[i-1] *((sin((i+(2*now-1)*2200) * x))*Short_Max_Value));
    }
    return out;
}

 double* getPhase(double* I,double* Q)
{
    double* out = new double[IQ_Length+1];
        out[0] = 0;
        for(int i = 1;i<=IQ_Length;i++) {
            out[i] = atan2(Q[i-1],I[i-1]);
//            Log.w("phase",String.valueOf(out[i]));
            out[0] +=out[i];
        }
        return out;
    }
 double countPhase(double last,double now)
{
    double dPhase;
    if ((now >= last && now - last < M_PI)||(now <last && last - now < M_PI))
        dPhase = now - last;
    else if (now -last >= M_PI)
        dPhase = now - last - 2 * M_PI;
    else if (last -now >= M_PI)
        dPhase = now - last + 2 * M_PI;
    else
        dPhase = 0;
    return dPhase;
}

 double* getDist(double lastDist,double lastPhase,double* Phase,int fre)
{
    double* temp = new double[IQ_Length];
        memcpy(temp,Phase+1,IQ_Length*sizeof(double));
        double v = 34300;
        double wl = v/fre;
        double* Dist = new double[IQ_Length];
        if(lastPhase<0)
            lastPhase = lastPhase +2*M_PI;
        for(int i = 0;i<IQ_Length;i++) {     //i=1
            if(temp[i]<0)
                temp[i]+=(M_PI*2);
            if (i >0)
                Dist[i] = Dist[i-1]+countPhase(temp[i-1],temp[i])/2/M_PI*wl/2;
            else
                Dist[0] = lastDist+countPhase(lastPhase,temp[0])/2/M_PI*wl/2;
        }
//        Log.w("dist",String.valueOf(Dist[Dist.length-1]));
        return Dist;
    }

double myADist(double *I,double *Q,double *Dist);
double demo(short *CoRecord,int now,Last *last,
            LEVD *levdI, LEVD *levdQ,double DIST[110],double *tempII,double *tempQQ)
{
    double totPhase = 0;
    double* Phase[numfre];
    double* Dist[numfre];
    bool flag = true;

    double I_A[880],Q_A[880];

    for(int w = 0; w < numfre ; w++ )
    {
        int *I;
        int *Q;
        I = Ichange(CoRecord,Freqarrary[w],now);
        Q = Qchange(CoRecord,Freqarrary[w],now);

        long long II[165];
        MyCic(I,II);
        long long QQ[165];
        MyCic(Q,QQ);
        for(int i =55;i<165;i++){
            tempII[w*110+i-55]=(double)II[i];
            tempQQ[w*110+i-55]=(double)QQ[i];
        }
        //----------------LEDV-----------------
        if(levdI[w].levd(tempII)&&levdQ[w].levd(tempQQ))
        {
            memcpy(I_A+w*110,levdI[w].levd_out,sizeof(double)*110);
            memcpy(Q_A+w*110,levdQ[w].levd_out,sizeof(double)*110);
            Phase[w] = getPhase(levdI[w].levd_out,levdQ[w].levd_out);
            totPhase +=Phase[w][0];
            Dist[w] = getDist(last[w].lastDist,last[w].lastPhase,Phase[w],Freqarrary[w]);
//            //LOGW("%lf",Dist[w][110-1]);
            if(fabs(Dist[w][IQ_Length-1]-last[w].lastDist)<0.2||fabs(Dist[w][IQ_Length-1]-last[w].lastDist)>10.0||fabs(Dist[w][IQ_Length-1])>100.0)
                flag = false;        //过滤

            last[w].setLastPhase(Phase[w][IQ_Length]);
        }
        else{
            flag = false;
        }
    }

    if(flag) {

        for(int i =0;i<110;i++) {
            DIST[i] = 0;
            for(int j =0;j<numfre;j++)
                DIST[i]+=Dist[j][i];
            DIST[i]/=numfre;
        }
        double D_re = DIST[IQ_Length-1];
        double redist = myADist(I_A,Q_A,DIST);
        //LOGW("AD%f",redist);
        if(fabs(redist-D_re)<20.0&&redist>0)
        {
            D_re = redist;
        }
        if(D_re<0||(redist<0&&fabs(redist-D_re)<20.0))
            D_re=0;
        for (int w = 0; w < numfre; w++)
            last[w].setLastDist(D_re);
    }
    else
        DIST[110-1] = last[0].lastDist;
    totPhase=totPhase/numfre;


    return totPhase;
}
int MaxLoc(double  in[],int length)
{
    int re=0;
    double max = in[0];
    for(int i = 1;i<length;i++)
    {
        if(in[i]>max)
        {
            max = in[i];
            re = i;
        }
    }
    return re;
}
double myADist(double *I,double *Q,double *Dist)
{
    double Thr = 2.5e13;
    double dist=Dist[110-1];
    double basedist = 34300.0/(350*64)/2.0;         //补充到64位

    double *RE;
    RE = new double[64*110];
    ADist(I,Q,RE);
    double re[64][110];
    int Loc[64];            //j 0-109
    double Value[64];
    for( int i =0;i<64;i++)
    {
        memcpy(re[i],RE+i*110,110*sizeof(double));
        Loc[i] = MaxLoc(re[i],110);     //j 0-109
        Value[i] = re[i][Loc[i]];
    }

        int LOC = MaxLoc(Value,64);        //i 0-63
        if(LOC<8&&re[LOC][Loc[LOC]]>Thr)
        {
            //LOGW("ADV%lf",re[LOC][Loc[LOC]]);

            dist = basedist * LOC + Dist[110-1]-Dist[Loc[LOC]];
            if(dist>80)
            {
                //LOGW("ADF1%lf",Dist[110-1]);
                //LOGW("ADF2%lf",Dist[Loc[LOC]]);
            }
            //LOGW("ADF%lf",dist);
        }
    return dist;
}