#include "stats.hpp"
#include <ctype.h>
#include <iomanip>
#include <random>
#include <set>
#include <sstream>

#define ENUMSTAT(p) p = (int)STAT::p

enum class TYPE
{
	FOF,
	POD,
	SOE,
	GOE,
	COL
};

stat_block substat_level(STAT, int);
stat_block mainstat_level(STAT, int);

class Artifact
{
  private:
	TYPE type;
	STAT main_stat;
	STAT sub_stat[4];

	std::set<STAT> main;
	std::set<STAT> sub;

	int sub_lvl[4] = {0, 0, 0, 0};

  public:
	Artifact(TYPE);
	std::string id();
	std::string mainstat_str();

	void id(std::string);
	stat_block total();

	void generate();
	void shuffle_main();
	void shuffle_subs();
	void shuffle_lvls();

	std::map<STAT, int> tc_map();
};