/*************************************************************************
	> File Name: primes.c
	> Description: thread primes.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 09时35分21秒
 ************************************************************************/
#include "unp.h"

void *compute_prime(void *arg){
	int candidate = 2;
	int n = *((int *)arg);

	while(1){
		int factor;
		int is_prime = 1;
		/*check it if the prime*/
		for(factor = 2; factor < candidate; factor++){
			if(candidate % factor == 0){
				is_prime = 0;
				break;
			}
		}
		/*the prime is that we find.*/
		if(is_prime){
			if(--n == 0)
				return (void *)candidate;
		}
		candidate++;
	}
	return NULL;
}

int main(){
	pthread_t thread;
	int which_prime = 5000;
	int prime;
	
	/*start compute thread, get the 5000 prime.*/
	pthread_create(&thread, NULL, &compute_prime, &which_prime);

	/*do other work*/

	/*wait the end of thread, get the result.*/
	pthread_join(thread, (void *)&prime);
	
	/*output the max prime.*/
	printf("The %dth prime number is %d.\n", which_prime, prime);
	
	return 0;
}


