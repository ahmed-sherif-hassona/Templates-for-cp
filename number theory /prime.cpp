bool is_prime(long long n) {       // o(rot n)
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;

    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------

const int N = 1e6+5;
bool is_comp[N]; // true = مش prime    O(nloglogn)
void sieve(int n) {
    is_comp[1] = true;
    for (int i = 2; i * i <= n; i++) {
        if (!is_comp[i]) {
            for (int j = i * i; j <= n; j += i)
                is_comp[j] = true;
        }
    }
}
