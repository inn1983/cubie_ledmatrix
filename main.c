#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include <sys/time.h>

#include "gpio_lib.h"
#define PD0    SUNXI_GPD(0)
#define PD1    SUNXI_GPD(1)
#define PD2    SUNXI_GPD(2)
#define PD3    SUNXI_GPD(3)
#define PD4    SUNXI_GPD(4)
#define PD5    SUNXI_GPD(5)
#define PD6    SUNXI_GPD(6)
#define PD7    SUNXI_GPD(7)
#define PD8    SUNXI_GPD(8)
#define PD9    SUNXI_GPD(9)
#define PD10    SUNXI_GPD(10)
#define PD11    SUNXI_GPD(11)
#define PD12    SUNXI_GPD(12)
#define PD13    SUNXI_GPD(13)
#define PD14    SUNXI_GPD(14)
#define PD15    SUNXI_GPD(15)
#define PD16    SUNXI_GPD(16)
#define PD17    SUNXI_GPD(17)
#define PD18    SUNXI_GPD(18)
#define PD19    SUNXI_GPD(19)
#define PD20    SUNXI_GPD(20)
#define PD21    SUNXI_GPD(21)
#define PD22    SUNXI_GPD(22)
#define PD23    SUNXI_GPD(23)
#define PD24    SUNXI_GPD(24)
#define PD25    SUNXI_GPD(25)
#define PD26    SUNXI_GPD(26)
#define PD27    SUNXI_GPD(27)

#define MISO    SUNXI_GPE(3)
#define MOSI    SUNXI_GPE(2)
#define SCK     SUNXI_GPE(1)
#define CS      SUNXI_GPE(0)


#define D_port	SUNXI_GPD(25)
#define C_port SUNXI_GPD(26)
#define B_port SUNXI_GPD(23)
#define A_port SUNXI_GPD(21)
#define G_port SUNXI_GPD(19)
#define DI_port SUNXI_GPD(17)
#define CLK_port SUNXI_GPD(2)
#define Latch_port SUNXI_GPD(0)

#define MILLION 1000000L

unsigned char table2[] = {
  0x00,0x02,0x00,0x02,0xf8,0x3f,0x00,0x04,0x40,0x04,0xf0,0x07,0x5c,0x1c,0x44,0x34,
  0x46,0x24,0x82,0x64,0x82,0x44,0x06,0x45,0x04,0x46,0x1c,0x38,0x70,0x00,0x00,0x00,
  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  
  0x00,0x02,0x00,0x02,0xf8,0x3f,0x00,0x04,0x40,0x04,0xf0,0x07,0x5c,0x1c,0x44,0x34,
  0x46,0x24,0x82,0x64,0x82,0x44,0x06,0x45,0x04,0x46,0x1c,0x38,0x70,0x00,0x00,0x00,
  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};



