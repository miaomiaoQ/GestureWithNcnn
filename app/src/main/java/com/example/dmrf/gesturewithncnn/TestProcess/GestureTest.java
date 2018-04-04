package com.example.dmrf.gesturewithncnn.TestProcess;

import android.content.Context;
import android.os.Environment;

import com.example.dmrf.gesturewithncnn.JniClass.GestureNcnn;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class GestureTest {

    private GestureNcnn gestureNcnn;
    private Context context;

    public GestureTest(Context context) {
        this.context = context;
    }


    public void InitTest(){
        try {
            InitGestureNcnn();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void DetectTest(){
        float i_Data[]=new float[4400];
        float q_Data[]=new float[4400];
        float score[]=new float[13];
        int len_i[]=new int[1];
        len_i[0]=4400;
        gestureNcnn.Detect(i_Data,q_Data,score,len_i);

    }

    private void InitGestureNcnn() throws IOException {


        gestureNcnn = new GestureNcnn();


        try {
            copyBigDataToSD("gesture.bin");

            copyBigDataToSD("gesture.param");
        } catch (IOException e) {
            e.printStackTrace();
        }
        //模型初始化
        File sdDir = Environment.getExternalStorageDirectory();//获取跟目录
        String sdPath = sdDir.toString() + "/gesturencnn/";
        boolean b = gestureNcnn.InitNcnn(sdPath);

    }


    private void copyBigDataToSD(String strOutFileName) throws IOException {

        File sdDir = Environment.getExternalStorageDirectory();//获取跟目录
        File file = new File(sdDir.toString() + "/gesturencnn/");
        if (!file.exists()) {
            file.mkdir();
        }

        String tmpFile = sdDir.toString() + "/gesturencnn/" + strOutFileName;
        File f = new File(tmpFile);
        if (f.exists()) {
            return;
        }
        InputStream myInput;
        java.io.OutputStream myOutput = new FileOutputStream(sdDir.toString() + "/gesturencnn/" + strOutFileName);
        myInput = context.getAssets().open(strOutFileName);
        byte[] buffer = new byte[1024];
        int length = myInput.read(buffer);
        while (length > 0) {
            myOutput.write(buffer, 0, length);
            length = myInput.read(buffer);
        }
        myOutput.flush();
        myInput.close();
        myOutput.close();

    }


}
