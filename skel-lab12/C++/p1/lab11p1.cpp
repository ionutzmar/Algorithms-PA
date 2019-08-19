#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <set>
#include <queue>
#include <vector>

#include "State.h"

class StateComparator {
 public:
  /* Determina algoritmul folosit. */
  enum Algorithm {
    BestFirst,
    AStar,
  };

  StateComparator(Algorithm algorithm, const State solution_State)
      : solution_State_(solution_State),
      algorithm_(algorithm) { }

  int f(State* state) const{
    /* f(n) = g(n) + h(n) */
    /* g(n) = numarul de mutari din pozitia initiala */
    switch(algorithm_) {
      case BestFirst:
        /* g(n) = 0 */
		//functie potrivita pentru BestFirst
        return state->approx_distance(solution_State_);
      case AStar:
        return state->distance() + state->approx_distance(solution_State_);
    }
    return 0;
  }

  bool operator() (State* State1, State* State2) const {
    return f(State1) > f(State2);
  }

 private:
  const State solution_State_;
  const Algorithm algorithm_;
};

/* functie care determina daca doua stari sunt identice */
bool is_explored(std::vector<State*>& closed, State* state) {
  for (std::vector<State*>::const_iterator it = closed.begin();
       it != closed.end();
       ++it) {
    if (state->has_same_state(**it)) {
      return true;
    }
  }
  return false;
}

State* getStateReference(std::vector<State*>& closed, State* state) {
  for (std::vector<State*>::const_iterator it = closed.begin();
       it != closed.end();
       ++it) {
    if (state->has_same_state(**it)) {
      return &(**it);
    }
  }
  return NULL;
}

State* getStateReferenceQueue(std::priority_queue<State*>& closed, State* state) {
  for (std::vector<State*>::const_iterator it = closed.begin();
       it != closed.end();
       ++it) {
    if (state->has_same_state(**it)) {
      return &(**it);
    }
  }
  return NULL;
}
int State::M;
int State::N;
int** State::matrix;

int main() {
  	/* Deschidem un fisier si citim din el configuratia initiala si finala. */
  	std::ifstream in("Puzzle.in");

  	/* Dimensiunea puzzle-ului este setata global, per clasa. */
  	in >> State::M >> State::N;
  	State* initial_State = new State();
  	State* solution_State = new State();
  	in >> *initial_State >> *solution_State;

  	std::cout << "initial point " << *initial_State << std::endl;
  	std::cout << "final point " << *solution_State << std::endl;

	State::matrix = new int*[State::M];
	for(int i = 0; i < State::M; i++) {
		State::matrix[i] = new int[State::N];
		for(int j = 0; j < State::N; j++)
			in >> State::matrix[i][j];
	}

  	/* Pentru nodurile in curs de explorare, implementate ca o coada de
   	* prioritati. */
  	std::priority_queue<State*, std::vector<State*>, StateComparator> open(
      	StateComparator(StateComparator::AStar, *solution_State));

  	/* Initial doar nodul de start este in curs de explorare. */
  	initial_State->set_distance(0);
  	initial_State->set_parent(NULL);
  	open.push(initial_State);

  	/* Pentru nodurile care au fost deja expandate. */
  	std::vector<State*> closed;

	/*TODO: implementare A* */
    while (!open.empty()) {
        State* currentState = open.top();
        open.pop();

        if (currentState->has_same_state((const State&)*solution_State)) {
            currentState->print_path();

            return 0;
        } else if(!is_explored(closed,  currentState)) {
            closed.push_back(currentState);
            std::vector<State*> expanded;
            currentState->expand(expanded);
            for (auto aState : expanded) {
                aState->set_distance(currentState->distance() + 1);
                if (!(is_explored(closed, currentState) || is_explored(closed, currentState))) {
                    aState->set_parent(aState);
                    open.push(aState);
                } else {
                    State* node = (getStateReference(closed, aState) == NULL ? getStateReferenceQueue(open, aState) : getStateReference(closed, aState));
                }
            }
        }

    }

  	return 0;
}
