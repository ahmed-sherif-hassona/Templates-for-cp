long long modPow(long long a,long long b,long long MOD){

    a%=MOD;

    long long ans=1;

    while(b){

        if(b&1)
            ans=(ans*a)%MOD;

        a=(a*a)%MOD;

        b>>=1;
    }

    return ans;
}
