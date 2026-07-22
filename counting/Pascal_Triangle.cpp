const int N=1005;

long long C[N][N];

void build(){

    for(int i=0;i<N;i++){

        C[i][0]=1;
        C[i][i]=1;

        for(int j=1;j<i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }

}
