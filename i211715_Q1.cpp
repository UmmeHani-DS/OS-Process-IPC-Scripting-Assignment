#include <iostream>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

int N_processes()
{
   // STEP:1 Generate random number btw 10-99

        srand(time(0));

        int num = rand() % 90 + 10;

    // STEP:2 Multipy generated number by last digit of roll no. (21i-1715)

    num = num * 5;

    // STEP:3 Divide roll number with the generated number.

    int roll = 211715;

    int div = roll / num;

    // STEP:4 Take mod of number with 25.If number is less than 10, add 15 to it.

    div = div % 25;

    if(div < 10)
    {
        div = div + 15;
    }

    
    return div;
}

void matrixMultiply(int row[], int** matrix, int result[], int size, int rowId)
 {
    for (int i = 0; i < size; i++) 
    {
        result[i] = 0;

        for (int j = 0; j < size; j++) 
        {
            result[i] += row[j] * matrix[j][i];
        }
    }

    // Save the result to a text file with the process id

    string filename = "result_" + to_string(rowId) + ".txt";

    ofstream outFile(filename);

    for (int i = 0; i < size; i++)
     {
        outFile << result[i] << " ";
    }

    outFile.close();
}

void display(int** matrix , int size)
{
    // Display the result matrix

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}

int main()
{
    int n = N_processes();

    // Create a n x n matrix (dynamic allocation)

    int** matrix = new int*[n];

    for (int i = 0; i < n; i++) 
    {
        matrix[i] = new int[n];
    }

    // Populate the matrix with random numbers

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            matrix[i][j] = rand() % 90 + 10;
        }
    }

    // Create n processes and save the whole matrix in a text file.

    pid_t childProcesses[n];

    for (int i = 0; i < n; i++)
     {
        pid_t pid = fork();

        if (pid == 0) 
        {
            // Child process
            int resultRow[n];
            matrixMultiply(matrix[i], matrix, resultRow, n, i);
            exit(0);
        }
        
        else 
        {
            // Parent process
            childProcesses[i] = pid;
        }
    }


    // Read and display the result matrices from text files

     int** resultMatrix = new int*[n];

        for (int i = 0; i < n; i++) 
        {
            resultMatrix[i] = new int[n];
        }


    for (int i = 0; i < n; i++)
    {
        string filename = "result_" + to_string(i) + ".txt";

        ifstream inFile(filename);

        for (int j = 0; j < n; j++) 
        {
            inFile >> resultMatrix[i][j];
        }

        display(resultMatrix , n);

        cout << "Next matrix" << endl;

        inFile.close();
    }


    return 0;
}