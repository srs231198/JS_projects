//Shreyas Raj Singh sxs170100

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;


//a function to count the number of equations;
int numOfEquations(fstream &);

//a function to get the input from matrix.txt
void FileInput(double *, fstream &, int );

//a function to display the matrix
void displayMatrix(double *, int numEQ);

//a function to prompt users for input
void menu(double *, int );

//a function to switch rows
void switchRows(double *, int );

//a function to multiply a row with the given multiplier
void multiplier(double *, int);

//a function to add the scalar multiple of a row to another
void scalarAddition(double *, int);

//a function to check for the reduced echelon form
bool MatrixComplete(double *, int);

int main(){

    fstream inputfile;
    double *matrix;

    int num_equations = 0;

    num_equations = numOfEquations(inputfile);
//    //check for number of players
//    if(num_equations > 4 || num_equations < 2){
//        cout << "Only 2-4 players allowed" << endl;
//        exit(0);
//    }
    int sizeOfArray = num_equations*4;

    matrix = new double[sizeOfArray]();

   displayMatrix(matrix, num_equations);

    //call the function and store the value of the num of rows in num_equations
    FileInput(matrix, inputfile, num_equations);

   displayMatrix(matrix, num_equations);

    //get the users choice and call the corresponding function
    menu(matrix, num_equations);

    delete [] matrix;

    inputfile.close();
}


int numOfEquations(fstream &inputfile){
    string player;
    int playerCount = 0;
    inputfile.open("commands.txt", ios :: in);

    while(inputfile >> player) {
        if (!player.empty())
            playerCount++;
    }

    inputfile.close();
    return playerCount;
}

void FileInput(double *matrix, fstream &inputfile, int numEQ) {

    inputfile.open("commands.txt", ios::in | ios :: binary);

    string equation,variable;

    double *ptm;

    ptm = matrix;

    int counter = 0, pos = 0;

    while(inputfile >> equation){

        int sign = 1;

        //get length of string
        int length = int(equation.length());

        unsigned long i = 0;


        while(length > 0){

            //update pointer position
            ptm += counter*4;

            variable = "";
            //check for sign of the variable
            if(equation.at(i) == '+'){
                sign = 1;
                equation = equation.substr(i + 1);
            }
            else if(equation.at(i) == '-'){
                sign = -1;
                equation = equation.substr(i + 1);
            }


            //check for variable
            if(equation.at(i) == 'x'){
                variable = equation.substr(0, i);
                equation = equation.substr(i + 1);

                length = (int)equation.size();

                *ptm = sign;

                i = 0;
            }
            else if(equation.at(i) == 'y'){

                //extract the variable from the equation
                variable = equation.substr(0, i);
                equation = equation.substr(i + 1);

                length = (int)equation.size();

                ptm++;

                *ptm = sign;

                pos = 1;

                i = 0;
            }
            else if(equation.at(i) == 'z'){
                variable = equation.substr(0, i);
                equation = equation.substr(i + 1);

                length = (int)equation.size();

                ptm += 2;

                *ptm = sign;

                pos = 2;

                i = 0;
            }
            else if(equation.at(i) == '='){
                variable = equation.substr(i + 1);

                length = 0;

                ptm += 3;

//                *ptm = sign;

                pos = 3;

                sign = 1;

                i = 0;
            }
            else{
                i++;
            }

            if(variable.length() > 0){
                double n = stod(variable);
                *ptm = n*sign;

            }

            cout << *ptm << " ";

            //set the pointer to the original position
            ptm = matrix;

//
        }

        //initialize the counter
        counter++;

    }

    inputfile.close();
}

void displayMatrix(double *matrix, int numEQ){
    int length = numEQ*4;
    double *ptm;
    ptm = matrix;
    int counter = 0;
    cout << endl;

    //loop till the end of the array
    for(int i = 0; i < length; i++){
        cout << setw(2) << *ptm << " ";
        ptm++;
        counter++;
        //when 4 values are outputted then print a newline
        if(counter == 4){
            counter = 0;
            cout << endl;
        }
    }
    cout << endl;
}

void menu( double *matrix, int numEQ){

    double *ptm ;
    int choice = 0;
    ptm = matrix;

    //while choice is not quit aka 4
    while(choice != 4) {

        //check if the matrix is complete or not
        if(MatrixComplete(matrix, numEQ))
            break;

        //display the matix to the user
        displayMatrix(matrix, numEQ);

        //present the user with choices
        cout << "Please choose an option\n"
                "o 1 – Switch two rows\n"
                "o 2 – Multiply row by non-zero number\n"
                "o 3 – Add scalar multiple of one row to another row\n"
                "o 4 – Quit\n";
        //get the choice
        cin >> choice;

        //call appropriate functions based on the user's input
        switch (choice) {
            case 1 :
                switchRows(matrix, numEQ);
                break;
            case 2 :
                multiplier(matrix, numEQ);
                break;
            case 3 :
                scalarAddition(matrix, numEQ);
                break;
            case 4 :
                cout << "Program terminating" << endl;
                break;
            default:
                cout << "enter a number between 1 and 4 corresponding to the assigned action" << endl;
        }
    }
    //display the updated matrix to the user
    displayMatrix(matrix, numEQ);

}

