#include "CubeAction.h"
#include <iostream>

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
  std::cout << mMove.DisplayString() << std::endl;
}

const Move &Action::getMove() const
{
  return mMove;
}

} // namespace rubiks
} // namespace ai

std::ostream &operator<<(std::ostream &os, const ai::rubiks::Action &action)
{
  os << action.getMove().DisplayString();
  return os;
}
