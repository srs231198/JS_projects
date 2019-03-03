//Shreyas Raj Singh sxs170100

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


//a function to count the number of players;
int numOfPlayers(fstream &);

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

int main(){

    fstream inputfile;
    double *matrix;

    int num_equations = 0;
    num_equations = numOfPlayers(inputfile);
    //check for number of players
    if(num_equations > 4 || num_equations < 2){
        cout << "Only 2-4 players allowed" << endl;
        exit(0);
    }
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


int numOfPlayers(fstream &inputfile){
    string player;
    int playerCount = 0;
    inputfile.open("commands.txt", ios :: in);
    int t = (int)inputfile.tellp();

    while(!inputfile.eof()){
        getline(inputfile,player);
        if(player.size() > 0)
            playerCount++;
    }

 //   int t = inputfile.tellp();
    inputfile.seekp(0, ios::beg);

    inputfile.close();
    return playerCount;
}

void FileInput(double *matrix, fstream &inputfile, int numEQ) {
    int var = 0, sign = 1, counter = 0;
    char ch;
    double *ptm;
    ptm = matrix;

    bool valid, until = false;

    inputfile.open("commands.txt", ios::in);


    while(!until) {

        valid = false;
        until = false;
        var = 1;
        //while there are less than 4 cols
        //the loop will also terminate if we reach a newline or constant
        while(!valid){
            //check for the character pointed at by the file pointer
            // and store it in c
            int c = inputfile.peek();

            if(c == 10){
                inputfile.seekg(1,ios :: cur);
                break;
            }

            //check for operator
            c = inputfile.peek();
            if (c == 45) {
                inputfile.seekg(1, ios::cur);
                sign = -1;
            } else if( c == 43) {
                inputfile.seekg(1, ios::cur);
                sign = 1;
            }

            c = inputfile.peek();
            //check if the val is a digit
            if (isdigit(c)) {
                inputfile >> var;
            }

            //check for character
            c = inputfile.peek();
            if (isalpha(c)) {

                inputfile >> ch;

                //check for x
                if (c == 120) {
                    *ptm = var * sign;
                    cout << *ptm << " ";

                }
                //check for y
                else if (c == 121) {
                    ptm++;
                    *ptm = var * sign;
                    cout << *ptm << " ";
                    ptm--;
                }
                //check for z
                else if (c == 122) {
                    ptm += 2;
                    *ptm = var * sign;
                    cout << *ptm << " ";
                    ptm -= 2;
                }
            }

            //check for "=" sign
            c = inputfile.peek();
            if(c == 61){
                inputfile.seekg(1, ios :: cur);
                inputfile >> var;
                ptm += 3;
                *ptm = var;
                cout << *ptm << endl;
                ptm += 1;
                counter++;
                if(counter == numEQ){
                    until = true;
                    valid = true;
                }

            }

        }

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
    cout << "Enter the rows that you want to switch: " << endl;
    cin >> row1 >> row2;

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

        //multiply the multiplier to the given row
        for (int i = 0; i < 4; i++, ptm++){
            //if the pointer is non zero let the
            if(*ptm == 0){
                continue;
            }
            *ptm *= multiplier;
        }
        ptm -= 4;
    }
    else{
        cout << "The row input must be between " << "1 and " << numEQ << endl;
    }

    cout << "Enter the row you want to be added by the multiplied row" << endl;
    cin >> row1;

    //add the rows together
    if(row1 <= numEQ && row1 > 0){
        row1--;

        //set the position of the pointer
        ptm1 += row1*4;

        for(int i = 0; i < 4; i++, ptm++, ptm1++){
            *ptm1 += *ptm;
        }
    }
    else{
        cout << "The row input must be between " << "1 and " << numEQ << endl;
    }



}