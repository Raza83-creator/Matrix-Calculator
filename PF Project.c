#include <stdio.h>

#define MAX 100

//Echelon form and Reduced Echelon form

void div(int row, int column, int div_row, int div_column, int num_of_row, int num_of_column, float arr[][MAX], float arr2[][MAX]) {
    int i, j;

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            arr2[i][j] = arr[i][j];
        }
    }

    i = row;
    float pivot = arr[div_row][div_column];

    if (pivot != 0) {
        for (j = column; j < num_of_column; j++) {
            arr2[i][j] = arr[i][j] / pivot;
        }
    }

    printf("\n");

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            arr[i][j] = arr2[i][j];
            printf("\t %.2f", arr[i][j]);
        }
        printf("\n");
    }
}

void sub(int row, int column, int sub_row, int sub_column, int num_of_row, int num_of_column, float arr[][MAX], float arr2[][MAX]) {
    int i, j;

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            arr2[i][j] = arr[i][j];
        }
    }

    float factor = arr[row][column];

    for (j = 0; j < num_of_column; j++) {
        arr2[row][j] = arr[row][j] - (arr[sub_row][j] * factor);
    }

    printf("\n");

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            arr[i][j] = arr2[i][j];
            printf("\t %.2f", arr[i][j]);
        }
        printf("\n");
    }
}

void echelon() {

    int num_of_row, num_of_column;
    int i, j;
input:
    printf("Enter number of rows: ");
    scanf("%d", &num_of_row);

    printf("Enter number of columns: ");
    scanf("%d", &num_of_column);

    if (num_of_row < 1 || num_of_row > MAX || num_of_column < 1 || num_of_column > MAX) {
        printf("Invalid row or column size.\n");
        goto input;
    }

    float arr[MAX][MAX];
    float arr2[MAX][MAX] = {0};

    printf("\nEnter matrix elements:\n");

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            scanf("%f", &arr[i][j]);
        }
    }

    printf("\nOriginal Matrix:\n");

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            printf("\t%.2f", arr[i][j]);
        }
        printf("\n");
    }

    {
        int i = 0;
        int j;

        while (i < num_of_row && i < num_of_column) {

            int count[MAX] = {0};

            for (int r = i; r < num_of_row; r++) {
                for (int c = 0; c < num_of_column; c++) {
                    if (arr[r][c] > -1e-6 && arr[r][c] < 1e-6) {
                        count[r]++;
                    } else {
                        break;
                    }
                }
            }

            for (int r = i; r < num_of_row - 1; r++) {
                for (int k = r + 1; k < num_of_row; k++) {
                    if (count[r] > count[k]) {
                        for (int c = 0; c < num_of_column; c++) {
                            float temp = arr[r][c];
                            arr[r][c] = -arr[k][c];
                            arr[k][c] = temp;
                        }

                        int temp_count = count[r];
                        count[r] = count[k];
                        count[k] = temp_count;
                    }
                }
            }

            printf("\n");

            for (int r = 0; r < num_of_row; r++) {
                for (int c = 0; c < num_of_column; c++) {
                    printf("\t%.2f", arr[r][c]);
                }
                printf("\n");
            }

            div(i, i, i, i, num_of_row, num_of_column, arr, arr2);

            j = i + 1;

            while (j < num_of_row) {
                sub(j, i, i, i, num_of_row, num_of_column, arr, arr2);
                j++;
            }

            i++;
        }

        for (int i = num_of_row - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                sub(j, i, i, i, num_of_row, num_of_column, arr, arr2);
            }
        }
    }

    printf("\nRow Echelon Form / Reduced Matrix:\n");

    for (i = 0; i < num_of_row; i++) {
        for (j = 0; j < num_of_column; j++) {
            printf("\t%.2f", arr[i][j]);
        }
        printf("\n");
    }
}


//Transpose

