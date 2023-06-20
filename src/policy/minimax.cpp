#include <cstdlib>
#include <cmath>
#include <limits.h>
#include <set>

#include "../state/state.hpp"
#include "./minimax.hpp"

int minimax(State* state, int depth, int player){
  if(depth==0 || state->game_state!=UNKNOWN || state->legal_actions.size()==0){
    return state->evaluate();
  }  
  auto actions = state->legal_actions;
  int value;
  if(player){
    value = -1 * INT_MAX;
    for(auto it:actions){
      value = std::max(value,minimax(state->next_state(it),depth-1,0));
    }
    return value;
  }
  else{
    value = INT_MAX;
    for(auto it:actions){
      value = std::min(value,minimax(state->next_state(it),depth-1,1));
    }
    return value;
  }
}

Move Minimax::get_move(State *state, int depth){
  // if no legal action
  if(!state->legal_actions.size())
    state->get_legal_actions();
  int max = minimax(state,depth,1);
  for(auto it:state->legal_actions){
    state->next_state(it)->evaluate()==max;
    return it;
  }
}