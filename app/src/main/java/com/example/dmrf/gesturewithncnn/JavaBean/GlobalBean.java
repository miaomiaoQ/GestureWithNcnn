package com.lee.edu.mydemo.JavaBean;

import android.annotation.SuppressLint;
import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.lee.edu.mydemo.Thread.InstantPlayThread;
import com.lee.edu.mydemo.Thread.InstantRecordThread;
import com.lee.edu.mydemo.Utils.FrequencyPlayerUtils;
import com.lee.edu.mydemo.Utils.SqueezeNcnn;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;


/**
 * Created by dmrf on 18-3-15.
 */

public class GlobalBean {




   /*
   set audio
    */

    public double[] Freqarrary = {17500, 17850, 18200, 18550, 18900, 19250, 19600, 19950, 20300, 20650};        //设置播放频率
    public int encodingBitrate = AudioFormat.ENCODING_PCM_16BIT;// 编码率（默认ENCODING_PCM_16BIT）
    public int channelConfig = AudioFormat.CHANNEL_IN_MONO;        //声道（默认单声道） 单道  MONO单声道，STEREO立体声
    public AudioRecord audioRecord;    //录音对象
    public FrequencyPlayerUtils FPlay;
    public int sampleRateInHz = 44100;//采样率（默认44100，每秒44100个点）
    public int recBufSize = 4400;            //定义录音片长度
    public int numfre = 8;
    public char[] CODE = {'A', 'B', 'C', 'J', 'K', 'F', 'G', 'L', 'M', 'N', 'O', 'H', 'I'};
    public float[] scores = new float[13];
    public int[] len_i = new int[2];


    /*
    views
     */
    public Button btnPlayRecord;        //开始按钮
    public Button btnStopRecord;        //结束按钮
    public TextView tvDist;            //显示距离
    public TextView tvDist2;            //显示距离
    public ImageView flag_small;

    public int is_in_count = -1;
    public int gesture_length=1100;

    /*
    variable
     */
    public boolean flag = true;        //播放标志
    public ArrayList<Double> L_I[];
    public ArrayList<Double> L_Q[];


    public String whoandwhich = "ncnntest";

    private Context context;
    private SqueezeNcnn squeezeNcnn;


