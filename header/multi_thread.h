#include <pthread.h>

int t_num = 0;
int no_of_threads = 64;
int N,n,size;;
int *mtB, *mtA, *mtoutput;
pthread_mutex_t lock;
// Creating a function for threads to multiply their dedicated diagonals(row + col values) 
void *multiply( void *arg){
    /*t_num is global variable shared between all the created threads so 
    it is kept inside mutex */
    
    pthread_mutex_lock(&lock);
    int thread_num = t_num++;  /*thread_num is assigned to every thread on the basis of FCFS*/
    pthread_mutex_unlock(&lock);
    
    // k is defined to identify the offset of a thread, from where it 
    // needs to work and how much it needs to work
    int k = thread_num*size;
    
    /*Starting half threads will perform their tasks on initial loop*/
    if (thread_num/n == 0){
        for(int i = k; i < k + size; ++i) {
            int temp = 0;
            // Iterate over diagonal elements
            for(int j = 0; j < i + 1; ++j) {
                int rowA = j;
                int colA = i - j;
                int rowB = i - j;
                int colB = N - j - 1;
                temp += mtA[rowA * N + colA] * mtB[rowB * N + colB];
            }
            mtoutput[i] = temp;
        }
    }
    
    /*Later half threads will perform their tasks on final loop*/
    else{
        // Except last assigned thread all other will run till their assigned size
        if (t_num != no_of_threads){
            for(int i = k; i < k + size ; ++i) {
                int temp = 0;
                // Iterate over diagonal elements
                for(int j = 0; j < 2*N - (i + 1); ++j) {
                    int rowA = i + 1 + j - N;
                    int colA = N - j - 1;
                    int rowB = N - j - 1;
                    int colB = 2 * N - j - 2 - i;
                    temp += mtA[rowA * N + colA] * mtB[rowB * N + colB];
                }
                mtoutput[i] = temp;
            
            }
        }
        
        // last assigned thread will run 1 less time then the assigned size
        else{
            for(int i = k; i < k+ size-1; ++i) {
            int temp = 0;
            // Iterate over diagonal elements
            for(int j = 0; j < 2*N - (i + 1); ++j) {
                int rowA = i + 1 + j - N;
                int colA = N - j - 1;
                int rowB = N - j - 1;
                int colB = 2 * N - j - 2 - i;
                temp += mtA[rowA * N + colA] * mtB[rowB * N + colB];
            }
            mtoutput[i] = temp;
            }
        }
    }
    return NULL;
}

void multiThread(int Num, int *matA, int *matB, int *output)
{   
    /*Initialize global variables*/
    N = Num;
    mtA = matA;
    mtB = matB;
    mtoutput = output;
    pthread_t tid[no_of_threads];
    /*size is the number of diagonals a thread needs to cover*/
    size = 2*N/no_of_threads;
    /*n will partition the initial half of threads and later half 
    of the threads as they have dedicated multiplication loops */
    n = no_of_threads/2;
    /*Creating threads*/
    for (int i = 0; i < no_of_threads; i++){
        pthread_create(&tid[i], NULL, multiply, NULL);
    }

    /*Instructing threads to perform their dedicated work*/
    for (int i = 0; i < no_of_threads; i++){
        pthread_join(tid[i], NULL);
    }
    // Reassign output of multiplication to output matrix pointer
    output = mtoutput;

}
