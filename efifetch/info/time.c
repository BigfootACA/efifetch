#include"efi.h"
#include"info.h"
#include"print.h"
#include"init.h"

static void fill_seconds(efifetch*ctx,uint64_t uptime_sec){
	uint64_t uptime_xsec=uptime_sec%60;
	uint64_t uptime_min=uptime_sec/60,uptime_xmin=uptime_min%60;
	uint64_t uptime_hour=uptime_min/60,uptime_xhour=uptime_hour%24;
	uint64_t uptime_day=uptime_hour/24,uptime_xday=uptime_day%30;
	uint64_t uptime_month=uptime_day/30,uptime_xmonth=uptime_month%12;
	uint64_t uptime_year=uptime_month/12,uptime_xyear=uptime_year;
	RESET(UPTIME);
	if(uptime_xsec>0)SETF(UPTIME,"%llu secs",uptime_xsec);
	if(uptime_xmin>0){
		if(!IS_EMPTY(UPTIME))APPEND(UPTIME,", ");
		APPENDF(UPTIME,"%llu mins",uptime_xmin);
	}
	if(uptime_xhour>0){
		if(!IS_EMPTY(UPTIME))APPEND(UPTIME,", ");
		APPENDF(UPTIME,"%llu hours",uptime_xhour);
	}
	if(uptime_xday>0){
		if(!IS_EMPTY(UPTIME))APPEND(UPTIME,", ");
		APPENDF(UPTIME,"%llu days",uptime_xday);
	}
	if(uptime_xmonth>0){
		if(!IS_EMPTY(UPTIME))APPEND(UPTIME,", ");
		APPENDF(UPTIME,"%llu months",uptime_xmonth);
	}
	if(uptime_xyear>0){
		if(!IS_EMPTY(UPTIME))APPEND(UPTIME,", ");
		APPENDF(UPTIME,"%llu years",uptime_xyear);
	}
}

#if defined(__x86_64__) || defined(__i386__) || defined(__aarch64__)
static inline uint64_t rd_timer(void){
        uint64_t val=0;
        #if defined(__x86_64__) || defined(__i386__)
        uint32_t hi=0,lo=0;
        asm volatile("rdtsc":"=a"(lo),"=d"(hi));
        val=((uint64_t)lo)|(((uint64_t)hi)<<32);
        #define TIMER_TYPE "x86 tsc"
        #elif defined(__aarch64__)
        asm volatile("mrs %0, cntvct_el0":"=r"(val));
        #define TIMER_TYPE "arm64 cntvct"
        #else
        #error no timer backend found
        #endif
        return val;
}

static uint64_t timer_calc_ms(uint64_t period){
        uint64_t start,end,ret;
        start=rd_timer();
        g_bs->stall(period*1000);
        end=rd_timer();
        ret=(end-start)/period;
        dbg_printf(
                TIMER_TYPE" calib %llu ms: %llu MHz\n",
                (unsigned long long)period,
                (unsigned long long)ret/1000
        );
        return ret;
}

static uint64_t timer_calib(){
        uint64_t ct=0,calib=0;
        dbg_printf("starting calibrate "TIMER_TYPE" timer\n");
        ct++,calib+=timer_calc_ms(50);
        ct++,calib+=timer_calc_ms(20);
        ct++,calib+=timer_calc_ms(100);
        ct++,calib+=timer_calc_ms(10);
        ct++,calib+=timer_calc_ms(80);
        calib/=ct;
        dbg_printf(
                TIMER_TYPE" calib freq: %llu MHz\n",
                (unsigned long long)calib/1000
        );
        if(calib<=0)dbg_printf("bad timer "TIMER_TYPE"\n");
        return calib;
}

static uint64_t tick_get_ms(void){
        static bool inited=false;
        static uint64_t calib=0;
        if(!inited)inited=true,calib=timer_calib();
        if(calib<=0)return 0;
        return rd_timer()/calib;
}

static void fill_arch_timer(efifetch*ctx){
	if(!IS_EMPTY(UPTIME))return;
	uint64_t ms=tick_get_ms();
	if(ms<=0)return;
	fill_seconds(ctx,ms/1000);
}

#else

static void fill_arch_timer(efifetch*ctx){}

#endif

static void fill_timestamp_proto(efifetch*ctx){
	efi_status st;
	efi_timestamp_protocol*ts=NULL;
	efi_timestamp_properties prop={};
	if(!IS_EMPTY(UPTIME))return;
	st=g_bs->locate_proto(
		&gEfiTimestampProtocolGuid,
		NULL,(void**)&ts
	);
	if(efi_error(st)){
		dbg_printf("locate timestamp protocol failed: %m\n",st);
		return;
	}
	st=ts->get_properties(&prop);
	if(efi_error(st)){
		dbg_printf("get timestamp properties failed: %m\n",st);
		return;
	}
	uint64_t uptime_tick=ts->get_timestamp();
	fill_seconds(ctx,uptime_tick/prop.frequency);
}

void efifetch_load_info_time(efifetch*ctx){
	if(!IS_EMPTY(UPTIME))return;
	fill_timestamp_proto(ctx);
	fill_arch_timer(ctx);
}
