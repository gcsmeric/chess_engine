#include <iostream>
#include "../chess-library-master/include/chess.hpp"
using std::string;
using std::cout;
using std::endl;
using std::cin;
using namespace chess;
using namespace uci;

int mg_pawn_table[64] = {
      0,   0,   0,   0,   0,   0,  0,   0,
     98, 134,  61,  95,  68, 126, 34, -11,
     -6,   7,  26,  31,  65,  56, 25, -20,
    -14,  13,   6,  21,  23,  12, 17, -23,
    -27,  -2,  -5,  12,  17,   6, 10, -25,
    -26,  -4,  -4, -10,   3,   3, 33, -12,
    -35,  -1, -20, -23, -15,  24, 38, -22,
      0,   0,   0,   0,   0,   0,  0,   0,
};

int eg_pawn_table[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
    178, 173, 158, 134, 147, 132, 165, 187,
     94, 100,  85,  67,  56,  53,  82,  84,
     32,  24,  13,   5,  -2,   4,  17,  17,
     13,   9,  -3,  -7,  -7,  -8,   3,  -1,
      4,   7,  -6,   1,   0,  -5,  -1,  -8,
     13,   8,   8,  10,  13,   0,   2,  -7,
      0,   0,   0,   0,   0,   0,   0,   0,
};

int mg_knight_table[64] = {
    -167, -89, -34, -49,  61, -97, -15, -107,
     -73, -41,  72,  36,  23,  62,   7,  -17,
     -47,  60,  37,  65,  84, 129,  73,   44,
      -9,  17,  19,  53,  37,  69,  18,   22,
     -13,   4,  16,  13,  28,  19,  21,   -8,
     -23,  -9,  12,  10,  19,  17,  25,  -16,
     -29, -53, -12,  -3,  -1,  18, -14,  -19,
    -105, -21, -58, -33, -17, -28, -19,  -23,
};

int eg_knight_table[64] = {
    -58, -38, -13, -28, -31, -27, -63, -99,
    -25,  -8, -25,  -2,  -9, -25, -24, -52,
    -24, -20,  10,   9,  -1,  -9, -19, -41,
    -17,   3,  22,  22,  22,  11,   8, -18,
    -18,  -6,  16,  25,  16,  17,   4, -18,
    -23,  -3,  -1,  15,  10,  -3, -20, -22,
    -42, -20, -10,  -5,  -2, -20, -23, -44,
    -29, -51, -23, -15, -22, -18, -50, -64,
};

int mg_bishop_table[64] = {
    -29,   4, -82, -37, -25, -42,   7,  -8,
    -26,  16, -18, -13,  30,  59,  18, -47,
    -16,  37,  43,  40,  35,  50,  37,  -2,
     -4,   5,  19,  50,  37,  37,   7,  -2,
     -6,  13,  13,  26,  34,  12,  10,   4,
      0,  15,  15,  15,  14,  27,  18,  10,
      4,  15,  16,   0,   7,  21,  33,   1,
    -33,  -3, -14, -21, -13, -12, -39, -21,
};

int eg_bishop_table[64] = {
    -14, -21, -11,  -8, -7,  -9, -17, -24,
     -8,  -4,   7, -12, -3, -13,  -4, -14,
      2,  -8,   0,  -1, -2,   6,   0,   4,
     -3,   9,  12,   9, 14,  10,   3,   2,
     -6,   3,  13,  19,  7,  10,  -3,  -9,
    -12,  -3,   8,  10, 13,   3,  -7, -15,
    -14, -18,  -7,  -1,  4,  -9, -15, -27,
    -23,  -9, -23,  -5, -9, -16,  -5, -17,
};

int mg_rook_table[64] = {
     32,  42,  32,  51, 63,  9,  31,  43,
     27,  32,  58,  62, 80, 67,  26,  44,
     -5,  19,  26,  36, 17, 45,  61,  16,
    -24, -11,   7,  26, 24, 35,  -8, -20,
    -36, -26, -12,  -1,  9, -7,   6, -23,
    -45, -25, -16, -17,  3,  0,  -5, -33,
    -44, -16, -20,  -9, -1, 11,  -6, -71,
    -19, -13,   1,  17, 16,  7, -37, -26,
};

int eg_rook_table[64] = {
    13, 10, 18, 15, 12,  12,   8,   5,
    11, 13, 13, 11, -3,   3,   8,   3,
     7,  7,  7,  5,  4,  -3,  -5,  -3,
     4,  3, 13,  1,  2,   1,  -1,   2,
     3,  5,  8,  4, -5,  -6,  -8, -11,
    -4,  0, -5, -1, -7, -12,  -8, -16,
    -6, -6,  0,  2, -9,  -9, -11,  -3,
    -9,  2,  3, -1, -5, -13,   4, -20,
};

int mg_queen_table[64] = {
    -28,   0,  29,  12,  59,  44,  43,  45,
    -24, -39,  -5,   1, -16,  57,  28,  54,
    -13, -17,   7,   8,  29,  56,  47,  57,
    -27, -27, -16, -16,  -1,  17,  -2,   1,
     -9, -26,  -9, -10,  -2,  -4,   3,  -3,
    -14,   2, -11,  -2,  -5,   2,  14,   5,
    -35,  -8,  11,   2,   8,  15,  -3,   1,
     -1, -18,  -9,  10, -15, -25, -31, -50,
};

