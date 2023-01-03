// Program    : ASM_05_JumpSearch.c
// Created by : Peter Oo
// Created on : 1/1/2023 (3:02 PM).
//

#include <stdio.h>
#include <math.h>
#define key 26

int jumpSearch(const int *arr, int length, int value);
int min(int value1, int value2);

/* Perfectly distributed data base */
int db0[] = {10,20,30,40,50,60,70,80,90,110,130,150,160,180,
            200,210,250,260,300, 320};

/* Moderately distributed data base */
int db[] = {10,11,15,20,25,30,34,36,39,40,45,49,55,80,
                  95,100,150,256,560, 1020};

/* Badly distributed data base at the end */
// Such distributed data base will lead to the whole program to do only linear search coz of badly improper data distribution
int db1[] = {10,11,15,20,25,30,34,36,39,40,45,49,55,80,
            95,100,150,256,300, 12000};

int main(){
    int len = sizeof(db)/sizeof(db[0]);

    int result = jumpSearch(db, len, key);
    if(result != -1){
        printf("We found at index %d: value = %d \n", result, db[result]);
    }
    else
        printf("Not found!");

    return 0;
}

int min(int value1, int value2){
    if(value1<value2)
        return value1;
    else
        return value2;
}

int jumpSearch(const int *arr, int length, int value){
    if(value >= arr[0] && value <= arr[length-1]){
        if(value == arr[0])
            return 0;
        else{
            int interval = ((arr[length-1] - (arr[0]-1)) / (length-1));
            int avg_step = (int)ceil((double)value / interval);
            int step = avg_step;
            int previous=0;
            int inc;
            while(value > arr[(step=min(step, length-1))]){
                if(value == arr[step+1])
                    return step+1;
                if((arr[step]-arr[previous]) != 0){
                    inc = (arr[step] - (arr[previous]-1)) / (step - previous);
                    inc = (inc + interval)/2;
                    inc = (int)ceil((double)value / inc);
                }
                else
                    step++;
                previous = step;
                step += inc;
            }
            if(value == arr[step]){
                return step;
            }
            else{
                if(value == arr[step-1])
                    return step-1;
                while(previous < step){
                    if(value == arr[++previous])
                        return previous;
                }
            }
            return -1;
        }
    }
    else
        return -1;
}


/*
 * Algorithm
 * find interval of estimated number at each index
 * step = key / interval
 * if key > db[step] <= label
 * find increment , find average increment
 * step = step + increment;
 * goto label
 * if key < db[step]
 * do linear search.
 * */