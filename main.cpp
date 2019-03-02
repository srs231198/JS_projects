//Shreyas Raj Singh sxs170100

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int col = 4;

//a function to get the input from matrix.txt
void FileInput(int *, fstream &);

//a function to count the number of players;
//int numOfPlayers(fstream &);

int main(){

    fstream inputfile;
    int *matrix;
    //int num_players = numOfPlayers(inputfile);
    matrix = new int[16];
//    int num_equations = 0;
    //inputfile.open("commands.txt", ios :: in);
    //call the function and store the value of the num of rows in num_equations
    FileInput(matrix, inputfile);
    inputfile.close();
}

//
//int numOfPlayers(fstream &inputfile){
//    string player;
//    int playerCount = 0;
//    while(!inputfile.eof()){
//        getline(inputfile,player,'\n');
//        playerCount++;
//    }
//    int t = inputfile.tellp();
//
//
//    return playerCount;
//}


//Funtion below will open the file given and parse through the equation in the file
//the equations in the file will be stored as an augmented matrix in matrix[][]
//eg- 3x + 4y + 5z = 12
//     x +  y +  z = 11
// will be stored as [(3, 4, 5, 12),
//                    (1 , 1, 1, 11)]
//in matrix[][]

void FileInput(int *matrix, fstream &inputfile) {
    int var = 0;
    char ch;
    int *ptm;
    ptm = matrix;

    while(!inputfile.eof()){

    }


}
