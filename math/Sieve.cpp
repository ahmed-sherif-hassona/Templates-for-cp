const int MAXN = 1000000;

vector<bool> isPrime(MAXN + 1, true);

void sieve() {

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= MAXN; i++) {

        if (!isPrime[i])
            continue;

        for (int j = i * i; j <= MAXN; j += i)
            isPrime[j] = false;
    }
}
