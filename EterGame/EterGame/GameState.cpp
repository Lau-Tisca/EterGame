#include "GameState.h"
#include <iostream>
#include <fstream>

json GameState::to_json() const {
    return {
        {"gameMode", gameMode},
        {"board", board},
        {"player1Hand", player1Hand},
        {"player2Hand", player2Hand},
        {"player1Score", player1Score},
        {"player2Score", player2Score}
    };
}

GameState GameState::from_json(const json& j) {
    GameState state;
    j.at("gameMode").get_to(state.gameMode);
    j.at("board").get_to(state.board);
    j.at("player1Hand").get_to(state.player1Hand);
    j.at("player2Hand").get_to(state.player2Hand);
    j.at("player1Score").get_to(state.player1Score);
    j.at("player2Score").get_to(state.player2Score);
    return state;
}