#include <algorithm>
#include <generator.hpp>

float SecretSpearOfWangshengCharged(stat_block base, stat_block artif)
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
	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK] + e_atk;
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

void HUTAO()
{
	artifact_build ab;

	ab.id("HP:HP%1EM1CR1CD6|ATK:HP%1EM1CR1CD6|EM:HP%1ATK%1CR5CD2|"
	      "EDMG:HP%1EM1CR3CD4|CR:HP%1ATK%1EM1CD6");

	stat_block base, weapon;
	base[STAT::HP] = 15552;
	base[STAT::ATK] = 106.43;
	base[STAT::CD] = 38.4;
	base[STAT::EDMG] = 33;

	// R5 DM = 82021.5
	weapon[STAT::ATK] = 454.36;
	weapon[STAT::CR] = 36.8;
	weapon[STAT::ATK_] = 48;

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
	float RESPEN = 20 + 15;
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

	stat[STAT::ATK_] += 20; // Elegy
	stat[STAT::ATK_] += 20; // ZL Artif
	stat[STAT::ER] += 20;   // Artif set
	stat[STAT::EDMG] +=
	    std::min(stat[STAT::ER] * .25, 75.0); // Artif set
	stat[STAT::EDMG] += 50;                   // Yelan

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

	if (stat[STAT::ER] < 240)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}

void XINGQIU()
{
	artifact_build ab;

	ab.id("HP:ATK%1ATK1CR4CD3|ATK:ATK%1ER1CR3CD4|ER:ATK%1ATK1CR4CD3|"
	      "EDMG:ATK%1ATK1CR4CD3|CR:ATK%1ATK1ER1CD6");

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
	float RESPEN = 20 + 15;
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

	stat[STAT::HP_] += 25; // WOTER
	stat[STAT::ER] += 20;  // Artif set
	stat[STAT::EDMG] +=
	    std::min(stat[STAT::ER] * .25, 75.0); // Artif set
	stat[STAT::EDMG] += 50;                   // Yelan

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

	ab.id("HP:HP%1ER1CR6CD1|ATK:HP%1HP1CR4CD3|HP%:HP1ER1CR4CD3|EDMG:"
	      "HP%1ER1CR1CD6|CD:HP%3HP1ER1CR4");

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

float zlshield(stat_block base, stat_block artif)
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

	stat[STAT::HP_] += 25;  // WOTER
	stat[STAT::HP_] += 20;  // Artif
	stat[STAT::ATK_] += 20; // ARTIF

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

	float shield = (2712 + 0.23 * total_hp) * 1.55 * 1.5; // 43460

	float recharge = stat[STAT::ER] / 350;

	return shield * 0.5 / 43460 + ultimagedamage * 0.2 / 65526 +
	       0.3 * recharge;
}

void zl()
{
	artifact_build ab;

	ab.id("HP:HP%1ATK%1CR3CD4|ATK:HP%1ATK%1CR6CD1|ATK%:HP%"
	      "1ATK1CR6CD1|EDMG:HP%1ATK%1CR3CD4|CD:HP%1ATK%1ATK1CR6");

	stat_block base, weapon;
	base[STAT::HP] = 14695;
	base[STAT::DEF] = 738;
	base[STAT::ATK] = 251;
	base[STAT::EDMG] = 28.8;

	weapon[STAT::ATK] = 354;
	weapon[STAT::HP_] = 46.9;
	character ZL(base, weapon);

	ZL.eval_func = &zlshield;
	ZL.artifacts = ab;

	std::cout << ZL.evaluate() << std::endl;

	Generator g(ZL);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	ZL.artifacts = ab;
	std::cout << ZL.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float soumetsu(stat_block base, stat_block artif)
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

	stat[STAT::CR] += 15; // CRYO
	stat[STAT::CR] += 40; // ARTF

	stat[STAT::ATK_] += 20; // Diona
	stat[STAT::EDMG] += 15; // Artif set
	stat[STAT::EDMG] += 60; // Mona
	stat[STAT::ATK_] += 48; // Mona
	stat[STAT::ATK_] += 20; // Mona

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

	ab.id("HP:ATK%1ATK1CR1CD6|ATK:ATK%1ER1CR1CD6|ER:ATK%2ATK1CR1CD5|"
	      "EDMG:ATK%3ER1CR1CD4|CD:ATK%1ATK1EM1CR6");

	stat_block base, weapon;
	base[STAT::HP] = 12858;
	base[STAT::DEF] = 784;
	base[STAT::ATK] = 342;
	base[STAT::CD] = 38.4;

	weapon[STAT::ATK] = 454;
	weapon[STAT::ATK_] = 55.1;
	character AYAKA(base, weapon);

	AYAKA.eval_func = &soumetsu;
	AYAKA.artifacts = ab;

	std::cout << AYAKA.evaluate() << std::endl;

	Generator g(AYAKA);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	AYAKA.artifacts = ab;
	std::cout << AYAKA.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float grandode(stat_block base, stat_block artif)
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

	stat[STAT::CR] += 15;   // CRYO
	stat[STAT::ATK_] += 20; // Diona
	stat[STAT::EM] += 200;  // Diona
	stat[STAT::EDMG] += 15; // Artif set

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float dot = 0.67 * total_atk * 20;
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

	ab.id("HP:ATK%1EM1CR4CD3|ATK:ATK%1ER2CR4CD2|ATK%:ER1EM1CR4CD3|"
	      "EDMG:ATK%1ER1CR4CD3|CD:ATK%3ER1EM1CR4");

	stat_block base, weapon;
	base[STAT::HP] = 10531;
	base[STAT::DEF] = 669;
	base[STAT::ATK] = 263;
	base[STAT::ER] = 32;

	weapon[STAT::ATK] = 510;
	weapon[STAT::EM] = 165;
	weapon[STAT::EDMG] = 30;
	character VENTI(base, weapon);

	VENTI.eval_func = &grandode;
	VENTI.artifacts = ab;

	std::cout << VENTI.evaluate() << std::endl;

	Generator g(VENTI);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	VENTI.artifacts = ab;
	std::cout << VENTI.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float writeninthestars(stat_block base, stat_block artif)
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

	stat[STAT::CR] += 15; // CRYO

	stat[STAT::ATK_] += 20;                  // Diona
	stat[STAT::EDMG] += 60;                  // Mona
	stat[STAT::ATK_] += 20;                  // Mona
	stat[STAT::EDMG] += stat[STAT::ER] * .2; // Mona

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage = 7.96 * total_atk;
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	if (stat[STAT::ER] < 250)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}

