#include <pthread.h>
#include <math.h>
// Create other necessary functions here

int t_num = 0;
int no_of_threads = 256;
int N,n,size;;
int *mtB, *mtA, *mtoutput;
pthread_mutex_t lock;
void *multiply( void *arg){
    
    pthread_mutex_lock(&lock);
    int thread_num = t_num++;
    pthread_mutex_unlock(&lock);
    int k = thread_num*size;
    // cout<<thread_num << "\t"<<t_num<<"\t"<<size<<endl;
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
            //  cout<<i<< endl;
        }
    }
    
    else{
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

    // Iterate over second half of output elements

    }
    return NULL;
}
// Fill in this function
void multiThread(int Num, int *matA, int *matB, int *output)
{   
    N = Num;
    mtA = matA;
    mtB = matB;
    mtoutput = output;
    pthread_t tid[no_of_threads];
    // cout<<"K: "<<k<<endl;
    size = 2*N/no_of_threads;
    n = no_of_threads/2;

    for (int i = 0; i < no_of_threads; i++){
        pthread_create(&tid[i], NULL, multiply, NULL);
    }
    for (int i = 0; i < no_of_threads; i++){
        pthread_join(tid[i], NULL);
    }
    
    output = mtoutput;


    // cout<<"MT: ";
	// for(int i = 0; i< 2*N-1;i++)	cout<<output[i]<<"\t";
	// cout<<endl;
}
