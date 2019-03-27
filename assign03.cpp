#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#define T 3

using namespace std;

int N = 10;
vector<int> data;

void merge(vector<int> data, int p, int q, int r);
int partition_last_pivot(vector<int> arr, int left, int right);

void swap(int index1, int index2){
    int temp = data.at(index1);
    data.at(index1) = data.at(index2);
    data.at(index2) = temp;
}
void bubble_sort(){
    for(int i = data.size()-1; i>=0; i--){
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
void quick_sort_last(vector<int> arr, int left, int right){
    if(left<right){
        int pivot = partition_last_pivot(arr, left, right);
        quick_sort_last(arr, left, pivot-1);
        quick_sort_last(arr, pivot+1, right);
    }
}
int partition_last_pivot(vector<int> arr, int left, int right){
    int i=left-1;
    //int j=left;

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(arr.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);
    return i+1;
}
void quick_sort_first_pivot(){
    int pivot = data.at(0);
}
void quick_sort_random_pivot(){
    srand((unsigned int) time(NULL));
    int pivot = rand()%data.size();
}
void generateRandomData(){
    srand((unsigned int) time(NULL));
    for(int i=0; i<N; i++){
        // random 수 생성
        int number = rand()%N+1;
        data.push_back(number);
    }
}
void generateReversedData(){
    for(int i=0; i<N; i++){
        data.push_back(N-i);
    }
}

void runningTest(){
    for(int i=0; i<T; i++) {
       for(int j=0; j<2; j++){
            if(j==0){
                clock_t start, end;
                start = clock();
                generateRandomData();
                end = clock();
                double result = (double)(end-start)/CLOCKS_PER_SEC;
            }
            else{
                clock_t start, end;
                start = clock();
                generateReversedData();
                end = clock();
                double result = (double)(end-start)/CLOCKS_PER_SEC;
            }
       }
    }
}

int main(void) {
    clock_t start, end;

    start = clock();

//    generateReversedData();
    generateRandomData();  
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';

    merge_sort(data, 0, data.size()-1);
//    quick_sort_last(data, 0, data.size()-1);

    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';

    end = clock();
    double result = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"걸린 시간: "<<result<<"sec"<<'\n';

    return 0;
}