int HC595_Data_Send(unsigned char daH, unsigned char daL, int han)
{
	int i;
	sunxi_gpio_output(Latch_port, LOW);
	sunxi_gpio_output(CLK_port, LOW);
	
	
	unsigned char dummyL1 = 0xA0;
	unsigned char dummyH1 = 0xA0;
	
	unsigned char dummyL2 = 0xA0;
	unsigned char dummyH2 = 0xA0;
	unsigned int delay = 0;
	
	//usleep(delay);
	for(i=0;i<8;i++){
		if(((dummyL1)&0x01)!=0) sunxi_gpio_output(DI_port,HIGH);
		else sunxi_gpio_output(DI_port,LOW);
		sunxi_gpio_output(CLK_port,HIGH);
		//usleep(delay);
		sunxi_gpio_output(CLK_port,LOW);
		dummyL1 >>= 1;
	}

	//usleep(delay);
	for(i=0;i<8;i++){
        if(((dummyH1)&0x01)!=0) sunxi_gpio_output(DI_port,HIGH);
        else sunxi_gpio_output(DI_port,LOW);
		sunxi_gpio_output(CLK_port,HIGH);
		//usleep(delay);
		sunxi_gpio_output(CLK_port,LOW);
		dummyH1 >>= 1;
    }
	
	//usleep(delay);
	for(i=0;i<8;i++){
		if(((dummyL2)&0x01)!=0) sunxi_gpio_output(DI_port,HIGH);
		else sunxi_gpio_output(DI_port,LOW);
		sunxi_gpio_output(CLK_port,HIGH);
		//usleep(delay);
		sunxi_gpio_output(CLK_port,LOW);
		dummyL2 >>= 1;
	}
	
	//usleep(delay);
	for(i=0;i<8;i++){
		if(((dummyH2)&0x01)!=0) sunxi_gpio_output(DI_port,HIGH);
		else sunxi_gpio_output(DI_port,LOW);
		sunxi_gpio_output(CLK_port,HIGH);
		//usleep(delay);
		sunxi_gpio_output(CLK_port,LOW);
		dummyH2 >>= 1;
	}
	

	
	sunxi_gpio_output(G_port,HIGH);
	
	switch (han){
		case 0: 
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 1:
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 2:
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 3:
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 4: 
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 5:
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 6:
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 7:
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, LOW);
			break;
		case 8:
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 9: 
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 10: 
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 11: 
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, LOW);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 12: 
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 13: 
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, LOW);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 14: 
			sunxi_gpio_output(A_port, LOW);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, HIGH);
			break;
		case 15: 
			sunxi_gpio_output(A_port, HIGH);
			sunxi_gpio_output(B_port, HIGH);
			sunxi_gpio_output(C_port, HIGH);
			sunxi_gpio_output(D_port, HIGH);
			break;
		}
	sunxi_gpio_output(Latch_port, HIGH);
	sunxi_gpio_output(G_port, LOW);
	sunxi_gpio_output(Latch_port, LOW);
	
	return 0;
}
int main()
{
	struct timespec slptm;
	slptm.tv_sec = 0;
	int cont = 1000;
    slptm.tv_nsec = 1000*cont;      //1000 ns = 1 us
	struct sched_param param;
	long interval;
	struct timeval tend,tstart;
	int maxpri; 
    int sched = SCHED_RR;
	
	maxpri = sched_get_priority_max(SCHED_RR);
	
    param.sched_priority = maxpri;
    sched_setscheduler(getpid(),sched,&param);
	fprintf(stderr,"priority is %d\n",param.sched_priority);
	int scheduler = sched_getscheduler(getpid());
	fprintf(stderr,"scheduler is %d\n",scheduler);
	
    if(SETUP_OK!=sunxi_gpio_init()){
        printf("Failed to initialize GPIO\n");
        return -1;
    }

    sunxi_gpio_set_cfgpin(D_port,OUTPUT);
	sunxi_gpio_set_cfgpin(C_port,OUTPUT);
	sunxi_gpio_set_cfgpin(B_port,OUTPUT);
	sunxi_gpio_set_cfgpin(A_port,OUTPUT);
	sunxi_gpio_set_cfgpin(G_port,OUTPUT);
	sunxi_gpio_set_cfgpin(DI_port,OUTPUT);
	sunxi_gpio_set_cfgpin(CLK_port,OUTPUT);
	sunxi_gpio_set_cfgpin(Latch_port,OUTPUT);
	
	int i;
	int j=0;
	int k=0;
	while(1){
		for(i=0; i<40000; i++){
			gettimeofday(&tstart,NULL);
		
			HC595_Data_Send(~table2[(k*16+j)*2+1],~table2[(k*16+j)*2],j);
			j++;
			if(j==16) j=0;
			//usleep(1000);
			//nanosleep(&slptm, NULL);
			clock_nanosleep(CLOCK_REALTIME , 0, &slptm, NULL);
			gettimeofday(&tend,NULL);
			
			interval = MILLION*(tend.tv_sec - tstart.tv_sec)
                   +(tend.tv_usec-tstart.tv_usec);
			
			if (interval>=2000)
				fprintf(stderr,"the expected time is %d us,but real time cost is %lu us\n",cont,interval);
		}
		k++;
		if(k==1) k=0;
		//usleep(10000);
	}
	
/*
    int i;
    for(i=0;i<5;i++){
        if(sunxi_gpio_output(PD16,HIGH)){
            printf("Failed to set GPIO pin value\n");
            return -1;
        }

        usleep(500000);
        if(sunxi_gpio_output(PD16,LOW)){
            printf("Failed to set GPIO pin value\n");
            return -1;
        }
        usleep(500000);
    }
*/
    sunxi_gpio_cleanup();

    return 0;
    
}

