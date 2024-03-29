#ifndef _MAZEPROBLEM_H_
#define _MAZEPROBLEM_H_

#include <ai_search.h>
#include "MazeModel.h"
#include "MazeState.h"
namespace cgl
{
  namespace Maze
  {
    class Problem : public ai::Search::Problem
    {
    public:
      Problem(ai::Search::State *initial_state_in, Model *model_in);
      virtual ~Problem();

      virtual std::vector<ai::Search::Action *> Actions(const ai::Search::State * const state_in);
      
      virtual ai::Search::State *Result(const ai::Search::State * const state_in, const ai::Search::Action * const action_in);
      
      virtual bool   GoalTest(const ai::Search::State * const state_in) const;

      virtual double StepCost(const ai::Search::State  * const state1_in,
                              const ai::Search::Action * const action_in,
                              const ai::Search::State  * const state2_in) const;
      
      virtual double Heuristic(const ai::Search::State  * const state_in) const;

      bool SetGoal(State *goal_state_in);
    protected:
      Model *model;
      State *goal_state;
    private:
    };
  }
}

#endif /* _MAZEPROBLEM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
