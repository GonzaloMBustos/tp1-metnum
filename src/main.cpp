#include "matrix.h"
#include "fileHandler.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <chrono>

using namespace std;

void basicTesting()
{
    SparseMatrixReloaded sm(2, 2, 0.0001);

    sm[1][1] = 2;
    sm[1][2] = 0;
    sm[2][1] = 0;
    sm[2][2] = 2;

    cout << "--------------Matriz 1 de 2x2--------------" << endl;
    sm.showMatrix(cout);

    SparseMatrixReloaded sm2(2, 2, 0.0001);
    sm2[1][1] = 3;
    sm2[1][2] = 0;
    sm2[2][1] = 0;
    sm2[2][2] = 2;

    cout << "--------------Matriz 2 de 2x2--------------" << endl;
    sm2.showMatrix(cout);

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm *sm2;

    sm.showMatrix(cout);

    SparseMatrixReloaded sm3b31(3, 3, 0.0001);
    sm3b31[1][1] = 2;
    sm3b31[1][2] = 1;
    sm3b31[1][3] = 0;
    sm3b31[2][1] = 1;
    sm3b31[2][2] = 1;
    sm3b31[2][3] = 3;
    sm3b31[3][1] = 0;
    sm3b31[3][2] = 0;
    sm3b31[3][3] = 1;

    cout << "==============Matriz 1 de 3x3==============" << endl;
    sm3b31.showMatrix(cout);
    ;

    SparseMatrixReloaded sm3b32(3, 3, 0.0001);
    sm3b32[1][1] = 2;
    sm3b32[1][2] = 1;
    sm3b32[1][3] = 0;
    sm3b32[2][1] = 1;
    sm3b32[2][2] = 1;
    sm3b32[2][3] = 3;
    sm3b32[3][1] = 0;
    sm3b32[3][2] = 0;
    sm3b32[3][3] = 1;

    cout << "==============Matriz 2 de 3x3==============" << endl;
    sm3b32.showMatrix(cout);
    ;

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm3b31 *sm3b32;
    sm3b31.showMatrix(cout);

    SparseMatrixReloaded sm4b41(4, 4, 0.0001);
    sm4b41[1][1] = 2;
    sm4b41[1][2] = 1;
    sm4b41[1][3] = 0;
    sm4b41[1][4] = 1;
    sm4b41[2][1] = 1;
    sm4b41[2][2] = 1;
    sm4b41[2][3] = 2;
    sm4b41[2][4] = 3;
    sm4b41[3][1] = 0;
    sm4b41[3][2] = 0;
    sm4b41[3][3] = 1;
    sm4b41[3][4] = 1;
    sm4b41[4][1] = 1;
    sm4b41[4][2] = 0;
    sm4b41[4][3] = 3;
    sm4b41[4][4] = 1;

    cout << "==============Matriz 1 de 4x4==============" << endl;
    sm4b41.showMatrix(cout);

    SparseMatrixReloaded sm4b42(4, 4, 0.0001);
    sm4b42[1][1] = 2;
    sm4b42[1][2] = 1;
    sm4b42[1][3] = 0;
    sm4b42[1][4] = 2;
    sm4b42[2][1] = 1;
    sm4b42[2][2] = 1;
    sm4b42[2][3] = 3;
    sm4b42[2][4] = 3;
    sm4b42[3][1] = 0;
    sm4b42[3][2] = 4;
    sm4b42[3][3] = 1;
    sm4b42[3][4] = 1;
    sm4b42[4][1] = 0;
    sm4b42[4][2] = 1;
    sm4b42[4][3] = 2;
    sm4b42[4][4] = 1;

    cout << "==============Matriz 2 de 4x4==============" << endl;
    sm4b42.showMatrix(cout);

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm4b41 *sm4b42;
    sm4b41.showMatrix(cout);
    // vector<double> b = {0,0,0,0};
    // sm4b41.EG(b);

    SparseMatrixReloaded sm2b2(2, 2, 0.0001);
    sm2b2[1][1] = 1;
    sm2b2[1][2] = 0;
    sm2b2[2][1] = 0;
    sm2b2[2][2] = 1;

    cout << "--------------Matriz 1 de 2x2--------------" << endl;
    sm2b2.showMatrix(cout);

    SparseMatrixReloaded sm2b22(2, 2, 0.0001);
    sm2b22[1][1] = 2;
    sm2b22[1][2] = 1;
    sm2b22[2][1] = 1;
    sm2b22[2][2] = 4;

    cout << "--------------Matriz 2 de 2x2--------------" << endl;
    sm2b22.showMatrix(cout);

    vector<double> b = {0, 0};
    sm2b22.EG(b);
    sm2b22.showMatrix(cout);

    cout << "==============Matrix sum===================" << endl;
    sm2b2 + sm2b22;
    sm2b2.showMatrix(cout);

    cout << "==============Matriz de 4x4===================" << endl;
    sm4b42[1][1] = 1;
    sm4b42[1][2] = 2;
    sm4b42[1][3] = 1;
    sm4b42[1][4] = -1;
    sm4b42[2][1] = 3;
    sm4b42[2][2] = 2;
    sm4b42[2][3] = 4;
    sm4b42[2][4] = 4;
    sm4b42[3][1] = 4;
    sm4b42[3][2] = 4;
    sm4b42[3][3] = 3;
    sm4b42[3][4] = 4;
    sm4b42[4][1] = 2;
    sm4b42[4][2] = 0;
    sm4b42[4][3] = 1;
    sm4b42[4][4] = 5;
    sm4b42.showMatrix(cout);

    vector<double> b2 = {5, 16, 22, 15};
    cout << "============== B original ===================" << endl;
    cout << "[" << b2[0] << ", " << b2[1] << ", " << b2[2] << ", " << b2[3] << "]" << endl;
    cout << "==============EG===================" << endl;
    sm4b42.EG(b2);
    sm4b42.showMatrix(cout);
    cout << "============== B post EG ===================" << endl;
    cout << "[" << b2[0] << ", " << b2[1] << ", " << b2[2] << ", " << b2[3] << "]" << endl;
    cout << "==============BackSubst===================" << endl;
    vector<double> rta = sm4b42.backwardSubstitution(b2);
    cout << "[" << rta[0] << ", " << rta[1] << ", " << rta[2] << ", " << rta[3] << "]" << endl;

    cout << "==============Multiply by scalar===================" << endl;
    sm4b42.multiplyByScalar(2);
    sm4b42.showMatrix(cout);
}

