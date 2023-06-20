#include <cstdlib>
#include <cmath>
#include <limits.h>
#include <set>

#include "../state/state.hpp"
#include "./minimax.hpp"

std::set<Move> s;
int minimax(State* state, int depth){
  if(depth==0 || state->game_state!=UNKNOWN || state->legal_actions.size()==0){
    return state->evaluate();
  }  
  auto actions = state->legal_actions;
  int value;
  if(depth%2==1){
    value = -1 * INT_MAX;
    for(auto it:actions){
      if(s.find(it)!=s.cend()){
        s.insert(it);
        value = std::max(value,minimax(state->next_state(it),depth-1));
      }
    }
    return value;
  }
  else{
    value = INT_MAX;
    for(auto it:actions){
      if(s.find(it)!=s.cend()){
        s.insert(it);
      value = std::min(value,minimax(state->next_state(it),depth-1));
      }
    }
    return value;
  }
}
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  
}