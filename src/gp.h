/* 
 * $Header: /home/ma/p/pruess/.cvsroot/manna_range/dmitry_20151021/gp.h,v 1.2 2015/10/21 11:37:00 pruess Exp $
 *
 * This is lifted from
 * Header: /home/ma/p/pruess/.cvsroot/manna_corr/manna_duration5D_actactcorr.c,v 1.29 2015/10/16 02:28:12 pruess Exp
 */
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX (255)
#endif

long long int total_malloced=0LL;
#define MALLOC(a,n) {if ((a=malloc(((long long int)(n))*((long long int)sizeof(*(a)))))==NULL) \
   {fprintf(stderr, "Fatal error (%s::%i) malloc(3)ing %lli bytes for variable %s: %i (%s).\n", \
         __FILE__, __LINE__, (long long int)(((long long int)n)*((long long int)sizeof(*(a)))), #a, errno, strerror(errno)); exit(EXIT_FAILURE);} else { \
    total_malloced+=((long long int)( ((long long int)(n))*((long long int)sizeof(*(a))))); printf("#Info: malloc(3)ed %lli bytes for %s, total: %lli (%g GiB)\n", (long long int)(((long long int)(n))*((long long int)sizeof(*(a)))), #a, total_malloced, ((double)total_malloced)/((double)(1024LL*1024LL*1024LL))); }}


/*Gunnar's boolean version of MT starts here*/
/* RNG (lifted from opgp_cp.c) */
//#include "mt19937ar_clean_bkp.h"
#ifndef SEED
#define SEED (5UL)
#endif
#define RNG_MT_BITS (32)
#define RNG_MAX (~0UL)
#define RNG_TYPE unsigned long
#define RNG_MT_MAX (4294967295.)
#define RNG_TYPE_OUT "%lu"

RNG_TYPE seed = SEED;
void init_genrand(RNG_TYPE);
RNG_TYPE genrand_int32(void);
double genrand_real1(void);
double genrand_real2(void);


RNG_TYPE mt_bool_rand=0UL;
int      mt_bool_ptr=RNG_MT_BITS;
RNG_TYPE mt_bool_mask=1UL<<(RNG_MT_BITS-1);
RNG_TYPE mt_4_rand=0UL;
int      mt_4_ptr=RNG_MT_BITS;
int      mt_4_shifted=0;
RNG_TYPE mt_4_mask=3UL<<(RNG_MT_BITS-2);
RNG_TYPE mt_4_randV2=0UL;
int      mt_4_shiftedV2=RNG_MT_BITS;
RNG_TYPE mt_2_randV2=0UL;
int      mt_2_shiftedV2=RNG_MT_BITS;

#define OLD_RNG_MT_BOOLEAN ( ( mt_bool_ptr==RNG_MT_BITS ) ?  \
        ((mt_bool_ptr=1, mt_bool_rand=genrand_int32()) & 1) : \
        (mt_bool_rand & (1<<mt_bool_ptr++)) )
#define RNG_MT_BOOLEAN ( ( mt_bool_mask==(1UL<<(RNG_MT_BITS-1)) ) ?  \
        ((mt_bool_mask=1UL, mt_bool_rand=genrand_int32()) & mt_bool_mask) : \
        (mt_bool_rand & (mt_bool_mask+=mt_bool_mask)) )
#define RNG_MT_4 ( ( mt_4_mask==(3UL<<(RNG_MT_BITS-2)) ) ?  \
        ((mt_4_shifted=0, mt_4_mask=3UL, mt_4_rand=genrand_int32()) & mt_4_mask) : \
        (mt_4_shifted+=2, (mt_4_rand & (mt_4_mask<<=2))>>mt_4_shifted) )
#define RNG_MT_4V2 ( ( mt_4_shiftedV2==RNG_MT_BITS ) ?  \
        ((mt_4_shiftedV2=2, mt_4_randV2=genrand_int32()) & 3UL) : \
        (mt_4_shiftedV2+=2, (mt_4_randV2>>=2) & 3UL) )
#define RNG_MT_2V2 ( ( mt_2_shiftedV2==RNG_MT_BITS ) ?  \
        ((mt_2_shiftedV2=1, mt_2_randV2=genrand_int32()) & 1UL) : \
        (mt_2_shiftedV2++, (mt_2_randV2>>=1) & 1UL) )
