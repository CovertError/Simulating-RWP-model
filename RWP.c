#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
/*

 #     #                                              #######           #######                   #####
 #  #  # ###### #       ####   ####  #    # ######       #     ####        #    #    # ######    #     # # #    # #    # #        ##   ##### #  ####  #    #
 #  #  # #      #      #    # #    # ##  ## #            #    #    #       #    #    # #         #       # ##  ## #    # #       #  #    #   # #    # ##   #
 #  #  # #####  #      #      #    # # ## # #####        #    #    #       #    ###### #####      #####  # # ## # #    # #      #    #   #   # #    # # #  #
 #  #  # #      #      #      #    # #    # #            #    #    #       #    #    # #               # # #    # #    # #      ######   #   # #    # #  # #
 #  #  # #      #      #    # #    # #    # #            #    #    #       #    #    # #         #     # # #    # #    # #      #    #   #   # #    # #   ##
  ## ##  ###### ######  ####   ####  #    # ######       #     ####        #    #    # ######     #####  # #    #  ####  ###### #    #   #   #  ####  #    #

Author: Omar Yassin

supervisor: Dr. Wesam

Version:1.0

Discription:
Welcome to the best project in the entire world nothing is better than this .
this project is a Simulation of the Random Waypoint (RWP) mobility model.
and this is done by using a linked List.

*/
struct node {
    float  speed;
    int objID;
    float  posX; // INITIALIZATION of the node
    float  posXDest;
    float  posY;
    float  posYDest;
    struct node *next;
};

struct list {
    struct node *start;
    struct node *first; //INITIALIZATION
};


void InitList(struct list *sList){
    sList->start = NULL;
}

void push(struct list *sList,float  posX, float  posY, float  speed, float  posXDest, float  posYDest, int objID ){
    struct node *p;
    p = malloc(sizeof(struct node));
    p->objID= objID;
    p->speed = speed;
    p->posXDest = posXDest;
    p->posY = posY;                //pushing the nodes to the Linked list and setting the vlaues of the nodes
    p->posX = posX;
    p->posYDest = posYDest;
    p->next = sList->start;
    sList->start = p;

}
void deleteNode(struct list *sList, struct node *n){
    struct node *head = sList->start;
    // When node to be deleted is head node
    if(head == n){
        if(head->next == NULL) {
            head=NULL;
            return;
        }
        // store address of next node
        n = head->next;

        // Remove the link of next node
        head->next = head->next->next;

        // free memory
        free(n);

        return;
    }


    // When not first node, follow the normal deletion process

    // find the previous node
    struct node *prev = head;
    while(prev->next != NULL && prev->next != n)
    prev = prev->next;

    // Check if node really exists in Linked List
    if(prev->next == NULL){
        printf("\n Given node is not present in Linked List");
        return;
    }

    // Remove node from Linked List
    prev->next = prev->next->next;

    // Free memory
    free(n);

    return;
}

