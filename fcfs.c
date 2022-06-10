void insert_max_fcfs(HeapType *h, process_in item) 
{
    //최대 히프: 부모 노드의 키값이 자식 노드 키값보다 크거나 같음.
    //현재 요소의 개소가 heap_size인 히프 h에 item 삽입한다.
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.arrival_time > h->heap[i / 2].arrival_time)) 
    {
        //우선순위 비교해서 재정렬, 트리를 다시 올라가면서 부모 노드와 비교
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; //새로운 노드를 삽입
}

process_in delete_max_fcfs(HeapType *h) 
{
    //부모 노드의 키값이 자식 노드의 키값보다 작거나 같음. 가장 큰 키값을 가진 노드를 삭제함, 따라서 루트 노드 삭제됨.
        //1. 루트 노드 삭제
        //2. 마지막 노드를 루트 노드로 이동
        //3. 루트에서부터 단말 노드까지의 경로에 있는 노드들을 교환
    int parent, child;
    process_in item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size)
    {
        //현재 노드의 자식노드중 더 큰 자식노드를 찾는다.
        if ((child < h->heap_size) &&
            (h->heap[child].arrival_time) < h->heap[child + 1].arrival_time)
            child++;
        if (temp.arrival_time >= h->heap[child].arrival_time) //우선순위 판단
            break;
        //한단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

HeapType *sort_fcfs(process_in a[], int n) // rr 히프 정렬 실행
{
    int i;
    HeapType *h;
   printf("< process >\n");
   printf("| process_id | priority | computing_time | arrival_time |\n");
    h = create(); //히프 생성
    init(h); //초기화

    for (i = 0; i < n; i++)
    {
        insert_max_fcfs(h, a[i]); //입력받은 프로세스 수만큼 삽입
    }
    for (i = (n - 1); i >= 0; i--)
    {
        a[i] = delete_max_fcfs(h); //삭제
      

        printf("%5d \t\t %5d \t\t %5d \t\t %5d \t\t\n", a[i].process_id, a[i].priority,  a[i].computing_time,a[i].arrival_time);
    }
    
 
    for (i = 0; i < n; i++)
    {
      

        printf("%5d \t\t %5d \t\t %5d \t\t %5d \t\t\n", a[i].process_id, a[i].priority,  a[i].computing_time,a[i].arrival_time);
   
    }
printf("\n");
    return h;
   
}

double fcfs(process_in a[], int n){
    printf("===================================================FCFS===================================================\n");
    
    sort_fcfs(a, n);
    double At,final = 0;

    printf("| process_id | priority | computing_time | turn_around time | arrival_time | kill_time | 정규화 반환 시간 |\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    
    for (int i = 0; i < n; i++){


        if(i == 0) { //종료시간 구함.
            a[i].kill_time = a[i].computing_time;
            a[i].turn_around_time = a[i].kill_time;
        }
        else {
            a[i].kill_time = a[i-1].kill_time + a[i].computing_time;
            a[i].turn_around_time = a[i].kill_time - a[i].arrival_time;
        }
        At = ((double)(a[i].turn_around_time / (double)a[i].computing_time));
        final += At;

        printf("%5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \t\t %lf \n", a[i].process_id, a[i].priority,  a[i].computing_time, a[i].turn_around_time, a[i].arrival_time, a[i].kill_time, At);
        // printf("%d번째 정규화 반환시간:%lf\n",i+1,At);
    }

    printf("FCFS 정규화 평균 반환 시간:%lf\n",final / (double)n);
    printf("\n");

    return final/(double)n;
}
