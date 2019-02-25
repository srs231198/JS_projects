//Shreyas Raj Singh sxs170100

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int col = 4;

//a function to get the input from matrix.txt
int FileInput(int *, fstream &);

int main(){

    fstream inputfile;
    int *matrix;
    matrix = new int[16];
    int num_equations = 0;
    inputfile.open("commands.txt", ios :: in | ios :: out | ios :: binary);
    //call the function and store the value of the num of rows in num_equations
    num_equations = FileInput(matrix, inputfile);
    inputfile.close();
}

//Funtion below will open the file given and parse through the equation in the file
//the equations in the file will be stored as an augmented matrix in matrix[][]
//eg- 3x + 4y + 5z = 12
//     x +  y +  z = 11
// will be stored as [(3, 4, 5, 12),
//                    (1 , 1, 1, 11)]
//in matrix[][]
int FileInput(int *matrix, fstream &inputfile) {
    unsigned long index = 0;
    int line_count = 0;
    string equation, variable;

    //there are 2 delimiters the "+" and "=" sign, both of them help to isolate variables
    string addition_delimiter = "+";
    string equalTo_delimiter = "=";

    //loop until the end of the file
    while(!inputfile.eof()) {
        //get input equation from line
        getline(inputfile, equation);

        //initialize column variable to be used in matrix[][]
        int col = 0;
       //while index doesn't return
        do {
            //break out of the loop when 4 columns have been filled
            if(col >= 4){
                break;
            }

            //search for the delimiter "+"
            index = equation.find(addition_delimiter);
            if (index != string::npos) {

                //modify string to take out the variable before "+" operator
                variable = equation.substr(0, index);
                equation = equation.substr(index + 1);

                //search for the value of the variable, i.e. 3x has value 3
                if(variable.length() > 1){
                    variable = variable.at(0);

                    //store value of the variable in the 2D matrix
                    matrix[line_count][col] = stoi(variable);
                    //increment column to store value in the next column
                    col++;
                }

                //otherwise if the variable is simgular, i.e. x or y or z then
                //place the value in the matrix as one
                else if(variable.length() == 1){
                    //store 1 in the stated position
                    matrix[line_count][col] = 1;
                    //increment the column number
                    col++;
                }

            }
            //search for delimiter "=" if "+" not found
            else{
                //find first known location of "='
                index = equation.find(equalTo_delimiter);

                //check for occurrence
                //There's no need to loop here because we've reached the end of the equation
                if (index != string::npos) {
                    variable = equation.substr(0, index);
                    equation = equation.substr(index + 1);
                    //search for the value of the variable, i.e. 3x has value 3
                    if(variable.length() > 1){
                        variable = variable.at(0);

                        //store value of the variable in the 2D matrix
                        matrix[line_count][col] = stoi(variable);
                        //increment column to store value in the next column
                        col++;
                    }

                    //otherwise if the variable is simgular, i.e. x or y or z then
                    //place the value in the matrix as one
                    else if(variable.length() == 1){
                        //store 1 in the stated position
                        matrix[line_count][col] = 1;
                        //increment the column number
                        col++;
                    }

                    //add the value of the constant to the 4th column
                    matrix[line_count][col] = stoi(equation);
                    col++;
                }
            }
        }while(index != string::npos);

        //increment the count of the number of rows
        line_count++;
    }

    //return the line count back to num_equations.
    return line_count;
}

