#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <climits>

using namespace std;

class SeedToSoil {
public:
    SeedToSoil(unsigned long x, unsigned long y, unsigned long z) : start_soil(x), start_seed(y), range(z) {}
    unsigned long start_soil = 0;
    unsigned long start_seed = 0;
    unsigned long range = 0;
};

class SoilToFertilizer {
public:
    SoilToFertilizer(unsigned long x, unsigned long y, unsigned long z) : start_fertilizer(x), start_soil(y),range(z) {}
    unsigned long start_fertilizer = 0;
    unsigned long start_soil = 0;
    unsigned long range = 0;
};

class FertilizerToWater {
public:
    FertilizerToWater(unsigned long x, unsigned long y, unsigned long z) : start_water(x), start_fertilizer(y),range(z) {}
    unsigned long start_water = 0;
    unsigned long start_fertilizer = 0;
    unsigned long range = 0;
};

class WaterToLight {
public:
    WaterToLight(unsigned long x, unsigned long y, unsigned long z) : start_light(x), start_water(y), range(z) {}
    unsigned long start_light = 0;
    unsigned long start_water = 0;
    unsigned long range = 0;
};

class LightToTemperature {
public:
    LightToTemperature(unsigned long x, unsigned long y, unsigned long z) : start_temperature(x), start_light(y),range(z) {}
    unsigned long start_temperature = 0;
    unsigned long start_light = 0;
    unsigned long range = 0;
};

class TemperatureToHumidity {
public:
    TemperatureToHumidity(unsigned long x, unsigned long y, unsigned long z) : start_humidity(x), start_temperature(y),range(z) {}
    unsigned long start_humidity = 0;
    unsigned long start_temperature = 0;
    unsigned long range = 0;
};

class HumidityToLocation {
public:
    HumidityToLocation(unsigned long x, unsigned long y, unsigned long z) : start_location(x), start_humidity(y), range(z) {}
    unsigned long start_location = 0;
    unsigned long start_humidity = 0;
    unsigned long range = 0;
};

