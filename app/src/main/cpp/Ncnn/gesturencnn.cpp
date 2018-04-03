#include <jni.h>
#include <string>
#include <vector>

using namespace std;

#include "net.h"

static ncnn::Net squeezenet;


static void mean(float *data, int len, float &mean, float &max, float &min) {


    float sum = data[0];
    max = data[0];
    min = data[0];

    for (int i = 1; i < 4400; ++i) {
        sum += data[i];
        if (data[i] > max)max = data[i];
        if (data[i] < min)min = data[i];
    }

}


static void normalize(float *data, int len) {


    float m = 0.0;
    float mx = 0.0;
    float mn = 0.0;
    mean(data, len, m, mx, mn);
    for (int i = 0; i < 4400; ++i) {
        data[i] = (data[i] - m) / (mx - mn);
    }


}


static int detect_gesture(float *data, float *cls_scores, int i_len) {


    ncnn::Mat in = ncnn::Mat(550, 8, 2, data);


    ncnn::Extractor ex = squeezenet.create_extractor();
    ex.set_light_mode(true);
    ex.set_num_threads(4);

    int d = ex.input("data", in);

    ncnn::Mat out;

    int c = ex.extract("prob", out);


    for (int j = 0; j < out.w; j++) {

        cls_scores[j] = out[j];
    }

    return out.w;
}

static int gesture_predict(float *i, float *q, float *cls_scores, int i_len) {


    int l = i_len;
    normalize(i, l);
    normalize(q, l);

    float data[8800];
    for (int j = 0; j < 8800; ++j) {
        if (j < 4400) {
            data[j] = i[j];
        } else {
            data[j] = q[j - 4400];
        }

    }
    int c = detect_gesture(data, cls_scores, i_len);

    return c;

}

JNIEXPORT jboolean JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_GestureNcnn_InitNcnn(JNIEnv *env, jobject instance,
                                                                    jstring gestureDetectionModelPath_) {

    //获取GESTURECNN模型的绝对路径的目录（不是/aaa/bbb.bin这样的路径，是/aaa/)
    const char *gestureDetectionModelPath = env->GetStringUTFChars(gestureDetectionModelPath_, 0);
    if (NULL == gestureDetectionModelPath) {
        return false;
    }

    string tGestureModelDir = gestureDetectionModelPath;
    string tLastChar = tGestureModelDir.substr(tGestureModelDir.length() - 1, 1);

    //目录补齐/
    if ("\\" == tLastChar) {
        tGestureModelDir = tGestureModelDir.substr(0, tGestureModelDir.length() - 1) + "/";
    } else if (tLastChar != "/") {
        tGestureModelDir += "/";
    }


    std::vector<std::string> param_files;
    param_files.resize(1);
    param_files[0] = {tGestureModelDir + "/gesture.param"};

    std::vector<std::string> bin_files;
    bin_files.resize(1);
    bin_files[0] = {tGestureModelDir + "/gesture.bin"};
    squeezenet.load_param(param_files[0].data());
    squeezenet.load_model(bin_files[0].data());

    env->ReleaseStringUTFChars(gestureDetectionModelPath_, gestureDetectionModelPath);

    return true;
}

JNIEXPORT void JNICALL
Java_com_example_dmrf_gesturewithncnn_JniClass_GestureNcnn_Detect(JNIEnv *env,
                                                                  jobject /* this */,
                                                                  jfloatArray I,
                                                                  jfloatArray Q,
                                                                  jfloatArray CLS_SCORES,
                                                                  jintArray LEN_I) {

    jfloat *data_i = (env)->GetFloatArrayElements(I, 0);
    jfloat *data_q = (env)->GetFloatArrayElements(Q, 0);
    jfloat *cls_scores = (env)->GetFloatArrayElements(CLS_SCORES, 0);
    jint *len_i = (env)->GetIntArrayElements(LEN_I, 0);


    gesture_predict(data_i, data_q, cls_scores, len_i[0]);


    (env)->ReleaseFloatArrayElements(I, data_i, 0);
    (env)->ReleaseFloatArrayElements(Q, data_q, 0);
    (env)->ReleaseFloatArrayElements(CLS_SCORES, cls_scores, 0);
    (env)->ReleaseIntArrayElements(LEN_I, len_i, 0);

}

