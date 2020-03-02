/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2169589",              /* Student ID */

    "ALPER KOCAMAN",     /* full name */
    "e2169589@ceng.metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * CONVOLUTION KERNEL
 ***************/

/******************************************************
 * Your different versions of the convolution functions  go here
 ******************************************************/

/* 
 * naive_conv - The naive baseline version of convolution 
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim,int *src, int *ker,int *dst) {
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[j*dim+i] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[j*dim+i] = dst[j*dim+i] +src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
        }
            
        
}

/* 
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dst) 
{
    int i,j,acc,dim2,num; 

    int *src2 = src ;

    int k0,k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14,k15;
    int k16,k17,k18,k19,k20,k21,k22,k23,k24,k25,k26,k27,k28,k29,k30,k31;
    int k32,k33,k34,k35,k36,k37,k38,k39,k40,k41,k42,k43,k44,k45,k46,k47;
    int k48,k49,k50,k51,k52,k53,k54,k55,k56,k57,k58,k59,k60,k61,k62,k63;

    num = dim-7 ;
    
    dim2 = dim+dim ;


    k0 = ker[0 ]; k1 = ker[1 ]; k2 = ker[2 ]; k3 = ker[3 ]; k4 = ker[4 ]; k5 = ker[5 ]; k6 = ker[6 ]; k7 = ker[7 ]; 
    k8  = ker[dim+0 ] ; k9  = ker[dim+1] ; k10 = ker[dim+2 ] ; k11 = ker[dim+3 ] ; k12 = ker[dim+4 ] ;
    k13 = ker[dim+5 ] ; k14 = ker[dim+6 ] ; k15 = ker[dim+7 ] ; 
    k16 = ker[dim2+0 ] ; k17 = ker[dim2+1] ; k18 = ker[dim2+2 ] ; k19 = ker[dim2+3 ] ; k20 = ker[dim2+4 ] ; 
    k21 = ker[dim2+5 ] ; k22 = ker[dim2+6 ] ; k23 = ker[dim2+7 ] ;
    dim2+=dim;
    k24 = ker[dim2+0 ] ; k25 = ker[dim2+1] ; k26 = ker[dim2+2 ] ; k27 = ker[dim2+3 ] ; k28 = ker[dim2+4 ] ; 
    k29 = ker[dim2+5 ] ; k30 = ker[dim2+6 ] ; k31 = ker[dim2+7 ] ; 
    dim2+=dim;
    k32 = ker[dim2+0 ] ; k33 = ker[dim2+1] ; k34 = ker[dim2+2 ] ; k35 = ker[dim2+3 ] ; k36 = ker[dim2+4 ] ; 
    k37 = ker[dim2+5 ] ; k38 = ker[dim2+6 ] ; k39 = ker[dim2+7 ] ;
    dim2+=dim;
    k40 = ker[dim2+0 ] ; k41 = ker[dim2+1] ; k42 = ker[dim2+2 ] ; k43 = ker[dim2+3 ] ; k44 = ker[dim2+4 ] ; 
    k45 = ker[dim2+5 ] ; k46 = ker[dim2+6 ] ; k47 = ker[dim2+7 ] ; 
    dim2+=dim;
    k48 = ker[dim2+0 ] ; k49 = ker[dim2+1] ; k50 = ker[dim2+2 ] ; k51 = ker[dim2+3 ] ; k52 = ker[dim2+4 ] ; 
    k53 = ker[dim2+5 ] ; k54 = ker[dim2+6 ] ; k55 = ker[dim2+7 ] ;
    dim2+=dim;
    k56 = ker[dim2+0 ] ; k57 = ker[dim2+1] ; k58 = ker[dim2+2 ] ; k59 = ker[dim2+3 ] ; k60 = ker[dim2+4 ] ; 
    k61 = ker[dim2+5]  ; k62 = ker[dim2+6 ] ; k63 = ker[dim2+7 ] ;

    for(i=0 ; i!=num ;i++ ){

        for(j=0 ; j!=num ;j++ ) {

        	src = src2 ;

            acc   = src[0]*k0 ;
            acc  += src[1]*k1 ;
            acc  += src[2]*k2 ;
            acc += src[3]*k3 ;
            acc  += src[4]*k4 ;
            acc += src[5]*k5 ;
            acc  += src[6]*k6 ;
            acc += src[7]*k7 ;
            src+=dim ;
            acc  += src[0]*k8 ;
            acc += src[1]*k9 ;
            acc  += src[2]*k10 ;
            acc += src[3]*k11 ;
            acc  += src[4]*k12 ;
            acc += src[5]*k13 ;
            acc  += src[6]*k14 ;
            acc += src[7]*k15 ;
            src += dim ;
            acc  += src[0]*k16 ;
            acc += src[1]*k17 ;
            acc  += src[2]*k18 ;
            acc += src[3]*k19 ;
            acc  += src[4]*k20 ;
            acc += src[5]*k21 ;
            acc  += src[6]*k22 ;
            acc += src[7]*k23 ;
            src += dim ;
            acc  += src[0]*k24 ;
            acc += src[1]*k25 ;
            acc  += src[2]*k26 ;
            acc += src[3]*k27 ;
            acc  += src[4]*k28 ;
            acc += src[5]*k29 ;
            acc  += src[6]*k30 ;
            acc += src[7]*k31 ;
            src += dim ;
            acc  += src[0]*k32 ;
            acc += src[1]*k33 ;
            acc  += src[2]*k34 ;
            acc += src[3]*k35 ;
            acc  += src[4]*k36 ;
            acc += src[5]*k37 ;
            acc  += src[6]*k38 ;
            acc += src[7]*k39 ;
            src += dim ;
            acc  += src[0]*k40 ;
            acc += src[1]*k41 ;
            acc  += src[2]*k42 ;
            acc += src[3]*k43 ;
            acc  += src[4]*k44 ;
            acc += src[5]*k45 ;
            acc  += src[6]*k46 ;
            acc += src[7]*k47 ;
            src += dim ;
            acc  += src[0]*k48 ;
            acc += src[1]*k49 ;
            acc  += src[2]*k50 ;
            acc += src[3]*k51 ;
            acc  += src[4]*k52 ;
            acc += src[5]*k53 ;
            acc  += src[6]*k54 ;
            acc += src[7]*k55 ;
            src += dim ;
            acc  += src[0]*k56 ;
            acc += src[1]*k57 ;
            acc  += src[2]*k58 ;
            acc += src[3]*k59 ;
            acc  += src[4]*k60 ;
            acc += src[5]*k61 ;
            acc  += src[6]*k62 ;
            acc += src[7]*k63 ;

            *dst = acc ;

            dst++ ;
            src2++ ;

        }
         
        src2 += 7 ;
        dst += 7 ;   
    }
}

/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_conv_functions() {
    add_conv_function(&naive_conv, naive_conv_descr);   
    add_conv_function(&convolution, convolution_descr);   
    /* ... Register additional test functions here */
}

