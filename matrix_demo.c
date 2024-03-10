#include "mex.h"

void matrix_demo(double *c, mwSize rows, mwSize cols, double *output_cc) {
    int i, j, k;
    
    //错误的形式
    printf("matlab的矩阵以一维数组传入c中, 按照c以 行 储存的下标输出为(错误的形式): \n");
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%f", c[cols * i + j]);
        }
        printf("\n");
    }
    printf("\n");printf("\n");

    //正确的形式
    printf("正确的形式: \n");
    printf("matlab的矩阵以一维数组传入c中, 按照c以 列 储存的下标输出为(正确的形式): \n");
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%f", c[j * rows + i]);
        }
        printf("\n");
    }
    printf("\n");printf("\n");

    double *c_1d = (double *)calloc(rows*cols, sizeof(double));
    printf("在c中创建指针形式的一维数组c_1d:\n");
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            c_1d[i * cols + j] = i * cols + j;//以行来储存
            printf("%f", c_1d[cols * i + j]);
        }
        printf("\n");
    }
    printf("\n");printf("\n");
    
    //正确的形式
    printf("在c中c_1d按照c以 行 储存的下标赋值给二维数组c_2d(正确的形式): \n");
    double **c_2d = (double **)calloc(rows, sizeof(double *));
    for (i = 0; i < rows; i++){
        c_2d[i] = (double *)calloc(cols, sizeof(double));
    }
    printf("c_2d: \n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c_2d[i][j] = c_1d[i * cols + j];
            printf("%f ",c_2d[i][j]);
        }
        printf("\n");
    }
    printf("\n");printf("\n");

    //正确的形式
    printf("把从matlab中传来的一维数组形式的矩阵以 列 储存的下标, 赋值给c中创建的二维数组c_2d(正确的形式): \n");
    printf("c_2d: \n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c_2d[i][j] = c[i + j * rows];
            printf("%f ",c_2d[i][j]);
        }
        printf("\n");
    }
    printf("\n");printf("\n");

    //正确的形式
    printf("c中创建的二维数组c_2d赋值给要输出到matlab中的output_cc(正确的形式): \n");
    printf("output_cc在C中的输出为: \n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            output_cc[i + j * rows] = c_2d[i][j];
            printf("%f ",output_cc[i + j * rows]);//output_cc以 列 储存
        }
        printf("\n");
    }
    printf("\n");printf("\n");


}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

    // 获取输入参数
    double *c = mxGetPr(prhs[0]);
    mwSize rows = mxGetM(prhs[0]);
    mwSize cols = mxGetN(prhs[0]);


    // 分配输出参数内存
    plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL); // cc

    // 获取输出参数指针

    double *output_cc = mxGetPr(plhs[0]);


    // 调用函数计算结果
    matrix_demo(c, rows, cols, output_cc);
}
