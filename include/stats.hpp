#include <iostream>
#include <map>
#include <string>

enum class STAT
{
	HP_,
	HP,
	ATK_,
	ATK,
	DEF_,
	DEF,
	ER,
	EM,
	EDMG,
	PDMG,
	CR,
	CD,
	HEAL
};

class stat_block
{
  private:
	std::map<STAT, float> value;

  public:
	stat_block operator+(const stat_block&);
	stat_block& operator+=(const stat_block&);
	float& operator[](STAT);
	friend std::ostream& operator<<(std::ostream&, const stat_block&);

	std::map<STAT, float> map() { return value; };
};

std::ostream& operator<<(std::ostream&, const STAT&);

std::string stat_str(STAT);

STAT str_stat(std::string);