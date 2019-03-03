//Shreyas Raj Singh sxs170100

#include <iostream>
#include <fstream>
#include <string>

using namespace std;



//a function to get the input from matrix.txt
void FileInput(double *, fstream &, int );

//a function to count the number of players;
int numOfPlayers(fstream &);

//a function to display the matrix
void displayMatrix(double *, int numEQ);

//a function to prompt users for input
void menu(double *, int );

//a function to switch rows
void switchRows(double *, int );

int main(){

    fstream inputfile;
    double *matrix;

    int num_equations = 0;
    num_equations = numOfPlayers(inputfile);
    //check for number of players
    if(num_equations > 4){
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


//Funtion below will open the file given and parse through the equation in the file
//the equations in the file will be stored as an augmented matrix in matrix[][]
//eg- 3x + 4y + 5z = 12
//     x +  y +  z = 11
// will be stored as [(3, 4, 5, 12),
//                    (1 , 1, 1, 11)]
//in matrix[][]

void FileInput(double *matrix, fstream &inputfile, int numEQ) {
    int var = 0, sign = 1;
    char ch;
    double *ptm;
    ptm = matrix;

    inputfile.open("commands.txt", ios::in);
    int t = (int) inputfile.tellp();

    for(int i = 0; i < numEQ ; i++) {

        int col = 4;

        //move pointer to the next set of positions
        if(i != 0)
            ptm += 4;

        //while there are less than 4 cols
        //the loop will also terminate if we reach a newline or constant
        for(int j = 0 ; j < col-1; j++) {
            //check for the character pointed at by the file pointer
            // and store it in c
            int c = inputfile.peek();

            //check if the val is a digit
            if (isdigit(c)) {
                inputfile >> var;
            } else {
                var = 1;
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
                    break;
                }
            }

            //check for operator
            c = inputfile.peek();
            if (c == 45) {
                inputfile.seekp(1, ios::cur);
                sign = -1;
            } else {
                inputfile.seekp(1, ios::cur);
                sign = 1;
            }
        }

        //check for "=" sign
        int  c = inputfile.peek();
        if(c == 61){
            inputfile.seekp(1, ios :: cur);
            inputfile >> var;
            ptm += 3;
            *ptm = var;
            cout << *ptm << endl;
            ptm -= 3;
        }

    }
    inputfile.close();
}

void displayMatrix(double *matrix, int numEQ){
    int length = numEQ*4;
    double *ptm;
    ptm = matrix;
    int counter = 0;
    for(int i = 0; i < length; i++){
        cout << *ptm << " ";
        ptm++;
        counter++;
        if(counter == 4){
            counter = 0;
            cout << endl;
        }
    }
}

void menu( double *matrix, int numEQ){

    double *ptm ;
    int choice;
    ptm = matrix;

    while(choice != 4) {
        displayMatrix(matrix, numEQ);
        cout << "Please choose an option\n"
                "o 1 – Switch two rows\n"
                "o 2 – Multiply row by non-zero number\n"
                "o 3 – Add scalar multiple of one row to another row\n"
                "o 4 – Quit\n";
        cin >> choice;

        switch (choice) {
            case 1 :
                switchRows(matrix, numEQ);
            case 4 :
                cout << "Program terminating" << endl;
        }
    }
    displayMatrix(matrix, numEQ);

}

void switchRows(double *matrix, int numEQ){

}
