/* Tomado de https://gist.github.com/sowmyagowri/f4bde25b3ebba1e6e9930afbdf31a25b */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <chrono>

#define num_threads 27

using namespace std;
using namespace std::chrono;
typedef struct {
    int row; 
    int col;
    int (* board)[9];
} parameters;
int result[num_threads] = {0};
void *check_grid(void *params);
void *check_rows(void *params);
void *check_cols(void *params);
int sudoku_checker(int sudoku[9][9]);
int main(void) {
    int sudoku[9][9] =
    {
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 7, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
     };
    steady_clock::time_point start_time_single_thread = steady_clock::now();
    if(sudoku_checker(sudoku))
        printf("Con un solo hilo: Solución INCORRECTA del sudoku\n");
    else
        printf("Con un solo hilo: Solución CORRECTA del sudoku\n");
    steady_clock::time_point end_time_single_thread = steady_clock::now();
    duration<double> elapsed_time_single_thread = duration_cast<duration<double>>(end_time_single_thread - start_time_single_thread);
    cout << endl << "Tiempo total usando un solo hilo: " << elapsed_time_single_thread.count() << " segundos" << endl << endl;
    steady_clock::time_point start_time_threads = steady_clock::now();
    pthread_t threads[num_threads];
    int threadIndex = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i%3 == 0 && j%3 == 0) {
                parameters *gridData = (parameters *) malloc(sizeof(parameters));
                gridData->row = i;
                gridData->col = j;
                gridData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, check_grid, gridData);
            }
            if (j == 0) {
                parameters *rowData = (parameters *) malloc(sizeof(parameters));
                rowData->row = i;
                rowData->col = j;
                rowData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, check_rows, rowData);
            }
            if (i == 0) {
                parameters *columnData = (parameters *) malloc(sizeof(parameters));
                columnData->row = i;
                columnData->col = j;
                columnData->board = sudoku;
                pthread_create(&threads[threadIndex++], NULL, check_cols, columnData);
            }
        }
    }
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
    for (int i = 0; i < num_threads; i++) {
        if (result[i] == 0) {
            cout << "Con varios hilos: Solución INCORRECTA del sudoku" << endl;
            steady_clock::time_point end_time_threads = steady_clock::now();
            duration<double> elapsed_time_threads = duration_cast<duration<double>>(end_time_threads - start_time_threads);
            cout << endl << "Tiempo total utilizando 27 hilos: " << elapsed_time_threads.count() << " segundos" << endl;
            return 1;
        }
    }
    cout << "Con varios hilos: Solución CORRECTA del sudoku" << endl;
    steady_clock::time_point end_time_threads = steady_clock::now();
    duration<double> elapsed_time_threads = duration_cast<duration<double>>(end_time_threads - start_time_threads);
    cout << endl << "Tiempo total utilizando 27 hilos: " << elapsed_time_threads.count() << " segundos" << endl;
}
void *check_grid(void * params) {
    parameters *data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int validarray[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            int val = data->board[i][j];
            if (validarray[val] != 0) {
				printf("[*check_grid] Error en la cuadricula que inicia en la fila %d, columna %d, \n",startRow,startCol);
                pthread_exit(NULL);
            } else {
                validarray[val] = 1;
			}
        }
    }
    result[startRow + startCol/3] = 1; 
    pthread_exit(NULL);
}

void *check_rows(void *params) {
    parameters *data = (parameters *) params;
    int row = data->row;
    int validarray[10] = {0};
    for (int j = 0; j < 9; j++) {
        int val = data->board[row][j];
        if (validarray[val] != 0) {
			printf("[*check_rows] Error en la fila %d\n",row);
            pthread_exit(NULL);
		} else {
            validarray[val] = 1;
		}
    }
    result[9 + row] = 1; 
    pthread_exit(NULL);
}

void *check_cols(void *params) {
    parameters *data = (parameters *) params;
    int col = data->col;
    int validarray[10] = {0};
    for (int i = 0; i < 9; i++) {
        int val = data->board[i][col];
        if (validarray[val] != 0) {
			printf("[*check_cols] Error en la columna %d, \n",col);
            pthread_exit(NULL);
		} else {
            validarray[val] = 1;
		}
    }
    result[18 + col] = 1; 
    pthread_exit(NULL);
 }

int check_line(int input[9]) {
    int validarray[10] = {0};
    for (int i = 0; i < 9; i++) {
        int val = input[i];
        if (validarray[val] != 0)
            return 1;
        else
            validarray[val] = 1;
    }
    return 0;
}

int check_grid(int sudoku[9][9]) {
    int temp_row, temp_col;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp_row = 3 * i;
            temp_col = 3 * j;
            int validarray[10] = {0};
            for(int p=temp_row; p < temp_row+3; p++) {
                for(int q=temp_col; q < temp_col+3; q++) {
                    int val = sudoku[p][q];
                    if (validarray[val] != 0)
                        return 1;
                    else
                        validarray[val] = 1;
                }
            }
        }
    }
    return 0;
}

int sudoku_checker(int sudoku[9][9]) {
    for (int i=0; i<9; i++) {
        if(check_line(sudoku[i]))
            return 1;
        int check_col[9];
        for (int j=0; j<9; j++)
            check_col[j] = sudoku[i][j];
        if(check_line(check_col))
            return 1;
        if(check_grid(sudoku))
            return 1;
    }
    return 0;
}