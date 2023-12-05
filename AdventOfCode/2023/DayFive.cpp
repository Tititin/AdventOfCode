#include "DayFive.h"

bool isNumber(const std::string& _word)
{
	if (_word.size() == 0)
		return false;
	for (int i = 0; i < _word.size(); i++)
	{
		if (_word[i] < '0' || _word[i] > '9')
			return false;
	}
	return true;
}

void addSeeds(std::vector<unsigned long long int>& _seeds, const unsigned long long int& _start, const unsigned long long int& _range)
{
	for (unsigned long long int i = 0; i < _range; i++)
	{
		_seeds.push_back(_start + i);
	}
}

void convertSeedToSoil(unsigned long long int& _seed, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	//std::cout << "SEED VALUE = " << _seed << std::endl;
	while (!mapFound && _maps[i].name == "soil" && i < _maps.size())
	{
		if (_seed < _maps[i].sourceStart + _maps[i].range && _seed >= _maps[i].sourceStart)
		{
			/*std::cout << "||MAP FOUND !" << std::endl;
			std::cout << "||MAP NAME = " << _maps[i].name << std::endl;
			std::cout << "||MAP SOURCE = " << _maps[i].sourceStart << std::endl;
			std::cout << "||MAP DEST = " << _maps[i].destinationStart << std::endl;
			std::cout << "||MAP RANGE = " << _maps[i].range << std::endl;*/
			int tmp = _seed - _maps[i].sourceStart;
			mapFound = true;
			_seed = _maps[i].destinationStart + tmp;
			//std::cout << "SOIL VALUE = " << _seed << std::endl;
		}
		//std::cout << std::endl;
		i = i + 1;
	}
}

void convertSoilToFert(unsigned long long int& _soil, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	while (_maps[i].name != "fertilizer")
		i += 1;
	while (!mapFound && _maps[i].name == "fertilizer" && i < _maps.size())
	{
		//std::cout << "--" << _maps[i].name << std::endl;
		if (_soil < _maps[i].sourceStart + _maps[i].range && _soil >= _maps[i].sourceStart)
		{
			//std::cout << "ABC";
			int tmp = _soil - _maps[i].sourceStart;
			mapFound = true;
			_soil = _maps[i].destinationStart + tmp;
		}
		i = i + 1;
	}
}

void convertFertToWater(unsigned long long int& _fert, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	while (_maps[i].name != "water")
		i += 1;
	while (!mapFound && _maps[i].name == "water" && i < _maps.size())
	{
		if (_fert < _maps[i].sourceStart + _maps[i].range && _fert >= _maps[i].sourceStart)
		{
			//std::cout << "DEF";
			int tmp = _fert - _maps[i].sourceStart;
			mapFound = true;
			_fert = _maps[i].destinationStart + tmp;
		}
		i = i + 1;
	}
}

void convertWaterToLight(unsigned long long int& _water, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	while (_maps[i].name != "light")
		i += 1;
	while (!mapFound && _maps[i].name == "light" && i < _maps.size())
	{
		if (_water < _maps[i].sourceStart + _maps[i].range && _water >= _maps[i].sourceStart)
		{
			//std::cout << "GHI";
			int tmp = _water - _maps[i].sourceStart;
			mapFound = true;
			_water = _maps[i].destinationStart + tmp;
		}
		i = i + 1;
	}
}

void convertLightToTemp(unsigned long long int& _light, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	while (_maps[i].name != "temperature")
		i += 1;
	while (!mapFound && _maps[i].name == "temperature" && i < _maps.size())
	{
		if (_light < _maps[i].sourceStart + _maps[i].range && _light >= _maps[i].sourceStart)
		{
			//std::cout << "JKL";
			int tmp = _light - _maps[i].sourceStart;
			mapFound = true;
			_light = _maps[i].destinationStart + tmp;
		}
		i = i + 1;
	}
}

void convertTempToHumid(unsigned long long int& _temp, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	while (_maps[i].name != "humidity")
		i += 1;
	while (!mapFound && _maps[i].name == "humidity" && i < _maps.size())
	{
		if (_temp < _maps[i].sourceStart + _maps[i].range && _temp >= _maps[i].sourceStart)
		{
			//std::cout << "MNO";
			int tmp = _temp - _maps[i].sourceStart;
			mapFound = true;
			_temp = _maps[i].destinationStart + tmp;
		}
		i = i + 1;
	}
}