void MONA()
{
	artifact_build ab;

	ab.id("HP:ATK%1ER4CR1CD3|ATK:ATK%1ER2CR3CD3|ER:ATK%1ATK1CR3CD4|"
	      "EDMG:ATK%1ER4CR3CD1|CR:ATK%1ATK1ER6CD1");

	stat_block base, weapon;
	base[STAT::HP] = 10409;
	base[STAT::DEF] = 653;
	base[STAT::ATK] = 287;
	base[STAT::ER] = 32;

	weapon[STAT::ATK] = 401;
	character MONA(base, weapon);

	MONA.eval_func = &writeninthestars;
	MONA.artifacts = ab;

	std::cout << MONA.evaluate() << std::endl;

	Generator g(MONA);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	MONA.artifacts = ab;
	std::cout << MONA.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float cocktail(stat_block base, stat_block artif)
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
	    (1409 + 0.122 * total_hp) * 1.15 * 1.75 * 1.3; // 16104

	float heal = (962.29 + 0.085 * total_hp) *
	             (1 + stat[STAT::HEAL] / 100); // 5535.41

	if (stat[STAT::ER] < 170)
		return stat[STAT::ER] * .35 / 350;

	return heal * .2 / 5535.41 + shield * .7 / 16104 +
	       stat[STAT::ER] * 0.1 / 350;
}

void DIONA()
{
	artifact_build ab;

	ab.id("HP:HP%6DEF%1DEF1ER1|ATK:HP%6HP1ATK%1ER1|HP%:HP1ATK%1DEF%"
	      "1ER6|HP%:HP1ER6EM1CD1|HP%:HP1DEF1ER6EM1");

	stat_block base, weapon;
	base[STAT::HP] = 9570;

	weapon[STAT::ER] = 30.6;
	character DIONA(base, weapon);

	DIONA.eval_func = &cocktail;
	DIONA.artifacts = ab;

	std::cout << DIONA.evaluate() << std::endl;

	Generator g(DIONA);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	DIONA.artifacts = ab;
	std::cout << DIONA.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float keqingq(stat_block base, stat_block artif)
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

	stat[STAT::EDMG] += 15; // artif

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

void KQNG()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::HP] = 13103;
	base[STAT::DEF] = 799;
	base[STAT::ATK] = 323;
	base[STAT::CD] = 38.4;

	weapon[STAT::ATK] = 509.61;
	weapon[STAT::ATK_] = 41.3;
	weapon[STAT::EDMG] = 36;
	character KQNG(base, weapon);

	KQNG.eval_func = &keqingq;
	KQNG.artifacts = ab;

	std::cout << KQNG.evaluate() << std::endl;

	Generator g(KQNG);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	KQNG.artifacts = ab;
	std::cout << KQNG.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float oz(stat_block base, stat_block artif)
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

	stat[STAT::EDMG] += 35;

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float AGG = 1446.9 * 1.15;
	AGG *= 1.0 + 5 * stat[STAT::EM] / (stat[STAT::EM] + 1200);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float oz = .8 * total_atk + AGG;
	oz *= (1 + stat[STAT::EDMG] / 100);
	oz *= CRIT;
	oz *= REDUC;
	oz *= DEF_MULT;

	return oz;
}

