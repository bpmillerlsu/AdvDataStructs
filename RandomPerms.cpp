#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void printArray (int array[], int arraySize);
void printArray (double array[], int arraySize);

class RandomPermutation {
private:
    int hasPrintedOnce = 0, *permutation, *numAttempts;
    
public:
    RandomPermutation(int, int, int);
    void fillPermutation(int numItems, int seed){
        int m, attempt = 1, *isUsed;
        srand(seed);
        isUsed = new int[numItems], permutation = new int[numItems], numAttempts = new int[numItems];
        
        cout << "The random integers m generated:" << endl;
        
        for (int i = 0; i < numItems; ++i){
            attempt = 0;
            do {
                m = rand() % numItems;
                cout << m << " ";
                ++attempt;
                if (!isUsed[m]){
                    permutation[i] = m;
                    numAttempts[i] = attempt;
                    isUsed[m] = 1;
                    break;
                }
            } while (1);
        }
        
        cout << endl << endl << "permutation: ";
        printArray(permutation, numItems);
        cout << endl << "numAttempts: ";
        printArray(numAttempts, numItems);
        cout << endl << "--------------------" << endl;
    }
    
    void averNumAttempts(int numItems, int numIterations){
        int *minNumAttempts, *maxNumAttempts;
        double *averNumAttempts;
        averNumAttempts = new double[numItems], minNumAttempts = new int[numItems], maxNumAttempts = new int[numItems];
        
        for (int i = 0; i < numItems; ++i)
            averNumAttempts[i] = minNumAttempts[i] = maxNumAttempts[i] = numAttempts[i];
        
        for (int i = 1; i < numIterations; ++i){
            fillPermutation(numItems, rand() % numItems);
            for (int j = 0; j < numItems; ++j){
                if (numAttempts[j] < minNumAttempts[j])
                    minNumAttempts[j] = numAttempts[j];
                else if (numAttempts[j] > maxNumAttempts[j])
                    maxNumAttempts[j] = numAttempts[j];
                averNumAttempts[j] += numAttempts[j];
            }
        }
        
        for (int i = 0; i < numItems; ++i)
            averNumAttempts[i] = averNumAttempts[i] / numIterations;
        
        cout << "maxNumAttempts = ";
        printArray(maxNumAttempts, numItems);
        cout << endl;
        cout << "minNumAttempts = ";
        printArray(minNumAttempts, numItems);
        cout << endl;
        cout << "averNumAttempts = ";
        printArray(averNumAttempts, numItems);
        cout << endl << "--------------------" << endl;
    }
    
    int** cycles(int numItems){
        int** cycle = new int*[numItems];
        for (int i = 0; i < 10; ++i)
            cycle[i] = new int[numItems];
        
        int currCycle[numItems];
        for(int i = 0; i < numItems; ++i){
            currCycle[i] = permutation[i];

        }
        return cycle;
    }
};

RandomPermutation::RandomPermutation(int numItems, int seed, int numIterations){
    fillPermutation(numItems, seed);
    averNumAttempts(numItems, numIterations);
    cycles(numItems);
}

void printArray (int array[], int arraySize){
    cout << "[ ";
    for (int i = 0; i < arraySize; ++i){
        cout << array[i] << ", ";
    }
    cout << "] ";
}

void printArray (double array[], int arraySize){
    cout << "[ ";
    for (int i = 0; i < arraySize; ++i){
        cout << fixed << setprecision(2) << array[i] << ", ";
    }
    cout << "] ";
}

int main(){
    int seed = time(NULL);
    int numIterations = 3;
    int numItems = 10;
    
    RandomPermutation(numItems, seed, numIterations);
    
    return 0;
}