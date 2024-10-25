#include "pQueue.h"




    pQueue::pQueue(){
        this->count = 0;
    };

    pQueue::~pQueue(){};

    void pQueue::swap(int posA, int posB){
        PCB temp = queue[posA];
        queue[posA] = queue[posB];
        queue[posB] = temp;
    };

    void pQueue::reheapify(){
        int pos = 0;
        queue[0] = queue[count - 1];
        count--;

        while(pos < count){
            int larger = getLargerChild(pos);

            if(larger == -1 || queue[pos].priority >= queue[larger].priority)
                break;

            swap(pos, larger);
            pos = larger;
        }
    };

    int pQueue::getLargerChild(int index){
        int LC = (2 * index) + 1;
        int RC = (2 * index) + 2;

        if(LC >= count)
            return -1;

        if(RC >= count)
            return LC;

        if(queue[LC].priority > queue[RC].priority)
            return LC;
        else
            return RC;
    };

    void pQueue::trickleUp(){
        int x = count - 1;

        while(x > 0){
            int parent = getParent(x);

            //If parent has larger priority, then swap
            if(queue[x].priority > queue[parent].priority){
                swap(x, parent);
                x = parent;
            } else
                break;
        }
    };

    int pQueue::getParent(int index){
        return ((isEven(index)) ? ((index - 2) / 2) : ((index - 1) / 2));
        /*
        if(isEven(index))
            return((index - 2) / 2);
        else
            return((index - 1) / 2);
            */
    };

    bool pQueue::isEven(int index){
        return (index % 2 == 0);   
    };

    void pQueue::addPCB(PCB pcb){
         queue[count++] = pcb;
        trickleUp();
    };

    PCB pQueue::removePCB(){
        PCB highestPriority = queue[0];
        reheapify();
        return highestPriority;
    };

    int pQueue::size(){
        return count;
    };
