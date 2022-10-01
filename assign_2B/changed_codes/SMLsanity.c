#include "types.h"
#include "user.h"


int
main(int argc, char *argv[])
{
	if (argc != 2){
				printf(1, "Usage: SMLsanity <n>\n");
				exit();
 		}
	int i;
	int n;
	int j = 0;
	int k;
	int retime;
	int rutime;
	int stime;
	n = atoi(argv[1]);
	i = n; //unimportant
	int pid;
	for (i = 0; i < 3 * n; i++) {
		j = i % 3;
		pid = fork();
		if (pid == 0) {//child
			j = (getpid() - 4) % 3; // ensures independence from the first son's pid when gathering the results in the second part of the program
			#if SCHEDFLAG == SML
			switch(j) {
				case 0:
          set_prio(1);
					break;
				case 1:
          set_prio(2);
					break;
				case 2:
          set_prio(3);
					break;
			}
			#endif
      for (k = 0; k < 100; k++){
						int x = k+1;
						for (j = 0; j < 1000000; j++){
                if(j%2==0)
								{  
									x = x + 1;
								}else
								{
									x = x -1;
								}
            }
						if(x%1000000!=0)
						{
							sleep(1);
						}
					}
			exit(); // children exit here
		}
		continue; // father continues to spawn the next child
	}
	for (i = 0; i < 3 * n; i++) {
		pid = wait3(&retime, &rutime, &stime);
		int res = (pid - 4) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0: // CPU bound processes
				printf(1, "Priority 1, pid: %d, termination: %d, crreation: %d, \n", pid, retime, rutime);
				break;
			case 1: // CPU bound processes, short tasks
				printf(1, "Priority 2, pid: %d, termination: %d, creation: %d\n", pid, retime, rutime);
				break;
			case 2: // simulating I/O bound processes
				printf(1, "Priority 3, pid: %d, termination: %d, creation: %d\n", pid, retime, rutime);
				break;
		}
	}
	exit();
}