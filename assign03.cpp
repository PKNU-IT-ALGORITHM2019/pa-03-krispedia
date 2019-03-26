#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#define T 3

using namespace std;

int N = 100;
vector<int> data;

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
void merge(){

}
void merge_sort(){

}
void quick_sort_last_pivot(){
    int pivot = data.at(data.size()-1);

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

    bubble_sort();

    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';

    end = clock();
    double result = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"걸린 시간: "<<result<<"sec"<<'\n';

    return 0;
}
