#include <stddef.h>
#include <cstdio>
#include <math.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif // NN_ASSERT

class Mat{
    public:
        size_t rows;
        size_t cols;
        float *es;

        Mat(unsigned new_rows, unsigned new_cols);
        ~Mat();
        Mat& operator=(const Mat& other);
        Mat(const Mat& other);
        Mat row(size_t row); //returns row
        Mat copy(); //returns copy
        Mat dot(Mat &m, size_t dr, size_t dc);   // returns dot
        void sum(Mat &m);          //adds m to self
        void print(const char *name);
        void print();
        void rand(float low, float high);
        void fill(float f);
        void sig(); //applies sigmoid to self
        float* at(size_t row, size_t col);
};

float rand_float();
float sigmoid(float x);


float rand_float(){
    return (float)rand() / (float)RAND_MAX;
}

float sigmoid(float x){
    return 1.f/(1.f + expf(-x));
}

float* Mat::at(size_t row, size_t col){
    return &es[row*cols + col];
}


void Mat::sig(){
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            *(at(i, j)) = sigmoid(*at(i, j));
        }
    }
}

Mat::Mat(unsigned new_rows, unsigned new_cols) {
    rows = new_rows;
    cols = new_cols;
    es   = (float*)NN_MALLOC(sizeof(*es) * rows * cols);
    NN_ASSERT(es != NULL);
}

Mat Mat::dot(Mat &m, size_t dr, size_t dc) {
    NN_ASSERT(cols == m.rows);
    NN_ASSERT(dr == rows);
    NN_ASSERT(dc == m.cols);

    Mat d(dr, dc);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < m.cols; j++) {
            *d.at(i, j) = 0.f;
            for (unsigned k = 0; k < cols; k++) {
                *d.at(i, j) += *at(i, k) * *m.at(k, j);
            }
        }
    }

    return d;
}

void Mat::sum(Mat &m) {
    NN_ASSERT(rows == m.rows);
    NN_ASSERT(cols == m.cols);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            *at(i, j) += *m.at(i, j);
        }
    }
}

Mat Mat::row(size_t row){
    Mat m(1, cols);
    for (size_t j = 0; j < cols; j++){
        *m.at(0, j) = *at(row, j);
    }
    return m;
}

Mat Mat::copy(){
    Mat c(rows, cols);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            *c.at(i, j) = *at(i, j);
        }
    }

    return c;
}

void Mat::print(const char *name){
    printf("%s = [\n", name);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            printf("%f      ", *at(i, j));
        }
        printf("\n");
    }
    printf("]\n\n");
}

void Mat::print(){
    printf("m = [\n");
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            printf("%f ", *at(i, j));
        }
        printf("\n");
    }
    printf("]\n\n");
}

void Mat::rand(float low, float high){
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            *at(i, j) = rand_float()*(high - low) + low;
        }
    }
}

void Mat::fill(float f){
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            *at(i, j) = f;
        }
    }
}

Mat::~Mat() {
    free(es);
}

Mat& Mat::operator=(const Mat& other){
    if(this == &other) return *this;

    free(es);

    rows = other.rows;
    cols = other.cols;

    es = (float*)NN_MALLOC(sizeof(*es) * rows * cols);

    for(size_t i = 0; i < rows * cols; i++){
        es[i] = other.es[i];
    }

    return *this;
}

Mat::Mat(const Mat& other) {
    rows = other.rows;
    cols = other.cols;
    es = (float*)NN_MALLOC(sizeof(*es) * rows * cols);
    NN_ASSERT(es != nullptr);
    for (size_t i = 0; i < rows * cols; i++) {
        es[i] = other.es[i];
    }
}