/***************
 * MATRIX MULTIP KERNEL
 ***************/

/******************************************************
 * Your different versions of the matrix multiplications  go here
 ******************************************************/

/* 
 * naive_matrix_multiplication - The naive baseline version of matrix multiplication 
 */
char naive_matrix_multiplication_descr[] = "Naive_matrix_multiplication: Naive baseline implementation";
void naive_matrix_multiplication(int dim,int *src, int *src2,int *dst) {
    int i,j,k;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {
            dst[j*dim+i]=0;
            for(k = 0; k < dim; k++) 
                dst[j*dim+i] = dst[j*dim+i] + src[j*dim+k]*src2[i+k*dim];
        }    
}


/* 
 * matrix_multiplication - Your current working version of matrix_multiplication
 * IMPORTANT: This is the version you will be graded on
 */
char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst) 
{

    int i ,j ,k,idim=0,jdim,num;

    int acc0 , acc1  ;
   
    int *transpose = (int *) malloc(dim*dim*4) ;

    int *t2 = transpose ;

    num = dim>>5 ;

    for(i=0 ; i!=dim ; i++) {

        jdim = 0;

        for(j=0 ; j!=dim ;j++){

            transpose[i+jdim] = src2[idim+j] ;

            jdim+= dim ;

        }

        idim += dim;
    }

    if(dim == 32){

        for(i = 0; i != 32; i++){

        transpose = t2 ;

            for(j = 0; j != 32; j++) {

                acc0 = src[0] * transpose[0] ;
                acc1 = src[1] * transpose[1] ;
                acc0 += src[2] * transpose[2] ;
                acc1 += src[3] * transpose[3] ;
                acc0 += src[4] * transpose[4] ;
                acc1 += src[5] * transpose[5] ;
                acc0 += src[6] * transpose[6] ;
                acc1 += src[7] * transpose[7] ;
                acc0 += src[8] * transpose[8] ;
                acc1 += src[9] * transpose[9] ;
                acc0 += src[10] * transpose[10] ;
                acc1 += src[11] * transpose[11] ;
                acc0 += src[12] * transpose[12] ;
                acc1 += src[13] * transpose[13] ;
                acc0 += src[14] * transpose[14] ;
                acc1 += src[15] * transpose[15] ;
                acc0 += src[16] * transpose[16] ;
                acc1 += src[17] * transpose[17] ;
                acc0 += src[18] * transpose[18] ;
                acc1 += src[19] * transpose[19] ;
                acc0 += src[20] * transpose[20] ;
                acc1 += src[21] * transpose[21] ;
                acc0 += src[22] * transpose[22] ;
                acc1 += src[23] * transpose[23] ;
                acc0 += src[24] * transpose[24] ;
                acc1 += src[25] * transpose[25] ;
                acc0 += src[26] * transpose[26] ;
                acc1 += src[27] * transpose[27] ;
                acc0 += src[28] * transpose[28] ;
                acc1 += src[29] * transpose[29] ;
                acc0 += src[30] * transpose[30] ;
                acc1 += src[31] * transpose[31] ;

                transpose +=32 ;
                    
                *dst =acc0 +acc1 ;

                dst ++ ;
            }
   
            src+=32 ;
        }    


    }

    else if(dim == 64){

        for(i = 0; i != 64; i++){

            transpose = t2 ;

            for(j = 0; j != 64; j++) {

                acc0 = src[0] * transpose[0] ;
                acc1 = src[1] * transpose[1] ;
                acc0 += src[2] * transpose[2] ;
                acc1 += src[3] * transpose[3] ;
                acc0 += src[4] * transpose[4] ;
                acc1 += src[5] * transpose[5] ;
                acc0 += src[6] * transpose[6] ;
                acc1 += src[7] * transpose[7] ;
                acc0 += src[8] * transpose[8] ;
                acc1 += src[9] * transpose[9] ;
                acc0 += src[10] * transpose[10] ;
                acc1 += src[11] * transpose[11] ;
                acc0 += src[12] * transpose[12] ;
                acc1 += src[13] * transpose[13] ;
                acc0 += src[14] * transpose[14] ;
                acc1 += src[15] * transpose[15] ;
                acc0 += src[16] * transpose[16] ;
                acc1 += src[17] * transpose[17] ;
                acc0 += src[18] * transpose[18] ;
                acc1 += src[19] * transpose[19] ;
                acc0 += src[20] * transpose[20] ;
                acc1 += src[21] * transpose[21] ;
                acc0 += src[22] * transpose[22] ;
                acc1 += src[23] * transpose[23] ;
                acc0 += src[24] * transpose[24] ;
                acc1 += src[25] * transpose[25] ;
                acc0 += src[26] * transpose[26] ;
                acc1 += src[27] * transpose[27] ;
                acc0 += src[28] * transpose[28] ;
                acc1 += src[29] * transpose[29] ;
                acc0 += src[30] * transpose[30] ;
                acc1 += src[31] * transpose[31] ;
                acc0 += src[32] * transpose[32] ;
                acc1 += src[33] * transpose[33] ;
                acc0 += src[34] * transpose[34] ;
                acc1 += src[35] * transpose[35] ;
                acc0 += src[36] * transpose[36] ;
                acc1 += src[37] * transpose[37] ;
                acc0 += src[38] * transpose[38] ;
                acc1 += src[39] * transpose[39] ;
                acc0 += src[40] * transpose[40] ;
                acc1 += src[41] * transpose[41] ;
                acc0 += src[42] * transpose[42] ;
                acc1 += src[43] * transpose[43] ;
                acc0 += src[44] * transpose[44] ;
                acc1 += src[45] * transpose[45] ;
                acc0 += src[46] * transpose[46] ;
                acc1 += src[47] * transpose[47] ;
                acc0 += src[48] * transpose[48] ;
                acc1 += src[49] * transpose[49] ;
                acc0 += src[50] * transpose[50] ;
                acc1 += src[51] * transpose[51] ;
                acc0 += src[52] * transpose[52] ;
                acc1 += src[53] * transpose[53] ;
                acc0 += src[54] * transpose[54] ;
                acc1 += src[55] * transpose[55] ;
                acc0 += src[56] * transpose[56] ;
                acc1 += src[57] * transpose[57] ;
                acc0 += src[58] * transpose[58] ;
                acc1 += src[59] * transpose[59] ;
                acc0 += src[60] * transpose[60] ;
                acc1 += src[61] * transpose[61] ;
                acc0 += src[62] * transpose[62] ;
                acc1 += src[63] * transpose[63] ;

                transpose +=64 ;
                    
                *dst =acc0 +acc1 ;

                dst++ ;
            }
    
            src+=64 ;
        }         
    }

    else if(dim == 128){

		for(i = 0; i != 128; i++){

        transpose = t2 ;

            for(j = 0; j != 128; j++) {

                acc0 = src[0] * transpose[0] ;
                acc1 = src[1] * transpose[1] ;
                acc0 += src[2] * transpose[2] ;
                acc1 += src[3] * transpose[3] ;
                acc0 += src[4] * transpose[4] ;
                acc1 += src[5] * transpose[5] ;
                acc0 += src[6] * transpose[6] ;
                acc1 += src[7] * transpose[7] ;
                acc0 += src[8] * transpose[8] ;
                acc1 += src[9] * transpose[9] ;
                acc0 += src[10] * transpose[10] ;
                acc1 += src[11] * transpose[11] ;
                acc0 += src[12] * transpose[12] ;
                acc1 += src[13] * transpose[13] ;
                acc0 += src[14] * transpose[14] ;
                acc1 += src[15] * transpose[15] ;
                acc0 += src[16] * transpose[16] ;
                acc1 += src[17] * transpose[17] ;
                acc0 += src[18] * transpose[18] ;
                acc1 += src[19] * transpose[19] ;
                acc0 += src[20] * transpose[20] ;
                acc1 += src[21] * transpose[21] ;
                acc0 += src[22] * transpose[22] ;
                acc1 += src[23] * transpose[23] ;
                acc0 += src[24] * transpose[24] ;
                acc1 += src[25] * transpose[25] ;
                acc0 += src[26] * transpose[26] ;
                acc1 += src[27] * transpose[27] ;
                acc0 += src[28] * transpose[28] ;
                acc1 += src[29] * transpose[29] ;
                acc0 += src[30] * transpose[30] ;
                acc1 += src[31] * transpose[31] ;
                acc0 += src[32] * transpose[32] ;
                acc1 += src[33] * transpose[33] ;
                acc0 += src[34] * transpose[34] ;
                acc1 += src[35] * transpose[35] ;
                acc0 += src[36] * transpose[36] ;
                acc1 += src[37] * transpose[37] ;
                acc0 += src[38] * transpose[38] ;
                acc1 += src[39] * transpose[39] ;
                acc0 += src[40] * transpose[40] ;
                acc1 += src[41] * transpose[41] ;
                acc0 += src[42] * transpose[42] ;
                acc1 += src[43] * transpose[43] ;
                acc0 += src[44] * transpose[44] ;
                acc1 += src[45] * transpose[45] ;
                acc0 += src[46] * transpose[46] ;
                acc1 += src[47] * transpose[47] ;
                acc0 += src[48] * transpose[48] ;
                acc1 += src[49] * transpose[49] ;
                acc0 += src[50] * transpose[50] ;
                acc1 += src[51] * transpose[51] ;
                acc0 += src[52] * transpose[52] ;
                acc1 += src[53] * transpose[53] ;
                acc0 += src[54] * transpose[54] ;
                acc1 += src[55] * transpose[55] ;
                acc0 += src[56] * transpose[56] ;
                acc1 += src[57] * transpose[57] ;
                acc0 += src[58] * transpose[58] ;
                acc1 += src[59] * transpose[59] ;
                acc0 += src[60] * transpose[60] ;
                acc1 += src[61] * transpose[61] ;
                acc0 += src[62] * transpose[62] ;
                acc1 += src[63] * transpose[63] ;

                acc0 += src[64] * transpose[64] ;
                acc1 += src[65] * transpose[65] ;
                acc0 += src[66] * transpose[66] ;
                acc1 += src[67] * transpose[67] ;
                acc0 += src[68] * transpose[68] ;
                acc1 += src[69] * transpose[69] ;
                acc0 += src[70] * transpose[70] ;
                acc1 += src[71] * transpose[71] ;
                acc0 += src[72] * transpose[72] ;
                acc1 += src[73] * transpose[73] ;
                acc0 += src[74] * transpose[74] ;
                acc1 += src[75] * transpose[75] ;
                acc0 += src[76] * transpose[76] ;
                acc1 += src[77] * transpose[77] ;
                acc0 += src[78] * transpose[78] ;
                acc1 += src[79] * transpose[79] ;
                acc0 += src[80] * transpose[80] ;
                acc1 += src[81] * transpose[81] ;
                acc0 += src[82] * transpose[82] ;
                acc1 += src[83] * transpose[83] ;
                acc0 += src[84] * transpose[84] ;
                acc1 += src[85] * transpose[85] ;
                acc0 += src[86] * transpose[86] ;
                acc1 += src[87] * transpose[87] ;
                acc0 += src[88] * transpose[88] ;
                acc1 += src[89] * transpose[89] ;
                acc0 += src[90] * transpose[90] ;
                acc1 += src[91] * transpose[91] ;
                acc0 += src[92] * transpose[92] ;
                acc1 += src[93] * transpose[93] ;
                acc0 += src[94] * transpose[94] ;
                acc1 += src[95] * transpose[95] ;
                acc0 += src[96] * transpose[96] ;
                acc1 += src[97] * transpose[97] ;
                acc0 += src[98] * transpose[98] ;
                acc1 += src[99] * transpose[99] ;
                acc0 += src[100] * transpose[100] ;
                acc1 += src[101] * transpose[101] ;
                acc0 += src[102] * transpose[102] ;
                acc1 += src[103] * transpose[103] ;
                acc0 += src[104] * transpose[104] ;
                acc1 += src[105] * transpose[105] ;
                acc0 += src[106] * transpose[106] ;
                acc1 += src[107] * transpose[107] ;
                acc0 += src[108] * transpose[108] ;
                acc1 += src[109] * transpose[109] ;
                acc0 += src[110] * transpose[110] ;
                acc1 += src[111] * transpose[111] ;
                acc0 += src[112] * transpose[112] ;
                acc1 += src[113] * transpose[113] ;
                acc0 += src[114] * transpose[114] ;
                acc1 += src[115] * transpose[115] ;
                acc0 += src[116] * transpose[116] ;
                acc1 += src[117] * transpose[117] ;
                acc0 += src[118] * transpose[118] ;
                acc1 += src[119] * transpose[119] ;
                acc0 += src[120] * transpose[120] ;
                acc1 += src[121] * transpose[121] ;
                acc0 += src[122] * transpose[122] ;
                acc1 += src[123] * transpose[123] ;
                acc0 += src[124] * transpose[124] ;
                acc1 += src[125] * transpose[125] ;
                acc0 += src[126] * transpose[126] ;
                acc1 += src[127] * transpose[127] ;

                transpose +=128 ;
                    
                *dst =acc0 +acc1 ;

                dst++ ;
            }
    
            src+=128 ;
        }

    } 
    else{

    for(i = 0; i != dim; i++){

        transpose = t2 ;

        for(j = 0; j != dim; j++) {

            acc0 = 0 ;
            acc1 = 0 ;

            for(k = 0; k != num; k++){ 

                acc0 += src[0] * transpose[0] ;
                acc1 += src[1] * transpose[1] ;
                acc0 += src[2] * transpose[2] ;
                acc1 += src[3] * transpose[3] ;
                acc0 += src[4] * transpose[4] ;
                acc1 += src[5] * transpose[5] ;
                acc0 += src[6] * transpose[6] ;
                acc1 += src[7] * transpose[7] ;
                acc0 += src[8] * transpose[8] ;
                acc1 += src[9] * transpose[9] ;
                acc0 += src[10] * transpose[10] ;
                acc1 += src[11] * transpose[11] ;
                acc0 += src[12] * transpose[12] ;
                acc1 += src[13] * transpose[13] ;
                acc0 += src[14] * transpose[14] ;
                acc1 += src[15] * transpose[15] ;
                acc0 += src[16] * transpose[16] ;
                acc1 += src[17] * transpose[17] ;
                acc0 += src[18] * transpose[18] ;
                acc1 += src[19] * transpose[19] ;
                acc0 += src[20] * transpose[20] ;
                acc1 += src[21] * transpose[21] ;
                acc0 += src[22] * transpose[22] ;
                acc1 += src[23] * transpose[23] ;
                acc0 += src[24] * transpose[24] ;
                acc1 += src[25] * transpose[25] ;
                acc0 += src[26] * transpose[26] ;
                acc1 += src[27] * transpose[27] ;
                acc0 += src[28] * transpose[28] ;
                acc1 += src[29] * transpose[29] ;
                acc0 += src[30] * transpose[30] ;
                acc1 += src[31] * transpose[31] ;


                src+=32 ;
                transpose +=32 ;
            }

            src -= dim ;

            *dst =acc0 +acc1 ;

            dst++ ;
        }

        src += dim ;    
    }

    }    

}

/*********************************************************************
 * register_matrix_multiplication_functions - Register all of your different versions
 *     of the matrix multiplication  with the driver by calling the
 *     add_matrix_multiplication_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_matrix_multiplication_functions() {
    add_matrix_multiplication_function(&naive_matrix_multiplication, naive_matrix_multiplication_descr);   
    add_matrix_multiplication_function(&matrix_multiplication, matrix_multiplication_descr);
    /* ... Register additional test functions here */
}
