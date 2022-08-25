#include "character.hpp"

class Generator
{
  private:
	character* generation;

	float max_value = 0;

	void fill();
	void evaluate();

  public:
	Generator(character);
	int gen_size = 1000;
	int max_gen = 1000000;
	int max_idle = 200;

	character base;

	artifact_build generate();
};