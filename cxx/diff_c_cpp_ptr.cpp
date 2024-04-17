#ifdef __cplusplus
extern "C" {
#endif

int main()
{
    double* f;
    int* i;
    void* sth;

    sth = f;
    // g++ compiler complains: invalid conversion from
    // 'void*' to 'int*', but gcc won't
    i = sth;
}

// 'extern "C"' only affects nothing other than function name mangling
#ifdef __cplusplus
}
#endif

