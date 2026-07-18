vector<pair<long long,int>> factorize(long long n){

    vector<pair<long long,int>> factors;

    for(long long i=2;i<=n/i;i++){

        if(n%i==0){

            int cnt=0;

            while(n%i==0){

                cnt++;
                n/=i;

            }

            factors.push_back({i,cnt});
        }
    }

    if(n>1)
        factors.push_back({n,1});

    return factors;
}
