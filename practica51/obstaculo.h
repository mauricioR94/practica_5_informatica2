#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <vector>
#include <utility>
using namespace std;
class obstaculo
{
private:
    int max_x, max_y;
    vector<pair<int , int >> esquinas;
    int centro;

public:
    obstaculo();
};

#endif // OBSTACULO_H
