#include <stdio.h>
#include <stdlib.h>

//scans scores and adds them to an array
//count is how many integers are scanned in
void readScores(int* parr, int* pcount){
    int score;
    while(scanf("%d", &score) != EOF){
        parr[(*pcount)++] = score;
    }
}

//displays results for the test file
//format - score[place in array]: [score]
void displayScores(int* parr, int* count){
    for(int i = 0; i < *count; i++){
        printf("score %d: %d\n", i, parr[i]);
    }
}

//histogram struct
struct freq{
    int value;
    int frequency;
};

//calulates the histogram for an array of integers
void calcHistogram(int* parr, int* pcount, struct freq* phist, int* phistCount){
    //variables
    int index = 0;
    int found = 0;

    //iterates through the array
    for(int i = 0; i < *pcount; i++){
        //iterates through the histogram
        for(int j = 0; j < index; j++){
            //if the value is found in the histogram
            if(parr[i] == phist[j].value){
                //increment the frequency
                phist[j].frequency++;
                found = 1;
                break;
            }
        }
        //if the value is not found in the histogram
        if(!found){
            //add the value to the histogram
            phist[index].value = parr[i];
            phist[index].frequency = 1;
            index++;
        }
        found = 0;
    }
    *phistCount = index;
}

//displays the results of the histogram
void displayHistogram(struct freq* phist, int* phistCount){
    for(int i = 0; i < *phistCount; i++){
        printf("value %d: freq %d\n", phist[i].value, phist[i].frequency);
    }
}

//sorts the histogram by highest -> lowest frequencies using selection sort
void sortHistogram(struct freq* phist, int* phistCount){
    //variables
    int maxIndex;
    struct freq temp;

    //iterates through the histogram
    for(int i = 0; i < *phistCount; i++){
        //sets the minimum index to the current index
        maxIndex = i;

        //iterates through the histogram
        for(int j = i + 1; j < *phistCount; j++){
            //if the frequency is less than the minimum frequency
            if(phist[j].frequency > phist[maxIndex].frequency){
                //set the minimum index to the current index
                maxIndex = j;
            }
        }
        //swap the current index with the minimum index
        temp = phist[i];
        phist[i] = phist[maxIndex];
        phist[maxIndex] = temp;
    }
}

int main(){
    //variables
    int arr[100];
    int count = 0;
    
    //pointers
    int* pcount = &count;

    //reading and displaying scores
    printf("Scores:\n");
    readScores(arr, pcount);
    displayScores(arr, pcount);

    //allocating memory for histogram
    struct freq* phist= malloc(sizeof(struct freq) * count);

    //checking if malloc was successful
    if(phist == NULL){
        printf("Memory not allocated\n");
        return 1;
    }

    //variables
    int histCount = 0;
    //pointers
    int* phistCount = &histCount;

    //calculating and displaying histogram
    printf("Histogram:\n");
    calcHistogram(arr, pcount, phist, phistCount);
    displayHistogram(phist, phistCount);

    //sorting and displaying histogram
    printf("Histogram sorted by frequency:\n");
    sortHistogram(phist, phistCount);
    displayHistogram(phist, phistCount);

    //freeing memory
    free(phist);

    return 0;
}