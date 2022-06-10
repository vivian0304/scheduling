#define MAX_ELEMENT 200
#define SIZE 100
#define true 1
#define false 0
#define MAX 10000000    

typedef struct
{
    int process_id;        //프로세스 번호
    int priority;          //우선순위
    int arrival_time;      //도착시간
    int kill_time;         //종료시간
    int computing_time;    //서비스시간(Ts)
    int complete_time;      // 종료시간
    int turn_around_time;  //반환시간(Tr)
    int remaining_time;    // 남은시간
    int total;
} process_in;

typedef struct
{
    process_in heap[MAX_ELEMENT];
    int heap_size;
    
} HeapType; //히프에 프로세스 삽입

HeapType* create()
{ //생성 함수
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h) //초기화 함수
{
    h->heap_size = 0;
}