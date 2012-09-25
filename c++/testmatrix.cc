/*
 * =============================================================================
 *
 *       Filename:  testmatrix.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月05日 10时53分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#define SAMPLES 1000
#define MATSIZE 513

#include <time.h>
#include <iostream>
int mat[MATSIZE][MATSIZE];

void transpose()
{
    for ( int i = 0 ; i < MATSIZE ; i++ )
        for ( int j = 0 ; j < MATSIZE ; j++ )
        {
            int aux = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = aux;
        }
}

int main()
{
    //initialize matrix
    for ( int i = 0 ; i < MATSIZE ; i++ )
        for ( int j = 0 ; j < MATSIZE ; j++ )
            mat[i][j] = i+j;

    int t = clock();
    for ( int i = 0 ; i < SAMPLES ; i++ )
        transpose();
    int elapsed = clock() - t;

    std::cout << CLOCKS_PER_SEC << std::endl;
    float se = (float)elapsed / CLOCKS_PER_SEC;

    std::cout << "Average for a matrix of " << MATSIZE << ": " << se <<" s"<< std::endl;
}


