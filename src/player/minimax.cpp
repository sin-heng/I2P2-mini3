#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/minimax.hpp"


State* root;

void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        board.board[pl][i][j] = c;
      }
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}

void write_valid_spot(std::ofstream& fout) {
  // Keep updating the output until getting killed.
  while(true) {
    // Choose a random spot.
    auto move = Minimax::get_move(root, 5);// odd number
    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    break;
  }
}

int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
