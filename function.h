#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
void display(vector< vector<float> > vd);
vector< vector<float> > padding(vector< vector<float> > input,int p);
vector< vector<float> > relu(vector< vector<float> > vd ,int n );
vector< vector<float> > tanh(vector< vector<float> > vd,int n);
vector< vector<float> > max_pool (vector< vector <float> > v , int n );
vector< vector<float> > avg_pool (vector< vector <float> > v , int n );
vector< vector<float> > mult(vector< vector<float> > M1,vector< vector<float> > M2,int k1,int k2,int k3);
vector< vector<float> > mux(vector< vector<float> > kernal,vector< vector<float> > input,int k,int n);
vector< vector<float> > Convolution(vector< vector<float> > kernal,vector< vector<float> > input,int k,int n);
void softmax (vector<float> vec);
void sigmoid (vector<float> vec);
void display(vector< vector<float> > vd){
    int i, j;
    int n=vd.size();
    int k=vd[0].size();
    // cout << "Output Matrix:" << endl;
    for(i = 0; i < n; ++i){
        for(j = 0; j < k; ++j){
            cout << vd[i][j] << " ";
            if(j == k- 1)
                cout << endl;
        }
    }
}
vector< vector<float> > padding(vector< vector<float> > input,int p){
    int n=input.size();
    vector< vector<float> >  pad_matrix(n+2*p, vector<float>(n+2*p));
    int i=0,j=0;
    for(int x=p;x<n+p;x++){
        for(int y=p;y<n+p;y++){
            pad_matrix[x][y] = input[i][j];
            j++;
        }
        i++;j=0;
    }
    // disply(pad_matrix);
    return pad_matrix;    
}
vector< vector<float> > relu(vector< vector<float> > vd){
    int n=vd.size();
    vector< vector<float> >  matrix(n, vector<float>(n));    
    for(int i = 0; i < n; ++i){
        // cout<<"asdf"<<endl;
        for(int j = 0; j < n; ++j){
            if( vd[i][j] < 0 ){
                matrix[i][j]=0;
                }
            else matrix[i][j]=vd[i][j];
        }    
    }
    return matrix;
}
vector< vector<float> > tanh(vector< vector<float> > vd){
    int i, j;
    float f;
    int n=vd.size();
    vector< vector<float> >  matrix(n, vector<float>(n));
    for(i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            matrix[i][j]=tanh(vd[i][j]);
        }
    }
    return matrix;
}
vector< vector<float> > max_pool (vector< vector <float> > v){
    int n=v.size();	
    int t = n;
    vector< vector<float> > mat_temp(t,vector<float>(t));
    if(t%2!=0){
        t=t+1;
        mat_temp.resize(t);
        for (int i = 0; i < t; ++i)
            mat_temp[i].resize(t);
        for(int i=0; i<t-1; i++){
            for (int j=0; j<t-1; j++){
                mat_temp[i][j] = v[i][j];
            }
        }
    }
    else{
    	for (int i=0;i<t; i++){
     	    for (int j=0;j<t; j++){
               mat_temp[i][j] = v[i][j];
            }
        }
    }
    vector< vector<float> > matrix (t/2,vector<float>(t/2));
    vector<float> vec(4) ;
    float temp,max;
    for (int i=0; i<n; i=i+2){
        for (int j=0; j<n; j=j+2){
            vec[0] = mat_temp[i][j];
            vec[1] = mat_temp[i][j+1];
            vec[2] = mat_temp[i+1][j];
            vec[3] = mat_temp[i+1][j+1];
            max=vec[0];
            for (int k=0;k<4;k++){
                if( max < vec[k] )
                    max = vec[k];
            }
            matrix[i/2][j/2] = max;
            vec.clear();
        }
    }
    return matrix;
}

