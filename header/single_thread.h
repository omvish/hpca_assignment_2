// Optimize this function
void singleThread(int N, int *matA, int *matB, int *output)
{	// create a matrix to store the transposed data of matrix B -> desB
	int *desB = new int[N * N];
	// Block by block matrix transpose
	int blocksize = 8;
	for (int row = 0; row < N; row += blocksize) {
		for (int col = 0; col < N; col += blocksize) {
		    for (int i = row; i < row + blocksize; ++i) {
		        for (int j = col; j < col + blocksize; ++j) {
		            desB[i + j*N] = matB[j + i*N];
		        }
		    }
		}
	}
	/* To feed data of DMM to output matrix	matA is same as given 
	matrix only matB is changed to its transpose so that only row 
	to row multiplication is needed now (ith row of matA is 
	multiplied with N-ith row of desB )*/
	for (int i = 0;i < N ; i++){
		for (int j = 0; j < N; j++){
			int rowB = N- 1- i;
			output[i+j] += matA[i * N + j] * desB[rowB * N + j];
		}
	}	
}	
