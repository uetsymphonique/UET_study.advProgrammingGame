#include "Player.hpp"
Player::Player(){
    this->totalSwings = 0;
    this->namePlayer = "";
}
Player::Player(std::string namePlayer,int totalSwings){
    this->totalSwings = totalSwings;
    this->namePlayer = namePlayer;
}
void Player::setNamePlayer(std::string namePlayer){
    this->namePlayer = namePlayer;
}
void Player::setTotalSwings(int totalSwings){
    this->totalSwings = totalSwings;
}
string Player::getNamePlayer(){
    return namePlayer;
}
int Player::getTotalSwings(){
    return totalSwings;
}
istream& operator>>(istream& is,Player& player){
    is>>player.totalSwings>>player.namePlayer;
    return is;
}
ostream& operator<<(ostream& os,Player player){
    os<<player.namePlayer<<": "<<player.totalSwings;
    return os;
}


