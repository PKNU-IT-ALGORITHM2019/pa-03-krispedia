#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#define T 3

using namespace std;

int N[3] = {500, 10000, 100000};
double runningTime[9][6] = {0.0};
vector<double> randomTime(10,0);
vector<double> randomTime_origin(10,0);
vector<int> data;
vector<int> data_origin;

void merge(vector<int> data, int p, int q, int r);
int partition_last_pivot(int left, int right);
int partition_median_pivot(int left, int right);
int partition_first_pivot(int left, int right);
int partition_random_pivot(int left, int right);

void print_result() {

    cout<<"            \tRandom1000";

    cout<<"    Reverse1000";

    cout<<"    Random10000";

    cout<<"    Reverse10000";

    cout<<"    Random100000";

    cout<<"    Reverse100000"<<'\n';
    int i;
    for(i=0; i<7; i++){
        cout.flags(ios::right);
        if(i==0)
            cout<<"   Bubble sort";
        else if(i==1)
            cout<<"Selection sort";
        else if(i==2)
            cout<<"Insertion sort";
        else if(i==3)
            cout<<"\t Merge";
        else if(i==4)
            cout<<"\tQuick1";
        else if(i==5)
            cout<<"\tQuick2"; 
        else if(i==6)
            cout<<"\tQuick3";                    
        //cout<<"Bubble Sort";
        /*
        switch (i){
            cout.flags(ios::right);
            case 0: cout<<"Bubble sort";
            cout.flags(ios::right);
            case 1: cout<<"Selection sort";
            cout.flags(ios::right);
            case 2: cout<<"Insertion sort";
            cout.flags(ios::right);
            case 3: cout<<"Merge";
            cout.flags(ios::right);
            case 4: cout<<"Quick1";
            cout.flags(ios::right);
            case 5: cout<<"Quick2";
            cout.flags(ios::right);
            case 6: cout<<"Quick3";
        }
        */
        
        for(int j=0; j<6; j++){
            cout.width(12);
            cout<<runningTime[i][j]<<"sec ";
        }
        cout<<'\n';
    }
}
void swap(int index1, int index2){
    int temp = data.at(index1);
    data.at(index1) = data.at(index2);
    data.at(index2) = temp;
}
void bubble_sort(){
    for(int  i = data.size()-1; i>=0; i--){
        for(int j = 1; j<=i; j++){
            if(data.at(j-1)>data.at(j))
                swap(j-1, j);
        }
    }
}
void selection_sort(){
    for(int i=data.size()-1; i>=0; i--){
        int max = data.at(i);
        int maxIndex = i;
        for(int j=0; j<=i; j++){
            if(data.at(j)>max){
                max = data.at(j);
                maxIndex = j;
            }
        }
        if(maxIndex != i)
            swap(i,maxIndex);
    }
}
void insertion_sort(){
    for(int i=1; i<data.size(); i++){
        int temp = data.at(i);
        int locIndex = 0;
        bool hitBig = false;
        for(int j=0; j<i; j++){
            if(data.at(j)>data.at(i)){
                locIndex = j;
                hitBig = true;
                break;
            }
        }
        if(hitBig == false){
            locIndex = i;
            continue;
        }

        for(int j=i; j>locIndex; j--){
            data.at(j) = data.at(j-1);
        }
        data.at(locIndex) = temp;
    }
}
void merge_sort(vector<int> arr, int left, int right){
//    cout<<"merge sort start!"<<'\n';
    if(left<right){
        int mid = (left+right)/2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(data, left, mid, right);
    }
}
void merge(vector<int> arr, int left, int mid, int right){
//    cout<<"merge start!"<<'\n';
    vector<int> sortedData;
    int i=left;
    int j=mid+1;
    int k=left;

    while(i<=mid && j<=right){
        if(arr.at(i)<=arr.at(j)){
            sortedData.push_back(arr.at(i++));
        }
        else{
            sortedData.push_back(arr.at(j++));
        }
    }
    // front array done
    if(i>mid){
        for(int l=j; l<=right; l++)
            sortedData.push_back(arr.at(l));
    }
    // back array done
    else if(j>right){
        for(int l=i; l<=mid; l++)
            sortedData.push_back(arr.at(l));
    }
    for(int l=left; l<=right; l++){
        data[l] = sortedData.at(l-left);
    }
/*  print data 
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
        cout<<'\n';
*/
}
void quick_sort_last(int left, int right){
    if(left<right){
        int pivot = partition_last_pivot(left, right);
        quick_sort_last(left, pivot-1);
        quick_sort_last(pivot+1, right);
    }
}
int partition_last_pivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}
void quick_sort_median(int left, int right){
    if(left<right){
        int pivot = partition_median_pivot(left, right);
        quick_sort_last(left, pivot-1);
        quick_sort_last(pivot+1, right);
    }
    
}
int get_median(){
    int mediumIndex = data.size()/2;
    int lastIndex = data.size()-1;
//    cout<<"mediumIndex: "<<mediumIndex<<'\n';
    if((data.at(0)>data.at(mediumIndex) && data.at(0)<data.at(lastIndex)) || (data.at(0)<data.at(mediumIndex) && data.at(0)>data.at(lastIndex)))
        return 0;
    else if((data.at(0)<data.at(mediumIndex) && data.at(mediumIndex)<data.at(lastIndex)) || (data.at(0)>data.at(mediumIndex) && data.at(mediumIndex)>data.at(lastIndex)))
        return mediumIndex;
    else
        return lastIndex;
}
int partition_median_pivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    int checkIndex = get_median();
    swap(checkIndex, right);

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}
void quick_sort_random(int left, int right){
    if(left<right){
        int pivot = partition_random_pivot(left, right);
        quick_sort_last(left, pivot-1);
        quick_sort_last(pivot+1, right);
    }
    
}
int partition_random_pivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    srand((unsigned) time(NULL));
    int checkIndex = rand()%(right-left+1);
    swap(checkIndex, right);

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}