void switchRows(double *matrix, int numEQ){

    int row1 = 0, row2 = 0;
    double temp;
    double *ptm1;
    double *ptm2;
    ptm1 = matrix;
    ptm2 = matrix;

    //ask the user for the rows they want to switch
    cout << "Enter the first row: " << endl;
    cin >> row1;
    cout << "Enter the second row: " << endl;
    cin >> row2;

    //check that the input is between 1 and 4 for both rows
    if((row1 <= numEQ && row1 > 0) && (row2 <= numEQ && row2 > 0)){


        row1--, row2--;
        //set the position of position counter
        if(row1 > row2){
            ptm2 += row1*4;
            ptm1 += row2*4;
        }
        else{
            ptm2 += row2*4;
            ptm1 += row1*4;
        }

        //switch the rows
        for (int i = 0; i < 4; i++, ptm1++, ptm2++){
            temp = *ptm1;
            *ptm1 = *ptm2;
            *ptm2 = temp;
        }
    }
    else{
        //error message to warn user of invalid input
        cout << "The row input must be between " << "1 and " << numEQ << endl;
    }
}

void multiplier(double *matrix, int numEQ){
    double multiplier = 0;
    int row;

    double *ptm;
    ptm = matrix;

    //get the value of the row to be multiplied
    cout << "Enter the row you want multiplied" << endl;
    cin >> row;

    if(row <= numEQ && row > 0) {

        //get the value of the multiplier
        cout << "Enter the value you want to multiply the row with :" << endl;
        cin >> multiplier;

        //check for non-zero values
        if (multiplier == 0) {
            cout << "the multiplier needs to be a non-zero value" << endl;
            return;
        }

        //make the row into a compatible type
        row--;

        //set the position of the pointer
        ptm += row*4;

        //multiply the multiplier to the given row
        for (int i = 0; i < 4; i++, ptm++){
            //if the pointer is non zero let the
            if(*ptm == 0){
                continue;
            }
            *ptm *= multiplier;
        }

    }
    else{
        //error message to warn user of invalid input
        cout << "The row input must be between " << "1 and " << numEQ << endl;
    }
}

void scalarAddition(double *matrix, int numEQ){
    double multiplier = 0;
    int row, row1;

    double *ptm;
    ptm = matrix;

    double *ptm1;
    ptm1 = matrix;

    //get the value of the row to be multiplied
    cout << "Enter the row you want multiplied" << endl;
    cin >> row;

    if(row <= numEQ && row > 0) {

        //get the value of the multiplier
        cout << "Enter the value you want to multiply the row with :" << endl;
        cin >> multiplier;

        //check for non-zero values
        if (multiplier == 0) {
            cout << "the multiplier needs to be a non-zero value" << endl;
            return;
        }

        //make the row into a compatible type
        row--;

        //set the position of the pointer
        ptm += row*4;

        cout << "Enter the row you want to be added by the multiplied row" << endl;
        cin >> row1;

        //add the rows together
        if(row1 <= numEQ && row1 > 0){
            row1--;

            //set the position of the pointer
            ptm1 += row1*4;

            for(int i = 0; i < 4; i++, ptm++, ptm1++){

                if(*ptm == 0){
                    continue;
                }
                *ptm *= multiplier;
                *ptm1 += *ptm;
                *ptm /= multiplier;

            }
        }
        else{
            //error message to warn user of invalid input
            cout << "The row input must be between " << "1 and " << numEQ << endl;
        }


    }
    else{
        //error message to warn user of invalid input
        cout << "The row input must be between " << "1 and " << numEQ << endl;
    }

}

bool MatrixComplete(double *matrix, int NumEQ){
    bool valid = true;

    bool leading = true;

    double  x=0, y = 0, z = 0;

    bool x_value = false, y_value = false, z_value = false;

    double *ptm;
    ptm = matrix;

    int row = 0;

    int col = 0, lead = 0;

    while(row < NumEQ){

        //if there are 4 equations check the bottom row for all zeroes
        if(row == 3 && NumEQ == 4){

            ptm = matrix;

            ptm += 12;

            for(int i = 0; i < 4 ; i++,ptm++){
                if(*ptm == 0){
                    continue;
                }
                else{
                    return false;
                }
            }
        }


        //check for leading 1 in each row, cycling through columns
        for(col = 0; col < 4; col ++, ptm++){

            //check for the 4th column
            if(col == 3){
                continue;
            }
            //check for zeroes
            if(*ptm == 0){
                continue;
            }
            //check for leading 1
            if(*ptm == 1){
                //make sure that lead is not bigger than
                if(lead > col){
                    valid = false;
                    leading = false;
                    break;
                }

//                //check that each column has only the leading 1 in it
//                //assign the pointer to the beginning of the matrix
//                ptm = matrix;
//                //move the pointer to the beginning of the array
//                ptm += row+4;
//                for(int i = 0 ; i < 3; i++){
//                    if(i == col){
//                        continue;
//                    }
//                    else if(*ptm == 0){
//                        continue;
//                    }
//                    else{
//                        valid = false;
//                        break;
//                    }
//                }
//
//                //put matrix back to the original position
//                ptm = matrix;
//                ptm += (row*4 + col);


                //assign values to columns based on specific variables

                    switch (col) {
                        case 0:
                            lead = col;
                            x_value = true;
                            break;

                        case 1:
                            lead = col;
                            y_value = true;
                            break;

                        case 2:
                            lead = col;
                            z_value = true;
                            break;
                        default:
                            valid = false;
                    }


                //break out of the loop if the leading 1 is found
                break;
            }
            else {
                valid = false;
                break;
            }

        }

        //if the leading character is not in the proper place then break
        if(!leading){
            break;
        }

        //increment the number of equations to check
        row++;
    }

    if(valid){

            cout << "The matrix is in reduced echelon form" << endl;

            ptm = matrix;
            if(x_value){
                ptm += 4;
                x = *ptm;
                ptm -= 4;
                cout << "the value of x: " << x << endl;
            }
            if(y_value){
                ptm += 8;
                y = *ptm;
                ptm -= 8;
                cout << "the value of y: " << y << endl;
            }
            if(z_value){
                ptm += 12;
                z = *ptm;
                ptm -= 12;
                cout << "the value of z: " << z << endl;
            }
    }

    return valid;
}