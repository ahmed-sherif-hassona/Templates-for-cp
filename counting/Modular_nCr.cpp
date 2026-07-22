const int N=2e5+5;
const long long MOD=1e9+7;

long long fact[N],invFact[N];

long long power(long long a,long long b){

    long long ans=1;

    while(b){

        if(b&1)
            ans=ans*a%MOD;

        a=a*a%MOD;

        b>>=1;
    }

    return ans;

}

void init(){

    fact[0]=1;

    for(int i=1;i<N;i++)
        fact[i]=fact[i-1]*i%MOD;

    invFact[N-1]=power(fact[N-1],MOD-2);

    for(int i=N-2;i>=0;i--)
        invFact[i]=invFact[i+1]*(i+1)%MOD;

}

long long nCr(int n,int r){

    if(r<0||r>n)
        return 0;

    return fact[n]*invFact[r]%MOD*invFact[n-r]%MOD;

}