void transpose() {

    int i, j;
    int n;

    do {
        printf("\nEnter matrix dimensions(nxn): ");
        scanf("%d", &n);

        if(n <= 0) {
            printf("\nInvalid matrix dimensions!\n'n' must be greater than 0.");
        }

        if(n > MAX) {
            printf("\nInvalid matrix dimensions!\nThis program calculates upto 100x100 ordered matrix.");
        }

    } while(n <= 0 || n > MAX);

    float mat[MAX][MAX];
    float transpose[MAX][MAX];

    printf("\nEnter elements of matrix(%dx%d):\n", n, n);

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("Element[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &mat[i][j]);
        }
    }

    printf("\nOriginal Matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%.2f\t", mat[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            transpose[i][j] = mat[j][i];
        }
    }

    printf("\nTransposed Matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%.2f\t", transpose[i][j]);
        }
        printf("\n");
    }
}


//Cofactor

void cofactor(float mat[MAX][MAX], float temp[MAX][MAX], int p, int q, int n) {

    int i = 0, j = 0;

    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {

            if(row != p && col != q) {

                temp[i][j++] = mat[row][col];

                if(j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}


//Determinant

float determinant(float mat[MAX][MAX], int n) {

    float D = 0;

    if(n == 1)
        return mat[0][0];

    float temp[MAX][MAX];
    int sign = 1;

    for(int f = 0; f < n; f++) {

        cofactor(mat, temp, 0, f, n);

        D += sign * mat[0][f] * determinant(temp, n - 1);

        sign = -sign;
    }

    return D;
}


//adjoint

void adjoint() {

    int i, j;
    int n;

    do {
        printf("\nEnter matrix dimensions(nxn): ");
        scanf("%d", &n);

        if(n <= 0) {
            printf("\nInvalid matrix dimensions!\n'n' must be greater than 0.");
        }

        if(n > MAX) {
            printf("\nInvalid matrix dimensions!\nThis program calculates upto 100x100 ordered matrix.");
        }

    } while(n <= 0 || n > MAX);

    float mat[MAX][MAX];
    float adj[MAX][MAX];

    printf("\nEnter elements of matrix(%dx%d):\n", n, n);

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("Element[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &mat[i][j]);
        }
    }

    printf("\nOriginal Matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%.2f\t", mat[i][j]);
        }
        printf("\n");
    }

    if(n == 1) {

        adj[0][0] = 1;

        printf("\nAdjoint Of Matrix:\n");
        printf("%.2f\n", adj[0][0]);

        return;
    }

    int sign;
    float temp[MAX][MAX];

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {

            cofactor(mat, temp, i, j, n);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj[j][i] = sign * determinant(temp, n - 1);
        }
    }

    printf("\nAdjoint Of Matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%.2f\t", adj[i][j]);
        }
        printf("\n");
    }
}


//Add
void addition() {

    int num_matrices, r, c;

    printf("\nHow many matrices do you want to add? ");
    scanf("%d", &num_matrices);

    if (num_matrices < 2) {
        printf("You need at least 2 matrices for addition.\n");
        return;
    }

    printf("Enter dimensions of the matrices (row by column): ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0 || r > 100 || c > 100) {
        printf("Invalid dimensions!\n");
        return;
    }

    int result[100][100];
    printf("Enter elements of Matrix 1 (%d x %d):\n", r, c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &result[i][j]);
        }
    }

    for (int m = 2; m <= num_matrices; m++) {
        int next_mat[100][100];

        printf("Enter elements of Matrix %d (%d x %d):\n", m, r, c);

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                scanf("%d", &next_mat[i][j]);
                result[i][j] += next_mat[i][j];
            }
        }
    }

    printf("\nResultant Matrix (Sum of %d matrices):\n", num_matrices);

    for (int i = 0; i < r; i++) {
        printf("[ ");
        for (int j = 0; j < c; j++) {
            printf("%d ", result[i][j]);
        }
        printf("]\n");
    }
}


