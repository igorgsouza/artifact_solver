#include "artifact_build.hpp"

class character
{
  private:
	stat_block base;
	stat_block weapon;

	float BASE_ATK;
	float BASE_HP;
	float BASE_DEF;

  public:
	artifact_build artifacts;
	stat_block total();

	character();
	character(stat_block, stat_block);
	float evaluate();

	float (*eval_func)(stat_block, stat_block);
};
