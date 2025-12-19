#define CLR_RMV	"\033[0m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define ERRLOG_FILE "error_log.txt"

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define SEED 42
#define NTEST 100
#define NGROUP 5 


char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);

typedef enum s_e_ops
{
	OP_NULL = 0,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	SA,
	SB,
	SS,
	OP_COUNT,

}	e_ops;

typedef enum s_e_stats
{
	STAT_NULL = 0,
	STAT_TIME_TOT,
	STAT_TIME_AVG,
	STAT_MOVES_N,
	STAT_MOVES_NLOGN,
	STAT_MIN,
	STAT_MAX,
	STAT_MEAN,
	STAT_MEDIAN,
	STAT_STDDEV,
	STAT_P95,
	STAT_COUNT,
}	e_stats;

typedef struct s_tcount
{
	char **out;
	int *args;
	int	tot;
	int	nerr;
	int ops[OP_COUNT];
    clock_t start, end;
}	t_tcount;

static unsigned long int next = 1;

static char	*g_stats[STAT_COUNT] = {
	"null",
	"time_tot",
	"time_avg",
	"moves_n",
	"moves_nlogn",
	"min",
	"max",
	"mean",
	"median",
	"stddev",
	"p95",
};

static char	*g_legal_ops[OP_COUNT] = {	NULL, "pa", "pb", 
							"ra", "rb", "rr",
							"rra", "rrb", "rrr", 
							"sa", "sb", "ss", 
							};
int ft_rand(void)  /* RAND_MAX assumed to be 32767. */
{
    next = next * 1103515245 + 12345;
    return (unsigned)(next/65536) % RAND_MAX;// 32768;
}

int	ft_xsrand(void)
{
	next ^= next << 13;
	next ^= next >> 17;
	next ^= next << 5;
	return (next);
}

void ft_srand(unsigned seed)
{
    next = seed;
}


int g_pbuf =65536;
int g_nrange = 10000;

int g_current_test_id = 0;
void ps_capture(char **argv, char *out_buf, char *err_buf)
{
    int     out_pipe[2];
    int     err_pipe[2];
    pid_t   pid;
    ssize_t n;
    ssize_t out_total = 0;
    ssize_t err_total = 0;

    if (pipe(out_pipe) == -1)
        return;
    if (pipe(err_pipe) == -1)
        return;

    pid = fork();
    if (pid == -1)
        return;

    if (pid == 0)
    {
        /* child */
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(err_pipe[1], STDERR_FILENO);

        close(out_pipe[0]);
        close(out_pipe[1]);
        close(err_pipe[0]);
        close(err_pipe[1]);

        execv(argv[0], argv);

        perror("execv");
        _exit(1);
    }

    /* parent */
    close(out_pipe[1]);
    close(err_pipe[1]);

    while ((n = read(out_pipe[0], out_buf + out_total,
                     g_pbuf - out_total - 1)) > 0)
        out_total += n;

    while ((n = read(err_pipe[0], err_buf + err_total,
                     g_pbuf - err_total - 1)) > 0)
        err_total += n;

    out_buf[out_total] = '\0';
    err_buf[err_total] = '\0';

    close(out_pipe[0]);
    close(err_pipe[0]);

    waitpid(pid, NULL, 0);
}

/*
char	**get_nargs(char *path, int n)
{
	char	**argv;
	int		i;

	i = 0;
	ft_srand(SEED);
	argv = calloc(n + 1 , sizeof(char *));
	argv[i] = strdup(path);
	while (++i < n)
		argv[i] = ft_itoa((ft_rand() % (2 * g_nrange)) - g_nrange);
	argv[n] = NULL;
	return (argv);
}
*/

char **iisin(char **arr, char *val)
{
	int	i;

	i = -1;
	while (arr[++i])
		if (!strcmp(arr[i], val))
			return (&arr[i]);
	return (NULL);
}

char **get_nargs(char *path, int n)
{
    char	**argv;
    int		i;
    char	*tmp;

    i = 0;
    argv = calloc(n + 2, sizeof(char *));
    if (!argv)
        return (NULL);
    argv[i] = strdup(path);
    while (++i <= n)
	{
		tmp = ft_itoa(((unsigned)ft_xsrand() % (2 * g_nrange)) + g_nrange);
		if (!tmp)
			return (NULL);
		if (!iisin(argv, tmp ))
			argv[i] = tmp;
		else
		{
			--i;
			free(tmp);
		}
	}
	argv[n + 1] = NULL;
    return argv;
}

int	islegal(char *op)
{
	int iop;

	iop = 0;
	while (g_legal_ops[++iop])
		if (!strcmp((g_legal_ops[iop]), op))
			return (iop);
	return (0);
}
int	call_checker()
{

}
void count_test(t_tcount *counts, char *buf)
{
	char	**ops;
	int		op;
	int		i;

	i = -1;
	ops = ft_split(buf, '\n');
	while (ops[++i])
	{
		op = islegal(ops[i]);
		if (op)
			counts->ops[op]++; 
		else 
			counts->ops[0]++; 
		counts->tot++; 
	};
}
void print_count(t_tcount count)
{
	int	i;

	i = 0;
	printf("\ntot=%4i\t", count.tot);
	printf("err=%4i\t\n", count.nerr);
	while (++i < OP_COUNT)
		printf("%4s: %4i\t", g_legal_ops[i], count.ops[i]);
	printf("\n");

}

