#define N 3
double a[N] = {1, 2, 3},
       b[N] = {4, 5, 6};

double resultado = 0;

for (int i=0; i<N; i++)
    resultado += a[i] * b[i];

