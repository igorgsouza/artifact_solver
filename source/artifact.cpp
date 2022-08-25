#include <artifact.hpp>

stat_block substat_level(STAT s, int lvl)
{
	stat_block aux;
	float mult = 0;
	switch (s)
	{
		case STAT::ATK_:
		case STAT::HP_:
			mult = 5.83;
			break;
		case STAT::HP:
			mult = 298.76;
			break;
		case STAT::ATK:
			mult = 19.42;
			break;
		case STAT::DEF_:
			mult = 7.29;
			break;
		case STAT::DEF:
			mult = 23.13;
			break;
		case STAT::EM:
			mult = 23.3;
			break;
		case STAT::ER:
			mult = 6.48;
			break;
		case STAT::CR:
			mult = 3.89;
			break;
		case STAT::CD:
			mult = 7.77;
			break;
		default:
			aux[s] = 0;
			break;
	}
	aux[s] = mult * (lvl + 1);

	return aux;
}

stat_block mainstat_level(STAT s, int lvl = 20)
{
	stat_block aux;
	float mult = 0;
	switch (s)
	{
		case STAT::ATK_:
		case STAT::HP_:
			mult = 46.6;
			break;
		case STAT::HP:
			mult = 4780;
			break;
		case STAT::ATK:
			mult = 311;
			break;
		case STAT::DEF_:
			mult = 58.3;
			break;
		case STAT::ER:
			mult = 51.8;
			break;
		case STAT::EM:
			mult = 186.5;
			break;
		case STAT::EDMG:
			mult = 46.6;
			break;
		case STAT::PDMG:
			mult = 58.3;
			break;
		case STAT::CR:
			mult = 31.1;
			break;
		case STAT::CD:
			mult = 62.2;
			break;
		case STAT::HEAL:
			mult = 35.9;
			break;
		default:
			aux[s] = 0;
			break;
	}
	aux[s] = mult;

	return aux;
}

std::string Artifact::id()
{
	std::string aux;
	std::map<STAT, int> substat_map;

	aux += stat_str(main_stat) + ":";
	for (int i = 0; i < 4; i++)
	{
		substat_map.insert(std::pair(sub_stat[i], sub_lvl[i]));
	}

	for (std::map<STAT, int>::iterator it = substat_map.begin();
	     it != substat_map.end();
	     it++)
	{
		aux += stat_str(it->first) + std::to_string(it->second);
	}

	return aux;
};

stat_block Artifact::total()
{
	stat_block total = mainstat_level(main_stat);
	for (int i = 0; i < 4; i++)
		total += substat_level(sub_stat[i], sub_lvl[i]);
	return total;
}

Artifact::Artifact(TYPE type)
{
	this->type = type;
	switch (type)
	{
		case TYPE::FOF:
			main = {STAT::HP};
			sub = {STAT::ATK,
			       STAT::DEF,
			       STAT::HP_,
			       STAT::ATK_,
			       STAT::DEF_,
			       STAT::ER,
			       STAT::EM,
			       STAT::CR,
			       STAT::CD};
			break;
		case TYPE::POD:
			main = {STAT::ATK};
			sub = {STAT::HP,
			       STAT::DEF,
			       STAT::HP_,
			       STAT::ATK_,
			       STAT::DEF_,
			       STAT::ER,
			       STAT::EM,
			       STAT::CR,
			       STAT::CD};
			break;
		case TYPE::SOE:
			main = {STAT::HP_,
			        STAT::ATK_,
			        STAT::DEF_,
			        STAT::ER,
			        STAT::EM};
			sub = {STAT::HP,
			       STAT::ATK,
			       STAT::DEF,
			       STAT::HP_,
			       STAT::ATK_,
			       STAT::DEF_,
			       STAT::ER,
			       STAT::EM,
			       STAT::CR,
			       STAT::CD};
			break;
		case TYPE::GOE:
			main = {STAT::HP_,
			        STAT::ATK_,
			        STAT::DEF_,
			        STAT::EDMG,
			        STAT::PDMG,
			        STAT::EM};
			sub = {STAT::HP,
			       STAT::ATK,
			       STAT::DEF,
			       STAT::HP_,
			       STAT::ATK_,
			       STAT::DEF_,
			       STAT::ER,
			       STAT::EM,
			       STAT::CR,
			       STAT::CD};
			break;
		case TYPE::COL:
			main = {STAT::HP_,
			        STAT::ATK_,
			        STAT::DEF_,
			        STAT::CR,
			        STAT::CD,
			        STAT::HEAL,
			        STAT::EM};
			sub = {STAT::HP,
			       STAT::ATK,
			       STAT::DEF,
			       STAT::HP_,
			       STAT::ATK_,
			       STAT::DEF_,
			       STAT::ER,
			       STAT::EM,
			       STAT::CR,
			       STAT::CD};
			break;
		default:
			main = {STAT::ATK};
			sub = {STAT::DEF, STAT::HP, STAT::EDMG, STAT::PDMG};
			break;
	}
}

