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
    cout<<"merge sort start!"<<'\n';
    if(left<right){
        int mid = (left+right)/2;
        cout<<"mid: "<<mid<<'\n';
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(data, left, mid, right);
    }
}
void merge(vector<int> arr, int left, int mid, int right){
    cout<<"merge start!"<<'\n';
    vector<int> sortedData;
    int i=left;
    int j=mid+1;
    int k=left;

    cout<<"i: "<<i<<'\n';
    cout<<"j: "<<j<<'\n';
    cout<<"k: "<<k<<'\n';
    cout<<"left: "<<left<<'\n';
    cout<<"mid: "<<mid<<'\n';
    cout<<"right: "<<right<<'\n';
    while(i<=mid && j<=right){
        cout<<"start while!"<<'\n';
        cout<<"arr["<<i<<"]: "<<arr.at(i)<<'\n';
        cout<<"arr["<<j<<"]: "<<arr.at(j)<<'\n';
        if(arr.at(i)<=arr.at(j)){
            cout<<"check first if!"<<'\n';
            sortedData.push_back(arr.at(i++));
        }
        else{
            cout<<"check second if!"<<'\n';
            sortedData.push_back(arr.at(j++));
        }
        cout<<"sortedData[0]: "<<sortedData.at(0)<<'\n';
    }
    // front array done
    if(i>mid){
        cout<<"!start first if!"<<'\n';
        for(int l=j; l<=right; l++)
            sortedData.push_back(arr.at(l));
    }
    // back array done
    else if(j>right){
        cout<<"!start second if!"<<'\n';
        for(int l=i; l<=mid; l++)
            sortedData.push_back(arr.at(l));
    }
    cout<<"sortedData[1]: "<<sortedData.at(1)<<'\n';
    cout<<"sortedData: "<<" ";
    for(int l=left; l<=right; l++){
        cout<<sortedData.at(l-left)<<" ";
        data[l] = sortedData.at(l-left);
    }
    cout<<'\n';
    cout<<"data: "<<" ";
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';
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
