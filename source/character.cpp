#include <character.hpp>

character::character(stat_block base, stat_block weapon)
{
	this->base = base;
	this->weapon = weapon;

	this->base[STAT::CR] += 5;
	this->base[STAT::CD] += 50;
	this->base[STAT::ER] += 100;

	artifacts.generate();
}

float character::evaluate()
{
	return eval_func(base + weapon, artifacts.total());
}

character::character()
{
}