void convertHumidToLocation(unsigned long long int& _humid, std::vector<t_SoilMap>& _maps)
{
	bool	mapFound = false;
	int		i = 0;

	while (_maps[i].name != "location")
		i += 1;
	while (!mapFound && i < _maps.size() && _maps[i].name == "location")
	{
		//std::cout << "TRYING A LOCATION MAP" << std::endl;
		if (_humid < _maps[i].sourceStart + _maps[i].range && _humid >= _maps[i].sourceStart)
		{
			//std::cout << "PQR";
			int tmp = _humid - _maps[i].sourceStart;
			mapFound = true;
			_humid = _maps[i].destinationStart + tmp;
		}
		i = i + 1;
	}
}

std::string				getNameBasedOnState(const t_ProcessState _stateEnum)
{
	std::string			name;
	switch (_stateEnum)
	{
	case SEED_TO_SOIL:
		name = "soil";
		break;
	case SOIL_TO_FERT:
		name = "fertilizer";
		break;
	case FERT_TO_WATER:
		name = "water";
		break;
	case WATER_TO_LIGHT:
		name = "light";
		break;
	case LIGHT_TO_TEMP:
		name = "temperature";
		break;
	case TEMP_TO_HUMID:
		name = "humidity";
		break;
	case HUMID_TO_LOCATION:
		name = "location";
		break;
	default:
		name = "end";
		break;
	}
	return name;
}

void updateState(t_ProcessState& _state, const std::string& _word)
{
	if (_word == "seeds:")
		_state = SEEDS;
	if (_word == "seed-to-soil")
		_state = SEED_TO_SOIL;
	if (_word == "soil-to-fertilizer")
		_state = SOIL_TO_FERT;
	if (_word == "fertilizer-to-water")
		_state = FERT_TO_WATER;
	if (_word == "water-to-light")
		_state = WATER_TO_LIGHT;
	if (_word == "light-to-temperature")
		_state = LIGHT_TO_TEMP;
	if (_word == "temperature-to-humidity")
		_state = TEMP_TO_HUMID;
	if (_word == "humidity-to-location")
		_state = HUMID_TO_LOCATION;
	if (_state == HUMID_TO_LOCATION && _word == "")
		_state = END;
}

void	dayFive(const bool& isPartTwo)
{
	FileParser						_fileParser("2023\\InputFiles\\inputD5.txt");
	std::string						word;

	std::vector<unsigned long long int>	seeds;

	std::vector<t_SoilMap>			soilMaps;
	t_SoilMap						map;
	t_SoilVar						var = DEST;

	t_ProcessState					state = START;

	while ((word = _fileParser.readWordToString()) != "" || state != END)
	{
		//std::cout << word << std::endl;
		if (word != "map:" && !isNumber(word))
			updateState(state, word);
		else if (isNumber(word) && state == SEEDS)
		{
			if (isPartTwo)
			{
				unsigned long long int start = std::stoull(word);
				unsigned long long int range;
				word = _fileParser.readWordToString();
				if (isNumber(word))
				{
					range = std::stoull(word);
					addSeeds(seeds, start, range);
				}
			}
			else
				seeds.push_back(std::stoull(word));
		}
		else if (isNumber(word) && state != START && state != SEEDS)
		{
			if (var == DEST)
			{
				map.destinationStart = std::stoull(word);
				var = SRC;
			}
			else if (var == SRC)
			{
				map.sourceStart = std::stoull(word);
				var = RANGE;
			}
			else if (var == RANGE)
			{
				map.range = std::stoull(word);
				map.name = getNameBasedOnState(state);
				soilMaps.push_back(map);
				var = DEST;
			}
		}
	}

	for (int x = 0; x < seeds.size(); x++)
	{
		convertSeedToSoil(seeds[x], soilMaps);
		convertSoilToFert(seeds[x], soilMaps);
		convertFertToWater(seeds[x], soilMaps);
		convertWaterToLight(seeds[x], soilMaps);
		convertLightToTemp(seeds[x], soilMaps);
		convertTempToHumid(seeds[x], soilMaps);
		convertHumidToLocation(seeds[x], soilMaps);
	}

	unsigned long long int finalValue = -1;
	//DEBUG
	//std::cout << "SEEDS :";
	for (int i = 0; i < seeds.size(); i++)
	{
		if (finalValue == -1 || finalValue > seeds[i])
			finalValue = seeds[i];
		//std::cout << " " << seeds[i];
	}

	std::cout << finalValue;
	//std::cout << std::endl << std::endl;
	//for (int x = 0; x < soilMaps.size(); x++)
	//{
	//	std::cout << "==========" << std::endl;
	//	std::cout << "MAP TYPE = " << soilMaps[x].name << std::endl;
	//	std::cout << "DESTINATION = " << soilMaps[x].destinationStart << std::endl;
	//	std::cout << "SOURCE = " << soilMaps[x].sourceStart << std::endl;
	//	std::cout << "RANGE = " << soilMaps[x].range << std::endl;
	//}
	std::cout << std::endl;

}
