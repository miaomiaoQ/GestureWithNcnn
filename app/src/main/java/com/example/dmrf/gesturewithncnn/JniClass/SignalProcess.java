package com.example.dmrf.gesturewithncnn.JniClass;

public class SignalProcess {
    public native void DemoNew();

    public native int DemoL(short[] Record, double[] DIST, double[] tempII, double[] tempQQ);

    public native int DemoR(short[] Record, double[] DIST, double[] tempII, double[] tempQQ);


    static {
        System.loadLibrary("signalnative");
    }

}
