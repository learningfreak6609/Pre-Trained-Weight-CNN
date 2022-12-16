#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
#include "function.h"
using namespace std;
int main(int argc,char* argv[]){
    if(strcmp("vector_sigmoid",argv[1])==0){
       float temp;
       int x=0;
       vector<float> v;
       ifstream filess (argv[2]);
       while (filess>>temp){      
              v.push_back(temp);
       }
       sigmoid(v);
       return 0;
    }
    else if(strcmp("vector_softmax",argv[1])==0){
       float temp;
       int x=0;
       vector<float> v;
       ifstream filess (argv[2]);
       while (filess>>temp){      
              v.push_back(temp);
       }
       softmax(v);
       return 0;
    }
    //[1]convolution_withpadding_matrixmult [2]padsize [3]matrix1.txt [4]matrix1_numrows [5]matrix2.txt [6]matrix2_numrows
	int r=0,c=0;
    // matrix1.txt: input matrix
    // matrix2.txt: kernal matrix
    string n0=argv[4];
    int n,p,k;
    sscanf(n0.c_str(),"%d",&n);
    /////////////
    stringstream test(argv[1]);
    string segment;
    vector<string> seglist;
    while(getline(test, segment, '_')){
        seglist.push_back(segment);
    }
    // cout<<seglist[0]<<" "<<seglist[1]<<" "<<seglist[2]<<endl;
    // cout<<"n: "<<n<<" p: "<<p<<" k: "<<k<<endl;
    
    ///
    bool b1=false,b2=false;
    if(n<0){cout<<"please enter positive input size";return 0;}
    vector< vector<float> >  input_matrix(n, vector < float >(n) );
    float trim;
	ifstream file(argv[3]);
    while(file >> trim ){
        b1=true;
        input_matrix[r][c] = trim;
        if(r<n-1) r++;
        else {
            r=0;
            c++;
        }
    }
    if(b1);
    else{
        cout<<"please enter the valid input file"<<endl;
        return 0;
    }
    ///////////////////////////
    if(strcmp("Rectangular_unit",argv[1])==0){
        cout<<"relu :"<<endl;
        display(relu(input_matrix));
        return 0;
    }
    else if(strcmp("tan_hyperbolic",argv[1])==0){
        cout<<"tanh :"<<endl;
        display(tanh(input_matrix));
        return 0;
    }
    else if(strcmp("max_pool",argv[1])==0){
        cout<<"max_pool :"<<endl;
        display(max_pool(input_matrix));
        return 0;
    }
    else if(strcmp("avg_pool",argv[1])==0){
        cout<<"avg_pool :"<<endl;
        display(avg_pool(input_matrix));
        return 0;
    }
    //////////////////////////////
    string p0=argv[2];
    string k0=argv[6];
    sscanf(p0.c_str(),"%d",&p);
    sscanf(k0.c_str(),"%d",&k);
	ifstream file2(argv[5]);
    if(k<0){cout<<"please enter positive kernel size";return 0;}
    vector< vector<float> >  kernal_matrix(k, vector<float>(k));
    float temp=0;
    r=0;c=0;
    while(file2 >> temp ){
        b2=true;
        kernal_matrix[r][c] = temp;
        if(r<k-1) r++;
        else {
            r=0;
            c++;
        }
    }
    if(b2);
    else{
        cout<<"please enter the valid kernal input file"<<endl;
        return 0;
    }
    if(n<k){
        cout<<"kernal matrix should be smaller then input matrix in size"<<endl;
        cout<<"try again with different size"<<endl;
        return 0;
    }
    cout<<"Entered kernal_matrix"<<endl;
    display(kernal_matrix);
    cout<<"Entered input_matrix"<<endl;
    display(input_matrix);
    if(strcmp("convolution_withpadding_matrixmult",argv[1])==0){
        if(p<0){cout<<"please enter positive padding OR choose without padding";return 0;}
        cout<<"convolution_matrix :"<<endl;        
        vector< vector<float> >  input_matrix2(n+2*p, vector < float >(n+2*p) );
        input_matrix2 = padding(input_matrix,p);
        display(mux(kernal_matrix,input_matrix2));
        return 0;
    }
    else if(strcmp("convolution_withoutpadding_matrixmult",argv[1])==0){
        cout<<"convolution_matrix :"<<endl;        
        display(mux(kernal_matrix,input_matrix));
        return 0;
    }
    else if(strcmp("convolution_withpadding_withoutmatrixmult",argv[1])==0){
        if(p<0){cout<<"please enter positive padding OR choose without padding";return 0;}
        cout<<"convolution_matrix :"<<endl;
        vector< vector<float> >  input_matrix2(n+2*p, vector < float >(n+2*p) );
        input_matrix2 = padding(input_matrix,p);
        display(Convolution(input_matrix2,kernal_matrix));
        return 0;
    }
    else if(strcmp("convolution_withoutpadding_withoutmatrixmult",argv[1])==0){
        cout<<"convolution_matrix :"<<endl;
        display(Convolution(input_matrix,kernal_matrix));
        return 0;
    }
    else{
        cout<<"please type a command from provided ReadMe file thanks";
    }
    return 0;
}