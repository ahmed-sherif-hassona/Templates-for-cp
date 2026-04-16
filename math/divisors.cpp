vector<ll> get_divisors(ll n) {
  vector<ll> divs;
  for (int i = 1; 1LL * i * i <= n; i++) {
    if (n % i == 0) {
      divs.push_back(i);
      if (i != n / i) {
        divs.push_back(n / i);
      }
    }
  }
  sort(divs.begin(), divs.end());
  return divs;
}

//seive for nuber of divisors for all numbers
vector<int> sum(N + 1, 0);
for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
        sum[j] += i;
    }
}