int eg_queen_table[64] = {
     -9,  22,  22,  27,  27,  19,  10,  20,
    -17,  20,  32,  41,  58,  25,  30,   0,
    -20,   6,   9,  49,  47,  35,  19,   9,
      3,  22,  24,  45,  57,  40,  57,  36,
    -18,  28,  19,  47,  31,  34,  39,  23,
    -16, -27,  15,   6,   9,  17,  10,   5,
    -22, -23, -30, -16, -16, -23, -36, -32,
    -33, -28, -22, -43,  -5, -32, -20, -41,
};

int mg_king_table[64] = {
    -65,  23,  16, -15, -56, -34,   2,  13,
     29,  -1, -20,  -7,  -8,  -4, -38, -29,
     -9,  24,   2, -16, -20,   6,  22, -22,
    -17, -20, -12, -27, -30, -25, -14, -36,
    -49,  -1, -27, -39, -46, -44, -33, -51,
    -14, -14, -22, -46, -44, -30, -15, -27,
      1,   7,  -8, -64, -43, -16,   9,   8,
    -15,  36,  12, -54,   8, -28,  24,  14,
};

int eg_king_table[64] = {
    -74, -35, -18, -18, -11,  15,   4, -17,
    -12,  17,  14,  17,  17,  38,  23,  11,
     10,  17,  23,  15,  20,  45,  44,  13,
     -8,  22,  24,  27,  26,  33,  26,   3,
    -18,  -4,  21,  24,  27,  23,   9, -11,
    -19,  -3,  11,  21,  23,  16,   7,  -9,
    -27, -11,   4,  13,  14,   4,  -5, -17,
    -53, -34, -21, -11, -28, -14, -24, -43
};

int* pestoTables[12] =
{
    mg_pawn_table,
    mg_knight_table,
    mg_bishop_table,
    mg_rook_table,
    mg_queen_table,
    mg_king_table,
    eg_pawn_table,
    eg_knight_table,
    eg_bishop_table,
    eg_rook_table,
    eg_queen_table,
    eg_king_table
};

int coefficients[5] = {100,300,300,500,900};

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

//Given a board square and color, returns the corresponding pesto piece-square table index
int sqToPestoTableIndex(Square sq, Color color) {
    if (color == Color::WHITE) {
        return static_cast<int>(utils::squareFile(sq)) + 8*(7-static_cast<int>(utils::squareRank(sq)));
    }
    else {
        return static_cast<int>(utils::squareFile(sq)) + 8*static_cast<int>(utils::squareRank(sq));
    } 
}

//check if game is in the endgame stage based on amount of material left (so that depth can be increased thanks to lower branching factor)
bool isEndgame(Board board) {
    int mat = 0;
    int pieceIndex = 0;
    for (const PieceType p : {PieceType::PAWN, PieceType::KNIGHT, PieceType::BISHOP, PieceType::ROOK, PieceType::QUEEN}) {
        mat += coefficients[pieceIndex]*builtin::popcount(board.pieces(p, Color::WHITE));
        mat += coefficients[pieceIndex]*builtin::popcount(board.pieces(p, Color::BLACK));
        pieceIndex += 1;
    }
    return (mat <= 30);
}

int16_t eval(const Board& board) {
    //returns eval in centipawns of position (W.R.T. player who's turn it is)
    //i.e. eval of 100 when it's black's turn means black has an advantage worth roughly a pawn

    //material eval
    int16_t matEval = 0;
    Color sideToMove = board.sideToMove();
    int pieceIndex = 0;
    int whiteMat = 0;
    int blackMat = 0;
    for (const PieceType p : {PieceType::PAWN, PieceType::KNIGHT, PieceType::BISHOP, PieceType::ROOK, PieceType::QUEEN}) {
        whiteMat += coefficients[pieceIndex]*builtin::popcount(board.pieces(p, Color::WHITE));
        blackMat += coefficients[pieceIndex]*builtin::popcount(board.pieces(p, Color::BLACK));
        pieceIndex += 1;
    }
    matEval = whiteMat - blackMat;
    

    //determine whether to use middlegame or endgame piece-square tables
    int pestoTablesBaseIndex = 0;
    if (whiteMat + blackMat <= 30) {
        pestoTablesBaseIndex = 6;
    }
    int pieceSquareTableEval = 0;
    int piecePestoTableIndex = 1;

    //iterate through all pieces on the board and their positions and adjust evaluation according to pesto piece-square tables
    for (const PieceType p : {PieceType::PAWN, PieceType::KNIGHT, PieceType::BISHOP, PieceType::ROOK, PieceType::QUEEN, PieceType::KING}) {
        Bitboard whiteBB = board.pieces(p, Color::WHITE);
        Bitboard blackBB = board.pieces(p, Color::BLACK);
        while (whiteBB) {
            Square sq = builtin::poplsb(whiteBB);
            pieceSquareTableEval += pestoTables[pestoTablesBaseIndex+piecePestoTableIndex][sqToPestoTableIndex(sq, Color::WHITE)];
        }
        while (blackBB) {
            Square sq = builtin::poplsb(blackBB);
            pieceSquareTableEval -= pestoTables[pestoTablesBaseIndex+piecePestoTableIndex][sqToPestoTableIndex(sq, Color::BLACK)];
        }
        piecePestoTableIndex += 1;
    }

    if (sideToMove == Color::BLACK) {
        matEval *= -1;
        pieceSquareTableEval *= -1;
    }
    
    int16_t totalEval = matEval+pieceSquareTableEval;

    return totalEval;
}