vector< vector<float> > avg_pool (vector< vector <float> > v){
    int n=v.size();	
    int t = n;
    vector< vector<float> > mat_temp(t,vector<float>(t));
    if(t%2!=0){
        t=t+1;
        mat_temp.resize(t);
        for (int i = 0; i < t; ++i)
            mat_temp[i].resize(t);
        for(int i=0; i<t-1; i++){
            for (int j=0; j<t-1; j++){
                mat_temp[i][j] = v[i][j];
            }
        }
    }
    else{
    	for (int i=0;i<t; i++){
     	    for (int j=0;j<t; j++){
               mat_temp[i][j] = v[i][j];
            }
        }
    }
    vector< vector<float> > matrix (t/2,vector<float>(t/2));
    vector<float> vec(4) ;
    for (int i=0; i<n; i=i+2){
        for (int j=0; j<n; j=j+2){
            float sum = 0 ;
            int avg = 0 ;
            vec[0] = mat_temp[i][j];
            vec[1] = mat_temp[i][j+1];
            vec[2] = mat_temp[i+1][j];
            vec[3] = mat_temp[i+1][j+1];
            for (int k=0;k<4;k++){
                sum += vec[k];    
            }
            avg = sum/4 ;
            matrix[i/2][j/2] = avg;
            vec.clear();
        }   
    }
    return matrix;
}
vector< vector<float> > mult(vector< vector<float> > M1,vector< vector<float> > M2,int k1,int k2,int k3){
    vector< vector<float> >  result_matrix(k1, vector<float>(k3));
    for(int i = 0; i < k1; i++)
        for(int j = 0; j < k3; j++)
            for(int k = 0; k < k2; k++){
                result_matrix[i][j] = result_matrix[i][j] + (M1[i][k] * M2[k][j]);
            }
    return result_matrix;        
}
vector< vector<float> > mux(vector< vector<float> > kernal,vector< vector<float> > input){
    int n,k;
    n = input.size();
    k = kernal.size();
    int s=0,t=0;
    int ord=(n-k+1);
    vector< vector<float> >  PI_matrix(ord*ord, vector<float>(k*k));
    vector< vector<float> >  PW_matrix(k*k, vector<float>(1));
    for(int p=0;p<ord;p++){
        for(int q=0;q<ord;q++){
            for(int i=p;i<k+p;i++){
                for(int j=q;j<k+q;j++){
                    PI_matrix[s][t]=input[i][j];
                    t++;
                }
            }
            s++;
            t=0;
        }
    }
    int r=0;
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            PW_matrix[r][0]=kernal[i][j];
            r++;
        }
    }
    vector< vector<float> >  final_matrix(ord*ord, vector<float>(1));
    vector< vector<float> >  final2_matrix(ord, vector<float>(ord));    
    final_matrix = mult(PI_matrix,PW_matrix,ord*ord,k*k,1);
    int l=0;
    for(int y=0;y<ord;y++){
        for(int u=0;u<ord;u++){
            final2_matrix[y][u] = final_matrix[l][0];
            l++;
        }
    }
    return final2_matrix;
}
vector< vector<float> > Convolution(vector< vector<float> > input,vector< vector<float> > kernal){
    int n,k;
    n = input.size();
    k = kernal.size();
    int ord=n-k+1;
    vector< vector<float> >  C_matrix(ord, vector<float>(ord));
    for(int x=0;x<ord;x++){
        for(int y=0;y<ord;y++){
            int sum=0;
            for(int i=0;i<k;i++){
                for(int j=0;j<k;j++){
                   // if( (x-i+1)<=k && (y-j+1)<=k && (x-i+1)>0 && (y-j+1)>0 )
                    sum=sum+ input[x+i][y+j]*kernal[i][j];
                }
            }
            C_matrix[x][y]=sum;
        } 
    }
    return C_matrix;    
}
void sigmoid (vector<float> vec){
       float prob;
       vector<float> sig;
       for (int i = 0; i<vec.size(); i++){
              prob = (1/(1 + exp(-(vec[i]))));
              sig.push_back(prob);
       }
       for (int i = 0; i<sig.size(); i++){  
              cout<< sig[i]<<" , ";
              if(i==sig.size()-2){
               cout<< sig[i+1];
               break;
                }
       }     
       cout<<endl;
}
void softmax (vector<float> vec) {
       float prob;
       float sum =0;
       vector<float> soft;
       for (int i = 0; i < vec.size(); i++){
           sum = sum + exp(vec[i]);
       }
       for (int i = 0; i<vec.size(); i++){
           prob = (exp(vec[i])/sum);
           soft.push_back(prob);
       }
       for (int i = 0; i<soft.size(); i++){  
           cout<< soft[i]<< " , ";
           if(i==soft.size()-2){
               cout<< soft[i+1];
               break;
           }
       }
           cout<<endl;
}
