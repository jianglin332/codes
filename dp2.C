    #include <cstdio>
    const unsigned int mod = 1e9+7;
    unsigned int a[202020];
    main()
    {
        unsigned int n, m;
        scanf("%d%d", &n, &m);
        for (unsigned int i = 0; i < m; i++)
        {
            unsigned int f, t, d;
            char c = 0;
            while (scanf("%c", &c))
            {
                if (c == 'Q' || c == 'C')
                    break;
            };
            if (c == 'Q')
            {
                scanf("%d%d", &f, &t);
                unsigned int a1 = 0, a2 = 0, s = 0;
                for (unsigned int j = f; j <= t; j++)
                    a1 = (a1 + a[j]) % mod;
                for (unsigned int j = 1; j < f; j++)
                    s = (s + a[j]) % mod;
                for (unsigned int j = f; j <= t; j++)
                {
                    s = (s + a[j]) % mod;
                    a2 = (a2 + s) % mod;
                }
                printf("%u %u\n", a1, a2);
            }
            if (c == 'C')
            {
                scanf("%d%d%d", &f, &t, &d);
                for (unsigned int j = f; j <= t; j++)
                    a[j] = (d + a[j]) % mod;
            }
        }
        return 0;
    }
