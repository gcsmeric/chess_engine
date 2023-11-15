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
    //returns eval in centipawns of position (W.R.T. player who's turn it is)
    //i.e. eval of 100 when it's black's turn means black has an advantage worth roughly a pawn

    //material eval
    int16_t matEval = 0;
    Color sideToMove = board.sideToMove();
    std::vector<int> coefficients = {100,300,300,500,900};
    int coeffIndex = 0;
    for (const PieceType p : {PieceType::PAWN, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN}) {
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
    //int16_t currentTurnBonus = 15;
    if (sideToMove == Color::BLACK) {
        matEval *= -1;
    }
    int16_t totalEval = matEval+mobilityEval;
    //handle checkmate and stalemate positions
    if (currLegalMoves.size() == 0) {
        if (board.isAttacked(board.kingSq(sideToMove), sideToMove)) {
            totalEval = -32767;    
        }
        else {
            totalEval = 0;
        }
    }
    else if (currOpponentLegalMoves.size() == 0) {
        Color oppositeColor;
        if (sideToMove == Color::WHITE) {
            oppositeColor == Color::BLACK;
        }
        else {
            oppositeColor == Color::WHITE;
        }
        if (board.isAttacked(board.kingSq(oppositeColor), oppositeColor)) {
            totalEval = 32767;    
        }
        else {
            totalEval = 0;
        }
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

int16_t negaMax(Board board, int depth) {
    if (depth == 0) {
        return eval(board);
    }
    int16_t max = -32767; 
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (int i=0; i<currLegalMoves.size(); i++) {
        board.makeMove(currLegalMoves[i]);
        int16_t score = -negaMax(board, depth-1);
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
    int16_t max = -32767; 
    Move bestMove;
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (int i=0; i<currLegalMoves.size(); i++) {
        board.makeMove(currLegalMoves[i]);
        int16_t score = -negaMax(board, depth-1);
        if (score > max) {
            max = score;
            bestMove = currLegalMoves[i];
        }
        board.unmakeMove(currLegalMoves[i]);
    }
    return bestMove;
    //then implement alpha beta pruning https://www.chessprogramming.org/Alpha-Beta
}

int16_t quiesce(Board board, int16_t alpha, int16_t beta) {
    int16_t stand_pat = eval(board);
    if (stand_pat >= beta) {
        return beta;
    }
    if (alpha < stand_pat) {
        alpha = stand_pat;
    }
    //investigate all captures fully to avoid scenarios where max depth is reached mid piece-exchange
    //which can lead to faulty valuations (since capture-back is not seen by engine which'll erroneously
    //think it's gained material)
    Movelist currCaptureMoves = Movelist();
    movegen::legalmoves<MoveGenType::CAPTURE>(currCaptureMoves, board);
    for (int i=0; i<currCaptureMoves.size(); i++) {
        board.makeMove(currCaptureMoves[i]);
        int16_t score = -quiesce(board, -beta, -alpha);
        board.unmakeMove(currCaptureMoves[i]);

        if (score >= beta) {
            return beta;
        }
        if (score > alpha) {
            alpha = score;
        }
    }
    return alpha;
}

int16_t alphaBeta(Board board, int16_t alpha, int16_t beta, int remDepth) {
    if (remDepth == 0) {
        //cout << quiesce(board, alpha, beta) << "\n"; 
        return quiesce(board, alpha, beta);
    }
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (int i=0; i<currLegalMoves.size(); i++) {
        board.makeMove(currLegalMoves[i]);
        int16_t score = -alphaBeta(board, -beta, -alpha, remDepth-1);
        //cout << currLegalMoves[i] << " " << score << " " << remDepth << "\n";
        //cout << score << " " << remDepth << " " << alpha << " " << beta << "\n";
        if (score >= beta) {
            return beta;
        }
        if (score > alpha) {
            //cout << score << " " << remDepth << "\n";
            alpha = score;
        }
        board.unmakeMove(currLegalMoves[i]);
    }
    return alpha;
}

Move alphaBetaSearchRoot(Board board, int16_t alpha, int16_t beta, int remDepth) {
    assert(remDepth > 0);
    Move bestMove;
    Movelist currLegalMoves = Movelist();
    int16_t currMaxScore = -32767;
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (int i=0; i<currLegalMoves.size(); i++) {
        /*if (i==0) {
            bestMove = currLegalMoves[i];
        }*/
        board.makeMove(currLegalMoves[i]);
        int16_t score = -alphaBeta(board, -beta, -alpha, remDepth-1);
        cout << currLegalMoves[i] << " " << score << " " << remDepth << "\n";
        cout << quiesce(board, alpha, beta) << "\n";
        //cout << score << " " << remDepth << "\n";
        //cout << currLegalMoves[i] << " " << score << "\n";
        if (score >= beta) {
            //cout << "remdepth " << remDepth << "\n";
            return beta;
        }
        if (score > alpha) {
            alpha = score;
        }
        if (score > currMaxScore) {
            bestMove = currLegalMoves[i];
            //cout << "updated best legal move " << currLegalMoves[i] << "\n";
        }
        board.unmakeMove(currLegalMoves[i]);
    }
    return bestMove;
}

int main() {
    cout << "Launching chess program" << endl;
    Board board;
    Move inputMove;
    string inputMoveStr = "";
    int depth = 4;
    while (true){
        while (true) {
            cout << " Input your move: " << endl;
            cin >> inputMoveStr;
            inputMove = uci::uciToMove(board, inputMoveStr);
            Movelist currLegalMoves;
            movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
            bool isLegalMoveFlag = false;
            for (int i=0; i<currLegalMoves.size(); i++) {
                if (currLegalMoves[i] == inputMove) {
                    isLegalMoveFlag = true;
                }
            }
            if (verifyInputMove(inputMoveStr) && isLegalMoveFlag) {
                cout << "Move Accepted - Computing Response" << endl;
                break;
            }
            else {
                cout << "Invalid or illegal move. Please try again.";
            }
        }
    
        board.makeMove(inputMove);
        //Move engineResponse = rootNegaMax(board, depth);
        Move engineResponse = alphaBetaSearchRoot(board, -32767, 32767, depth);
        cout << "quiesce eval is " << quiesce(board, -32767, 32767) << "\n";
        cout << "normal eval is " << eval(board) << "\n";
        //cout << alphaBeta(board, -32767, 32767, depth) << "\n";
        board.makeMove(engineResponse);
        cout << engineResponse << "\n";
        //cout << "quiesce eval is " << quiesce(board, -32767, 32767) << "\n";
        //cout << "normal eval is " << eval(board) << "\n";
    }
    
    return 0;
}