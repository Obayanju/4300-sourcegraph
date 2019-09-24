#include "CubeProblem.h"
#include "CubeState.h"
#include "CubeAction.h"
#include "CubeAppData.h"
#include "CubeModel.h"
#include <sstream>

namespace ai
{
namespace rubiks
{

Problem::Problem(ai::Search::State *initial_state_in, const std::vector<Cube> &goal_cube_in)
    : ai::Search::Problem(initial_state_in), mGoalCubeIn(goal_cube_in)
{
  // empty
}

Problem::~Problem()
{
  // empty
}

bool Problem::GoalTest(const ai::Search::State *const state_in) const
{
  const State *const state = dynamic_cast<const State *const>(state_in);
  for (auto & goal_cube : mGoalCubeIn)
  {
    if (state->getModel() == goal_cube)
    {
      return true;
    }
  }
  return false;
}

// used to generate the list of legal actions given a particular state
std::vector<ai::Search::Action *> Problem::Actions(const ai::Search::State *const state_in)
{
  // const State *const rs1 = dynamic_cast<const State *const>(state_in);
  std::vector<ai::Search::Action *> actions;

  for (int i = Move::M_U; i <= Move::M_DP; i++)
  {
    Move bm = static_cast<Move::BasicMove>(i);
    Action *a = new Action(bm);
    actions.push_back(a);
  }

  return actions;
}

// used to generate the resulting state for applying an action in a given state
ai::Search::State *Problem::Result(const ai::Search::State *const state_in, const ai::Search::Action *const action_in)
{
  const State *const state = dynamic_cast<const State *const>(state_in);
  const Action *const action = dynamic_cast<const Action *const>(action_in);

  Cube model;
  model.applyMove(action->getMove(), state->getModel());
  return new State(model);
}

double Problem::StepCost(const ai::Search::State *const state1_in,
                         const ai::Search::Action *const action_in,
                         const ai::Search::State *const state2_in) const
{
  const Action *const action = dynamic_cast<const Action *const>(action_in);
  return action->getMove().getCost();
}

double Problem::Heuristic(const ai::Search::State *const state_in) const {
  const State *const state = dynamic_cast<const State *const>(state_in);
  Cube cube = state->getModel();
  std::vector<Facelet> facelets = cube.getFacelets();
}
} // namespace rubiks
} // namespace ai