void Artifact::generate()
{
	std::string current = id();

	int remaining = 5;
	for (int i = 0; i < 4; ++i)
		sub_lvl[i] = 0;

	std::random_device dev;
	std::mt19937 rng(dev());
	while (remaining != 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			std::uniform_int_distribution<> dist(0, remaining);
			int r = dist(rng);
			remaining -= r;
			sub_lvl[i] += r;
		}
	}

	std::uniform_int_distribution<> distmain(0, main.size() - 1);

	auto it = std::begin(main);

	std::advance(it, distmain(rng));

	main_stat = *it;

	std::set<STAT> aux = sub;

	it = aux.find(main_stat);
	if (it != aux.end())
		aux.erase(it);

	for (int i = 0; i < 4; ++i)
	{
		std::uniform_int_distribution<> distsub(0, aux.size() - 1);

		it = std::begin(aux);
		std::advance(it, distsub(rng));
		sub_stat[i] = *it;
		aux.erase(it);
	}

	if (current == id())
		generate();
}

void Artifact::shuffle_main()
{
	if (main.size() < 2)
		return;

	std::set<STAT> aux = main;

	auto it = aux.find(main_stat);
	if (it != aux.end())
		aux.erase(it);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> distmain(0, aux.size() - 1);

	it = std::begin(aux);
	std::advance(it, distmain(rng));

	main_stat = *it;

	aux = sub;
	it = aux.find(main_stat);
	if (it != aux.end())
		aux.erase(it);

	int repeated = 0;
	for (int i = 0; i < 4; ++i)
	{
		it = aux.find(sub_stat[i]);
		if (it != aux.end())
			aux.erase(it);
		else
			repeated = i;
	}

	if (sub.size() - aux.size() < 5)
	{
		std::uniform_int_distribution<> distsub(0, aux.size() - 1);
		it = std::begin(aux);
		std::advance(it, distmain(rng));

		sub_stat[repeated] = *it;
	}
}

void Artifact::shuffle_subs()
{
	std::string current = id();

	std::random_device dev;
	std::mt19937 rng(dev());
	std::set<STAT> aux = sub;

	auto it = aux.find(main_stat);
	if (it != aux.end())
		aux.erase(it);

	for (int i = 0; i < 4; ++i)
	{
		std::uniform_int_distribution<> distsub(0, aux.size() - 1);

		it = std::begin(aux);
		std::advance(it, distsub(rng));
		sub_stat[i] = *it;
		aux.erase(it);
	}

	if (current == id())
		shuffle_subs();
}

void Artifact::shuffle_lvls()
{
	std::string current = id();
	int remaining = 5;
	for (int i = 0; i < 4; ++i)
		sub_lvl[i] = 0;

	std::random_device dev;
	std::mt19937 rng(dev());
	while (remaining != 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			std::uniform_int_distribution<> dist(0, 1);
			int r = dist(rng);
			remaining -= r;
			sub_lvl[i] += r;
			if (remaining == 0)
				break;
		}
	}

	if (current == id())
		shuffle_lvls();
}

void Artifact::id(std::string id)
{
	int sep = id.find(':');
	main_stat = str_stat(id.substr(0, sep));
	id.erase(0, sep + 1);
	for (int i = 0; i < 4; i++)
	{
		for (sep = 0; sep < id.size(); ++sep)
			if (isdigit(id[sep]))
				break;

		sub_stat[i] = str_stat(id.substr(0, sep));
		sub_lvl[i] = (int)id[sep] - 48;
		id.erase(0, sep + 1);
	}
}