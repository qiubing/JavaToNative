#include "com_example_javatonative_MainActivity.h"
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif
#define LOG_TAG "JavaToNative"

//�ѵ���
void heapAdjust(int a[],int n,int i){
    int child;//�������ҽڵ��нϴ�Ľڵ�
    int temp;
    temp = a[i];
    while(2*i + 1 < n){
        child = 2*i + 1;
        if(child != n -1 && a[child] < a[child+1]){
            child++;//�ҽڵ�ϴ�
        }

        if(a[child] > temp){
            a[i] = a[child];
        }else {
            break;
        }
        i = child;//������һ������
    }
    a[i] = temp;
}

//������
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

//���鷭ת
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
    //��ȡ����ĳ���
    int length = (*env)->GetArrayLength(env,array);
    //��Java���������ת��ΪC/C++���͵�����,������һ��ָ��Java�������ڴ��ַ��ָ��
    jint* arrp = (*env)->GetIntArrayElements(env,array,0);
    //������
    HeapSort(arrp,length);
    //�ͷ�C/C++���飬������Java��������
    (*env)->ReleaseIntArrayElements(env,array,arrp,0);
}

/*
 * Class:     com_example_javatonative_MainActivity
 * Method:    heapSort
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_example_javatonative_MainActivity_reverseArrayNative(JNIEnv *env,
    jobject obj, jintArray array){
    //��ȡ����ĳ���
    jsize length = (*env)->GetArrayLength(env,array);
    int a[length];
    //ֱ�ӽ�Java�˵����鿽�������ص������У������޸ĵ��Ǳ��ص�ֵ��������µ�Java�˵�����
    (*env)->GetIntArrayRegion(env,array,0,length,a);
    //��ת����
    ReverseArray(a,length);
    //��ӡ����
    PrintArray(a,length);
}

#ifdef __cplusplus
}
#endif