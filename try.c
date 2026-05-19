void lru(int f,int ref[],int n){
    int t[10];
    int pos = -1;
    int frame[10];
    int clock = 0;
    int fault = 0;

    for(int i =0 ; i<f;i++){
        frame[i] = 0;
    
    printf("LRU ");
    }
    for(int i = 0 ; i<n;i++){
        int hit = 0 ;
        for(int j = 0 ;j<n;j++){
            if(frame[j] == ref[i]){
                hit = 1;
                pos = j;
                break;

            }
        }

        if(hit == 1){
            t[pos] == ++clock;
            display(frame,f);
            printf("Hit");

        else{
            min = 0;
            for(int i = 1 ; i<f ;i++){
                if(t[j]< time[min]){
                    min = j;

                }
            }
            

        }
        }



    }

}