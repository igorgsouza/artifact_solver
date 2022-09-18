#include "artifact.hpp"
#include <vector>

class artifact_build
{
  private:
	Artifact flower = Artifact(TYPE::FOF);
	Artifact plume = Artifact(TYPE::POD);
	Artifact sands = Artifact(TYPE::SOE);
	Artifact goblet = Artifact(TYPE::GOE);
	Artifact circlet = Artifact(TYPE::COL);

	int shuffle_weight = 50;
	int reset_weight = 10;

	int shuffle_method = 0;

  public:
	stat_block total();

	void generate();
	void mutate(int);
	std::string id();
	void id(std::string);
	void shuffle(Artifact&);
	std::string tc_id();
};