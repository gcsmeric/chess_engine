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
                char fifthChar = str[4];
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

int bitBoardCardinality (U64 x) {
   int count = 0;
   while (x) {
       count++;
       x &= x - 1;
   }
   return count;
}

/*float eval(Board board) {
    //material eval
    float matEval = 0;
    std::vector<int> coefficients = {1,3,3,5,9};
    int coeffIndex = 0;
    for (const auto p : {PieceType::PAWN, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN}) {
        matEval += coefficients[coeffIndex]*(bitBoardCardinality(board.pieces(p, Color::WHITE))-bitBoardCardinality(board.pieces(p, Color::BLACK)));
        coeffIndex += 1;
    }
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    Move randomMove = currLegalMoves[0];
    board.makeNullMove();
    Movelist currOpponentLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currOpponentLegalMoves, board);
    board.unmakeNullMove();
    float mobilityEval = 0.02*(currLegalMoves.size()-currOpponentLegalMoves.size());
    float currentTurnBonus = 0.1;
    if (board.sideToMove() == Color::BLACK) {
        mobilityEval *= -1;
        currentTurnBonus *= -1;
    }
    float totalEval = matEval+mobilityEval+currentTurnBonus;
    if (board.sideToMove() == Color::BLACK) {
        totalEval *= -1;
    }

    return totalEval;
    //IMPLEMENT NAIVE https://www.chessprogramming.org/Evaluation#Where_to_Start
    //MATERIAL EVAL (FIGURE OUT HOW TO ITERATE OVER PIECE AND COLOR ENUMS 
    //AND ADD THOSE VALS TO MATEVAL)
    //THEN ADD TO EVAL A FACTOR BASED ON MOBILITY AS IN LINK MATERIAL EXAMPLE ABOVE
    //(NUMBER OF LEGAL MOVES), THEN ALSO A FACTOR FOR WHO'S TURN IT IS AND FINALLY
    //SOME TABLES OF PIECE VALUES FOR EACH SQUARE https://www.chessprogramming.org/Piece-Square_Tables
    //https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
}*/

int16_t eval(Board board) {
    //material eval
    int16_t matEval = 0;
    std::vector<int> coefficients = {1000,3000,3000,5000,9000};
    int coeffIndex = 0;
    for (const auto p : {PieceType::PAWN, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN}) {
        matEval += coefficients[coeffIndex]*(bitBoardCardinality(board.pieces(p, Color::WHITE))-bitBoardCardinality(board.pieces(p, Color::BLACK)));
        coeffIndex += 1;
    }
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    Move randomMove = currLegalMoves[0];
    board.makeNullMove();
    Movelist currOpponentLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currOpponentLegalMoves, board);
    board.unmakeNullMove();
    int16_t mobilityEval = currLegalMoves.size()-currOpponentLegalMoves.size();
    int16_t currentTurnBonus = 150;
    if (board.sideToMove() == Color::BLACK) {
        mobilityEval *= -1;
        currentTurnBonus *= -1;
    }
    int16_t totalEval = matEval+mobilityEval+currentTurnBonus;
    if (board.sideToMove() == Color::BLACK) {
        totalEval *= -1;
    }

    return totalEval;
    //IMPLEMENT NAIVE https://www.chessprogramming.org/Evaluation#Where_to_Start
    //MATERIAL EVAL (FIGURE OUT HOW TO ITERATE OVER PIECE AND COLOR ENUMS 
    //AND ADD THOSE VALS TO MATEVAL)
    //THEN ADD TO EVAL A FACTOR BASED ON MOBILITY AS IN LINK MATERIAL EXAMPLE ABOVE
    //(NUMBER OF LEGAL MOVES), THEN ALSO A FACTOR FOR WHO'S TURN IT IS AND FINALLY
    //SOME TABLES OF PIECE VALUES FOR EACH SQUARE https://www.chessprogramming.org/Piece-Square_Tables
    //https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
}

float negaMax(Board board, int depth) {
    if (depth == 0) {
        return eval(board);
    }
    float max = -9999999; 
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (int i=0; i<currLegalMoves.size(); i++) {
        board.makeMove(currLegalMoves[i]);
        float score = -negaMax(board, depth-1);
        if (score > max) {
            max = score;
        }
        board.unmakeMove(currLegalMoves[i]);
    }
    return max;
    //then implement alpha beta pruning https://www.chessprogramming.org/Alpha-Beta
}

Move rootNegaMax(Board board, int depth) {
    assert(depth>0);
    float max = -9999999; 
    Move bestMove;
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (int i=0; i<currLegalMoves.size(); i++) {
        board.makeMove(currLegalMoves[i]);
        float score = -negaMax(board, depth-1);
        if (score > max) {
            max = score;
            bestMove = currLegalMoves[i];
        }
        board.unmakeMove(currLegalMoves[i]);
    }
    return bestMove;
    //then implement alpha beta pruning https://www.chessprogramming.org/Alpha-Beta
}

int main() {
    cout << "Launching chess program" << endl;
    Board board;
    Move inputMove;
    string inputMoveStr = "";
    //board.sideToMove(); !!
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
        Move engineResponse = rootNegaMax(board, 4);
        board.makeMove(engineResponse);
        cout << engineResponse;
    }
    
    return 0;
}