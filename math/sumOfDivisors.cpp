long long sumOfDivisors(long long n){

    long long ans = 1;

    for(long long i = 2; i <= n / i; i++){

        if(n % i == 0){

            long long term = 1;
            long long power = 1;

            while(n % i == 0){

                n /= i;
                power *= i;
                term += power;
            }

            ans *= term;
        }
    }

    if(n > 1)
        ans *= (1 + n);

    return ans;
}
