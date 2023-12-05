#pragma once

#ifndef DAYFIVE_H_
# define DAYFIVE_H_

#include "FileParser.h"

typedef enum			e_ProcessState
{
	START,
	SEEDS,
	SEED_TO_SOIL,
	SOIL_TO_FERT,
	FERT_TO_WATER,
	WATER_TO_LIGHT,
	LIGHT_TO_TEMP,
	TEMP_TO_HUMID,
	HUMID_TO_LOCATION,
	END
}						t_ProcessState;

typedef enum			e_SoilVar
{
	DEST = 0,
	SRC = 1,
	RANGE = 2
}						t_SoilVar;

typedef struct			s_SoilMap
{
	std::string			name;

	unsigned long long int	destinationStart;
	unsigned long long int	sourceStart;
	unsigned long long int	range;
}						t_SoilMap;

bool					isNumber(const std::string& _word);

void					addSeeds(std::vector<unsigned long long int>& _seeds, const unsigned long long int& _start, const unsigned long long int& _range);

std::string				getNameBasedOnState(const enum _stateEnum);

void					convertSeedToSoil(unsigned long long int& _seed, std::vector<t_SoilMap>& _maps);
void					convertSoilToFert(unsigned long long int& _soil, std::vector<t_SoilMap>& _maps);
void					convertFertToWater(unsigned long long int& _fert, std::vector<t_SoilMap>& _maps);
void					convertWaterToLight(unsigned long long int& _water, std::vector<t_SoilMap>& _maps);
void					convertLightToTemp(unsigned long long int& _light, std::vector<t_SoilMap>& _maps);
void					convertTempToHumid(unsigned long long int& _temp, std::vector<t_SoilMap>& _maps);
void					convertHumidToLocation(unsigned long long int& _humid, std::vector<t_SoilMap>& _maps);

void					updateState(t_ProcessState& _state, const std::string& _word);

void					dayFive(const bool& isPartTwo = false);

#endif // !DAYFIVE_H_
