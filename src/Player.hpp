#ifndef PLAYERCLASS__
#define PLAYERCLASS__
#include "params.hpp"
class Player{
public:
    Player();
    Player(std::string namePlayer,int totalSwings);
    friend istream& operator>> (istream& is,Player& player);
    friend ostream& operator<< (ostream& os,Player player);
    void setTotalSwings(int totalSwings);
    void setNamePlayer(std::string namePlayer);
    int getTotalSwings();
    string getNamePlayer();
private:
    int totalSwings;
    string namePlayer;
};
#endif // PLAYERCLASS__
