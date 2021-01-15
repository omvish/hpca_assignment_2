// Optimize this function
void singleThread(int N, int *matA, int *matB, int *output)
{
	int *desB = new int[N * N];
	
	int blocksize = 8;
	for (int i = 0; i < N; i += blocksize) {
		for (int j = 0; j < N; j += blocksize) {
		    for (int k = i; k < i + blocksize; ++k) {
		        for (int l = j; l < j + blocksize; ++l) {
		            desB[k + l*N] = matB[l + k*N];
		        }
		    }
		}
	}
	
	for (int i = 0;i < N ; i++){
		for (int j = 0; j < N; j++){
			int rowB = N- 1- i;
			output[i+j] += matA[i * N + j] * desB[rowB * N + j];
		}
	}
	// cout<<"ST: ";
	// for(int i = 0; i< 2*N-1;i++)	cout<<output[i]<<"\t";
	// cout<<endl;
	
}	
