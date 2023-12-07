#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <climits>

using namespace std;

class Data {
public:
    Data(unsigned long x, unsigned long y, unsigned long z) : start(x), target(y),range(z) {}
    unsigned long start = 0;
    unsigned long target = 0;
    unsigned long range = 0;
};

unsigned long findValue(const vector<Data>& data, unsigned long currentValue){
    for (auto d : data) {
        if (currentValue == d.start) {
            return d.target;
        }

        if (d.start < currentValue &&
            d.start + d.range > currentValue) {
            return d.target + (currentValue - d.start);
        }
    }

    return currentValue;
}


int main() {
    unsigned long answer = ULONG_MAX;

    ifstream file("../../input.txt");

    string line;
    vector<unsigned long> seeds;
    vector<Data> seed_to_soil_list;
    vector<Data> soil_to_fertilizer_list;
    vector<Data> fertilizer_to_water_list;
    vector<Data> water_to_light_list;
    vector<Data> light_to_temperature_list;
    vector<Data> temperature_to_humidity_list;
    vector<Data> humidity_to_location_list;

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

        int lastLine = nLine;

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
                Data sts = Data(-1, -1, -1);

                if (sts.target == -1)            // because nextToken is already the first number of the line
                    sts.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (sts.start == -1)
                        sts.start = stoul(nextToken);
                    else if (sts.range == -1)
                        sts.range = stoul(nextToken);
                }
                seed_to_soil_list.push_back(sts);
            } else if (soil_to_fertilizer) {
                Data stf = Data(-1, -1, -1);

                if (stf.target == -1)            // because nextToken is already the first number of the line
                    stf.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (stf.start == -1)
                        stf.start = stoul(nextToken);
                    else if (stf.range == -1)
                        stf.range = stoul(nextToken);
                }
                soil_to_fertilizer_list.push_back(stf);
            } else if (fertilizer_to_water) {
                Data ftw = Data(-1, -1, -1);

                if (ftw.target == -1)            // because nextToken is already the first number of the line
                    ftw.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (ftw.start == -1)
                        ftw.start = stoul(nextToken);
                    else if (ftw.range == -1)
                        ftw.range = stoul(nextToken);
                }
                fertilizer_to_water_list.push_back(ftw);
            } else if (water_to_light) {
                Data wtl = Data(-1, -1, -1);

                if (wtl.target == -1)            // because nextToken is already the first number of the line
                    wtl.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (wtl.start == -1)
                        wtl.start = stoul(nextToken);
                    else if (wtl.range == -1)
                        wtl.range = stoul(nextToken);
                }
                water_to_light_list.push_back(wtl);
            } else if (light_to_temperature) {
                Data ltt = Data(-1, -1, -1);

                if (ltt.target == -1)            // because nextToken is already the first number of the line
                    ltt.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (ltt.start == -1)
                        ltt.start = stoul(nextToken);
                    else if (ltt.range == -1)
                        ltt.range = stoul(nextToken);
                }
                light_to_temperature_list.push_back(ltt);
            } else if (temperature_to_humidity) {
                Data tth = Data(-1, -1, -1);

                if (tth.target == -1)            // because nextToken is already the first number of the line
                    tth.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (tth.start == -1)
                        tth.start = stoul(nextToken);
                    else if (tth.range == -1)
                        tth.range = stoul(nextToken);
                }
                temperature_to_humidity_list.push_back(tth);
            } else if (humidity_to_location) {
                Data htl = Data(-1, -1, -1);

                if (htl.target == -1)            // because nextToken is already the first number of the line
                    htl.target = stoul(nextToken);

                while (iss >> nextToken) {
                    if (htl.start == -1)
                        htl.start = stoul(nextToken);
                    else if (htl.range == -1)
                        htl.range = stoul(nextToken);
                }
                humidity_to_location_list.push_back(htl);
            }
        }
    }

    // FOR EACH SEED
    for (int i = 0; i < seeds.size(); i++) {
        unsigned long values[7];

        // BY DEFAULT, SOIL IS THE SAME AS SEED
        values[0] = findValue(seed_to_soil_list, seeds[i]);

        // Continue this pattern for other lists
        values[1] = findValue(soil_to_fertilizer_list, values[0]);
        values[2] = findValue(fertilizer_to_water_list, values[1]);
        values[3] = findValue(water_to_light_list, values[2]);
        values[4] = findValue(light_to_temperature_list, values[3]);
        values[5] = findValue(temperature_to_humidity_list, values[4]);
        values[6] = findValue(humidity_to_location_list, values[5]);

        if (values[6] < answer)
            answer = values[6];
    }

    cout << "ANSWER: " << answer;
}
