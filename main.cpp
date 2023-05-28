#include <algorithm>
#include <generator.hpp>

float SecretSpearOfWangshengCharged(stat_block base, stat_block artif)
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

	float reaction = 0;
	float chargeddmg = 0;

	stat[STAT::EDMG] += 33; // A2

	stat[STAT::HP_] += 25;  // Hydro
	stat[STAT::ATK_] += 25; // Pyro

	stat[STAT::ATK_] += 20; // Elegy
	stat[STAT::EM] += 100;  // Elegy
	stat[STAT::EDMG] += 50; // Yelan

	chargeddmg += 0.15;    // Thoma
	stat[STAT::EM] += 120; // Elegy

	// CWoF
	/* 	stat[STAT::EDMG] += 15 * 1.5;
	    reaction += 0.15; */

	// SR
	stat[STAT::ATK_] += 18;
	chargeddmg += .5;

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float VAPE =
	    1.5 *
	    (1 + reaction +
	     (278 * stat[STAT::EM] / (stat[STAT::EM] + 1400)) / 100);

	float total_hp =
	    HP * (1 + stat[STAT::HP_] / 100) + stat[STAT::HP];
	float e_atk = (0.0626) * total_hp;
	e_atk = std::min(e_atk, 4 * ATK);
	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK] + e_atk;
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float charged_dmg = 2.426 * total_atk;
	charged_dmg *= (1 + chargeddmg + stat[STAT::EDMG] / 100);
	charged_dmg *= VAPE;
	charged_dmg *= CRIT;
	charged_dmg *= REDUC;
	charged_dmg *= DEF_MULT;

	return charged_dmg;
}
void HUTAO()
{
	artifact_build ab;

	ab.id("HP:HP%1EM1CR1CD1|ATK:HP%1EM1CR1CD1|EM:HP%1ATK%1CR1CD1|"
	      "EDMG:HP%1EM1CR1CD1|CR:HP%1ATK%1EM1CD1");

	stat_block base, weapon;
	base[STAT::HP] = 15552;
	base[STAT::ATK] = 106.43;
	base[STAT::CD] = 38.4;

	// R5 DM = 59979.6
	weapon[STAT::ATK] = 454.36;
	weapon[STAT::CR] = 36.8;
	weapon[STAT::ATK_] = 48;

	// R5 DB = 57249.3
	/* 	weapon[STAT::ATK] = 454.36;
	    weapon[STAT::EM] = 220.51;
	    weapon[STAT::EDMG] = 36; */

	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &SecretSpearOfWangshengCharged;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float SwordRain(stat_block base, stat_block artif)
{
	float RES = 10;
	float RESPEN = 15;
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

	stat[STAT::ATK_] += 25; // Pyro

	// EoSF
	stat[STAT::ER] += 20;
	stat[STAT::EDMG] += std::min(stat[STAT::ER] * .25, 75.0);

	// NO + HotD
	/* stat[STAT::EDMG] += 20 + 15; */

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage = 1.085 * total_atk;
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	if (stat[STAT::ER] < 210)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}
void XINGQIU()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 201.78;
	base[STAT::ATK_] = 24;
	base[STAT::EDMG] = 20;

	weapon[STAT::ATK] = 454.36;
	weapon[STAT::ER] = 61.3;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &SwordRain;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float ExquisiteThrow(stat_block base, stat_block artif)
{
	float RES = 10;
	float RESPEN = 15;
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

	stat[STAT::HP_] += 25; // Hydro

	// EoSF
	stat[STAT::ER] += 20;
	stat[STAT::EDMG] += std::min(stat[STAT::ER] * .25, 75.0);

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_hp =
	    HP * (1 + stat[STAT::HP_] / 100) + stat[STAT::HP];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage = 0.0877 * total_hp;
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	if (stat[STAT::ER] < 190)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}
void YELAN()
{
	artifact_build ab;

	ab.id("HP:ER1EM1CR1CD1|ATK:HP%1ER1CR1CD1|HP%:HP1ER1CR1CD1|EDMG:"
	      "HP%1ER1CR1CD1|CR:HP%1HP1ER1CD1");

	stat_block base, weapon;
	base[STAT::HP] = 14450;
	base[STAT::ATK] = 243.96;
	base[STAT::CR] = 19.2;
	base[STAT::HP_] = 18;

	weapon[STAT::ATK] = 608.07;
	weapon[STAT::ER] = 55.1;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &ExquisiteThrow;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float SoumetsuCutting(stat_block base, stat_block artif)
{
	float RES = 10;
	float RESPEN = 40;
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

	stat[STAT::CR] += 15; // Cryo

	stat[STAT::EDMG] += 18; // A4

	stat[STAT::ATK_] += 20; // Diona Artif

	stat[STAT::ATK_] += 48; // TToDS
	stat[STAT::ATK_] += 25; // Mona Artif
	stat[STAT::EDMG] += 60; // Mona

	// Blizzard Strayer
	stat[STAT::EDMG] += 15;
	stat[STAT::CR] += 40;

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage = 2.02 * total_atk;
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	if (stat[STAT::ER] < 130)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}
void AYAKA()
{
	artifact_build ab;

	ab.id("HP:ATK%1ATK1CR1CD1|ATK:ATK%1EM1CR1CD1|ER:ATK%1ATK1CR1CD1|"
	      "EDMG:ATK%1ATK1CR1CD1|CD:ATK%1ATK1ER1CR1");

	stat_block base, weapon;
	base[STAT::ATK] = 342.03;
	base[STAT::CD] = 38.4;

	weapon[STAT::ATK] = 454.36;
	weapon[STAT::ATK_] = 55.1;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &SoumetsuCutting;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float WindsGrandOde(stat_block base, stat_block artif)
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

	RES = 10;
	float CRESPEN = 40;
	float CREDUC = 0;
	RES -= CRESPEN;
	if (RES < 0)
		CREDUC = 1 - (RES / 200);
	else if (RES < 75)
		CREDUC = 1 - RES / 100;
	else
		CREDUC = 1 / ((4 * RES / 100) + 1);

	float HP = base[STAT::HP];
	float ATK = base[STAT::ATK];
	float DEF = base[STAT::DEF];
	base[STAT::HP] = 0;
	base[STAT::ATK] = 0;
	base[STAT::DEF] = 0;

	stat_block stat = base + artif;

	stat[STAT::CR] += 15; // Cryo

	stat[STAT::ATK_] += 20; // Diona

	stat[STAT::EDMG] += 15; // Artif set

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float dot = 0.677 * total_atk * 20;
	dot *= (1 + stat[STAT::EDMG] / 100);
	dot *= CRIT;
	dot *= REDUC;
	dot *= DEF_MULT;

	float elmdot = 0.338 * total_atk * 15;
	elmdot *= (1 + 0.3);
	elmdot *= CRIT;
	elmdot *= CREDUC;
	elmdot *= DEF_MULT;

	float emmult = 1 + 16 * stat[STAT::EM] / (stat[STAT::EM] + 2000);
	emmult += 0.6; // artifact VV

	float swirldot = 0.6 * 1446.85 * emmult * CREDUC * 14;

	float ultimagedamage = dot + elmdot + swirldot;

	if (stat[STAT::ER] < 170)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}
void VENTI()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 263.10;
	base[STAT::ER] = 32;

	weapon[STAT::ATK] = 509.61;
	weapon[STAT::EM] = 165.38;
	weapon[STAT::EDMG] = 30;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &WindsGrandOde;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float StellarisPhantasm(stat_block base, stat_block artif)
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

	stat[STAT::CR] += 15; // Cryo

	stat[STAT::ATK_] += 20; // Diona Artif

	stat[STAT::EDMG] += 60;                  // Mona
	stat[STAT::EDMG] += stat[STAT::ER] * .2; // Mona

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage = 7.963 * total_atk;
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	if (stat[STAT::ER] < 209)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}
void MONA()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::HP] = 10409;
	base[STAT::DEF] = 653;
	base[STAT::ATK] = 287;
	base[STAT::ER] = 32;

	weapon[STAT::ATK] = 401;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &StellarisPhantasm;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float IcyPaws(stat_block base, stat_block artif)
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

	float total_hp =
	    HP * (1 + stat[STAT::HP_] / 100) + stat[STAT::HP];

	float shield =
	    (1772.6 + 0.144 * total_hp) * 1.3 * 1.15 * 1.75; // 16104

	float heal = (962.29 + 0.085 * total_hp) *
	             (1 + stat[STAT::HEAL] / 100); // 5535.41

	if (stat[STAT::ER] < 170)
		return stat[STAT::ER] * .35 / 350;

	return shield;
}
void DIONA()
{
	artifact_build ab;

	ab.id(
	    "HP:HP%1ATK1ER1CD1|ATK:HP%1HP1ER1CD1|HP%:HP1ATK%1ER1CD1|HP%:"
	    "HP1ER1EM1CR1|HP%:HP1ATK1ER1EM1");

	stat_block base, weapon;
	base[STAT::HP] = 9570;

	weapon[STAT::ER] = 61.3;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &IcyPaws;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float StarwardSwordConsecutiveSlash(stat_block base, stat_block artif)
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

	stat[STAT::EDMG] += 15; // artif

	stat[STAT::EDMG] += 35; // zl

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float AGG = 1446.9 * 1.15;
	AGG *= 1.2 + 5 * stat[STAT::EM] / (stat[STAT::EM] + 1200);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float slash = .432 * total_atk + AGG;
	slash *= (1 + stat[STAT::EDMG] / 100);
	slash *= CRIT;
	slash *= REDUC;
	slash *= DEF_MULT;

	return slash;
}
void KEQING()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 322.89;
	base[STAT::CD] = 38.4;

	// LB
	/* weapon[STAT::ATK] = 509.61;
	weapon[STAT::ATK_] = 41.3;
	weapon[STAT::EDMG] = 32; */

	// HoD
	weapon[STAT::ATK] = 509.61;
	weapon[STAT::CD] = 46.9;
	weapon[STAT::CR] = 28;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &StarwardSwordConsecutiveSlash;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float Nightrider(stat_block base, stat_block artif)
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

	stat[STAT::EDMG] += 35; // artif

	stat[STAT::EDMG] += 35; // zl artif

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float AGG = 1446.9 * 1.15;
	AGG *= 1.0 + 5 * stat[STAT::EM] / (stat[STAT::EM] + 1200);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float oz = 0.8 * total_atk + AGG;
	oz *= (1 + stat[STAT::EDMG] / 100);
	oz *= CRIT;
	oz *= REDUC;
	oz *= DEF_MULT;

	return oz;
}
void FISCHL()
{
	artifact_build ab;
	ab.id("HP:ATK%1EM1CR1CD1|ATK:ATK%1EM1CR1CD1|EM:ATK%1ATK1CR1CD1|"
	      "EDMG:ATK%1EM1CR1CD1|CR:ATK%1ATK1EM1CD1");

	stat_block base, weapon;
	base[STAT::ATK] = 244.26;
	base[STAT::ATK_] = 24;

	weapon[STAT::ATK] = 564.78;
	weapon[STAT::ATK_] = 27.6;
	weapon[STAT::EDMG] = 20;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &Nightrider;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float SeedSkandha(stat_block base, stat_block artif)
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

	// TALENT
	stat[STAT::CR] += std::min(24.0, (stat[STAT::EM] - 200) * 0.03);
	stat[STAT::EDMG] += std::min(80.0, (stat[STAT::EM] - 200) * 0.1);

	// DEEPWOOD
	stat[STAT::EDMG] += 15;
	REDUC = 1.1;

	// GILDED DREAM
	/* stat[STAT::EM] += 80 + 150; */

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float SPD = 1446.9 * 1.25;
	SPD *= 1.0 + 5 * stat[STAT::EM] / (stat[STAT::EM] + 1200);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	SPD = 0;

	float slash =
	    (1.8576 * total_atk + 3.7152 * stat[STAT::EM]) + SPD;
	slash *= (1 + stat[STAT::EDMG] / 100);
	slash *= CRIT;
	slash *= REDUC;
	slash *= DEF_MULT;

	return slash;
}
void NAHIDA()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 299;
	base[STAT::EM] = 115;

	/* // fof
	weapon[STAT::ATK] = 510;
	weapon[STAT::EM] = 180;
	weapon[STAT::ATK_] = -25; */

	/* // mappa mare
	weapon[STAT::ATK] = 565;
	weapon[STAT::EM] = 110;
	weapon[STAT::EDMG] = 16; */

	/* // sac fag
	weapon[STAT::ATK] = 454;
	weapon[STAT::EM] = 221; */

	// mg
	weapon[STAT::ATK] = 510;
	weapon[STAT::EM] = 187;
	weapon[STAT::EDMG] = 24;

	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &SeedSkandha;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float ZLScore(stat_block base, stat_block artif)
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

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_hp =
	    HP * (1 + stat[STAT::HP_] / 100) + stat[STAT::HP];
	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage =
	    8.35 * total_atk + 0.33 * total_hp; // 65526
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	float shield = (2712 + 0.23 * total_hp) * 1.25 * 1.5; // 43460

	float recharge = stat[STAT::ER];

	ultimagedamage /= 15280 / 100;
	recharge /= 151.8 / 100;

	return shield;
}
void ZHONGLI()
{
	artifact_build ab;

	ab.id("HP:HP%1ATK1DEF1CR1|ATK:HP%1HP1DEF1CR1|HP%:HP1ATK1DEF1CD1|"
	      "HP%:HP1ATK1ER1CD1|HP%:HP1ATK%1DEF%1CR1");

	stat_block base, weapon;
	base[STAT::HP] = 14695;
	base[STAT::ATK] = 251.14;
	base[STAT::EDMG] = 28.8;

	weapon[STAT::ATK] = 354.38;
	weapon[STAT::HP_] = 46.9;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &ZLScore;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float oblivion(stat_block base, stat_block artif)
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

	stat[STAT::ER] += 20; // Artif set
	stat[STAT::EDMG] +=
	    std::min(stat[STAT::ER] * .25, 75.0);        // Artif set
	stat[STAT::EDMG] += (stat[STAT::ER] - 100) * .4; // Passive
	stat[STAT::EDMG] += .3 * 90;

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float slash = (7.21 + .07 * 60) * total_atk;
	slash *= (1 + stat[STAT::EDMG] / 100);
	slash *= CRIT;
	slash *= REDUC;
	slash *= DEF_MULT;

	return slash;
}
void shogun()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 337;
	base[STAT::ER] = 32;

	// weapon[STAT::ATK] = 510;
	// weapon[STAT::ER] = 45.9;
	// weapon[STAT::EDMG] = 32;
	// weapon[STAT::CR] = 12;

	weapon[STAT::ATK] = 674;
	weapon[STAT::CR] = 22.1;
	weapon[STAT::ATK_] = 6;

	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &oblivion;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float KazuhaSlashDoT(stat_block base, stat_block artif)
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

	RES = 10;
	float CRESPEN = 40;
	float CREDUC = 0;
	RES -= CRESPEN;
	if (RES < 0)
		CREDUC = 1 - (RES / 200);
	else if (RES < 75)
		CREDUC = 1 - RES / 100;
	else
		CREDUC = 1 / ((4 * RES / 100) + 1);

	float HP = base[STAT::HP];
	float ATK = base[STAT::ATK];
	float DEF = base[STAT::DEF];
	base[STAT::HP] = 0;
	base[STAT::ATK] = 0;
	base[STAT::DEF] = 0;

	stat_block stat = base + artif;

	stat[STAT::ATK] += 614.54 + 129.10; // bennet
	stat[STAT::ATK_] += 20;             // bennet
	stat[STAT::ATK_] += 25;             // bennet
	stat[STAT::EDMG] += 15;             // bennet

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float dot = 2.16 * total_atk;
	dot *= (1 + stat[STAT::EDMG] / 100);
	dot *= CRIT;
	dot *= REDUC;
	dot *= DEF_MULT;

	float bonuspyr = (1.12 + 0.0004 * stat[STAT::EM]);

	float elmdot = 0.648 * total_atk;
	elmdot *= bonuspyr;
	elmdot *= CRIT;
	elmdot *= CREDUC;
	elmdot *= DEF_MULT;

	float emmult = 1 + 16 * stat[STAT::EM] / (stat[STAT::EM] + 2000);
	emmult += 0.6; // artifact VV

	float swirldot = 0.6 * 1446.85 * emmult * CREDUC;

	float ultimagedamage = dot + elmdot + swirldot;

	return ultimagedamage;
}
void KAZUHA()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 296.58;
	base[STAT::EM] = 115.2;

	weapon[STAT::ATK] = 509.61;
	weapon[STAT::EM] = 165.38;
	weapon[STAT::EDMG] = 12;
	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &KazuhaSlashDoT;
	CHARACTER.artifacts = ab;

	std::cout << CHARACTER.evaluate() << std::endl;

	Generator g(CHARACTER);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	CHARACTER.artifacts = ab;
	std::cout << CHARACTER.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

int main()
{

	MONA();

	return 0;
}