//sub
void subtraction() {

    int num_matrices, r, c;

    printf("\nHow many matrices do you want to subtract? ");
    scanf("%d", &num_matrices);

    if (num_matrices < 2) {
        printf("You need at least 2 matrices for subtraction.\n");
        return;
    }

    printf("Enter dimensions of the matrices (row by column): ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0 || r > 100 || c > 100) {
        printf("Invalid dimensions!\n");
        return;
    }

    int result[100][100];
    printf("Enter elements of Matrix 1 (%d x %d):\n", r, c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &result[i][j]);
        }
    }

    for (int m = 2; m <= num_matrices; m++) {
        int next_mat[100][100];

        printf("Enter elements of Matrix %d (%d x %d):\n", m, r, c);

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                scanf("%d", &next_mat[i][j]);
                result[i][j] -= next_mat[i][j];
            }
        }
    }

    printf("\nResultant Matrix (Difference of %d matrices):\n", num_matrices);

    for (int i = 0; i < r; i++) {
        printf("[ ");
        for (int j = 0; j < c; j++) {
            printf("%d ", result[i][j]);
        }
        printf("]\n");
    }
}


//Multiply
void multiplication() {

    int num_matrices;
    printf("\nHow many matrices do you want to multiply? ");
    scanf("%d", &num_matrices);

    if (num_matrices < 2) {
        printf("You need at least 2 matrices for multiplication.\n");
        return;
    }

    int r1, c1;
    printf("Enter dimensions of Matrix 1 (row by column): ");
    scanf("%d %d", &r1, &c1);

    if (r1 <= 0 || c1 <= 0 || r1 > 100 || c1 > 100) {
        printf("Invalid dimensions!\n");
        return;
    }

    int cur_r = r1;
    int cur_c = c1;

    int result[100][100];
    printf("Enter elements of Matrix 1 (%d x %d):\n", cur_r, cur_c);

    for (int i = 0; i < cur_r; i++) {
        for (int j = 0; j < cur_c; j++) {
            scanf("%d", &result[i][j]);
        }
    }

    int valid = 1;

    for (int m = 2; m <= num_matrices; m++) {
        int r2, c2;

        printf("\nEnter dimensions of Matrix %d (row by column): ", m);
        scanf("%d %d", &r2, &c2);

        // Corrected validation order
        if (r2 <= 0 || c2 <= 0 || r2 > 100 || c2 > 100) {
            printf("Invalid dimensions!\n");
            valid = 0;
            break;
        }

        if (cur_c != r2) {
            printf("Error: Cannot multiply! Columns of previous matrix (%d) must equal rows of Matrix %d (%d).\n", cur_c, m, r2);
            valid = 0;
            break;
        }

        int next_mat[100][100];
        printf("Enter elements of Matrix %d (%d x %d):\n", m, r2, c2);

        for (int i = 0; i < r2; i++) {
            for (int j = 0; j < c2; j++) {
                scanf("%d", &next_mat[i][j]);
            }
        }

        int temp[100][100];

        for (int i = 0; i < cur_r; i++) {
            for (int j = 0; j < c2; j++) {
                temp[i][j] = 0;

                for (int k = 0; k < cur_c; k++) {
                    temp[i][j] += result[i][k] * next_mat[k][j];
                }
            }
        }

        cur_c = c2;

        for (int i = 0; i < cur_r; i++) {
            for (int j = 0; j < cur_c; j++) {
                result[i][j] = temp[i][j];
            }
        }
    }

    if (valid) {
        printf("\nResultant Matrix (Product of %d matrices):\n", num_matrices);

        for (int i = 0; i < cur_r; i++) {
            printf("[ ");
            for (int j = 0; j < cur_c; j++) {
                printf("%d ", result[i][j]);
            }
            printf("]\n");
        }
    }
}

