#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static GMutex *mutex = NULL;
static gboolean t1_end = FALSE;
static gboolean t2_end = FALSE;
typedef struct _Arg Arg;
GPrivate *thr_key;

struct _Arg
{
	GMainLoop* loop;
	gint max;
	gint id;
};

void printrand()
{
	unsigned int i,j;
	
	j = rand();
	for(i=0; i< 100; ++i)
	{
		++j;
		uint64_t num = rand_r(&j);
		//printf("%ld | ", (num << 32)|num);
	}

	printf("\n");
}

void	run_1(Arg *arg)
{
	int i ;

	g_private_set(thr_key, 1);

	printrand();

	for(i=0; i<arg->max; i++)
	{
		if(g_mutex_trylock(mutex) == FALSE)
		{
			//g_print("%d : thread 2 locked the mutex \n", i);
			g_print("1 - %d: thread 2 lock mutex\n", i);
			g_mutex_unlock(mutex);
		}
		else
		{
			g_usleep(10);
		}
	}
	t1_end = TRUE;
    int tk = g_private_get(thr_key);
    g_print("1 %p thr_key is %d\n", g_thread_self(), tk);

}
void	run_2(Arg *arg)
{
	int i;

	 g_private_set(thr_key, 2);

	printrand();

	for(i=0; i<arg->max; i++)
	{
		if(g_mutex_trylock(mutex) == FALSE)
		{
			//g_print("%d : thread 1 locked mutex \n", i);
			g_print("2 - %d: thread 1 lock mutex\n", i);
			g_mutex_unlock(mutex);
		}
		else
		{
			g_usleep(10);
		}
	}
	t2_end = TRUE;
    int tk = g_private_get(thr_key);
    g_print("2 %p thr_key is %d\n", g_thread_self(), tk);
}

void run_3(Arg *arg)
{
	g_private_set(thr_key, 3);
	for(;;)
	{
		if(t1_end && t2_end)
		{
    		int tk = g_private_get(thr_key);
    		g_print("3 %p thr_key is %d\n", g_thread_self(), tk);
			g_main_loop_quit(arg->loop);
			break;
		}
	}
}

int	main(int argc, char *argv[])
{
	GMainLoop *mloop;
	Arg *arg;
	

	srand(100);

	if(!g_thread_supported())
		g_thread_init(NULL);
	mloop = g_main_loop_new(NULL, FALSE);
	
	arg = g_new(Arg, 1);
	arg->loop = mloop;
	arg->max = 11;
		
	thr_key = g_private_new (NULL);
	g_private_set(thr_key, 100);

	mutex = g_mutex_new();
	g_thread_create(run_1, arg, TRUE, NULL);
	g_thread_create(run_2, arg, TRUE, NULL);
	g_thread_create(run_3, arg, TRUE, NULL);
	
	g_main_loop_run(mloop);
	g_print("thread 3 quit\n");
	g_mutex_free(mutex);
	g_print("release mutex obj\n"); 
	g_free(arg);
	g_print("release arg memory\n");

	int tk = g_private_get(thr_key);
	g_print("main thr_key is %d\n", tk);
	
	return 0;
}


