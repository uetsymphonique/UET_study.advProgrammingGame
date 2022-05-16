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
    is>>player.totalSwings;
    getline(is,player.namePlayer,'\n');
    player.namePlayer.erase(0,1);
    return is;
}
ostream& operator<<(ostream& os,Player player){
    os<<player.totalSwings<<" "<<player.namePlayer;
    return os;
}


