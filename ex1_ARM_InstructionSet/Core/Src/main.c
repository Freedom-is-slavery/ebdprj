int test05(void);
int inside01(int p1, int p2);

int a;

int main(void)
{
    a = test05();  
}


int test05(void)
{
    int b1 = 2, b2 = 6;
    int ret;
    b1 = b1 * 2;
    ret = inside01(b1,b2);
    return ret;
}

int inside01(int p1, int p2)
{
    int p, c = 6;
    p = p1 * p2 + c;
    return p;
}
