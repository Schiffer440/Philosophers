#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
 
uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
	// get_time(void) - getimeofday(0) //
}

int main(void)
{
	struct timeval	tv;
	time_t	timenow;
	time_t	r_time;

	// // r_time = gettimeofday(&tv, NULL);
	// printf("seconds : %ld\nmicro seconds : %ld\n", tv.tv_sec, tv.tv_usec);
	// timenow = get_time() - gettimeofday(&tv, NULL);
	// printf("TIME:%ld\n", timenow);
	timenow = get_time();
	sleep(1);
	r_time = get_time() - timenow;
	printf("time passed%ld\n", r_time);
}
