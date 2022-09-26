#include "matrix.h"
#include "fileHandler.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <chrono>
#include <cmath>

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

double kahanSum(vector<double> &fa)
{
    double sum = 0.0;
    double c = 0.0;
 
    for(double f : fa){
        double y = f - c;
        double t = sum + y;
         
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
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
T buildD(T &W, double epsilon)
{
    unsigned int n = W.Columns();
    T D(n, n, epsilon);
    vector<double> cjs = W.sumColumns();
    for (unsigned int i = 0; i < n; i++)
    {
        if (cjs[i] > 0 && 1 / abs(cjs[i]) > W.Epsilon())
        {
            D.setValue(i, i, (1 / cjs[i]));
        }
    }
    return D;
}

template <typename T>
T buildEZ(T &W, double p, double epsilon)
{
    unsigned int n = W.Columns();
    vector<double> cjs = W.sumColumns();
    T E(n, 1, epsilon);
    T Z(1, n, epsilon);
    for (unsigned int i = 0; i < n; i++)
    {
        if (cjs[i] > 0 && ((1-p) / n) > W.Epsilon())
        {
            Z.setValue(0, i, ((1-p) / n) );
        }else if (cjs[i] == 0 && (double(1)/n) > W.Epsilon()){
            Z.setValue(0, i, (double(1)/n) );
        }
        E.setValue(i, 0, 1);
    }
    E*Z;
    return E;
}

template <typename T>
vector<double> PageRank(T &I, T &W, T &D, double p, vector<double> &e)
{
    W *D;
    W.multiplyByScalar((-1 * p));
    W + I;
    W.EG(e);
    vector<double> x = W.backwardSubstitution(e);
    return x;
}

void NormalizeResult(vector<double> &x)
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
vector<double> performExperiment(vector<tuple<unsigned int, unsigned int>> contents, double p, double epsilon, bool doOutput, bool doErrorCheck)
{

    T W(contents, epsilon);
    if (doOutput)
    {
        cout << "===== Matriz Input ====" << endl;
        W.showMatrix(cout);
    }

    T identity = buildIdentity<T>(get<0>(contents[0]), epsilon);
    if (doOutput)
    {
        cout << "===== Matriz Identidad ====" << endl;
        identity.showMatrix(cout);
    }

    T D = buildD<T>(W, epsilon);
    if (doOutput)
    {
        cout << "===== Matriz D ====" << endl;
        D.showMatrix(cout);
    }

    vector<double> e(get<0>(contents[0]), 1);

    vector<double> res = PageRank<T>(identity, W, D, p, e);

    if (doOutput)
    {
        cout << "===== PageRank result ====" << endl;
        cout << "[";
        for (long unsigned int i = 0; i < res.size(); i++)
        {
            cout << res[i] << ", ";
        }
        cout << "]" << endl;
    }

    NormalizeResult(res);

    if (doOutput)
    {
        cout << "===== Normalized result ====" << endl;
        cout << "[";
        for (long unsigned int i = 0; i < res.size(); i++)
        {
            cout << res[i] << ", ";
        }
        cout << "]" << endl;
    }

    //==========CALCULO ERROR |Ax - x|==========
    if (doErrorCheck)
    {
        W = T(contents, epsilon);
        T EZ = buildEZ<T>(W, p, epsilon);
        W.multiplyByScalar(p);
        W * D;
        W + EZ;
        

        T resMatrix(res.size(), 1, epsilon);
        for(unsigned int i = 0; i < res.size(); i++){
            resMatrix[i+1][1] = res[i];
        }
        cout << endl << "=== Matriz A: ===" << endl;
        W.showMatrix(cout);
        cout << "=== Vector X': ===" << endl;
        resMatrix.showMatrix(cout);
        cout << "=== A*X': ===" << endl;
        W * resMatrix;
        W.showMatrix(cout);
        //cout << "=== A*X' - X': ===" << endl;
        //resMatrix.multiplyByScalar(-1);
        //W + resMatrix;
        //W.showMatrix(cout);

        // NORMA 2
        vector<double> results(W.Rows(), 0);
        vector<double> results2(W.Rows(), 0);
        double acum = 0;
        double acum2 = 0;
        for(unsigned int i = 0; i < W.Rows(); i++){
            results[i] = pow(double(W[i+1][1]), 2);
            results2[i] = pow(resMatrix[i+1][1], 2);
        }
        acum = kahanSum(results);
        acum2 = kahanSum(results2);

        cout << "ERROR: " << abs(sqrt(acum) - sqrt(acum2)) << endl;
    }

    return res;
}

template <typename T>
void performTest(unsigned int matrix_size, unsigned int iterations, unsigned int warmup_iterations, unsigned int fill, float p, float epsilon)
{
    bool doErrorCheck = (iterations == 1 && warmup_iterations <= 1);
    cout << "===================================" << endl;
    cout << "Matrix size: " << matrix_size << "x" << matrix_size << endl;
    cout << "Fill: " << fill << "%" << endl;
    cout << "P: " << p << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << "Warmup iterations: " << warmup_iterations << endl;
    cout << "Metered iterations: " << iterations << endl;
    cout << "Error check: " << doErrorCheck << endl;
    cout << "===================================" << endl;

    cout << "Building contents..";
    srand(time(NULL));
    unsigned int threshold = (RAND_MAX / 100) * fill;
    vector<tuple<unsigned int, unsigned int>> contents;
    contents.emplace_back(matrix_size, matrix_size);

    unsigned int co = 0;
    for (unsigned int i = 0; i < matrix_size; i++)
    {
        for (unsigned int j = 0; j < matrix_size; j++)
        {
            unsigned int r = rand();
            if (r < threshold)
            {
                contents.emplace_back(i + 1, j + 1);
                co++;
            }
        }
    }

    cout << " DONE!" << endl
         << "Final fill: " << (double)co / (matrix_size * matrix_size) * 100 << "%" << endl
         << "Warming up..";
    for (unsigned int i = 0; i < warmup_iterations; i++)
    {
        performExperiment<T>(contents, p, epsilon, false, doErrorCheck);
    }

    vector<unsigned long long> times = vector<unsigned long long>();
    unsigned long long total = 0;
    cout << " DONE!" << endl
         << "Starting metered iterations..";
    vector<double> res;
    for (unsigned int i = 0; i < iterations; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        res = performExperiment<T>(contents, p, epsilon, false, doErrorCheck);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        unsigned long long micros = duration.count();
        total += micros;
        times.emplace_back(micros);
    }

    cout << " DONE!" << endl;

    cout << "Elapsed time: " << total / 1000 << "ms" << endl;
    cout << "Avg time: " << ((double)total) / times.size() / 1000 << "ms" << endl;
    cout << "=============================================" << endl;
    cout << "==TIME VALUES==" << endl;
    for (unsigned int i = 0; i < times.size(); i++)
    {
        cout << times[i] << endl;
    }
}

// MAIN:
int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        if (argc == 8 && !strcmp(argv[1], "test"))
        {
            cout << "[TESTING]" << endl;
            unsigned int size = atoi(argv[2]);
            unsigned int iterations = atoi(argv[3]);
            unsigned int warmup_iterations = atoi(argv[4]);
            unsigned int fill = atoi(argv[5]);
            float p = atof(argv[6]);
            float epsilon = atof(argv[7]);
            performTest<SparseMatrixReloaded>(size, iterations, warmup_iterations, fill, p, epsilon);
        }
        else
        {
            cout << argc << endl;
            basicTesting();
            cout << "Parametros invalido (especificar 'p' y archivo de entrada), por lo tanto se corrieron tests de debug" << endl;
        }
        return 0;
    }

    double p = atof(argv[2]);
    cout << "P = " << p << endl;

    cout << "Archivo: " << argv[1] << endl;
    FileHandler myFile = FileHandler(argv[1]);

    vector<tuple<unsigned int, unsigned int>> contents = myFile.readContents();
    vector<double> result = performExperiment<SparseMatrixReloaded>(contents, p, 0.00000000001, true, false); // Con este epsilon los resultados coinciden con los de la catedra
    myFile.writeOutResult(result, p);
    return 0;
}