void FISH()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::HP] = 13103;
	base[STAT::DEF] = 799;
	base[STAT::ATK] = 244;
	base[STAT::ATK_] = 24;

	weapon[STAT::ATK] = 564.78;
	weapon[STAT::ATK_] = 27.6;
	weapon[STAT::EDMG] = 20;
	character FISH(base, weapon);

	FISH.eval_func = &oz;
	FISH.artifacts = ab;

	std::cout << FISH.evaluate() << std::endl;

	Generator g(FISH);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	FISH.artifacts = ab;
	std::cout << FISH.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float dandelion(stat_block base, stat_block artif)
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

	stat[STAT::EDMG] += 15;

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float wind = 7.65 * total_atk;
	wind *= (1 + stat[STAT::EDMG] / 100);
	wind *= CRIT;
	wind *= REDUC;
	wind *= DEF_MULT;

	if (stat[STAT::ER] < 170)
		return stat[STAT::ER];

	return wind;
}

void JEAN()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::HP] = 13103;
	base[STAT::DEF] = 799;
	base[STAT::ATK] = 239;
	base[STAT::HEAL] = 22.1;

	weapon[STAT::ATK] = 454.36;
	weapon[STAT::ER] = 61.3;
	character JEAN(base, weapon);

	JEAN.eval_func = &dandelion;
	JEAN.artifacts = ab;

	std::cout << JEAN.evaluate() << std::endl;

	Generator g(JEAN);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	JEAN.artifacts = ab;
	std::cout << JEAN.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float iceshard(stat_block base, stat_block artif)
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

	stat[STAT::CR] += 15;   // CRYO
	                        // stat[STAT::CR] += 40;   // artif
	stat[STAT::EDMG] += 35; // artif
	// stat[STAT::ER] += 20; // Artif set
	// stat[STAT::EDMG] += std::min(stat[STAT::ER] * .25, 75.0);

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float ultimagedamage = 1.26 * total_atk;
	ultimagedamage *= (1 + stat[STAT::EDMG] / 100);
	ultimagedamage *= CRIT;
	ultimagedamage *= REDUC;
	ultimagedamage *= DEF_MULT;

	if (stat[STAT::ER] < 130)
		ultimagedamage = stat[STAT::ER];

	return ultimagedamage;
}

void GANYU()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::HP] = 9797;
	base[STAT::DEF] = 630;
	base[STAT::ATK] = 335;
	base[STAT::CD] = 38.4;

	weapon[STAT::ATK] = 510;
	weapon[STAT::ATK_] = 41.3;
	character GANYU(base, weapon);

	GANYU.eval_func = &iceshard;
	GANYU.artifacts = ab;

	std::cout << GANYU.evaluate() << std::endl;

	Generator g(GANYU);
	ab = g.generate();

	std::cout << ab.id() << std::endl;

	GANYU.artifacts = ab;
	std::cout << GANYU.evaluate() << std::endl;

	std::cout << ab.tc_id() << std::endl;
}

float tiggies(stat_block base, stat_block artif)
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

	// stat[STAT::EDMG] += 15; // artif
	stat[STAT::EM] += 80;  // artif
	stat[STAT::EM] += 150; // artif
	stat[STAT::EM] += 50;  // t1
	stat[STAT::EDMG] +=
	    std::min((float)60.0, (float)(stat[STAT::EM] * 0.06)); // t2

	stat[STAT::CR] = std::min((float)100, stat[STAT::CR]);

	float SPD = 1446.9 * 1.25;
	SPD *= 1.2 + 5 * stat[STAT::EM] / (stat[STAT::EM] + 1200);

	float total_atk =
	    ATK * (1 + stat[STAT::ATK_] / 100) + stat[STAT::ATK];
	float CRIT =
	    ((1 - stat[STAT::CR] / 100) +
	     (stat[STAT::CR] / 100) * (1 + stat[STAT::CD] / 100));

	float slash = 1.001 * total_atk + SPD;
	slash *= (1 + stat[STAT::EDMG] / 100);
	slash *= CRIT;
	slash *= REDUC;
	slash *= DEF_MULT;

	return slash;
}

void tifnari()
{
	artifact_build ab;

	stat_block base, weapon;
	base[STAT::ATK] = 268;
	base[STAT::EDMG] = 28.8;

	weapon[STAT::ATK] = 510;
	weapon[STAT::EM] = 165;
	weapon[STAT::EDMG] = 24;

	character CHARACTER(base, weapon);

	CHARACTER.eval_func = &tiggies;
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

int main()
{

	HUTAO();

	return 0;
}