//Divide
void division() {

    int num_matrices, r, c;

    printf("\nHow many matrices do you want to divide (element-wise)? ");
    scanf("%d", &num_matrices);

    if (num_matrices < 2) {
        printf("You need at least 2 matrices for division.\n");
        return;
    }

    printf("Enter dimensions of the matrices (row by column): ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0 || r > 100 || c > 100) {
        printf("Invalid dimensions!\n");
        return;
    }

    int result[100][100];
    printf("Enter elements of Matrix 1 (%d x %d):\n", r, c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &result[i][j]);
        }
    }

    int division_error = 0;

    for (int m = 2; m <= num_matrices; m++) {
        int next_mat[100][100];

        printf("Enter elements of Matrix %d (%d x %d):\n", m, r, c);

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                scanf("%d", &next_mat[i][j]);

                if (next_mat[i][j] == 0) {
                    division_error = 1;
                }
            }
        }

        if (division_error) {
            printf("\nError: Division by zero encountered in Matrix %d! Cannot proceed.\n", m);
            break;
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                result[i][j] = result[i][j] / next_mat[i][j];
            }
        }
    }

    if (!division_error) {
        printf("\nResultant Matrix (Element-wise Division of %d matrices):\n", num_matrices);

        for (int i = 0; i < r; i++) {
            printf("[ ");
            for (int j = 0; j < c; j++) {
                printf("%d ", result[i][j]);
            }
            printf("]\n");
        }
    }
}


//Determinant
void determinant2() {

    int n;

    printf("\nEnter the order of the square matrix (n x n): ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid order!\n");
        return;
    }

    double mat[100][100];
    printf("Enter elements of the %d x %d matrix:\n", n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    double det = 1.0;
    int swap_count = 0;
    int possible = 1;

    for (int i = 0; i < n; i++) {
        int pivot = i;

        while (pivot < n && mat[pivot][i] == 0) {
            pivot++;
        }

        if (pivot == n) {
            det = 0.0;
            possible = 0;
            break;
        }

        if (pivot != i) {
            for (int j = 0; j < n; j++) {
                double temp = mat[i][j];
                mat[i][j] = mat[pivot][j];
                mat[pivot][j] = temp;
            }
            swap_count++;
        }

        for (int j = i + 1; j < n; j++) {
            double factor = mat[j][i] / mat[i][i];

            for (int k = i; k < n; k++) {
                mat[j][k] -= factor * mat[i][k];
            }
        }
    }

    if (possible) {
        for (int i = 0; i < n; i++) {
            det *= mat[i][i];
        }

        if (swap_count % 2 != 0) {
            det = -det;
        }
    }

    printf("\nDeterminant of the matrix = %.0lf\n", det);
}




//Main Function

int main() {
	
	int choice;

    do {
    	
      	printf("MATRIX CALCULATOR\n");
        printf("1. Row Echelon Form\n");
        printf("2. Transpose\n");
        printf("3. Adjoint\n");
        printf("4. Addition\n");
        printf("5. Subtraction\n");
        printf("6. Multiplication\n");
        printf("7. Division\n");
        printf("8. Determinant\n");
        printf("9. Exit\n");
        
        
        do {
        	printf("\nEnter the type of calculation you want: ");
        	scanf("%d", &choice);
        	
        	if(choice < 1 || choice > 9) {
        		printf("Invalid Input!\nEnter a number between 1-9\n");
			}
		
		} while(choice < 1 || choice > 9);
		
        switch(choice) {

            case 1:
                echelon();
                break;

            case 2:
                transpose();
                break;

            case 3:
                adjoint();
                break;

            case 4:
            	addition();
            	break;
            	
            case 5:
            	subtraction();
            	break;
            	
            case 6:
            	multiplication();
            	break;
            	
            case 7:
            	division();
            	break;
            	
            case 8:
                determinant2();
                break;
          	
            case 9:
                printf("\nExiting program...");
                break;
            default:
            	printf("\nInvalid Input!\nEnter a number between 1-9\n");
        }
        
        printf("\n");
        
	} while(choice != 9);

    return 0;
}
