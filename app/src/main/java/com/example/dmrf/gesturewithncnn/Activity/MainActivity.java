package com.example.dmrf.gesturewithncnn.Activity;


import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.widget.TextView;

import com.example.dmrf.gesturewithncnn.JniClass.GestureNcnn;
import com.example.dmrf.gesturewithncnn.JniClass.SignalProcess;
import com.example.dmrf.gesturewithncnn.R;

public class MainActivity extends Activity {

    private TextView textView;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView=findViewById(R.id.sample_text);
        textView.setText("hello");
        GestureNcnn gestureNcnn=new GestureNcnn();
        SignalProcess signalProcess=new SignalProcess();

    }
}
