#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#define T 3

using namespace std;

int N = 1000;
vector<int> data;

void generateRandomData(){
    srand((unsigned int) time(NULL));
    for(int i=0; i<N; i++){
        // random 수 생성
        int number = rand()%1000+1;
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

    end = clock();
    double result = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"걸린 시간: "<<result<<"sec"<<'\n';

    return 0;
}
