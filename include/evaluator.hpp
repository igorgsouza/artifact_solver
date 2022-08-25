#include "stats.hpp"

class evaluator
{

  private:
	stat_block base;
	stat_block artifact;
	stat_block extra;

  public:
	int RES = 10;
	float RESPEN = 0;

	evaluator(stat_block, stat_block);

	float FINAL_HP();
	float FINAL_ATK();
	float FINAL_DEF();

	float DMG_REDUCTION();
	float DEF_REDUCTION();
};