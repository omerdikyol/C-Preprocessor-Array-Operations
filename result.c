int main()
{
    int A[10];
    float B[10];
    int C[10];
    float A[10];
    FILE *ff=fopen("f1","r");

    for (int i=0; i<10; i++)
        fscanf(ff, "%d" &A[i]);
    close(ff);

    for (int i=0; i<10; i++)
        B[i] = 5;

    for (int i=0; i<5; i++)
        X[i] = Q[i];

    for (int i=0; i<; i++)
        T[i] = M[i] + N[i];

    for (int i=0; i<; i++)
        Y[i] = A[i] - 5;

    for (int i=0; i<10; i++)
        C[i] = 2 / A[i];

    for (int i=0; i<10; i++)
        printf("%d", &C[i]);
}