#include <algorithm>
#include <generator.hpp>

float htcharged(stat_block base, stat_block artif)
{

	float RES = 10;
	float RESPEN = 20;
	float REDUC = 0;
	RES -= RESPEN;
	if (RES < 0)
		REDUC = 1 - (RES / 200);
	else if (RES < 75)
		REDUC = 1 - RES / 100;
	else
		REDUC = 1 / ((4 * RES / 100) + 1);

	float DEF_MULT = 0.5;

	float HP = base[STAT::HP];
	float ATK = base[STAT::ATK];
	float DEF = base[STAT::DEF];
	base[STAT::HP] = 0;
	base[STAT::ATK] = 0;
	base[STAT::DEF] = 0;

	stat_block stat = base + artif;

	stat[STAT::HP_] += 20;        // SoH
	stat[STAT::HP_] += 25;        // Woter
	stat[STAT::ATK_] += 20;       // Elegy
	stat[STAT::ATK_] += 20;       // ZL Artif
	stat[STAT::EM] += 100;        // Elegy
	stat[STAT::EDMG] += 15 * 1.5; // Artif set
	stat[STAT::EDMG] += 50;       // Yelan

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float VAPE =
	    1.5 *
	    (1 + 0.15 +
	     (278 * stat[STAT::EM] / (stat[STAT::EM] + 1400)) / 100);

	float total_hp =
	    HP * (1 + stat[STAT::HP_] / 100) + stat[STAT::HP];
	float e_atk = (0.0626) * total_hp;
	e_atk = std::min(e_atk, 4 * ATK);
	float soh_atk = 0.018 * total_hp;
	float total_atk = ATK * (1 + stat[STAT::ATK_] / 100) +
	                  stat[STAT::ATK] + e_atk + soh_atk;
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float charged_dmg = 2.426 * total_atk;
	charged_dmg *= (1 + stat[STAT::EDMG] / 100);
	charged_dmg *= VAPE;
	charged_dmg *= CRIT;
	charged_dmg *= REDUC;
	charged_dmg *= DEF_MULT;

	return charged_dmg;
}

float aytoe(stat_block base, stat_block artif)
{
	float RES = 10;
	float RESPEN = 0;
	float REDUC = 0;
	RES -= RESPEN;
	if (RES < 0)
		REDUC = 1 - (RES / 200);
	else if (RES < 75)
		REDUC = 1 - RES / 100;
	else
		REDUC = 1 / ((4 * RES / 100) + 1);

	float DEF_MULT = 0.5;

	float HP = base[STAT::HP];
	float ATK = base[STAT::ATK];
	float DEF = base[STAT::DEF];
	base[STAT::HP] = 0;
	base[STAT::ATK] = 0;
	base[STAT::DEF] = 0;

	stat_block stat = base + artif;

	stat[STAT::ATK_] += 20; // weapo

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_hp =
	    HP * (1 + stat[STAT::HP_] / 100) + stat[STAT::HP];
	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float namisen = (1.11 * 4 / 100) * total_hp;

	float edmg = 1.283 * total_atk * 1.19 + namisen;
	edmg *= (1 + stat[STAT::EDMG] / 100);
	edmg *= CRIT;
	edmg *= REDUC;
	edmg *= DEF_MULT;

	return edmg;
}

void hutao()
{
	std::string str =
	    "HP:HP%0EM1CR2CD2|ATK:HP%0EM0CR2CD3|HP%:ATK%0EM0CR5CD0|EDMG:"
	    "HP%0EM0CR3CD2|CR:HP%0ATK%0EM1CD4";

	artifact_build ab;
	ab.id(str);

	std::cout << ab.total() << std::endl;
	std::cout << str << std::endl;

	stat_block ht_base, homa;
	ht_base[STAT::HP] = 15552;
	ht_base[STAT::DEF] = 876;
	ht_base[STAT::ATK] = 106.43;
	ht_base[STAT::CD] = 38.4;
	ht_base[STAT::EDMG] = 33;
	homa[STAT::ATK] = 608.07;
	homa[STAT::CD] = 66.2;
	character HuTao(ht_base, homa);

	HuTao.eval_func = &htcharged;
	HuTao.artifacts = ab;

	std::cout << HuTao.evaluate() << std::endl;

	// return 0;

	Generator g(HuTao);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	HuTao.artifacts = ab;
	std::cout << HuTao.evaluate() << std::endl;
}

void ayato()
{
	stat_block ayt, bcliff;
	ayt[STAT::HP] = 13715;
	ayt[STAT::DEF] = 769;
	ayt[STAT::ATK] = 299;
	ayt[STAT::CD] = 38.4;
	bcliff[STAT::ATK] = 565;
	bcliff[STAT::CD] = 36.8;

	character Ayato(ayt, bcliff);
	artifact_build ab;

	Ayato.eval_func = &aytoe;
	Ayato.artifacts = ab;

	Generator g(Ayato);
	ab = g.generate();

	std::cout << ab.id() << std::endl;
}

void kazuha()
{
}

int main()
{

	ayato();

	return 0;
}