//naive negaMax implementation of minimax search
int16_t negaMax(Board board, int depth) {
    if (depth == 0) {
        return eval(board);
    }
    int16_t max = -32767; 
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (const auto &move : currLegalMoves) {
        board.makeMove(move);
        int16_t score = -negaMax(board, depth-1);
        board.unmakeMove(move);
        if (score > max) {
            max = score;
        }
    }
    //in case of mate, check if stalemate
    if (currLegalMoves.size() == 0) {
        Color sideToMove = board.sideToMove();
        if (board.isAttacked(board.kingSq(sideToMove), sideToMove)) {
            return -32767;
        }
        else {
            return 0;
        }
    }
    return max;
}

//root call for naive negaMax implementation of minimax search
Move rootNegaMax(Board board, int depth) {
    assert(depth>0);
    int16_t max = -32767; 
    Move bestMove;
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (const auto &move : currLegalMoves) {
        board.makeMove(move);
        int16_t score = -negaMax(board, depth-1);
        board.unmakeMove(move);
        if (score > max) {
            max = score;
            bestMove = move;
        }
    }
    return bestMove;
}

//quiescence eval function, a modified version of the basic eval function adjusted to operate with alpha-beta pruning
//and to fully investigate all capture sequences from the current position to ensure that depth-related limitations 
//don't lead to erroneous evaluation values
int16_t quiesce(Board& board, int16_t alpha, int16_t beta) {
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
    for (const auto &move : currCaptureMoves) {
        board.makeMove(move);
        int16_t score = -quiesce(board, -beta, -alpha);
        board.unmakeMove(move);

        if (score >= beta) {
            return beta;
        }
        if (score > alpha) {
            alpha = score;
        }
    }
    return alpha;
}

//negaMax minimax search with alpha-beta pruning optimization
int16_t alphaBeta(Board& board, int16_t alpha, int16_t beta, int remDepth) {

    if (remDepth == 0) {
        return quiesce(board, alpha, beta);
    }
    Movelist currLegalMoves = Movelist();
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (const auto &move : currLegalMoves) {
        board.makeMove(move);
        int16_t score = -alphaBeta(board, -beta, -alpha, remDepth-1);
        board.unmakeMove(move);
        if (score >= beta) {
            return beta;
        }
        if (score > alpha) {
            alpha = score;
        }
    }
    //in case of mate, check for stalemate 
    if (currLegalMoves.size() == 0) {
        Color sideToMove = board.sideToMove();
        if (board.isAttacked(board.kingSq(sideToMove), sideToMove)) {
            return -32767;
        }
        else {
            return 0;
        }
    }
    return alpha;
}

//root call for negaMax minimax search with alpha-beta pruning optimization
Move alphaBetaSearchRoot(Board& board, int16_t alpha, int16_t beta, int remDepth) {
    assert(remDepth > 0);
    Move bestMove = Move::NULL_MOVE;
    Movelist currLegalMoves = Movelist();
    int16_t currMaxScore = -32767;
    movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
    for (const auto &move : currLegalMoves) {
        board.makeMove(move);
        //account for triple repetition - avoid it in winning positions
        if (board.isRepetition() && (bestMove != Move::NULL_MOVE) && (quiesce(board, alpha, beta) > 500)) {
            board.unmakeMove(move);
            continue;
        }
        int16_t score = -alphaBeta(board, -beta, -alpha, remDepth-1);
        board.unmakeMove(move);
        if (score > alpha) {
            alpha = score;
        }
        if (score > currMaxScore) {
            currMaxScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

int main() {
    cout << "Launching chess program" << endl;
    Board board;
    Move inputMove;
    string inputMoveStr;
    int depth = 4;
    while (true){
        while (true) {
            cout << " Input your move in UCI format: " << endl;
            cin >> inputMoveStr;
            inputMove = uci::uciToMove(board, inputMoveStr);
            Movelist currLegalMoves;
            movegen::legalmoves<MoveGenType::ALL>(currLegalMoves, board);
            bool isLegalMoveFlag = false;
            for (const auto &move : currLegalMoves) {
                if (move == inputMove) {
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
        if (isEndgame(board)) {
            cout << "we're in the endgame now";
            depth = 6;
        }
        Move engineResponse = alphaBetaSearchRoot(board, -32767, 32767, depth);
        cout << engineResponse << "\n";
        board.makeMove(engineResponse);
        cout << board << "\n";
    }
    cout << "GAMEOVER";
    return 0;
}