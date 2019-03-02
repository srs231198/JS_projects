//Shreyas Raj Singh sxs170100

#include <iostream>
#include <fstream>
#include <string>

using namespace std;



//a function to get the input from matrix.txt
void FileInput(double *, fstream &, int );

//a function to count the number of players;
int numOfPlayers(fstream &);

int main(){

    fstream inputfile;
    double *matrix;

    int num_equations = 0;
    num_equations = numOfPlayers(inputfile);
    int sizeOfArray = num_equations*4;

    matrix = new double[sizeOfArray]();

    //call the function and store the value of the num of rows in num_equations
    FileInput(matrix, inputfile, num_equations);

    inputfile.close();
}


int numOfPlayers(fstream &inputfile){
    string player;
    int playerCount = 0;
    inputfile.open("commands.txt", ios :: in);
    int t = (int)inputfile.tellp();

    while(!inputfile.eof()){
        getline(inputfile,player);
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

        //while there are less than 4 cols
        //the loop will also terminate if we reach a newline or constant
        while (col > 0) {
            //check for the character pointed at by the file pointer
            // and store it in c
            int c = inputfile.peek();

            //check for newline
            if(c == 10){
                break;
            }

            //check if the val is a digit
            if (isdigit(c)) {
                inputfile >> var;
            }
            else{
                var = 1;
            }

            //check for character
            c = inputfile.peek();
            if (isalpha(c)) {

                inputfile >> ch;

                if (c == 120) {
                    *ptm = var*sign;
                }
                else if (c == 121) {
                    ptm++;
                    *ptm = var*sign;
                    ptm--;
                }
                else if (c == 122) {
                    ptm += 2;
                    *ptm = var*sign;
                    ptm -= 2;
                }
            }

            //check for operator
            c = inputfile.peek();
            if(c == 45){
                sign = -1;
            }
            else{
                sign = 1;
            }

            //decrement the coloum
            col--;
            //move pointer to the next set of positions
            ptm += 4;
        }

    }
    inputfile.close();
}