void print_group(t_tcount count[NTEST], int nargs)
{
	int	i;

	printf("\nn of args=%4i\t", nargs);
	i = 0;
	while (i < NTEST)
		print_count(count[i++]);
}

int	log2n(int n)
{
	if (n > 1)
		return (1 + log2n(n / 2));
	return (0); 
}

long	n_log_n(int n)
{
	if (n <= 1)
		return (0);
	return ((long)n * log2n(n));
}

void	print_stats(int stats[STAT_COUNT])
{
	int	i;

	i = -1;
	while (++i < STAT_COUNT)
	{
		printf("\t%s: %4i, ", g_stats[i], stats[i]);
	}
	
}

void	stats_group(t_tcount count[NTEST], int *stats, int nargs)
{
	int	i;
	int	cps;
	int	grp_tot;

	printf("\nNTEST: %i\tn of args:%4i \n", NTEST,nargs);
	i = 0;
	cps = CLOCKS_PER_SEC;
	grp_tot = 0;
//	clock_tot = 0;
	stats[STAT_MIN] = count[i].tot;
	while (i < NTEST)
	{
		grp_tot += count[i].tot;
		stats[STAT_TIME_TOT] += (count[i].end - count[i].start);
		if (count[i].tot < stats[STAT_MIN])
			stats[STAT_MIN] = count[i].tot;
		if (count[i].tot > stats[STAT_MAX])
			stats[STAT_MAX] = count[i].tot;
		i++;
	}
	//stats[STAT_TIME_TOT] = //CLOCKS_PER_SEC;
	stats[STAT_MOVES_N] = grp_tot / (i * nargs);
	stats[STAT_MOVES_NLOGN] = grp_tot / n_log_n(i * nargs);
	stats[STAT_MEAN] = grp_tot / i;
	stats[STAT_TIME_AVG] = stats[STAT_TIME_TOT] / NTEST ;// CLOCKS_PER_SEC; 
	stats[0] = grp_tot;
	print_stats(stats);
}
//void sum_count()

int main()
{
	int		nargs[] = {3, 5, 10, 100, 500, 0}; 
	char	**argv;
	char	*buf[2];
	t_tcount	counts[NGROUP][NTEST];
	int		stats[NGROUP][STAT_COUNT];
	int		i;
	int		j;
	int		n;
	int		ntests;

	i = -1;
	bzero(counts, sizeof(t_tcount) * (NGROUP * NTEST));
	bzero(stats, sizeof(int) * (NGROUP * STAT_COUNT));
	ntests = NTEST;
	while (nargs[++i])
	{
		ft_srand(SEED);
		n = nargs[i];
		g_pbuf = ((n * n) * 2);
		buf[0] = (char *)calloc(g_pbuf, 1);
		buf[1] = (char *)calloc(g_pbuf, 1);
		j = -1;
		while (++j < ntests)
		{
			bzero(buf[0], g_pbuf);
			bzero(buf[1], g_pbuf);
			argv = get_nargs("./push_swap", n);
			counts[i][j].start = clock();
			ps_capture(argv, buf[0], buf[1]);
			counts[i][j].end = clock();
			//printf("\n>>>> out_buf\n%s\n", buf[0]);
			//printf("\n>>>> err_buf\n%s\n", buf[1]);
			count_test(&counts[i][j], buf[0]);
			//	print_count(counts[i][j]);
			free(argv);
		}
	//	print_group(counts[i], nargs[i]);
		stats_group(counts[i], stats[i], nargs[i]);
	}
	return (0);	
}


/*
   void log_error(const char *fmt, ...)
   {
   FILE *f = fopen(ERRLOG_FILE, "a");
   if (!f)
   return;

   va_list args;
   va_start(args, fmt);

   vfprintf(f, fmt, args);
   fprintf(f, "\n---------------------------------------------\n");

   va_end(args);
   fclose(f);
   }

   void	test_print_chars(char *format, int a, int b, int c)
   {
   static int i = 0;
   static int last_id = -1;
   char *out1 = CAPTURE(printf(format, a, b, c));
   char *out2 = CAPTURE(ft_printf(format, a, b, c));

   if (g_current_test_id != last_id)
   {
   i = 0;
   last_id = g_current_test_id;
   printf("\n\nTesting; %c\n" , g_current_test_id);
   }
   printf("\t%i:" , ++i);
   if (strcmp(out1, out2) == 0)
   printf("%sOK%s", GREEN, CLR_RMV);
   else
   {
   printf("%sKO%s", RED, CLR_RMV);
   log_error(
   "Type : %c\n"
   "Test %d FAILED\n"
   "Format: \"%s\"\n"
   "Args: \"%c\", \"%c\", \"%c\"\n"
   "printf:\t\t|%i	|%s|\n"
   "ft_printf:\t|%i	|%s|\n",
   g_current_test_id, i, format, a, b, c, strlen(out1), out1, strlen(out2), out2
   );
   }
   free(out1);
   free(out2);
   }*/