int main() {
    unsigned long answer = ULONG_MAX;

    ifstream file("../../input.txt");

    string line;
    vector<unsigned long> seeds;
    vector<SeedToSoil> seed_to_soil_list;
    vector<SoilToFertilizer> soil_to_fertilizer_list;
    vector<FertilizerToWater> fertilizer_to_water_list;
    vector<WaterToLight> water_to_light_list;
    vector<LightToTemperature> light_to_temperature_list;
    vector<TemperatureToHumidity> temperature_to_humidity_list;
    vector<HumidityToLocation> humidity_to_location_list;

    string nextToken;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    int nLine = -1;
    bool seed_to_soil = false, soil_to_fertilizer = false, fertilizer_to_water = false,
            water_to_light = false, light_to_temperature = false, temperature_to_humidity = false, humidity_to_location = false;

    while (getline(file, line)) {
        istringstream iss(line);

        ++nLine;

        while (iss >> nextToken) {
            if (nLine == 0) {
                if (isdigit(nextToken[0]))
                    seeds.push_back(stoul(nextToken));
            } else if (!isdigit(nextToken[0])) {
                if (!seed_to_soil && seed_to_soil_list.empty()) {
                    seed_to_soil = true;
                    iss >> nextToken;   // read "map:"
                    continue;           // go to next line
                } else if (!soil_to_fertilizer && soil_to_fertilizer_list.empty()) {   // if isn't a number
                    seed_to_soil = false;                       // and seed_to_soil is already true
                    soil_to_fertilizer = true;                  // if soil_to_fertilizer is false it becomes true
                    iss >> nextToken;
                    continue;
                } else if (!fertilizer_to_water && fertilizer_to_water_list.empty()) {
                    soil_to_fertilizer = false;
                    fertilizer_to_water = true;
                    iss >> nextToken;
                    continue;
                } else if (!water_to_light && water_to_light_list.empty()) {
                    fertilizer_to_water = false;
                    water_to_light = true;
                    iss >> nextToken;
                    continue;
                } else if (!light_to_temperature && light_to_temperature_list.empty()) {
                    water_to_light = false;
                    light_to_temperature = true;
                    iss >> nextToken;
                    continue;
                } else if (!temperature_to_humidity && temperature_to_humidity_list.empty()) {
                    light_to_temperature = false;
                    temperature_to_humidity = true;
                    iss >> nextToken;
                    continue;
                } else if (!humidity_to_location && humidity_to_location_list.empty()) {
                    temperature_to_humidity = false;
                    humidity_to_location = true;
                    iss >> nextToken;
                    continue;
                }
            }


            if (seed_to_soil) {
                SeedToSoil sts = SeedToSoil(-1, -1, -1);

                if (sts.start_soil == -1)            // because nextToken is already the first number of the line
                    sts.start_soil = stoul(nextToken);

                while (iss >> nextToken) {
                    if (sts.start_seed == -1)
                        sts.start_seed = stoul(nextToken);
                    else if (sts.range == -1)
                        sts.range = stoul(nextToken);
                }
                seed_to_soil_list.push_back(sts);
            } else if (soil_to_fertilizer) {
                SoilToFertilizer stf = SoilToFertilizer(-1, -1, -1);

                if (stf.start_fertilizer == -1)            // because nextToken is already the first number of the line
                    stf.start_fertilizer = stoul(nextToken);

                while (iss >> nextToken) {
                    if (stf.start_soil == -1)
                        stf.start_soil = stoul(nextToken);
                    else if (stf.range == -1)
                        stf.range = stoul(nextToken);
                }
                soil_to_fertilizer_list.push_back(stf);
            } else if (fertilizer_to_water) {
                FertilizerToWater ftw = FertilizerToWater(-1, -1, -1);

                if (ftw.start_water == -1)            // because nextToken is already the first number of the line
                    ftw.start_water = stoul(nextToken);

                while (iss >> nextToken) {
                    if (ftw.start_fertilizer == -1)
                        ftw.start_fertilizer = stoul(nextToken);
                    else if (ftw.range == -1)
                        ftw.range = stoul(nextToken);
                }
                fertilizer_to_water_list.push_back(ftw);
            } else if (water_to_light) {
                WaterToLight wtl = WaterToLight(-1, -1, -1);

                if (wtl.start_light == -1)            // because nextToken is already the first number of the line
                    wtl.start_light = stoul(nextToken);

                while (iss >> nextToken) {
                    if (wtl.start_water == -1)
                        wtl.start_water = stoul(nextToken);
                    else if (wtl.range == -1)
                        wtl.range = stoul(nextToken);
                }
                water_to_light_list.push_back(wtl);
            } else if (light_to_temperature) {
                LightToTemperature ltt = LightToTemperature(-1, -1, -1);

                if (ltt.start_temperature == -1)            // because nextToken is already the first number of the line
                    ltt.start_temperature = stoul(nextToken);

                while (iss >> nextToken) {
                    if (ltt.start_light == -1)
                        ltt.start_light = stoul(nextToken);
                    else if (ltt.range == -1)
                        ltt.range = stoul(nextToken);
                }
                light_to_temperature_list.push_back(ltt);
            } else if (temperature_to_humidity) {
                TemperatureToHumidity tth = TemperatureToHumidity(-1, -1, -1);

                if (tth.start_humidity == -1)            // because nextToken is already the first number of the line
                    tth.start_humidity = stoul(nextToken);

                while (iss >> nextToken) {
                    if (tth.start_temperature == -1)
                        tth.start_temperature = stoul(nextToken);
                    else if (tth.range == -1)
                        tth.range = stoul(nextToken);
                }
                temperature_to_humidity_list.push_back(tth);
            } else if (humidity_to_location) {
                HumidityToLocation htl = HumidityToLocation(-1, -1, -1);

                if (htl.start_location == -1)            // because nextToken is already the first number of the line
                    htl.start_location = stoul(nextToken);

                while (iss >> nextToken) {
                    if (htl.start_humidity == -1)
                        htl.start_humidity = stoul(nextToken);
                    else if (htl.range == -1)
                        htl.range = stoul(nextToken);
                }
                humidity_to_location_list.push_back(htl);
            }
        }
    }

    // FOR EACH SEED
    for (int i = 0; i < seeds.size(); i++) {
        unsigned long soil = -1;
        unsigned long fertilizer = -1;
        unsigned long water = -1;
        unsigned long light = -1;
        unsigned long temperature = -1;
        unsigned long humidity = -1;
        unsigned long location = -1;

        unsigned diff;

        // BY DEFAULT, SOIL IS THE SAME AS SEED
        soil = seeds[i];
        for (int j = 0; j < seed_to_soil_list.size(); j++) {
            if (seeds[i] == seed_to_soil_list[j].start_seed) {
                soil = seed_to_soil_list[j].start_soil;
                break;
            }
            // FIND SOIL AND KEEP GOING -> [THE SEED WE'RE LOOKING FOR MUST BE HIGHER THAN THE START SEED AND LOWER THAN THE START SEED + RANGE]
            if (seed_to_soil_list[j].start_seed < seeds[i] &&
            seed_to_soil_list[j].start_seed + seed_to_soil_list[j].range > seeds[i]) {
                diff = seeds[i] - seed_to_soil_list[j].start_seed;
                soil = seed_to_soil_list[j].start_soil + diff;
            }
        }

        // BY DEFAULT, FERTILIZER IS THE SAME AS SOIL
        fertilizer = soil;
        for (int k = 0; k < soil_to_fertilizer_list.size(); k++) {
            if (soil == soil_to_fertilizer_list[k].start_soil) {
                fertilizer = soil_to_fertilizer_list[k].start_fertilizer;
                break;
            }
            // FIND FERTILIZER AND KEEP GOING
            if (soil_to_fertilizer_list[k].start_soil < soil &&
            soil_to_fertilizer_list[k].start_soil + soil_to_fertilizer_list[k].range > soil) {
                diff = soil - soil_to_fertilizer_list[k].start_soil;
                fertilizer = soil_to_fertilizer_list[k].start_fertilizer + diff;
            }
        }

        // BY DEFAULT, WATER IS THE SAME AS FERTILIZER
        water = fertilizer;
        for (int p = 0; p < fertilizer_to_water_list.size(); p++) {
            if (fertilizer == fertilizer_to_water_list[p].start_fertilizer) {
                water = fertilizer_to_water_list[p].start_water;
                break;
            }
            // FIND WATER AND KEEP GOING
            if (fertilizer_to_water_list[p].start_fertilizer < fertilizer &&
            fertilizer_to_water_list[p].start_fertilizer + fertilizer_to_water_list[p].range > fertilizer) {
                diff = fertilizer - fertilizer_to_water_list[p].start_fertilizer;
                water = fertilizer_to_water_list[p].start_water + diff;
            }
        }

        // BY DEFAULT, LIGHT IS THE SAME AS WATER
        light = water;
        for (int l = 0; l < water_to_light_list.size(); l++) {
            if (water == water_to_light_list[l].start_water) {
                light = water_to_light_list[l].start_light;
                break;
            }
            // FIND WATER AND KEEP GOING
            if (water_to_light_list[l].start_water < water &&
            water_to_light_list[l].start_water + water_to_light_list[l].range > water) {
                diff = water - water_to_light_list[l].start_water;
                light = water_to_light_list[l].start_light + diff;
            }
        }

        // BY DEFAULT, TEMPERATURE IS THE SAME AS LIGHT
        temperature = light;
        for (int m = 0; m < light_to_temperature_list.size(); m++) {
            if (light == light_to_temperature_list[m].start_light) {
                temperature = light_to_temperature_list[m].start_temperature;
                break;
            }

            // FIND TEMPERATURE AND KEEP GOING
            if (light_to_temperature_list[m].start_light < light &&
            light_to_temperature_list[m].start_light + light_to_temperature_list[m].range > light) {
                diff = light - light_to_temperature_list[m].start_light;
                temperature = light_to_temperature_list[m].start_temperature + diff;
            }
        }

        // BY DEFAULT, HUMIDITY IS THE SAME AS TEMPERATURE
        humidity = temperature;
        for (int n = 0; n < temperature_to_humidity_list.size(); n++) {
            if (temperature == temperature_to_humidity_list[n].start_temperature) {
                humidity = temperature_to_humidity_list[n].start_humidity;
                break;
            }

            if (temperature_to_humidity_list[n].start_temperature < temperature &&
            temperature_to_humidity_list[n].start_temperature + temperature_to_humidity_list[n].range > temperature) {
                diff = temperature - temperature_to_humidity_list[n].start_temperature;
                humidity = temperature_to_humidity_list[n].start_humidity + diff;
            }
        }

        // BY DEFAULT, LOCATION IS THE SAME AS HUMIDITY
        location = humidity;
        for (int v = 0; v < humidity_to_location_list.size(); v++) {
            if (humidity == humidity_to_location_list[v].start_humidity) {
                location = humidity_to_location_list[v].start_location;
                break;
            }

            if (humidity_to_location_list[v].start_humidity < humidity &&
            humidity_to_location_list[v].start_humidity + humidity_to_location_list[v].range > humidity) {
                diff = humidity - humidity_to_location_list[v].start_humidity;
                location = humidity_to_location_list[v].start_location + diff;
            }
        }

        if(location < answer)
            answer = location;
    }


    cout << "ANSWER: " << answer;
}
