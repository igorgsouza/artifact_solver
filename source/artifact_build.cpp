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

void artifact_build::mutate()
{
	std::string current = id();

	std::random_device dev;
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
		shuffle(circlet);

	if (current == id())
		mutate();
}

void artifact_build::shuffle(Artifact& artf)
{
	std::random_device dev;
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