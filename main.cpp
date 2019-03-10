//Shreyas Raj Singh sxs170100 CS 1337.007 Project 2

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

//a function to count the number of equations;
int numOfEquations(fstream &);

//a function to get the input from matrix.txt
void FileInput(double *, fstream &);

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

//a function to check if the row is in the proper format or not
bool rowChecker(double *, int);

int main(){

    fstream inputfile;
    double *matrix;

    int num_equations = 0;

    inputfile.open("matrix.txt", ios :: in);

    //check the file for invalid input
    if(!inputfile.good()){
        cout << "The file didn't open successfully" << endl;
        exit(0);
    }

    inputfile.close();

    //get the number of equations
    num_equations = numOfEquations(inputfile);
    //check for number of players
    if(num_equations > 4 || num_equations < 2){
        cout << "Only 2-4 players allowed" << endl;
        exit(0);
    }
    //get the size of array
    int sizeOfArray = num_equations*4;

    //initialize the array
    matrix = new double[sizeOfArray]();

    //call the function and store the value of the num of rows in num_equations
    FileInput(matrix, inputfile);

    //get the users choice and call the corresponding function
    menu(matrix, num_equations);

    //delete the matrix when done
    delete [] matrix;

    //close input file
    inputfile.close();

    return 0;
}


int numOfEquations(fstream &inputfile){
    string player;
    //initialize the player count
    int playerCount = 0;

    inputfile.open("matrix.txt", ios :: in);

    //while the file takes in input
    while(inputfile >> player) {
        //and the string is not empty
        if (!player.empty()) {
            //increment player count
            playerCount++;
        }
    }
    //close the input file
    inputfile.close();
    //return the number of equations
    return playerCount;
}

