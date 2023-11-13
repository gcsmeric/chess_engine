#include <iostream>
#include "../chess-library-master/include/chess.hpp"
using std::string;
using std::cout;
using std::endl;
using std::cin;
using namespace chess;

int main() {
    cout << "Launching chess program" << endl;
    Board board;
    while (true){
        Move inputMove;
        string inputMoveStr = "";
        while (inputMoveStr == "") {
            cout << " Input your move: " << endl;
            cin >> inputMoveStr;
            cout << inputMoveStr << endl;
        }

    }
    
    return 0;
}