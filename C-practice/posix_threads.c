#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static bool timmy_is_home = false;

/*!
 * @brief args for wait_for_timmy function.
 */
struct wait_for_timmy_args
{
	/*! interval time in seconds. */
	unsigned long int wait_time_s;
	/*! total time spent waiting in seconds. */
	unsigned long int total_time_s;
};

/*!
 * @brief wait for timmy to arrive home.
 * @param arguments parameters to the function.
 * @return NULL always.
 */
static void *wait_for_timmy(void *const arguments)
{
	struct wait_for_timmy_args *const args = arguments;
	const struct timespec wait = {.tv_nsec = 0, .tv_sec = args->wait_time_s};

	if (!timmy_is_home) /* WARNING: Data race. */
	{
		printf("Timmy isn't home yet, sleeping %lus...\n", args->wait_time_s);
		if (nanosleep(&wait, NULL) < 0)
		{
			perror("Something went wrong");
			return (NULL);
		}

		args->total_time_s += args->wait_time_s;
		args->wait_time_s *= 2;
		wait_for_timmy(args);
	}

	return (NULL);
}

/*!
 * @brief args for get_timmy_home function.
 */
struct get_timmy_home_args
{
	/*! distance in kilometers.*/
	double distance_km;
	/*! speed of travel in kilometers per hour. */
	const unsigned int speed_km_h;
};

/*!
 * @brief move Timmy across a certain distance at a specific speed.
 * @param arguments parameters to function.
 * @param speed_km_h speed in kilometers per hour.
 * @return total time taken in seconds.
 */
void *get_timmy_home(void *const arguments)
{
	struct get_timmy_home_args *const args = arguments;
	const struct timespec wait = {.tv_sec = 1};
	const double speed_km_s = args->speed_km_h / 3600.0;
	unsigned long int *total_time = calloc(1, sizeof(*total_time));

	if (!total_time)
		return (NULL);

	while (args->distance_km > 0)
	{
		if (nanosleep(&wait, NULL) < 0)
		{
			perror("Something went wrong");
			free(total_time);
			return (NULL);
		}

		args->distance_km -= speed_km_s;
		++(*total_time);
	}

	timmy_is_home = true; /* WARNING: Data race. */
	return (total_time);
}

/*!
 * @brief entry point.
 * @return 0 always.
 */
int main(void)
{
	pthread_t t1, t2;
	struct wait_for_timmy_args wfta = {.wait_time_s = 1};
	int err_t1 = pthread_create(&t1, NULL, wait_for_timmy, &wfta);
	int err_t2 = pthread_create(&t2, NULL, get_timmy_home, &(struct get_timmy_home_args){.distance_km = 5, .speed_km_h = 5000});

	if (err_t1)
		fprintf(stderr, "Could not create thread:%d:%s %s\n", err_t1, strerrorname_np(err_t1), strerror(err_t1));
	else
	{
		err_t1 = pthread_join(t1, NULL);
		if (err_t1)
			fprintf(stderr, "Could not join thread:%d:%s %s\n", err_t1, strerrorname_np(err_t1), strerror(err_t1));

		printf("Timmy is home! ");
		printf("Wait time %lus, total time %lus.\n", wfta.wait_time_s, wfta.total_time_s);
	}

	unsigned long int *time_of_travel = NULL;
	if (err_t2)
		fprintf(stderr, "Could not create thread:%d:%s %s\n", err_t2, strerrorname_np(err_t2), strerror(err_t2));
	else
	{
		err_t2 = pthread_join(t2, (void **)&time_of_travel);
		if (err_t2)
			fprintf(stderr, "Could not join thread:%d:%s %s\n", err_t2, strerrorname_np(err_t2), strerror(err_t2));
	}

	if (time_of_travel)
		printf("Timmy was travelling for %lus\n", *time_of_travel);

	free(time_of_travel);
	return (0);
}
