#include <artifact_build.hpp>

stat_block artifact_build::total()
{
	return flower.total() + plume.total() + sands.total() +
	       goblet.total() + circlet.total();
}

void artifact_build::generate()
{
	flower.generate();
	plume.generate();
	sands.generate();
	goblet.generate();
	circlet.generate();
}

std::string artifact_build::id()
{
	std::string aux = flower.id() + "|" + plume.id() + "|" +
	                  sands.id() + "|" + goblet.id() + "|" +
	                  circlet.id();
	return aux;
}

void artifact_build::mutate(int iteration = 0)
{
	shuffle_method = iteration % 4;
	std::string current = id();

	/* std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(1, 100);

	if (dist(rng) < shuffle_weight)
	    shuffle(flower);
	if (dist(rng) < shuffle_weight)
	    shuffle(plume);
	if (dist(rng) < shuffle_weight)
	    shuffle(sands);
	if (dist(rng) < shuffle_weight)
	    shuffle(goblet);
	if (dist(rng) < shuffle_weight)
	    shuffle(circlet); */

	switch (iteration % 5)
	{
		case 0:
			shuffle(flower);
			break;
		case 1:
			shuffle(plume);
			break;
		case 2:
			shuffle(sands);
			break;
		case 3:
			shuffle(goblet);
			break;
		case 4:
			shuffle(circlet);
			break;
		default:
			break;
	}
}

void artifact_build::shuffle(Artifact& artf)
{
	/* std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(1, 100);

	int n = dist(rng);
	float p = (100 - reset_weight) / 8.0;

	if (n < p)
	    artf.shuffle_main();
	else if (n < 4.0 * p)
	    artf.shuffle_lvls();
	else if (n < 8.0 * p)
	    artf.shuffle_subs();
	else
	    artf.generate(); */

	if (shuffle_method == 0)
		artf.shuffle_main();
	else if (shuffle_method == 1)
		artf.shuffle_lvls();
	else if (shuffle_method == 2)
		artf.shuffle_subs();
	else if (shuffle_method == 3)
		artf.generate();
}

void artifact_build::id(std::string id)
{
	int sep = 0;
	sep = id.find('|');
	flower.id(id.substr(0, sep));
	id.erase(0, sep + 1);

	sep = id.find('|');
	plume.id(id.substr(0, sep));
	id.erase(0, sep + 1);

	sep = id.find('|');
	sands.id(id.substr(0, sep));
	id.erase(0, sep + 1);

	sep = id.find('|');
	goblet.id(id.substr(0, sep));
	id.erase(0, sep + 1);

	sep = id.find('|');
	circlet.id(id.substr(0, sep));
}

std::string artifact_build::tc_id()
{
	std::string aux = "";
	std::map<STAT, int> substat_map;
	std::map<STAT, int> maps[5];
	maps[0] = flower.tc_map();
	maps[1] = plume.tc_map();
	maps[2] = sands.tc_map();
	maps[3] = goblet.tc_map();
	maps[4] = circlet.tc_map();

	aux += sands.mainstat_str() + " ";
	aux += goblet.mainstat_str() + " ";
	aux += circlet.mainstat_str() + " | ";

	for (int i = 0; i < 5; i++)
	{
		for (std::map<STAT, int>::iterator it = maps[i].begin();
		     it != maps[i].end();
		     it++)
		{
			std::map<STAT, int>::iterator x =
			    substat_map.find(it->first);
			if (x != substat_map.end())
				x->second += it->second;
			else
				substat_map.insert(std::pair(it->first, it->second));
		}
	}

	for (std::map<STAT, int>::iterator it = substat_map.begin();
	     it != substat_map.end();
	     it++)
	{
		aux += stat_str(it->first) + std::to_string(it->second) + " ";
	}

	return aux;
}