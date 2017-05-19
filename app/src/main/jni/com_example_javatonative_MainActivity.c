#include "com_example_javatonative_MainActivity.h"
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif
#define LOG_TAG "JavaToNative"

//堆调整
void heapAdjust(int a[],int n,int i){
    int child;//保存左右节点中较大的节点
    int temp;
    temp = a[i];
    while(2*i + 1 < n){
        child = 2*i + 1;
        if(child != n -1 && a[child] < a[child+1]){
            child++;//右节点较大
        }

        if(a[child] > temp){
            a[i] = a[child];
        }else {
            break;
        }
        i = child;//更新下一个对象
    }
    a[i] = temp;
}

//对排序
void HeapSort(int a[],int n){
    int i;
    for(i = n/2; i >= 0; i--){
        heapAdjust(a,n,i);
    }
    int j;
    for(j = n - 1; j > 0;j--){
        int temp = a[j];
        a[j] = a[0];
        a[0] = temp;
        heapAdjust(a,j,0);
    }
}

//数组翻转
void ReverseArray(int a[],int n){
    int i = 0;
    int j = n - 1;
    int temp;
    while(i<j){
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }
}

void PrintArray(int arr[],int n){
    int i;
    for(i = 0; i < n; i++){
        __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,"arr[%d]=%d",i,arr[i]);
    }
}
/*
 * Class:     com_example_javatonative_MainActivity
 * Method:    heapSort
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_example_javatonative_MainActivity_heapSortNative(JNIEnv *env,
    jobject obj, jintArray array){
    //获取数组的长度
    int length = (*env)->GetArrayLength(env,array);
    //将Java对象的数组转换为C/C++类型的数组,并返回一个指向Java端数组内存地址的指针
    jint* arrp = (*env)->GetIntArrayElements(env,array,0);
    //堆排序
    HeapSort(arrp,length);
    //释放C/C++数组，并更新Java数组内容
    (*env)->ReleaseIntArrayElements(env,array,arrp,0);
}

/*
 * Class:     com_example_javatonative_MainActivity
 * Method:    heapSort
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_example_javatonative_MainActivity_reverseArrayNative(JNIEnv *env,
    jobject obj, jintArray array){
    //获取数组的长度
    jsize length = (*env)->GetArrayLength(env,array);
    int a[length];
    //直接将Java端的数组拷贝到本地的数组中，这样修改的是本地的值，不会更新到Java端的数组
    (*env)->GetIntArrayRegion(env,array,0,length,a);
    //翻转数组
    ReverseArray(a,length);
    //打印数组
    PrintArray(a,length);
}

#ifdef __cplusplus
}
#endif