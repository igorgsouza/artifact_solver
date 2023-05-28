#include "character.hpp"

class Generator
{
  private:
	character* generation;

	float max_value = 0;

	void fill(int);
	void evaluate();

  public:
	Generator(character);
	int gen_size = 500;
	int max_gen = 2000;
	int max_idle = 100;

	character base;

	artifact_build generate();
};