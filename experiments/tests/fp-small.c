#include <pthread.h>
typedef unsigned char uint8_t;
typedef uint8_t result_t;
uint8_t         HPLClock_xxx_set_flag;
uint8_t         HPLClock_xxx_mscale;
uint8_t         HPLClock_xxx_nextScale;
void 
__vector_15_thread(void)
{
	{
		while (1) {
			__vector_15();
		}
	}
}
__inline static result_t 
HPLClock_xxx_Clock_xxx_fire(void)
{
	pthread_t       __cil_tmp1;
	{
		pthread_create(&__cil_tmp1, 0, __vector_15_thread, 0);
	}
}
void 
__attribute__((__interrupt__)) __vector_15(void)
{
	{
		if (HPLClock_xxx_set_flag) {
			HPLClock_xxx_mscale = HPLClock_xxx_nextScale;
		}
		HPLClock_xxx_Clock_xxx_fire();
	}
}
