//SPOJ
#include "stdio.h"
#include "stdlib.h"
#pragma GCC optimize "Ofast"
int main()
{
	int tcase;
	scanf("%d", &tcase);
	while(tcase--)
	{
		int m, n;
		scanf("%d %d", &m, &n);
		int *primes=new int[n-m+1];
		for(int i=0; i<=n-m; i++)
			primes[i]=0;
		for(int p=2; p*p<=n; p++)
		{
			int nt=m/p;
			nt=nt*p;
			for(; nt<=n; nt=nt+p)
				if(nt!=p && nt>=m)
					primes[nt-m]=1;
		}
		for(int i=0; i<=n-m; i++)
		{
			//printf("%d %d  ", i, primes[i]);
			if(primes[i]==0 && (i+m)!=1)
				printf("%d\n", i+m);
		}
		printf("\n");
		delete primes;
	}
	return 0;
}