void FileInput(double *matrix, fstream &inputfile) {

    inputfile.open("matrix.txt", ios::in | ios :: binary);

    string equation,variable;

    double *ptm;

    ptm = matrix;

    int counter = 0;

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

                i = 0;
            }
            else if(equation.at(i) == 'z'){
                variable = equation.substr(0, i);
                equation = equation.substr(i + 1);

                length = (int)equation.size();

                ptm += 2;

                *ptm = sign;

                i = 0;
            }
            else if(equation.at(i) == '='){
                variable = equation.substr(i + 1);

                length = 0;

                ptm += 3;

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

            //set the pointer to the original position
            ptm = matrix;
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
        cout << setw(4) << fixed << setprecision(2) << *ptm << " ";
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
    //declare a variable to store the user's choice
    int choice = 0;

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

    if(rowChecker(matrix, row)){
        cout << "you can't use multiplication with this row" << endl;
        return;
    }

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

    //make sure that the row is within range
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

        //make sure that the row is not in the reduced form
        if(rowChecker(matrix, row1)){
            cout << "you can't use scalar multiplication with this row" << endl;
            return;
        }

        //add the rows together
        if(row1 <= numEQ && row1 > 0){
            row1--;

            //make sure that the rows aren't added to themselves
            if(row == row1)
            {
                cout << "Can't add the scalar multiple of the row to itself!" << endl;
                return;
            }

            //set the position of the pointer
            ptm1 += row1*4;

            for(int i = 0; i < 4; i++, ptm++, ptm1++){

                //if the val is zero then all the multiplications will be 0
                if(*ptm == 0){
                    continue;
                }
                //multiply the first row by the multiplier
                *ptm *= multiplier;
                //add the second row with the first row
                *ptm1 += *ptm;
                //divide the first row with the multiplier
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

bool rowChecker(double *matrix, int row){
    double *ptm;
    ptm = matrix;

    bool complete;

    //counters to keep track of the number of 0's and 1's in the row
    double zero_counter = 0, one_counter = 0;

    //put the pointer at the start of the appropriate row
    row--;
    ptm += row*4;

    for(int col = 0; col < 3; col++, ptm++){
        //if the value is 0 continue the loop
        if(*ptm == 0.0){
            zero_counter++;
            //if the first 3 columns are zero then check that the last column is zero or not
            if(zero_counter == 3){
                //set pointer to the next column
                ptm = matrix;
                ptm += row*4 + 3;
                if(*ptm == 0.0){
                    zero_counter++;
                }
            }
            continue;
        }
        //if its one then...
        else if(*ptm == 1.0){
            one_counter++;

            //check if the 1 is being called twice
            if(one_counter > 1){
                //since there are two 1's in the row
                // set complete = false;
                break;
            }
        }
        //if the value is not 1 or 0 then set complete to false;
        else{
            // set complete = false;
            break;
        }

    }

    if((one_counter == 1 && zero_counter == 2)){
        complete = true;
    }
    else if(zero_counter == 4){
        complete = true;
    }
    else{
        complete = false;
    }

    return complete;
}

bool MatrixComplete(double *matrix, int NumEQ) {

    //complete is to check for the entire matrix
    //valid is to check the row
    bool complete = true;

    bool x_value = false, y_value = false, z_value = false;

    double *ptm;

    //have a counter to keep track of the
    int counter = 0;

    int lead = 0;

    double  x=0, y = 0, z = 0;

    //loop through rows and columns
    for(int row = 0; row < NumEQ; row++){

        //counters to keep track of the number of 0's and 1's in the row
        double zero_counter = 0, one_counter = 0;
        //check for the last row if the number of equations is 4 (To be done later)
        //if there are 4 equations check the bottom row for all zeroes
        if(row == 3){
            //start at the beginning of the matrix
            ptm = matrix;
            //go to the last row
            ptm += 12;
            //for all the columns
            for(int i = 0; i < 4 ; i++,ptm++){
                //check if the val at the position is a zero
                if(*ptm == 0.0){
                    continue;
                }
                //if its not then set complete to false and return complete
                else{
                    complete = false;
                    return complete;
                }
            }

        }

        //assign the matrix to the next row
        ptm = matrix;
        ptm += row*4;

        for(int col = 0; col < 3; col++, ptm++){
            //if the value is 0 continue the loop
            if(*ptm == 0.0){
                zero_counter++;
                continue;
            }
            //if its one then...
            else if(*ptm == 1.00){
                one_counter++;
                //check if the leading one is to the right of the previous one
                if(lead >= col && row != 0){
                    complete = false;
                    break;
                }

                //check if the 1 is being called twice
                if(one_counter > 1){
                    //since there are two 1's in the row
                    complete = false;
                    break;
                }

                //assign the lead a new value
                lead = col;


            }
            //if the value is not 1 or 0 then set complete to false;
            else{
                complete = false;
                break;
            }
        }

        //break out of the loop if not a complete matrix
        if(!complete){
            break;
        }

        //if there are 2 0's and a 1 then proceed...
        if(one_counter == 1 && zero_counter == 2){
            //assign values to columns based on specific variables
            ptm = matrix;
            switch(lead){
                //for x
                case 0:
                    x_value = true;
                    ptm += row*4 + 3;
                    x = *ptm;
                    counter++;
                    break;
                //for y
                case 1:
                    y_value = true;
                    ptm += row*4 + 3;
                    y = *ptm;
                    counter++;
                    break;
                //for z
                case 2:
                    z_value = true;
                    ptm += row*4 + 3;
                    z = *ptm;
                    counter++;
                    break;

                default: complete = false;
            }
        }

    }

    //make sure that the number of equations is equal to the number of variable solved
    //for a system of equations not equal to 4
    if(NumEQ < 4){
        //if the varibles solved is not equal to the number of eqautions
        if(counter != NumEQ){
            //set complete to false
            complete = false;
        }
    }
    //and for a system of 4 equations
    else if(NumEQ == 4){
        //increment the counter
        counter++;
        //if the counter is not equal to 4 then ...
        if(counter != NumEQ){
            //set complete to false
            complete = false;
        }
    }

    //if the matrix is in the complete form then find out the values of the appropriate variables
    if(complete){

        cout << "The matrix is in reduced echelon form" << endl;

        if(x_value){
            cout << "the value of x: " << x << endl;
        }
        if(y_value){
            cout << "the value of y: " << y << endl;
        }
        if(z_value){
            cout << "the value of z: " << z << endl;
        }
    }

    return complete;
}