template <typename T>
T buildIdentity(unsigned int n, double epsilon)
{
    T identity(n, n, epsilon);
    for (unsigned int i = 0; i < n; i++)
    {
        identity.setValue(i, i, 1);
    }
    return identity;
}

template <typename T>
T buildD(T& W, double epsilon)
{
    unsigned int n = W.Columns();
    T D(n, n, epsilon);
    vector<double> cjs = W.sumColumns();
    for (unsigned int i = 0; i < n; i++)
    {
        if (abs(cjs[i]) > W.Epsilon())
        {
            D.setValue(i, i, (1 / cjs[i]));
        }
    }
    return D;
}

template <typename T>
vector<double> PageRank(T& I, T& W, T& D, double p, vector<double>& e)
{
    W *D;
    W.multiplyByScalar((-1 * p));
    W + I;
    W.EG(e);
    vector<double> x = W.backwardSubstitution(e);
    return x;
}

void NormalizeResult(vector<double>& x)
{
    double sum = 0;
    for (long unsigned int i = 0; i < x.size(); i++)
    {
        sum += x[i];
    }
    for (long unsigned int i = 0; i < x.size(); i++)
    {
        x[i] = x[i] / sum;
    }
}

template <typename T>
vector<double> performExperiment(vector<tuple<unsigned int, unsigned int>> contents, double p, double epsilon, bool doOutput){

    T W(contents, epsilon);
    if (doOutput) {
        cout << "===== Matriz Input ====" << endl;
        W.showMatrix(cout);
    }
    
    T identity = buildIdentity<T>(get<0>(contents[0]), epsilon);
    if (doOutput) {
        cout << "===== Matriz Identidad ====" << endl;
        identity.showMatrix(cout);
    }
    
    T D = buildD<T>(W, epsilon);
    if (doOutput) {
        cout << "===== Matriz D ====" << endl;
        D.showMatrix(cout);
    }
    
    vector<double> e(get<0>(contents[0]), 1);

    vector<double> res = PageRank<T>(identity, W, D, p, e);
    
    if (doOutput) {
        cout << "===== PageRank result ====" << endl;
        cout << "[";
        for (long unsigned int i = 0; i < res.size(); i++)
        {
            cout << res[i] << ", ";
        }
        cout << "]" << endl;
    }

    NormalizeResult(res);
    
    if (doOutput) {
        cout << "===== Normalized result ====" << endl;
        cout << "[";
        for (long unsigned int i = 0; i < res.size(); i++)
        {
            cout << res[i] << ", ";
        }
        cout << "]" << endl;
    }
    return res;
}

