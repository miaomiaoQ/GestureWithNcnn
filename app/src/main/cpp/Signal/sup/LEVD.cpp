//
// Created by lisi on 2017/9/22.
//

#include "LEVD.h"

#define IQ_Length 110


Peak findpeaks(double* in,int length)
{
    Peak Peaks(length);       //
    int n=0;
    Peaks.Locs[n] = 0;
    Peaks.Value[n] = in[0];
    Peaks.Length++;
    if(in[1]>in[0])
        Peaks.type[n++] = false;
    else
        Peaks.type[n++] = true;
    for(int i = 1;i<length-1;i++)
    {
        if(in[i]>in[i-1]&&in[i]>in[i+1]) {
            Peaks.Locs[n] = i;
            Peaks.type[n]=true;
            Peaks.Value[n++] = in[i];
            Peaks.Length++;
        }
        if(in[i]<in[i-1]&&in[i]<in[i+1]) {
            Peaks.Locs[n] = i;
            Peaks.type[n]=false;
            Peaks.Value[n++] = in[i];
            Peaks.Length++;
        }
    }
    return Peaks;
}

LEVD::LEVD(){
    double *last = NULL;
    double *levd_SI = NULL;
    double *levd_out = NULL;
    flag = false;
    Thr = 1e11;
    first=true;
}

bool LEVD::levd(double *in) {
    bool RE = false;
    if(first)
    {
        first = false;
        last = new double[IQ_Length];
        memcpy(last,in,IQ_Length);
        if(levd_SI!=NULL) {
            delete (levd_SI);
            levd_SI = NULL;
        }
        levd_SI = new double[IQ_Length];
        if(levd_out!=NULL) {
            delete (levd_out);
            levd_out = NULL;
        }
        levd_out = new double[IQ_Length];
        return RE;
    }
    else
    {
        double *temp = new double[IQ_Length*2];
        memcpy(temp,last,IQ_Length*sizeof(double));
        memcpy(temp+IQ_Length,in,IQ_Length*sizeof(double));
            Peak p = findpeaks(temp,IQ_Length*2);
            double * Pks;
            int * Loc;
            bool* type;
            Pks = new double[p.getLength()+1];
            Loc = new int[p.getLength()+1];
            type = new bool[p.getLength()+1];

            int n = 0;
            if(!flag)
            {
                //------------------findfirst-----------
                int i = 1;
                for(;i<p.getLength();i++)
                {
                    if(fabs(p.Value[i-1]-p.Value[i])>Thr)
                    {
                        flag=true;
                        Pks[n] = p.Value[i-1];
                        Loc[n] = p.Locs[i-1];
                        type[n] = p.type[i-1];
                        n++;
                        Pks[n] = p.Value[i];
                        Loc[n] = p.Locs[i];
                        type[n] = p.type[i];
                        break;
                    }
                }
                if(flag==false)
                    return RE;
                //------------------findfirst end-----------
                for(;i<p.Length;i++)
                {
                    if(p.type[i]==type[n])
                    {
                        if(p.type[i]==true&&p.Value[i]>Pks[n])
                        {
                            Pks[n] = p.Value[i];
                            Loc[n] = p.Locs[i];
//                            type[n] = p.type[i];
                        }
                        else if(p.type[i]==false&&p.Value[i]<Pks[n])
                        {
                            Pks[n] = p.Value[i];
                            Loc[n] = p.Locs[i];
//                            type[n] = p.type[i];
                        }
                    }
                    else if(fabs(p.Value[i]-Pks[n])>Thr)
                    {
                        n++;
                        Pks[n] = p.Value[i];
                        Loc[n] = p.Locs[i];
                        type[n] = p.type[i];
                    }
                }//结束后n为合格顶点数

                if(Loc[0]>IQ_Length||n==0)
                    return RE;

                int j =1;
                levd_SI[0] = (temp[0]+Pks[0])/2;
                for(;j<Loc[0];j++)
                {
                    levd_SI[j] = levd_SI[j-1] * 0.95+0.05*(Pks[0]+temp[0])/2;
                }
                int e = 1;
                for(;j<IQ_Length;j++)
                {
                    if(e+1<=n&&j>Loc[e])
                        e++;
                    levd_SI[j] = levd_SI[j-1] * 0.95+0.05*(Pks[e-1]+Pks[e])/2;
                }

                for(i =0;i<IQ_Length;i++)
                    levd_out[i] = temp[i] - levd_SI[i];

                memcpy(last,in,IQ_Length*sizeof(double));
                if(Loc[n]<IQ_Length)
                {
                    last_Pks = Pks[n];
                    last_type = type[n];
                }
                else
                {
                    last_Pks = Pks[e-1];
                    last_type = type[e-1];
                }
                last_SI = levd_SI[IQ_Length-1];
                RE = true;
            }
            else        //flag
            {
//                Log.w("LEVD","There");
                //last
                n= 0;
                Pks[0] = last_Pks;
                type[0] = last_type;
                Loc[0] = -1;

                for(int i = 0;i<p.Length;i++)
                {
                    if(p.type[i]==type[n])
                    {
                        if(p.type[i]==true&&p.Value[i]>Pks[n])
                        {
                            Pks[n] = p.Value[i];
                            Loc[n] = p.Locs[i];
//                            type[n] = p.type[i];
                        }
                        else if(p.type[i]==false&&p.Value[i]<Pks[n])
                        {
                            Pks[n] = p.Value[i];
                            Loc[n] = p.Locs[i];
//                            type[n] = p.type[i];
                        }
                    }
                    else if(fabs(p.Value[i]-Pks[n])>Thr)
                    {
                        n++;
                        Pks[n] = p.Value[i];
                        Loc[n] = p.Locs[i];
                        type[n] = p.type[i];
                    }
                }
                if(n==0)        //本段没有极值
                    return RE;

                int e = 1;
                levd_SI[0] = last_SI *0.95 + 0.05*(Pks[e-1]+Pks[e])/2;
                for(int j =1;j<IQ_Length;j++)
                {
                    if(e+1<=n&&j>Loc[e])
                        e++;
                    levd_SI[j] = levd_SI[j-1] * 0.95+0.05*(Pks[e-1]+Pks[e])/2;
                }

                for(int i =0;i<IQ_Length;i++)
                    levd_out[i] = last[i] - levd_SI[i];

                memcpy(last,in,IQ_Length*sizeof(double));
                if(Loc[n]<IQ_Length)
                {
                    last_Pks = Pks[n];
                    last_type = type[n];
                }
                else
                {
                    last_Pks = Pks[e-1];
                    last_type = type[e-1];
                }
                last_SI = levd_SI[IQ_Length-1];
                RE = true;
            }
        delete[]temp;
        }//first
            return RE;
}