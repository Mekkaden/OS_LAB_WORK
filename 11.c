#include<stdio.h>
//work = copy of avalaible

int main(){
	int n,m;
	int alloc[10][10], max[10][10], need[10][10];
	int avail[10], work[10], finish[10], safeSeq[10];
	printf("Enter no: of processes:");
	scanf("%d",&n);
	printf("Enter no of resources(ex : ro , r1 ....):");
	scanf("%d",&m);
	printf("Enter Allocation matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&alloc[i][j]);
		}
	}
	printf("Enter Max matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&max[i][j]);
		}
	}
	printf("Enter Available resources:\n");
	for(int i=0;i<m;i++)
		scanf("%d",&avail[i]);
	//Need=Max-Allocation
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}
	//Safety Algorithm
	for(int j=0;j<m;j++)
		work[j]=avail[j];

	for(int i=0;i<n;i++)
		finish[i]=0;

	int count=0;

	while(count<n){
		int found=0; //flag
		for(int i=0;i<n;i++){
			if(finish[i]==0){
				int j;
				for(j=0;j<m;j++){
					if(need[i][j]>work[j])
						break;
				}
				if(j==m){
					for(int k=0;k<m;k++){
						work[k]+=alloc[i][k]; //freeing the instances of resources which were needed by the executint process wrt allocation , ie allocqationil ninnu current processinte kth resourcinte free aaya instance(after the ith process is completed) as its need < avalaible,  work(avaliavlea) kilekku kooti
					}
					safeSeq[count]=i;
                    count ++;
					finish[i]=1;
					found=1; //to understand that at least one process is in safe state
				}
			}
		}
		if(!found){
			printf("\nSystem is NOT in safe state\n");
			return 0;
		}
	}

	printf("\nSystem is in SAFE state.\nSafe Sequence: ");
	for(int i=0;i<n;i++)
		printf("P%d ",safeSeq[i]);

	//Resource Request Algorithm

	int pid, req[10];
	printf("\n\nEnter process no making request:");
	scanf("%d",&pid);
	printf("Enter request vector:\n");
	for(int j=0;j<m;j++)
		scanf("%d",&req[j]);
	//Request<=Need
	for(int j=0;j<m;j++){
		if(req[j]>need[pid][j]){ //ie, need is something to reach maximum , bcs max = need + allocation ,but punda is asking for more than need , so it exceeds max as max = alloc + need; 
			printf("\nError:Request exceeds maximum need\n");
			return 0;
		}
	}
	//Request<=Available
	for(int j=0;j<m;j++){
		if(req[j]>avail[j]){
			printf("\nProcess must wait..resource not available");
			return 0;
		}
	}
	for(int j=0;j<m;j++){
		avail[j]-=req[j];
		alloc[pid][j]+=req[j];
		need[pid][j]-=req[j]; //see if requested resources are  given ,  then the need should reduce
	}
	printf("\nRequest can be granted safely.\n");
	return 0;
}
