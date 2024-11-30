#include <iostream>
#include "Game.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    Wizard wizard1("Fire Mage", MagicPower::REMOVE_ROW_WITH_OWN_CARD);
    Wizard wizard2("Ice Mage", MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN);

    Game game(3, "Player1", "Player2", wizard1, wizard2);
    game.start();


	return 0;
}