void generateRandomData(int N){
    srand((unsigned int) time(NULL));
    data_origin.clear();
    for(int i=0; i<N; i++){
        // random 수 생성
        int number = rand()%N+1;
        data_origin.push_back(number);
    }
}
void generateReversedData(int N){
    data_origin.clear();
    for(int i=0; i<N; i++){
        data_origin.push_back(N-i);
    }
}
void printData(){
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';    
}
void addRunningTime(double time){

}
void saveRunningTime(int row, int col, double time){
    runningTime[row][col] = time;
}
void runSort(int i, int j) {

    cout<<"randomTime_origin"<<'\n';
    for(auto it=randomTime_origin.begin(); it!=randomTime_origin.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';
    cout<<"randomTime"<<'\n';
    for(auto it=randomTime.begin(); it!=randomTime.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';


    clock_t start, end; 
    
    data.resize(data_origin.size());
                        
    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();
    start = clock();
    cout<<"bubble sort"<<'\n';
    bubble_sort();
    end = clock();
    double resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        cout<<"resultTIME: "<<resultTime<<'\n';
        resultTime += randomTime.at(0);
        randomTime.at(0) += temp;
    }
    saveRunningTime(0,(i+1)*(j+1)-1, resultTime);
    //runningTime[0][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();

    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();
    start = clock();
    cout<<"selection sort"<<'\n';
    selection_sort();
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(1);
        randomTime.at(1) += temp;
    }
    saveRunningTime(1,(i+1)*(j+1)-1,resultTime);
    //runningTime[1][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();

    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();           
    start = clock();
    cout<<"insertion sort"<<'\n';
    insertion_sort();
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(2);
        randomTime.at(2) += temp;
    }
    saveRunningTime(2,(i+1)*(j+1)-1,resultTime);
    //runningTime[2][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();

    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();          
    start = clock();
    cout<<"merge sort"<<'\n';
    merge_sort(data, 0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(3);
        randomTime.at(3) += temp;
    }
    saveRunningTime(3,(i+1)*(j+1)-1,resultTime);
    //runningTime[3][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();
    // pivot 
    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();          
    start = clock();
    cout<<"quick_sort_last"<<'\n';
    quick_sort_last(0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(4);
        randomTime.at(4) += temp;
    }
    saveRunningTime(4,(i+1)*(j+1)-1,resultTime);
    //runningTime[4][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();
            
    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();
    start = clock();
    cout<<"quick_sort_median"<<'\n';
    quick_sort_median(0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(5);
        randomTime.at(5) += temp;
    }
    saveRunningTime(5,(i+1)*(j+1)-1,resultTime);
    //runningTime[5][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();
            
    copy(data_origin.begin(), data_origin.end(), data.begin());
    printData();
    start = clock();
    cout<<"quick_sort_random"<<'\n';
    quick_sort_random(0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(6);
        randomTime.at(6) += temp;
    }
    saveRunningTime(6,(i+1)*(j+1)-1,resultTime);
    //runningTime[6][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    printData();   
}
void runningTest(){
    for(int i=0; i<T-2; i++) {
       for(int j=0; j<2; j++){
           clock_t start, end; 
           if(j==0){
                copy(randomTime_origin.begin(), randomTime_origin.end(), randomTime.begin());
                cout<<"randomTime_origin"<<'\n';
                for(auto it=randomTime_origin.begin(); it!=randomTime_origin.end(); ++it)
                    cout<<*it<<" ";
                cout<<'\n';
                cout<<"randomTime"<<'\n';
                for(auto it=randomTime.begin(); it!=randomTime.end(); ++it)
                    cout<<*it<<" ";
                cout<<'\n';                
                for(int k=0; k<3; k++){
                    generateRandomData(N[i]);
                    //double result = (double)(end-start)/CLOCKS_PER_SEC;
                    runSort(i, j);

                }
                cout<<"runningTime"<<'\n';
                for(int k=0; k<7; k++){
                    cout<<runningTime[k][(i+1)*(j+1)-1]<<'\n';
                }
                for(int k=0; k<7; k++){
                    runningTime[k][(i+1)*(j+1)-1] /= 3.0;
                }
            }
            else{
                generateReversedData(N[i]);
                //double result = (double)(end-start)/CLOCKS_PER_SEC;
                runSort(i, j);
            }
       }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
/*
    clock_t start, end;

    start = clock();

//    generateReversedData();
    generateRandomData(10);  
    for(auto it=data_origin.begin(); it!=data_origin.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';
    
    data.resize(data_origin.size());
    copy(data_origin.begin(), data_origin.end(), data.begin());
//    merge_sort(data, 0, data.size()-1);
    quick_sort_last(0, data.size()-1);

//    bubble_sort();
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';

    for(auto it=data_origin.begin(); it!=data_origin.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';


    end = clock();
    double result = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"걸린 시간: "<<result<<"sec"<<'\n';
*/
    runningTest();
    print_result();

    return 0;
}
