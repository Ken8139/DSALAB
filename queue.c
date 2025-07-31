#include<stdio.h>
#define MAX 100
int main(){
     int queue[MAX];
     int front=-1,rear=-1;
     int value;
     int enqueuecount,dequeuecount;
     printf("Enter the no of element to insert to queue: ");
     scanf("%d",&enqueuecount);
     for(int i=0; i<enqueuecount;i++){
       if(rear == MAX -1){
         printf("Queue is full \n");
         break;
        }
        printf("Enter the value to insert :");
        scanf("%d",&value);
        if(front == -1){
           front =0;
        }
        rear++;
        queue[rear] =value;
        printf("Inserted value: %d\n",value);
      }
      printf("\nEnter the number deleted from the queue : ");
      scanf("%d",&dequeuecount);
      for(int i=0;i<dequeuecount;i++){
        if(front == -1|| front>rear){
         printf("Queue is empty \n");
         break;
        }
        printf("Deleted element: %d\n",queue[front]);
          front++;
      }
      if (front == -1 || front>rear) {
       printf("\n Queue is now empty.\n");
      }else{
      printf("\nRemaining element in the queue:\t");
        for (int i = front; i<= rear; i++){
          printf("%d",queue[i]);
        }
        printf("\n");
       }
       return 0;
 }
 
         
     
     
     
   
     	
