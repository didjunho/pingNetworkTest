#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

bool check_num(char in) {
    if (in == '0' || in == '1') {
        return true;
    }

    if (in == '2' || in == '3') {
        return true;
    }

    if (in == '4' || in == '5') {
        return true;
    }

    if (in == '6' || in == '7') {
        return true;
    }

    if (in == '8' || in == '9') {
        return true;
    }
    return false;
}

std::string get_ping(char ping_in[]) {
    std::string fixed;
    while(!check_num(*ping_in)) {
        ++ping_in;
    }
    
    while(check_num(*ping_in)) {
        fixed += *ping_in;
        ++ping_in;
    }
    return fixed;
}

int main(int argc, char * argv[]) {

    std::string init; //pinging ip, just for info
    std::string trash;
    int fail = 0; //time out/unreachable
    int slow = 0; //time > 120
    int pass = 0; //time < 120 && time > 0
    char ping[11];


    std::ifstream InFile("output.txt");

    InFile >> trash >> init;
    InFile >> trash >> trash >> trash >> trash >> trash;

    for(int i = 0; i < 100; ++i) {
        InFile >> trash;
        if(!strcmp(trash.c_str(), "Request")) {
            ++fail;
            InFile >> trash >> trash;
        }
        else { 
            InFile >> trash >> trash >> trash;
            if (!strcmp(trash.c_str(), "Destination")) {
                ++fail;
                InFile >> trash >> trash;
            }
            else {
                InFile >> ping;
                std::string ping_num = get_ping(ping);
                int fin_ping = atoi(ping_num.c_str());
                if(fin_ping > 120) {
                    ++slow;
                    InFile >> trash;
                }
                else if(fin_ping <= 120) {
                    ++pass;
                    InFile >> trash;
                }
                else {
                    return 1;
                }
            }
        }
    }

    for(int i = 0; i < 24; ++i) {
        InFile >> trash;
    }

    char stats[6];

    InFile >> stats;
    std::string stats_min = get_ping(stats);
    int min = atoi(stats_min.c_str());

    InFile >> trash >> trash;

    InFile >> stats;
    std::string stats_max = get_ping(stats);
    int max = atoi(stats_max.c_str());

    InFile >> trash >> trash;

    InFile >> stats;
    std::string stats_avg = get_ping(stats);
    int avg = atoi(stats_avg.c_str());


    std::cout << "Pinged IP: " << init << std::endl;
    std::cout << "Num Pass: " << pass << std::endl;
    std::cout << "Num Slow: " << slow << std::endl;
    std::cout << "Num Fail: " << fail << std::endl;
    if(fail == 0) {
        std::cout << "% Failed: 0%" << std::endl;
    }
    else {
        std::cout << "% Failed: " << double((fail/double(pass + slow + fail)))*100 << "%" <<std::endl;
    }
    std::cout << "Min Ping: " << min << std::endl;
    std::cout << "Max Ping: " << max << std::endl;
    std::cout << "Avg Ping: " << avg << std::endl;

    return 0;
}