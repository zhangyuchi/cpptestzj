#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


GIOChannel *g_fc=NULL; 

typedef struct{
    int value;
    int otherValue;
} s_t;



void sigexit_handler (int sig)
{
	GError *error=NULL;
    g_print("<<<<<< proc %d signal %d !!! >>>>>\n", getpid(), sig);
	
	if (g_fc)
		g_io_channel_shutdown(g_fc, 1, &error);
	
    if (sig == 11)
        abort ();
    else
        exit (1);
}

int get_rand128_str(uint8_t *randnumber, size_t size ) //seed is time+
{
    if (size< 16 )
        return -1; 

    GRand *rand = g_rand_new();

    long fnn = 1000000000000000;
    long enn = 9999999999999999;

    snprintf(randnumber, 16, "%f", g_rand_double_range(rand,fnn,enn));
    g_rand_free(rand);

    return 0;
}

static void null_log(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
    return;
} 

void printtofile(const gchar *string)
{
	printf("begin printtofile\n");
	//int fd = open("testlog",  O_APPEND);
	GError *error=NULL;
	gsize bytes_written=0;

	GDateTime *dt=NULL;

    dt= g_date_time_new_now_local();
    gchar *dts = g_date_time_format(dt, "%y-%m-%d %H:%M:%S  ");

    g_io_channel_write_chars(g_fc,
                             dts,
                             strlen(dts),
                             &bytes_written,
                             &error);
	
	g_io_channel_write_chars(g_fc,
                             string,
                             strlen(string),
                             &bytes_written,
                             &error);

	g_free(dts);
	g_date_time_unref(dt);
}

void ptr_free(void *data)
{
	printf("free data is %p\n", data);
}

int	main(int argc, char *argv[])
{
	GRand *rand;
	GTimer *timer;
	
	g_print("++++++++++++++++++++++++++++++test glib rand+++++++++++++++++++++++++++++++++++++++++++\n");
	
	bool yesorno = true;
	gint n;
	gint i, j;
	gint x = 0;

	timer = g_timer_new();
	g_timer_start(timer);
	GHashTable *hashtable = g_hash_table_new (g_str_hash, g_str_equal);

	for(n=0; n<20000; n++)
	{	
		uint8_t *buff = (uint8_t *)malloc(17);
		buff[16]=0;
		get_rand128_str(buff,16);
		//printf("%s\n", buff);
		g_hash_table_insert(hashtable, buff, buff);
	}

	int hashsize = g_hash_table_size(hashtable); 

	g_print("generate rand %d!!!\n", hashsize);

	g_timer_stop(timer);
	
	g_print("%d\tall:%.2f seconds was used!\n",x,g_timer_elapsed(timer,NULL));

	g_warning("%d : %s exiting.", 13, __func__);

	g_print("++++++++++++++++++++++++++++++test glib g_printf handler+++++++++++++++++++++++++++++++\n");

	g_debug("test debug log 1 done\n");
  	g_log_set_handler(NULL, G_LOG_LEVEL_DEBUG, null_log, NULL); 
	g_debug("test debug log 2 done\n");

	//init signal handler

	struct sigaction sa;

	sa.sa_handler = sigexit_handler;
    sa.sa_flags = 0;
    sigaction (SIGTERM, &sa, NULL);
    sigaction (SIGQUIT, &sa, NULL);
    sigaction (SIGSEGV, &sa, NULL);
    sigaction (SIGINT, &sa, NULL);

	//test log


	GError *error=NULL;
	g_fc = g_io_channel_new_file("testlog.dat", "a+", &error);
	
	char filename[256];
	filename[0] = 0;	

	int mret = g_mkdir_with_parents("./log", 0775);
	printf("mret is %d, errno is %d\n", mret, errno);	

	strncat(filename, "./log", 200);
	strcat(filename, "/log.dat");

	printf("logfile is %s\n", filename);
	error=NULL;
    g_fc = g_io_channel_new_file(filename, "a+", &error);

	if (g_fc == NULL)
		printf("create file error is %s\n", error->message);

	g_set_print_handler(printtofile);

	g_print("info level is %d, yesorno is %d\n",G_LOG_LEVEL_INFO, yesorno);
	g_print("debug" 
			"level is %d\n",G_LOG_LEVEL_DEBUG);
		
	g_message("test debug log 3 done\n");

	//`
	s_t test = {.value = 15, .otherValue = 16};
	g_message("value is %d, othervalue is %d\n", test.value, test.otherValue);

	printf("+++++++++++++++++++++++++++++test glib ptr array+++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	GPtrArray *relay_array = g_ptr_array_sized_new (500);
	g_ptr_array_add(relay_array, 123);

	printf("relay array first e is %d\n", g_ptr_array_index(relay_array,0));

	//pause();
	int g=0;

	GRand *myrand = g_rand_new();
	for ( ;g<10; ++g)
	{
		printf("%d ", g_rand_int_range(myrand, 0,0));
	}
	printf("\n");
	g_rand_free(myrand);

	printf("me = %d\n", 1>0?1:0);

	char ip[16] = "10.0.3.193";
	uint32_t ip1,ip2,ip3,ip4;
	sscanf(ip, "%d.%d.%d.%d", &ip1,&ip2,&ip3,&ip4);
	
	uint32_t nip = 0;
	nip += ip1<<24;
	nip += ip2<<16;
	nip += ip3<<8;
	nip += ip4;

	int nip1 = inet_addr("10.0.3.193");
		

	printf("ip is %d-%d-%d-%d, %u, %u\n", ip1,ip2,ip3,ip4, nip, nip1);

	s_t buffer[5];

	printf("buffer size is %d\n", sizeof(buffer));

	printf("+++++++++++++++++++++++++++++test glib ptr array size+++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	//GPtrArray *gpa = g_ptr_array_sized_new(100);
	//g_ptr_array_set_free_func(gpa, ptr_free);
	GPtrArray *gpa = g_ptr_array_new_full(100, ptr_free);	

	printf("init gba len is %d\n", gpa->len);
	
	int vs[10] = {1};
	
	int bai=0;
	for( ; bai<10; ++bai)
	{
		g_ptr_array_add(gpa, &vs[bai]);
		printf("gba size is %d\n", gpa->len);
	}

	g_ptr_array_free(gpa, 1);

	printf("+++++++++++++++++++++++++++++test glib byte+++++++++++++++++++++++++++++++++++++++++++++++++++\n");	

	GBytes *gb= g_bytes_new (vs, 40);
	printf("gb size is %d\n", g_bytes_get_size(gb));

	printf("++++++++++++++++++++++++++++test hash int64++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	GHashTable *dht = g_hash_table_new (g_direct_hash, g_direct_equal);	

	uint64_t num=0;
	while(1)
	{
		printf("%ld -> %ld\n", num, g_direct_hash(num));
		num += 1;	
	}	
	return 0;
}


