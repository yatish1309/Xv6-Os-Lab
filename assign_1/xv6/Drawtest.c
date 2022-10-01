#include "types.h"
#include "stat.h"
#include "user.h"

const int max_size = 2002;

int main(void){
	void *wolf_buffer = malloc(max_size);
	int wolf_size = wolfie(wolf_buffer,max_size);
	if(wolf_size==-1) printf(1,"Buffer size is too small\n");
	else printf(1,"%s\n",(char *)wolf_buffer);
	return 0;
}
