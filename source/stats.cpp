#include <stats.hpp>

stat_block stat_block::operator+(const stat_block& stbl)
{
	stat_block aux = *this;
	for (auto const& [key, val] : stbl.value)
	{
		aux[key] += val;
	}
	return aux;
}

stat_block& stat_block::operator+=(const stat_block& stbl)
{
	*this = *this + stbl;
	return *this;
}

float& stat_block::operator[](STAT s)
{
	if (this->value.find(s) == this->value.end())
	{
		this->value.insert(std::pair<STAT, float>(s, 0));
	}
	return this->value[s];
}

std::ostream& operator<<(std::ostream& os, const stat_block& stbl)
{
	for (auto const& [key, val] : stbl.value)
	{
		os << key << ':' << val << std::endl;
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const STAT& s)
{
	return os << stat_str(s);
}

std::string stat_str(STAT s)
{
	static std::map<STAT, std::string> strings;

	if (strings.size() == 0)
	{
		strings[STAT::HP_] = "HP%";
		strings[STAT::HP] = "HP";
		strings[STAT::ATK_] = "ATK%";
		strings[STAT::ATK] = "ATK";
		strings[STAT::DEF_] = "DEF%";
		strings[STAT::DEF] = "DEF";
		strings[STAT::ER] = "ER";
		strings[STAT::EM] = "EM";
		strings[STAT::EDMG] = "EDMG";
		strings[STAT::PDMG] = "PDMG";
		strings[STAT::CR] = "CR";
		strings[STAT::CD] = "CD";
		strings[STAT::HEAL] = "HEAL";
	}

	return strings[s];
}

STAT str_stat(std::string str)
{
	static std::map<STAT, std::string> strings;

	if (strings.size() == 0)
	{
		strings[STAT::HP_] = "HP%";
		strings[STAT::HP] = "HP";
		strings[STAT::ATK_] = "ATK%";
		strings[STAT::ATK] = "ATK";
		strings[STAT::DEF_] = "DEF%";
		strings[STAT::DEF] = "DEF";
		strings[STAT::ER] = "ER";
		strings[STAT::EM] = "EM";
		strings[STAT::EDMG] = "EDMG";
		strings[STAT::PDMG] = "PDMG";
		strings[STAT::CR] = "CR";
		strings[STAT::CD] = "CD";
		strings[STAT::HEAL] = "HEAL";
	}

	for (auto const& [key, val] : strings)
		if (val == str)
			return key;

	return STAT::HP;
}
