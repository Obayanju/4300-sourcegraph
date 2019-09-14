#ifndef _CUBESTATE_H_
#define _CUBESTATE_H_

#include "CubeModel.h"
#include "ai_search.h"

namespace ai
{
namespace rubiks
{
class State : public ai::Search::State
{
public:
  State(const Cube &cube);
  State(const State &rhs);
  virtual ~State();
  virtual void Display() const;
  virtual bool IsEqual(const ai::Search::State *const state_in) const;
  virtual bool IsLessThan(const ai::Search::State *const state_in) const;

  bool operator==(const State &rhs) const;
  State &operator=(const State &rhs);

protected:
  Cube mCube;

private:
};

} // namespace rubiks
} // namespace ai

std::ostream &operator<<(std::ostream &os, const ai::rubiks::State &state);

#endif /* _CUBESTATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
