#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.c"
#include "fcfs.c"
#include "priority.c"
#include "roundrobin.c"

int main()
{
    int type = 0;
    int  cnt = 0;
 
    int process_id = 0;
    int arrival_time = 0;

    process_in list[SIZE];
    process_in p_list[SIZE];
    process_in fcfs_list[SIZE];
    process_in rr_list[SIZE];
    list[0].arrival_time = 0;
    
    while(true){
        
        printf("type : ");
        scanf("%d",&type);
        
        switch(type){
            case 1:
                arrival_time += 10;
                    //도착시간은 이걸 입력했을 때 기준으로 바뀐다.
                    //입력전까지는 계속 0임.
                    //만약 입력받기 시작하면 그것을 기점으로 10씩 증가함.
                break;

            case 0:
                process_id++;
                printf("======================================================\n");
                printf("process_id\tpriority\tcomputing_time\n");
                printf("======================================================\n");
                printf("%d ",process_id);
                list[cnt].process_id = process_id;
                list[cnt].arrival_time = arrival_time;
                list[cnt].kill_time = 0;
                list[cnt].complete_time = 0;
                list[cnt].turn_around_time = 0;
                list[cnt].remaining_time = 0;
                scanf("%d %d", &list[cnt].priority, &list[cnt].computing_time);
                cnt++;
                break;
                        
            case -1:
                printf("END\n");

                for(int i=0; i<process_id; i++) {
                    p_list[i] = list[i];
                    fcfs_list[i] = list[i];
                    rr_list[i] = list[i];
                }

                double first = fcfs(fcfs_list, process_id);
                double second = priority(p_list, process_id);
                double third = rr(rr_list, process_id);

                printf("=======================TOTAL======================\n\n");
                printf("  FCFS 정규화 평균 반환 시간       : %lf\n", first);
                printf("  PRIORITY 정규화 평균 반환 시간   : %lf\n", second);
                printf("  ROUNDROBIN 정규화 평균 반환 시간 : %lf\n\n", third);
                printf("===================================================\n");
                return 0;

            default:
                printf("error");
        }
    }

    return 0;
}
