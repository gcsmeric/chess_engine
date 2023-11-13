#include <iostream>
#include "../chess-library-master/include/chess.hpp"
using std::string;
using std::cout;
using std::endl;
using std::cin;
using namespace chess;
using namespace uci;

bool verifyInputMove(string str) {
    // Check if the string has either 4 or 5 characters
    if (str.size() != 4 && str.size() != 5) {
        return false;
    }

    // Check conditions for the first 4 characters
    if (islower(str[0]) && isdigit(str[1]) && islower(str[2]) && isdigit(str[3])) {
        // Check specific range for the first and third characters
        if (str[0] >= 'a' && str[0] <= 'h' && str[2] >= 'a' && str[2] <= 'h' &&
            str[1] >= '1' && str[1] <= '8' && str[3] >= '1' && str[3] <= '8') {
            // If the string has 5 characters, check the 5th character
            if (str.size() == 5) {
                char fifthChar = std::tolower(str[4]); // Convert to lowercase for case-insensitivity
                if (fifthChar == 'n' || fifthChar == 'b' || fifthChar == 'r' || fifthChar == 'q') {
                    return true;
                }
            } else {
                // If the string has 4 characters, it's still considered valid
                return true;
            }
        }
    }

    // If any condition is not met, return false
    return false;
}

float eval(Board board) {
    //material eval
    float matEval = 9*board.pieces(PieceType::PAWN, Color::WHITE);
    PieceType::pw
    //IMPLEMENT NAIVE https://www.chessprogramming.org/Evaluation#Where_to_Start
    //MATERIAL EVAL (FIGURE OUT HOW TO ITERATE OVER PIECE AND COLOR ENUMS 
    //AND ADD THOSE VALS TO MATEVAL)
    //THEN ADD TO EVAL A FACTOR BASED ON MOBILITY AS IN LINK MATERIAL EXAMPLE ABOVE
    //(NUMBER OF LEGAL MOVES), THEN ALSO A FACTOR FOR WHO'S TURN IT IS AND FINALLY
    //SOME TABLES OF PIECE VALUES FOR EACH SQUARE https://www.chessprogramming.org/Piece-Square_Tables
    //https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
}

int main() {
    cout << "Launching chess program" << endl;
    Board board;
    Move inputMove;
    string inputMoveStr = "";
    while (true){
        while (true) {
            cout << " Input your move: " << endl;
            cin >> inputMoveStr;
            if (verifyInputMove(inputMoveStr)) {
                cout << "Move Accepted - Computing Response" << endl;
                break;
            }
        }
        inputMove = uci::uciToMove(board, inputMoveStr);
        board.makeMove(inputMove);



    }
    
    return 0;
}