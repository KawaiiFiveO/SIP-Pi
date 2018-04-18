//
// Created by kaito on 14.04.18.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include<errno.h>

struct sockaddr_in serv_addr;
//struct hostent *targetserver;
short sendNewValue=0;
int displayedDigits[4];
short overwriteDTMFdigitCache =1;
pthread_mutex_t digitMutex, sendflagMutex, lifeflagMutex, disconnMutex, overwriteCacheMutex;
struct addrinfo hints;
struct addrinfo *result, *rp;
struct socketlife
{
    int socketfd;
    short endMyLife;
    short disconnected;
    short keepaliveSuccess;
};

int makeDigitsArrToNumber(int* numbers, int amount)
{
    int temp = 0;
    //int powTenForZeroes=0;
    for (int i = 1, n=amount-1; i <= (int)pow(10,amount-1) && n>=0; i=i*10, n--) {
        if(numbers[n]==-1)
        {
            temp = temp * i;
        }
        else {
                temp = temp + (numbers[n] * i);
        }
    }
    return temp;
}

void tcpwriter (struct socketlife *param)
{
    int suc=0;
    short endMyLifeflag = 0;
    int numbers=0;
    char msgbuf[10] ="";
    int send_acked = 1;
    int oldnumbers = 0;
    int timeouts =0;
    clock_t countdown_start;
    clock_t countdown_end;
    clock_t timeout_start = clock();
    clock_t timeout_end;
    countdown_start = clock();
    short disconn = 0;
    pthread_mutex_lock(&lifeflagMutex);
    endMyLifeflag = param->endMyLife;
    pthread_mutex_unlock(&lifeflagMutex);
    do {
        pthread_mutex_lock(&disconnMutex);
        disconn = param->disconnected;
        pthread_mutex_unlock(&disconnMutex);
        while (endMyLifeflag == 0 && disconn ==0) {
            //Count seconds of microwave down, reset time offset on server if countdown reaches zero
            countdown_end = clock();
            //If timer set my microwave ended, send zeroes
            double elapsedTimeCoutdown = (double) (countdown_end - countdown_start) / CLOCKS_PER_SEC;
            if ((elapsedTimeCoutdown > (double) numbers) && numbers != 0) {
                //mutex lock
                pthread_mutex_lock(&sendflagMutex);
                sendNewValue = 1;
                //mutex unlock
                pthread_mutex_unlock(&sendflagMutex);
                //mutex lock
                pthread_mutex_lock(&digitMutex);
                bzero(displayedDigits, sizeof(displayedDigits));
                //mutex unlock
                pthread_mutex_unlock(&digitMutex);
                pthread_mutex_lock(&overwriteCacheMutex);
                overwriteDTMFdigitCache=1;
                pthread_mutex_unlock(&overwriteCacheMutex);
            }
            //timeout check
            timeout_end = clock();
            double elapsedTimeoutCheckTime = (double)(timeout_end - timeout_start) / CLOCKS_PER_SEC;
            if (elapsedTimeoutCheckTime >= 5) {
                pthread_mutex_lock(&disconnMutex);
                if (param->keepaliveSuccess==0)
                {
                    timeouts++;
                    if (timeouts>3) {
                        param->disconnected = 1;
                        timeouts=0;
                    }
                }else
                {
                    timeouts=0;
                    param->keepaliveSuccess=0;
                }
                pthread_mutex_unlock(&disconnMutex);
                if (send(param->socketfd, "ELPSY", strlen("ELPSY"), 0) <= -1) {
                    printf("ERROR DISCONNECTED!!");
                    shutdown(param->socketfd, SHUT_RDWR);
                    pthread_mutex_lock(&disconnMutex);
                    param->disconnected=1;
                    pthread_mutex_unlock(&disconnMutex);
                }
                timeout_start = clock();
            }
            pthread_mutex_lock(&sendflagMutex); //mutex lock
            if (sendNewValue == 1) {
                pthread_mutex_unlock(&sendflagMutex);  //mutex unlock
                countdown_start = clock();
                pthread_mutex_lock(&digitMutex);
                numbers = makeDigitsArrToNumber(displayedDigits, 4);
                pthread_mutex_unlock(&digitMutex);
                sprintf(msgbuf, "RCVTO %04d", numbers);
                suc = (int) send(param->socketfd, msgbuf, strlen(msgbuf), 0);
                if (suc < 0) {
                    oldnumbers = numbers;
                }
                //send_acked = 0;
                pthread_mutex_lock(&sendflagMutex);
                sendNewValue = 0;
                pthread_mutex_unlock(&sendflagMutex);
            } else {
                pthread_mutex_unlock(&sendflagMutex);  //mutex unlock
            }
            pthread_mutex_lock(&lifeflagMutex);
            endMyLifeflag = param->endMyLife;
            pthread_mutex_unlock(&lifeflagMutex);
            pthread_mutex_lock(&disconnMutex);
            disconn = param->disconnected;
            pthread_mutex_unlock(&disconnMutex);
        }
        pthread_mutex_lock(&lifeflagMutex);
        endMyLifeflag = param->endMyLife;
        pthread_mutex_unlock(&lifeflagMutex);
    }while (endMyLifeflag==0);
}

void tcplistener(struct socketlife *param)
{
    short lifeflag = 0;
    char msgbuf[10] ="";
    int send_acked = 1;
    socklen_t m = sizeof(serv_addr);
    int suc=0;
    int numbers=0;
    //int oldnumbers = 0;
    short disconn = 0;
    do {
        //mutex lock
        pthread_mutex_lock(&lifeflagMutex);
        lifeflag = param->endMyLife;
        pthread_mutex_unlock(&lifeflagMutex);
        pthread_mutex_lock(&disconnMutex);
        disconn = param->disconnected;
        pthread_mutex_unlock(&disconnMutex);
        while (disconn != 1 && lifeflag != 1) {
            pthread_mutex_lock(&sendflagMutex); //mutex lock
            if (sendNewValue == 0) {
                pthread_mutex_unlock(&sendflagMutex); //mutex unlock
                int valread = (int) read(param->socketfd, msgbuf, 10);
                if (strncmp(msgbuf, "RCVOK", 5) == 0) {
                    //send_acked = 1;
                    printf("SEND TIME FINISHED");
                }
                if (strncmp(msgbuf, "ELPSY", 5) == 0) {
                    suc = (int) send(param->socketfd, "KONGROO", strlen("KONGROO"), 0);
                }
                if (strncmp(msgbuf, "KONGROO", 7) == 0) {
                    pthread_mutex_lock(&disconnMutex);
                    param->keepaliveSuccess=1;
                    pthread_mutex_unlock(&disconnMutex);
                }
                if (strncmp(msgbuf, "MAILD", 5) == 0) {
                    //TODO: trigger audio effect in main thread
                }
            }
            else
            {
                pthread_mutex_unlock(&sendflagMutex); //mutex unlock
            }
            //mutex lock
            pthread_mutex_lock(&lifeflagMutex);
            lifeflag = param->endMyLife;
            pthread_mutex_unlock(&lifeflagMutex);
            pthread_mutex_lock(&disconnMutex);
            disconn = param->disconnected;
            pthread_mutex_unlock(&disconnMutex);
        }
        pthread_mutex_lock(&disconnMutex);
        disconn = param->disconnected;
        pthread_mutex_unlock(&disconnMutex);
    } while (lifeflag != 1);
}
