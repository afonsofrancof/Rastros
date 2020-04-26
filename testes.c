void a(int *tamanho)
{
    *tamanho++;
}

int main()
{
    int tamanho = 0;
    a(&tamanho);
    printf("%d \n", tamanho);
}