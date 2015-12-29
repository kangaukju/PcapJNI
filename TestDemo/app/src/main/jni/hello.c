#include <stdio.h>
#include <pcap/pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "com_example_kinow_testdemo_HlloNDK.h"
#include "com_example_kinow_testdemo_GetDev.h"

JNIEXPORT jstring JNICALL Java_com_example_kinow_testdemo_HlloNDK_getHello
        (JNIEnv *env, jobject obj)
{
    jstring str =  (*env)->NewStringUTF(env, "Hello World!!!");
    return str;
}

JNIEXPORT jstring JNICALL Java_com_example_kinow_testdemo_GetDev_getDevice
        (JNIEnv *env, jobject obj)
{
    jstring str =  NULL;
    char *dev;    // 사용중인 네트웍 디바이스 이름
    char *net;    // 네트웍 어드레스
    char *mask;   // 네트웍 mask 어드레스
    int ret;      //
    char errbuf[PCAP_ERRBUF_SIZE] = {0, };
    bpf_u_int32 netp;  // ip
    bpf_u_int32 maskp; // submet mask
    struct in_addr addr;
    char result[1024] = {0, };
    int len = 0;

    // 네트웍 디바이스 이름을 얻어온다.
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        str =  (*env)->NewStringUTF(env, errbuf);
        return str;
    }

    // 네트웍 디바이스 이름 출력
    len += snprintf(result, sizeof(result)-len, "DEV:%s", dev);

    // 네트웍 디바이스 이름 dev 에 대한
    // mask, ip 정보 얻어오기
    ret = pcap_lookupnet(dev, &netp, &maskp, errbuf);
    if (ret == -1) {
        str =  (*env)->NewStringUTF(env, errbuf);
        len += snprintf(result, sizeof(result)-len, "pcap_lookupnet:%s", str);
        return result;
    }

    // 네트웍 어드레스를 점박이 3형제 스타일로
    addr.s_addr = netp;
    net = inet_ntoa(addr);
    if (net == NULL) {
        str =  (*env)->NewStringUTF(env, "failed to inet_ntoa");
        len += snprintf(result, sizeof(result)-len, "inet_ntoa:%s", str);
        return str;
    }
    len += snprintf(result, sizeof(result)-len, ",NET:%s", net);

    // 마찬가지로 mask 어드레스를 점박이 3형제 스타일로
    addr.s_addr = maskp;
    mask = inet_ntoa(addr);
    if (mask == NULL) {
        str =  (*env)->NewStringUTF(env, "failed to inet_ntoa");
        len += snprintf(result, sizeof(result)-len, "inet_ntoa:%s", str);
        return str;
    }
    len += snprintf(result, sizeof(result)-len, ",MASK:%s", mask);

    str =  (*env)->NewStringUTF(env, result);
    return str;
}

