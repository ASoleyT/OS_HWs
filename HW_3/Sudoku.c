#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

///place to store that validations of rows,columns,3*3 squares
int sudoku[9][9];                
bool row_valid = true;           
bool col_valid = true;           
bool square_valid[9];            

///// struct to save 3*3 square
typedef struct {
    int start_row;
    int start_col;
    int index;
} square_args;

//-row validation
void* check_rows(void* arg) {

    for (int row=0;row<9;row++) {

        int seen[10]={0};
        
        for (int col=0;col<9;col++) {

            int num = sudoku[row][col];
            if (num < 1 || num > 9 || seen[num]) {
                
                row_valid = false;
                pthread_exit(NULL);

            }

            seen[num] = 1;

        }
    }

    pthread_exit(NULL);
    
}

///column validations
void* check_cols(void* arg) {

    for (int col=0; col<9; col++) {
    
        int seen[10] = {0};
        for (int row =0; row<9; row++) {
            
            int num = sudoku[row][col];
        
            if (num < 1 || num > 9 || seen[num]) {
                col_valid = false;
                pthread_exit(NULL);
            }

            seen[num] = 1;
        }

    }

    pthread_exit(NULL);

}

// check 3*3 squres 
void* check_square(void* arg) {
    square_args* data = (square_args*)arg;
    int seen[10] = {0};

    for (int row=0; row<3; row++) {
        for (int col=0; col<3; col++) {
           
            int num = sudoku[data->start_row + row][data->start_col + col];
            if (num < 1 || num > 9 || seen[num]) {
                square_valid[data->index] = false;
                pthread_exit(NULL);
            }
            seen[num] = 1;

        }
    }

    square_valid[data->index] = true;
    pthread_exit(NULL);
}

int main() {
    printf("Enter a matrix to be validated\n");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            scanf("%d", &sudoku[i][j]);

    pthread_t threads[11]; 
    square_args* args[9];

    pthread_create(&threads[0], NULL, check_rows, NULL);
    pthread_create(&threads[1], NULL, check_cols, NULL);

    int idx = 0;
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            args[idx] = malloc(sizeof(square_args));
            args[idx]->start_row = i;
            args[idx]->start_col = j;
            args[idx]->index = idx;
            pthread_create(&threads[2 + idx], NULL, check_square, args[idx]);
            idx++;
        }
    }

    for (int i = 0; i < 11; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 9; i++) {
        free(args[i]);
    }

    bool all_squares_valid = true;
    for (int i = 0; i < 9; i++) {
        if (!square_valid[i]) {
            all_squares_valid = false;
            break;
        }
    }

    if (row_valid && col_valid && all_squares_valid)
        printf("soduko is validated");
    else
        printf("soduko isnot validated\n");

    return 0;
}
