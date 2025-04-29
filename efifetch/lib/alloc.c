#include"efi.h"
#include"str.h"
#include"init.h"

__weak void*realloc(void*old,size_t size){
	void*pool=NULL;
	if(!g_bs)return NULL;
	pool=malloc(size);
	if(pool){
		uint64_t os=*((uint64_t*)old-8);
		memcpy(pool,old,MIN(size,os));
		free(old);
	}
	return pool;
}

__weak void*malloc(size_t size){
	void*pool=NULL;
	if(!g_bs)return NULL;
	g_bs->alloc_pool(efi_loader_data,size+8,(void**)&pool);
	if(!pool)return NULL;
	*((uint64_t*)pool)=size;
	return pool+8;
}

__weak void free(void*buffer){
        if(!g_bs||!buffer)return;
	g_bs->free_pool(buffer-8);
}

__weak char*strdup(const char*str){
        if(!str)return NULL;
        size_t len=strlen(str);
        void*dup=malloc(len+1);
        if(!dup)return NULL;
        memcpy(dup,str,len+1);
        return dup;
}

__weak char*strndup(const char*str,size_t max){
        if(!str)return NULL;
        size_t len=strnlen(str,max);
        void*dup=malloc(len+1);
        if(!dup)return NULL;
        memcpy(dup,str,len+1);
        return dup;
}

__weak void*memdup(const void*mem,size_t len){
        if(!mem||len<=0)return NULL;
        void*dup=malloc(len);
        if(!dup)return NULL;
        memcpy(dup,mem,len);
        return dup;
}

__weak void*zalloc(size_t size){
        void*m=malloc(size);
        if(m)memset(m,0,size);
        return m;
}

__weak void*calloc(size_t nmemb,size_t size){
        return zalloc(size*nmemb);
}
