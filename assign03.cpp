#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#define T 3

using namespace std;

int N[3] = {10, 10000, 100000};
double runningTime[9][6] ={0.0};
vector<int> data;
vector<int> data_origin;

void merge(vector<int> data, int p, int q, int r);
int partition_last_pivot(int left, int right);
int partition_first_pivot(int left, int right);
int partition_random_pivot(int left, int right);

void print_result() {

    cout<<"        \tRandom1000";

    cout<<"    Reverse1000";

    cout<<"    Random10000";

    cout<<"    Reverse10000";

    cout<<"    Random100000";

    cout<<"    Reverse100000"<<'\n';
    int i;
    for(i=0; i<7; i++){
        cout.flags(ios::right);
        if(i==0){
            cout.width(15);
            cout<<"Bubble sort";
        }
        else if(i==1){
            cout.width(15);
            cout<<"Selection sort";
        }
        else if(i==2){
            cout.width(15);
            cout<<"Insertion sort";
        }
        else if(i==3){
            cout.width(15);
            cout<<"Merge";
        }
        else if(i==4){
            cout.width(15);
            cout<<"Quick1";
        }
        else if(i==5){
            cout.width(15);
            cout<<"Quick2"; 
        }
        else if(i==6){
            cout.width(15);
            cout<<"Quick3";                    
        }
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
            cout.width(10);
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
/*
void quick_sort_first(int left, int right){
    if(left<right){
        int pivot = partition_first_pivot(left, right);
        quick_sort_last(left, pivot-1);
        quick_sort_last(pivot+1, right);
    }
    
}
int partition_first_pivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    int check = data.at(left);

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
    int checkIndex = left + rand()%(right-left)+1;
    int check = data.at(checkIndex);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}
*/
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

void runningTest(){
    for(int i=0; i<T-2; i++) {
       for(int j=0; j<2; j++){
           clock_t start, end; 
           if(j==0){
                generateRandomData(N[i]);
                //double result = (double)(end-start)/CLOCKS_PER_SEC;
            }
            else{
                generateReversedData(N[i]);
                //double result = (double)(end-start)/CLOCKS_PER_SEC;
            }
            data.resize(data_origin.size());
            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
            start = clock();
            cout<<"bubble sort"<<'\n';
            bubble_sort();
            end = clock();
            runningTime[0][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';

            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
            start = clock();
            cout<<"selection sort"<<'\n';
            selection_sort();
            end = clock();
            runningTime[1][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';

            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';            
            start = clock();
            cout<<"insertion sort"<<'\n';
            insertion_sort();
            end = clock();
            runningTime[2][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';

            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';            
            start = clock();
            cout<<"merge sort"<<'\n';
            merge_sort(data, 0, N[i]-1);
            end = clock();
            runningTime[3][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
            // pivot 추
            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';            
            start = clock();
            cout<<"quick_sort_last"<<'\n';
            quick_sort_last(0, N[i]-1);
            end = clock();
            runningTime[4][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
/*
            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
            start = clock();
            cout<<"quick_sort_first"<<'\n';
            quick_sort_first(0, N[i]-1);
            end = clock();
            runningTime[5][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';

            copy(data_origin.begin(), data_origin.end(), data.begin());
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
            start = clock();
            cout<<"quick_sort_random"<<'\n';
            quick_sort_random(0, N[i]-1);
            end = clock();
            runningTime[6][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
            for(auto it=data.begin(); it!=data.end(); ++it)
                cout<<*it<<" ";
            cout<<'\n';
*/
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