    @SuppressLint("HandlerLeak")
    public Handler mHandler = new Handler() {
        //设置圆环角度
        @SuppressLint("ResourceAsColor")
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case 0:
                    if (msg.obj.toString().equals("wait")) {
                        flag_small.setVisibility(View.GONE);
                       PredictGesture(0, tvDist);
                        PredictGesture(550, tvDist2);


                        for (int i = 0; i < 8; i++) {
                            L_I[i].clear();
                            L_Q[i].clear();
                        }

                    } else if (msg.obj.toString().equals("start")) {
                        tvDist.setVisibility(View.VISIBLE);
                        tvDist2.setVisibility(View.VISIBLE);
                        flag_small.setVisibility(View.VISIBLE);
                        Start();
                    } else if (msg.obj.toString().equals("stop")) {
                        flag_small.setVisibility(View.GONE);

                        btnPlayRecord.setVisibility(View.VISIBLE);

                        btnStopRecord.setVisibility(View.GONE);
                        tvDist.setVisibility(View.GONE);
                        tvDist2.setVisibility(View.GONE);
                        FPlay.colseWaveZ();
                        audioRecord.stop();

                    } else if (msg.obj.toString().equals("playe")) {
                        Toast.makeText(context, "发生了异常，请联系最帅的人优化代码～", Toast.LENGTH_SHORT).show();
                    }
                    break;
                case 1:
                    tvDist.setText(msg.obj.toString());
                    break;
                case 2:
                    tvDist2.setText(msg.obj.toString());
                    break;
            }
        }
    };


    private void PredictGesture(int a, TextView textView) {//第一个a为0，第二个a为550

        float data_i[] = new float[4400];
        float data_q[] = new float[4400];
        len_i[0] = 4400;

        int k = 0;
        int b = a + 550;
        for (int i = 0; i < 8; i++) {
            for (int j = a; j < b; j++) {
                data_i[k] = L_I[i].get(j).floatValue();
                data_q[k] = L_Q[i].get(j).floatValue();
                k++;
            }
        }


        squeezeNcnn.Detect(data_i, data_q, scores, len_i);

        float max = scores[0];
        int max_index = 0;
        for (int i = 1; i < 13; i++) {
            if (scores[i] > max) {
                max = scores[i];
                max_index = i;
            }
        }

        textView.setText(CODE[max_index] + ":" + max);

    }

    public GlobalBean(Context context) {
        this.context = context;
    }

    public void Init() {
        try {
            InitSqueezeNcnn();
        } catch (IOException e) {
            e.printStackTrace();
        }

        SimpleDateFormat formatter = new SimpleDateFormat("MM_dd");
        Date curDate = new Date(System.currentTimeMillis());//获取当前时间
        final String day = formatter.format(curDate);
        whoandwhich = whoandwhich + "_" + day;


        L_I = new ArrayList[8];
        L_Q = new ArrayList[8];

        for (int i = 0; i < 8; i++) {
            ArrayList<Double> list1 = new ArrayList<Double>();
            ArrayList<Double> list2 = new ArrayList<Double>();
            L_I[i] = list1;
            L_Q[i] = list2;

        }


        audioRecord = new AudioRecord(
                MediaRecorder.AudioSource.MIC,//从麦克风采集音频
                sampleRateInHz,//采样率，这里的值是sampleRateInHz = 44100即每秒钟采样44100次
                channelConfig,//声道设置，MONO单声道，STEREO立体声，这里用的是立体声
                encodingBitrate,//编码率（默认ENCODING_PCM_16BIT）
                recBufSize);//录音片段的长度，给的是minBufSize=recBufSize = 4400 * 2;


        btnStopRecord.setVisibility(View.GONE);
        btnPlayRecord.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("ResourceAsColor")
            @Override
            public void onClick(View v) {


                btnPlayRecord.setVisibility(View.GONE);


                btnStopRecord.setVisibility(View.VISIBLE);
                if (whoandwhich.equals("")) {
                    Toast.makeText(context, "不告诉我你是谁不让你录！", Toast.LENGTH_SHORT).show();
                    return;
                }

                Start();

                new InstantPlayThread(GlobalBean.this).start();        //播放(发射超声波)


                try {
                    Thread.sleep(10);    //等待开始播放再录音
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }


                new InstantRecordThread(GlobalBean.this, context).start();        //录音
                //录音播放线程

            }
        });


        //停止按钮
        btnStopRecord.setOnClickListener(new View.OnClickListener() {

            @SuppressLint("ResourceAsColor")
            @Override
            public void onClick(View v) {
                // TODO 自动生成的方法存根

            }
        });


    }


    @SuppressLint("ResourceAsColor")
    public void Stop() {

    }

    public void AddDataToList(ArrayList<Double>[] list, double[] data) {

        int count = -1;
        for (int i = 0; i < 880; i++) {
            if (i % 110 == 0) {
                count++;
            }
            list[count].add(data[i]);
        }

    }


    private void Start() {
        if (L_I[0] != null) {
            for (int i = 0; i < 8; i++) {
                L_I[i].clear();
                L_Q[i].clear();
            }
        }

        flag = true;

    }


    private void InitSqueezeNcnn() throws IOException {


        squeezeNcnn = new SqueezeNcnn();


        try {
            copyBigDataToSD("gesture.bin");

            copyBigDataToSD("gesture.param");
        } catch (IOException e) {
            e.printStackTrace();
        }
        //模型初始化
        File sdDir = Environment.getExternalStorageDirectory();//获取跟目录
        String sdPath = sdDir.toString() + "/gesturencnn/";
        boolean b = squeezeNcnn.InitNcnn(sdPath);

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
