package com.lee.edu.mydemo.Utils;

/**
 * Created by lisi on 2017/3/16.
 */

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Handler;
import android.os.Message;



public class FrequencyPlayerUtils {
    private AudioTrack audioTrack;		//播放音轨

    private final int sampleRate = 44100;	//采样率
    private int numSamples=120960;		//？？ 不同频率叠加音频采样点数量？
    private int numfreq=1;			//叠加的数量
    private double sample[] = new double[numSamples];
    private double freqOfTone[]= null; // hz17500

    private int sampleRateInHz = 44100; // 采样率
    private int mChannel = AudioFormat.CHANNEL_OUT_MONO;// 声道 ：单声道
    private int mSampBit = AudioFormat.ENCODING_PCM_16BIT;// 采样精度 :16bit
    private AudioTrackZThread audioTrackZThread;
    private boolean isRunning = false;
    private AudioTrack audioTrackz;
    private Handler mHandler;

    public FrequencyPlayerUtils(int num, double[]freArray,Handler handler) {
        mHandler=handler;
        numfreq = num;
        freqOfTone = freArray;

        int bufferSize = AudioTrack.getMinBufferSize(sampleRateInHz, mChannel,
                mSampBit);
        audioTrackz = new AudioTrack(AudioManager.STREAM_SYSTEM,
                sampleRateInHz, mChannel, mSampBit, bufferSize * 2,
                AudioTrack.MODE_STREAM);
        audioTrackz.setStereoVolume(1.0f, 0.0f);
        audioTrackz.play();
    }

    public void palyWaveZ() {
        audioTrackZThread = new AudioTrackZThread();
        audioTrackZThread.start();
    }

    public void colseWaveZ() {
        if (audioTrackz != null) {
            if (!AudioTrackZThread.interrupted()) {
                isRunning = false;
            }
            // audioTrackz.stop();
            // audioTrackz.release();
        }
    }

    class AudioTrackZThread extends Thread  {
        private short m_iAmp = (short) (Short.MAX_VALUE / numfreq);
        private short m_bitDateZ[] = new short[44100];
        private double x = 2.0 * Math.PI  / 44100.0;

        @Override
        public void run() {
            isRunning = true;
            for (int i = 0; i < 44100; i++) {
                m_bitDateZ[i]=0;
                for(int j=0;j<numfreq;j++)
                    m_bitDateZ[i] += (short) (m_iAmp* Math.sin(x * i * freqOfTone[j]));		//叠加频率
            }

            int m_bitDateZSize = m_bitDateZ.length;
            do {
                try {
                    audioTrackz.write(m_bitDateZ, 0, m_bitDateZSize);
                }catch (RuntimeException e){
                    Message msg3 = new Message();
                    msg3.what = 0;

                    msg3.obj = ("playe");

                    mHandler.sendMessage(msg3);
                }

                // Log.v("isRunn", isRunning+"");
            } while (isRunning);
            super.run();
        }
    }

}
