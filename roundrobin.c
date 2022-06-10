void insert(HeapType *h, process_in item) 
{
    //최대 히프: 부모 노드의 키값이 자식 노드 키값보다 크거나 같음.
    //현재 요소의 개소가 heap_size인 히프 h에 item 삽입한다.
    int i;

    i = ++(h->heap_size);
    
    h->heap[i] = item; //새로운 노드를 삽입

}

HeapType *sort_rr(process_in a[], int n, int timeslice) //히프 정렬 실행
{
    int i, type = true, total = 0;
    HeapType *h;
    h = create(); //히프 생성
    init(h); //초기화

    int arr[n];
    for(int i=0; i<n; i++) {
        arr[i] = a[i].computing_time;
        a[i].remaining_time = a[i].computing_time;
    }

    // TODO 도착시간 고려해야 함
    while(type){
        for (i = 0; i < n; i++)
        {
            // if(a[i].arrival_time > total) {
            //     total = total + (a[i].arrival_time - total);
            //     if(i != 0)
            //         break;
            // }

            if(timeslice < a[i].computing_time && a[i].remaining_time > 0){
                
                if(arr[i] - timeslice < 0) {
                    a[i].remaining_time = 0;
                    total = total + arr[i];
                }
                else {
                    a[i].remaining_time = arr[i] - timeslice;
                    total = total + timeslice;
                }

                arr[i] = arr[i]-timeslice;

                a[i].complete_time = total;
                
                insert(h, a[i]);
                
            } else if(a[i].remaining_time > 0) {
                total = total + a[i].computing_time + a[i].remaining_time;
                a[i].complete_time = total;
                
                a[i].remaining_time = 0;
                insert(h, a[i]);
                arr[i] = 0;
            }
        }

        for(int i=0; i<n; i++) {
            if(arr[i] > 0) {
                type = true;
                break;
            }
            else
                type = false;
        }
    }
    
    printf("< process >\n");
    printf("| process_id | computing_time | arrival_time | remaining_time | complete_time\n");
    for(int i=1; i <= h->heap_size; i++){
        printf("%5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \n", h->heap[i].process_id, h->heap[i].computing_time, h->heap[i].arrival_time, h->heap[i].remaining_time, h->heap[i].complete_time);
    }
    printf("\n\n");

    return h;
}

double rr(process_in a[], int n){
    printf("===============================================ROUND ROBIN================================================\n");
  
    sort_rr(a, n, 20);
   
    double At,final = 0;

    printf("| process_id | priority | computing_time | turn_around_time | arrival_time | complete_time | remaining_time | 정규화 반환 시간 |\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    for (int i = 0; i < n; i++) {

        a[i].turn_around_time = a[i].complete_time - a[i].arrival_time;

        At = ((double)(a[i].turn_around_time / (double)a[i].computing_time));
        final += At;

        printf("%5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \t\t %5lf \n", 
            a[i].process_id, a[i].priority, a[i].computing_time, 
            a[i].turn_around_time, a[i].arrival_time, a[i].complete_time, a[i].remaining_time, At);

        // printf("NO.%d clock:%lf\n",i+1,At);
    }

    printf("ROUND ROBIN 정규화 평균 반환 시간:%lf\n",final / (double)n);
    printf("\n");

    return final/(double)n;
}