template<typename T>
void performTest(unsigned int matrix_size, unsigned int iterations, unsigned int warmup_iterations, unsigned int fill, float p, float epsilon){
    cout << "===================================" << endl;
    cout << "Matrix size: " << matrix_size << "x" << matrix_size << endl;
    cout << "Fill: " << fill << "%" << endl;
    cout << "P: " << p << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << "Warmup iterations: " << warmup_iterations << endl;
    cout << "Metered iterations: " << iterations << endl;
    cout << "===================================" << endl;

    cout << "Building contents..";    
    srand(time(NULL));
    unsigned int threshold = (RAND_MAX / 100) * fill;
    vector<tuple<unsigned int, unsigned int>> contents;
    contents.emplace_back(matrix_size, matrix_size);
    for(unsigned int i = 1; i < matrix_size; i++){
        for(unsigned int j = 1; j < matrix_size; j++){
            unsigned int r = rand();
            if (r < threshold){
                contents.emplace_back(i, j);
            }
        }
    }
    
    cout << " DONE!" << endl << "Warming up..";
    for(unsigned int i = 0; i < warmup_iterations; i++){
        performExperiment<T>(contents, p, epsilon, false);
    }
    
    vector<unsigned long long> times = vector<unsigned long long>();
    unsigned long long total = 0;
    cout << " DONE!" << endl << "Starting metered iterations..";
    for(unsigned int i = 0; i < iterations; i++){
        auto start = std::chrono::high_resolution_clock::now();
        
        performExperiment<T>(contents, p, epsilon, false);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        unsigned long long micros = duration.count();
        total += micros;
        times.emplace_back(micros);
    }

    cout << " DONE!" << endl;

    cout << "Elapsed time: " << total/1000 << "ms" << endl;
    cout << "Avg time: " << ((double)total)/times.size()/1000 << "ms" << endl;
    cout << "=============================================" << endl;
    cout << "==TIME VALUES==" << endl;
    for (unsigned int i = 0; i < times.size(); i++){
        cout << times[i] << endl;
    }
}

// MAIN:
int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        if (argc == 8 && !strcmp(argv[1],"test")){
            cout << "[TESTING]" << endl;
            unsigned int size = atoi(argv[2]);
            unsigned int iterations = atoi(argv[3]);
            unsigned int warmup_iterations = atoi(argv[4]);
            unsigned int fill = atoi(argv[5]);
            float p = atof(argv[6]);
            float epsilon = atof(argv[7]);
            performTest<SparseMatrixReloaded>(size, iterations, warmup_iterations, fill, p, epsilon);

        }else{
            cout << argc << endl;
            basicTesting();
            cout << "Parametros invalido (especificar 'p' y archivo de entrada), por lo tanto se corrieron tests de debug" << endl;
        }
        return 0;
    }

    double p = atof(argv[2]);
    cout << "P = " << p << endl;
    // SparseMatrix testMatrix = SparseMatrix(2, 2);
    // testMatrix[0][0] = 1;
    // testMatrix[0][1] = 2;
    // testMatrix[1][0] = 3;
    // testMatrix[1][1] = 4;

    // cout << "Size: " << testMatrix.Columns() << " x " << testMatrix.Rows() << endl;

    // testMatrix.showMatrix(cout);
    cout << "Archivo: " << argv[1] << endl;
    FileHandler myFile = FileHandler(argv[1]);

    vector<tuple<unsigned int, unsigned int>> contents = myFile.readContents();
    vector<double> result = performExperiment<SparseMatrixReloaded>(contents, p, 0.00000000001, true);    // Con este epsilon los resultados coinciden con los de la catedra
    myFile.writeOutResult(result, p);
    return 0;
    /*
    cout << "===== Matriz Input ====" << endl;

    SparseMatrixReloaded W(contents, 0.0001);
    W.showMatrix(cout);

    cout << "===== Matriz Identidad ====" << endl;
    SparseMatrixReloaded identity = buildIdentity(get<0>(contents[0]));
    identity.showMatrix(cout);

    cout << "===== Matriz D ====" << endl;
    SparseMatrixReloaded D = buildD<SparseMatrixReloaded>(W);
    D.showMatrix(cout);

    vector<double> e(get<0>(contents[0]), 1);

    vector<double> res = PageRank(identity, W, D, p, e);
    cout << "===== PageRank result ====" << endl;
    cout << "[";
    for (long unsigned int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ", ";
    }
    cout << "]" << endl;

    NormalizeResult(&res);
    cout << "===== Normalized result ====" << endl;
    cout << "[";
    for (long unsigned int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ", ";
    }
    cout << "]" << endl;

    myFile.writeOutResult(res);

    return 0;
    */
}