void movement(struct list *sList,int simTime,int  areaX,int  areaY,int totalT,int objects) {
    struct node *p = sList->start;
    struct node *head = sList->start;
    int done=1;
    int flag=0;
    int flag2=0;                     //INITIALIZATION
    int actaulTimeSpent=simTime;
    int timeSpent=simTime;
    int count=1;
    float totalX=0;
    float totalY=0;
    float speedX=0;
    float speedY=0;

    while (done) {

        float objSpeed = p->speed;
        float objPosX = p->posX;
        float objPosXDest = p->posXDest;  //INITIALIZATION
        float objPosYDest = p->posYDest;
        float objPosY = p->posY;
        int objID = p->objID;
        if ((objPosX== objPosXDest) && (objPosY==objPosYDest)) {
            objPosXDest = rand() % (areaX + 1);
            p->posXDest = objPosXDest;                 //getting a random position and setting it to the node
            objPosYDest = rand() % (areaY + 1);
            p->posYDest = objPosYDest;

        }

        if (objPosX>objPosXDest) {
            totalX = objPosX - objPosXDest; //Checking if the X start position is bigger than the end and if it then set flag to 1
            flag=1;
        }else{
            totalX = objPosXDest - objPosX;
            flag=0; //else set flag to 0
        }
        if (objPosY>objPosYDest) {
            totalY = objPosY - objPosYDest;//Checking if the Y start position is bigger than the end and if it then set flag to 1
            flag2=1;
        }else{
            totalY = objPosYDest - objPosY;
            flag2=0;//else set flag to 0
        }
        float angel= atan(totalY/totalX);//getting the angel theta from the total deistence of y over the total of x
        float speedY= objSpeed*sin(angel);//getting the velocity of y by multiplying the object speed by sin theta
        float speedX= objSpeed*cos(angel);//getting the velocity of x by multiplying the object speed by cos theta
        if (flag==1) {
            speedX= speedX*(-1); // multiplying the X speed with -1
        }if (flag2==1) {
            speedY= speedY*(-1); // multiplying the Y speed with -1
        }if (flag2==0) {
            speedY=abs(speedY);//taking the absulote value of speedY becuase sometimes using sin might give us a negitive value
        }
        if (((objPosX < objPosXDest) && ( (objPosXDest - objPosX)> (speedX*simTime) ))) {
            objPosX+= simTime* speedX;// checking if the current position is smalller than the destenation position and if
            p->posX = objPosX;       //  the final destenation -  the current is bigger than the distence needed to be covered
        }else if((objPosX > objPosXDest) && (objPosX - objPosXDest) > (abs(speedX)*simTime)) {
            objPosX+= simTime* speedX;// checking if the current position is bigger than the destenation position and if
            p->posX = objPosX;      //  the current - the final destenation  is bigger than the absulote value of the distence needed to be covered

        } else{
            objPosX=objPosXDest;
            p->posX = objPosX; //esle setting the those defaults

        }
        if (((objPosY < objPosYDest) && ((objPosYDest - objPosY)> (speedY*simTime)))) {
            objPosY+= simTime* speedY;
            p->posY = objPosY;// this is doing the exact same thing with X but with Y
        }else if((objPosY > objPosYDest) && (objPosY - objPosYDest) > (abs(speedY)*simTime)) {
            objPosY+= simTime* speedY;
            p->posY = objPosY;// this is doing the exact same thing with X but with Y

        } else{
            objPosY=objPosYDest;
            p->posY = objPosY;

        }

        if (p->next == NULL) {
            timeSpent+= simTime;
            p = head;//checking if the next node is null and if so adding simTime to the timeSpent

        }else{
            p=p->next;//going to the next node

        }
        if (totalT<actaulTimeSpent) {
            p = head;//setting p to head
            while (p-> next != NULL) {// looping around the whole list and deleting every node
                deleteNode(sList, p);// calling the deleteNode function
            }
            break;
        }
        printf("the location of object number %d with speed of %.2f is at x = %.2f y= %.2f at time %d and it's moving to x= %.2f y= %.2f \n",objID,objSpeed,objPosX, objPosY, actaulTimeSpent, objPosXDest, objPosYDest);
        if (p->next == NULL) {//if the next node is null
            actaulTimeSpent+= simTime;//adding the simTime to the actual time spent
        }

        count++;
    }

}
void printingAsscii() {
    printf (" #######  ##     ##    ###    ########     ##    ##    ###     ######   ######  #### ##    ## \n");
    printf ("##     ## ###   ###   ## ##   ##     ##     ##  ##    ## ##   ##    ## ##    ##  ##  ###   ## \n");
    printf ("##     ## #### ####  ##   ##  ##     ##      ####    ##   ##  ##       ##        ##  ####  ## \n"); //being cool lol
    printf ("##     ## ## ### ## ##     ## ########        ##    ##     ##  ######   ######   ##  ## ## ## \n");
    printf ("##     ## ##     ## ######### ##   ##         ##    #########       ##       ##  ##  ##  #### \n");
    printf ("##     ## ##     ## ##     ## ##    ##        ##    ##     ## ##    ## ##    ##  ##  ##   ### \n");
    printf (" #######  ##     ## ##     ## ##     ##       ##    ##     ##  ######   ######  #### ##    ## \n\n");
}

int main(int argc, char** argv){
    srand(time(0));
    int objects;
    int simTime;
    int  minSpeed;
    int  maxSpeed; //INITIALIZATION
    int  areaX;
    int  areaY;
    int totalT;
    float  posXDest;
    float  posX;
    float  posYDest;
    float  posY;
    float  speed;

    struct list MyList;//INITIALIZATION
    InitList(&MyList);//INITIALIZATION
    printingAsscii();//PRINTING MY NAME
    // printf("Enter the x distence of the area: \n" );
    scanf("%d",&areaX);
    // printf("Enter the y distence of the area: \n" );
    scanf("%d",&areaY);
    // printf("Enter the number of objects: \n" );
    scanf("%d",&objects);
    // printf("Enter the min speed: \n" ); //commenting it out to use an input and output file
    scanf("%d",&minSpeed);
    // printf("Enter the max speed: \n" );
    scanf("%d",&maxSpeed);
    // printf("Enter the Simulation time granularity: \n" );
    scanf("%d",&simTime);
    // printf("Enter the Simulation total time: \n" );
    scanf("%d",&totalT);

    for(int x = 0; x < objects; x++){
        posX = rand() % (areaX + 1);//getting a random position for the nodes
        posY = rand() % (areaY + 1);//getting a random position for the nodes
        posXDest = rand() % (areaX + 1);//getting a random destenation
        posYDest = rand() % (areaY + 1);//getting a random destenation
        speed = rand() % (maxSpeed - minSpeed + 1) + minSpeed;//getting a random speed
        push(&MyList, posX, posY, speed, posXDest, posYDest,x);//calling the push function
    }
    movement(&MyList, simTime, areaX, areaY, totalT, objects);//calling the movement function

    return 0;
}
