long long numberOfDivisors(long long n){

    long long ans = 1;

    for(long long i = 2; i <= n / i; i++){

        if(n % i == 0){

            int cnt = 0;

            while(n % i == 0){

                cnt++;
                n /= i;
            }

            ans *= (cnt + 1);
        }
    }

    if(n > 1)
        ans *= 2;

    return ans;
}
