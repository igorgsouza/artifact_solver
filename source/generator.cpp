#include <generator.hpp>

Generator::Generator(character cha)
{
	base = cha;
	generation = new character[gen_size];
}

void Generator::fill(int iteration)
{
	generation[0] = base;
	for (int i = 1; i < gen_size; ++i)
	{
		generation[i] = base;
		generation[i].artifacts.mutate(iteration + i - 1);
	}
}

void Generator::evaluate()
{
	int iterator = 0;
	for (int i = 0; i < gen_size; ++i)
	{
		float val = generation[i].evaluate();
		if (val > max_value)
		{
			iterator = i;
			max_value = val;
		}
	}
	base = generation[iterator];
}

artifact_build Generator::generate()
{
	int idle_gen = max_idle;
	int iteration = 0;
	float old_best = max_value;
	do
	{
		fill(iteration);
		evaluate();
		iteration++;
		if (old_best == max_value)
		{
			idle_gen--;
			if (idle_gen % 10 == 0)
				std::cout << idle_gen << std::endl;
		}
		else
		{
			idle_gen = max_idle;
			old_best = max_value;
			std::cout << max_value << std::endl;
		}
	} while (iteration < max_gen && idle_gen > 0);

	return base.artifacts;
}
