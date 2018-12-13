//正弦波のテーブルを3つ吐き出す
#include <stdio.h>
#include <math.h>

#define FS 31250

int main(int argc ,char** argv)
{
	if (argc != 4){
		fprintf(stderr, "usage gen_sin_table f1 f2 f3\n");
		exit(0);
	}
	
	int f1 = atoi(argv[1]);
	int f2 = atoi(argv[2]);
	int f3 = atoi(argv[3]);

	int flist[3] = {f1, f2, f3};
	int nS[3] = {FS / f1, FS / f2, FS / f3};
	
	

	int j=0;
	int i=0;
	
	for (j=0; j<3; j++){
		
		printf("unsigned char sample%d[%d] ={",j,nS[j]);
		for (i=0; i<nS[j];i++){
			printf("%.0f,", 127 + 127*sin(2*3.14159*flist[j]*i/31250));
		}
		printf("};\n");
	}
	return 0;
}
