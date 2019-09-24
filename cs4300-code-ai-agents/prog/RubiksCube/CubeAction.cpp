#include "CubeAction.h"
#include <iostream>

// An instance of this class needs to be able to uniquely
// identify any of the legal actions

namespace ai
{
namespace rubiks
{

Action::Action(const Move &move)
    : mMove(move)
{
}

Action::~Action()
{
}

void Action::Display() const
{
  std::cout << mMove.getName() << std::endl;
}

const Move &Action::getMove() const
{
  return mMove;
}

} // namespace rubiks
} // namespace ai

std::ostream &operator<<(std::ostream &os, const ai::rubiks::Action &action)
{
  os << action.getMove().getName();
  return os;
}
