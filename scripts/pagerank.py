import numpy as np
import argparse
from tpRunner import TpRunner
from os import path


def back_substitution(a, b):
    n = len(a)
    x = [0]*n
    for i in range(n-1, -1, -1):
        for j in range(i+1, n):
            print("B%d = %f - %f * % f" % (i, b[i], a[i, j], x[j]))
            b[i] = b[i] - a[i, j] * x[j]
        x[i] = b[i] / a[i, i]
        print("X%d = %f" % (i, x[i]))
    return x


def eliminacion_gaussiana(a_matrix, b=None):
    if b is None:
        b = np.zeros(len(a_matrix))

    print("======MATRIZ INICIAL======")
    print(a_matrix)

    print("======VECTOR B======")
    print(b)

    print("======MATRIZ EXTENDIDA======")
    a_matrix = np.column_stack((a_matrix, b))
    print(a_matrix)

    for i in range(len(a_matrix)):
        for j in range(i+1, len(a_matrix)):
            coef = a_matrix[j][i] / a_matrix[i][i]
            print("\n============================")
            print('F%d = F%d - %.2f*F%d' % (j,j,coef, i))
            a_matrix[j] = a_matrix[j] - coef*a_matrix[i]
            # for (x, y), value in np.ndenumerate(a_matrix):
            #     a_matrix[x][y] = a_matrix[x][y] if abs(a_matrix[x][y]) > 0.00001 else 0

    triangulated = a_matrix[:, :-1]
    result = a_matrix[:, -1]
    return triangulated, result


def load_matrix_from_file(filePath):
    if not path.exists(filePath):
        raise ValueError('El archivo no existe')

    with open(filePath, 'r') as f:
        content = f.read()
        if not content:
            raise ValueError('Contenido invalido')
        values = content.strip().split('\n')
        dimension = int(values[0])
        if int(dimension) <= 0:
            raise ValueError('La dimension es menor o igual que 0')

        w_matrix = np.zeros([dimension, dimension])

        for value in values[2:]:
            n, m = value.split(' ')
            w_matrix[int(m)-1][int(n)-1] += 1

        return w_matrix


def calculate_page_rank(w_matrix, p):
    print('\n==Matriz W de %dx%d==' % (len(w_matrix), len(w_matrix)))
    print(w_matrix)

    w_columns = w_matrix.sum(axis=0)
    print('\n==Suma de sus columnas==')
    print(w_columns)

    d_matrix = np.diag([1 / c if c > 0 else 0 for c in w_columns])
    print('\n==Matriz D==')
    print(d_matrix)

    i_matrix = np.identity(len(w_columns))
    print('\n==Matriz I==')
    print(i_matrix)

    temp_matrix = i_matrix - p*w_matrix@d_matrix
    print('\n==Matriz I-p*WD==')
    print(temp_matrix)

    b_vector = np.ones(len(temp_matrix)).transpose()

    solution_numpy = np.linalg.solve(temp_matrix, b_vector)

    suma = sum(solution_numpy)
    solution_numpy_n = np.copy(solution_numpy)
    if suma != 0:
        solution_numpy_n = [float("{:.6f}".format(s/suma)) for s in solution_numpy]

    '''triangulada, b_t = eliminacion_gaussiana(temp_matrix, b_vector)
    print('\n==Matriz Triangulada (Manual)==')
    print(triangulada)
    print('\n==Nuevo vector B==')
    print(b_t)

    sol = back_substitution(triangulada, b_t)
    print('\n==Solucion NO normalizada (Manual)==')
    print(sol)
    '''
    print('\n==Solucion NO normalizada (Numpy)==')
    print(solution_numpy)

    '''suma = sum(sol)
    if suma != 0:
        sol = [float("{:.6f}".format(s/suma)) for s in sol]

    print('\n==Solucion normalizada (Manual)==')
    print(sol)
    '''
    print('\n==Solucion normalizada (Numpy)==')
    print(solution_numpy_n)

    z_vector = np.array([(1-p)/len(w_matrix) if c != 0 else 1/len(w_matrix) for c in w_columns])
    e_vector = np.ones(len(w_matrix))
    a_matrix = p * w_matrix@d_matrix + np.outer(e_vector, z_vector)

    print('\n==ERROR (Numpy)==')
    print(np.sqrt(sum([a**2 for a in (a_matrix@solution_numpy_n) - solution_numpy_n])))

    return solution_numpy_n


def run_with_p(file, p):
    w = load_matrix_from_file(file)
    py_result = calculate_page_rank(w, p)
    TpRunner('../src/tp').run([file, str(p)])

    print("\n==Solucion de C++==")
    with open(args.file + '.out') as f:
        c_result = [float(n) for n in (f.read().split('\n')[1:])]
        print(c_result)

    d = zip(py_result, c_result)  # [(p1, c1), (p2, c2), ...... (pn, cn)]
    print(sum([abs(c[1] - c[0]) for c in d]))
    return c_result[-2] / c_result[-1]

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Corre el experimento de PageRank utilizando numpy')
    parser.add_argument('-f', '--file', help='Path al archivo de test', type=str)
    parser.add_argument('-p', help='El p a utilizar', type=float, required=True)
    args = parser.parse_args()

    if args.file is None:
        print("Falta el path al archivo")
        exit()

    w = load_matrix_from_file(args.file)
    py_result = calculate_page_rank(w, args.p)
    runner = TpRunner('../src/tp')
    runner.run([args.file, str(args.p)])

    print("\n==Solucion de C++==")
    with open(args.file + '.out') as f:
        c_result = [float(n) for n in (f.read().split('\n')[1:])]
        print(c_result)

    error_c = runner.output.split("ERROR: ")[1].split('\n')[0]
    print("\n==Error de C++==\n %s" % error_c)

    print("\n==Diferencia entre resultados C++ y numpy==")
    d = zip(py_result, c_result)  # [(p1, c1), (p2, c2), ...... (pn, cn)]
    print(sum([abs(c[1] - c[0]) for c in d]))