/*Gunnar's boolean version of MT ends here*/
#define MOMENT_TYPE long double   /*@ \colabel{moment_type} @*/
#define MOMENT_OUT_FMT "%10.20Lg"

MOMENT_TYPE mom_pow;
int         mom_cnt;

#define MOMENTS_DECL(n,m) MOMENT_TYPE mom_ ##n[(m) + 1]; const int mom_max_ ##n = m;
#define MOMENTS_INIT(n) {for (mom_cnt=0; mom_cnt<=mom_max_ ##n; mom_cnt++) mom_ ##n [mom_cnt]=0;}
#define MOMENTS(n,x) {mom_ ##n [0]++; for (mom_pow=1, mom_cnt=1; mom_cnt<=mom_max_ ##n; mom_cnt++) {\
                         mom_pow*=((MOMENT_TYPE)(x)); mom_ ##n[mom_cnt]+=mom_pow;}}
#define MOMENTS_OUT(n)  { printf("#M_%s " MOMENTS_PREAMBLE_FMT " %i " MOMENT_OUT_FMT " ", #n, \
							  MOMENTS_PREAMBLE_ARGS \
			                                  mom_max_ ##n, mom_ ##n [0]); \
                           for (mom_cnt=0; mom_cnt<=mom_max_ ##n; mom_cnt++) \
                             printf(" " MOMENT_OUT_FMT, mom_ ##n [mom_cnt]/((mom_ ##n [0]) ? mom_ ##n [0] : -1)); \
                           fputc('\n', stdout);}

/*
MOMENTS_DECL(size, 8);
MOMENTS_DECL(duration, 8);
MOMENTS_DECL(density, 8);
MOMENTS_DECL(ratio, 8);
*/

#define PRINT_PARAM(a,f) fprintf(stdout, "# Info: PRINT_PARAM " #a ": " f "\n", a)

void preamble(int argc, char *argv[]);
void postamble(void);


void preamble(int argc, char *argv[]) 
{
int ch;
printf("# Info: $Header: /home/ma/p/pruess/.cvsroot/manna_range/dmitry_20151021/gp.h,v 1.2 2015/10/21 11:37:00 pruess Exp $\n");

  { time_t tm;
  time(&tm);
  printf("# Info: Time: %s", ctime(&tm));
  }
  
  { char hostname[128];
  gethostname(hostname, sizeof(hostname)-1);
  hostname[sizeof(hostname)-1]=(char)0;
  printf("# Info: Hostname: %s\n", hostname);
  }

  { char cwd[1024];
  getcwd(cwd, sizeof(cwd)-1);
  cwd[sizeof(cwd)-1]=(char)0;
  printf("# Info: Directory: %s\n", cwd);
  }
  
  printf("# Info: PID: %i\n", (int)getpid());

printf("# Info: Command: [");
for (ch=0; ch<argc; ch++) printf(" %s", argv[ch]);
printf("]\n");
}


void postamble(void)
{ 
time_t tm;
struct rusage rus;

tm=time(NULL);

printf("# Info Terminating at %s", ctime(&tm));
if (getrusage(RUSAGE_SELF, &rus)) {
  printf("# Info getrusage(2) failed.\n");
} else {
printf("# Info getrusage.ru_utime: %li.%06li\n", (long int)rus.ru_utime.tv_sec, (long int)rus.ru_utime.tv_usec); 
printf("# Info getrusage.ru_stime: %li.%06li\n", (long int)rus.ru_stime.tv_sec, (long int)rus.ru_stime.tv_usec); 

#define GETRUSAGE_long(f) printf("# Info getrusage.%s: %li\n", #f, rus.f);
GETRUSAGE_long(ru_maxrss);
GETRUSAGE_long(ru_ixrss);
GETRUSAGE_long(ru_idrss);
GETRUSAGE_long(ru_isrss);
GETRUSAGE_long(ru_minflt);
GETRUSAGE_long(ru_majflt);
GETRUSAGE_long(ru_nswap);
GETRUSAGE_long(ru_inblock);
GETRUSAGE_long(ru_oublock);
GETRUSAGE_long(ru_msgsnd);
GETRUSAGE_long(ru_msgrcv);
GETRUSAGE_long(ru_nsignals);
GETRUSAGE_long(ru_nvcsw);
GETRUSAGE_long(ru_nivcsw);
}
printf("#Info: Good bye and thanks for all the fish.\n");
}
