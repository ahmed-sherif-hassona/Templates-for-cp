long long nPr(int n,int r){
    long long ans=1;
    for(int i=0;i<r;i++)
        ans*=n-i;
    return ans;
}
