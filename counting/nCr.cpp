long long nCr(int n,int r){

    if(r>n) return 0;

    if(r>n-r)
        r=n-r;

    long long ans=1;

    for(int i=1;i<=r;i++){

        ans*=n-r+i;
        ans/=i;

    }

    return ans;

}
