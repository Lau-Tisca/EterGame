#pragma once

enum class MagicPower {
    NONE,
    //Puterile vrajitorilor
    REMOVE_OPPONENT_CARD_OVER_OWN,
    REMOVE_ROW_WITH_OWN_CARD,
    COVER_OPPONENT_CARD,
    CREATE_HOLE,
    MOVE_STACK_WITH_OWN_CARD,
    GAIN_EXTRA_CARD,
    MOVE_STACK_WITH_OPPONENT_CARD,
    MOVE_ROW_TO_EDGE,

    // Puterile elementelor
    CONTROLLED_EXPLOSION,
    DESTRUCTION,
    FLAMES,
    LAVA,
    FROM_ASHES,
    SPARKS,
    BLIZZARD,
    WHIRLWIND,
    HURRICANE,
    BLAST,
    MIRAGE,
    STORM,
    TIDE,
    FOG,
    WAVE,
    WHIRLPOOL,
    TSUNAMI,
    CASCADE,
    SUPPORT,
    EARTHQUAKE,
    SHATTER,
    BORDERS,
    AVALANCHE,
    BOULDER
};

// Supraincarcă operatorul `<<` pentru `MagicPower`
inline std::ostream& operator<<(std::ostream& os, MagicPower power) {
    std::string powerName;
    switch (power) {
    case MagicPower::REMOVE_ROW_WITH_OWN_CARD: powerName = "Remove Row with Own Card"; break;
    case MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN: powerName = "Remove Opponent Card Over Own"; break;
    case MagicPower::COVER_OPPONENT_CARD: powerName = "Cover Opponent Card"; break;
    case MagicPower::CREATE_HOLE: powerName = "Create Hole"; break;
    case MagicPower::MOVE_STACK_WITH_OWN_CARD: powerName = "Move Stack with Own Card"; break;
    case MagicPower::GAIN_EXTRA_CARD: powerName = "Gain Extra Ether Card"; break;
    case MagicPower::MOVE_STACK_WITH_OPPONENT_CARD: powerName = "Move Stack with Opponent Card"; break;
    case MagicPower::MOVE_ROW_TO_EDGE: powerName = "Move Row to Edge"; break;

        //Elemente
    case MagicPower::CONTROLLED_EXPLOSION: powerName = "Controlled Explosion"; break;
    case MagicPower::DESTRUCTION: powerName = "Destruction"; break;
    case MagicPower::FLAMES: powerName = "Flames"; break;
    case MagicPower::LAVA: powerName = "Lava"; break;
    case MagicPower::FROM_ASHES: powerName = "From Ashes"; break;
    case MagicPower::SPARKS: powerName = "Sparks"; break;
    case MagicPower::BLIZZARD: powerName = "Blizzard"; break;
    case MagicPower::WHIRLWIND: powerName = "Whirlwind"; break;
    case MagicPower::HURRICANE: powerName = "Hurricane"; break;
    case MagicPower::BLAST: powerName = "Blast"; break;
    case MagicPower::MIRAGE: powerName = "Mirage"; break;
    case MagicPower::STORM: powerName = "Storm"; break;
    case MagicPower::TIDE: powerName = "Tide"; break;
    case MagicPower::FOG: powerName = "Fog"; break;
    case MagicPower::WAVE: powerName = "Wave"; break;
    case MagicPower::WHIRLPOOL: powerName = "Whirlpool"; break;
    case MagicPower::TSUNAMI: powerName = "Tsunami"; break;
    case MagicPower::CASCADE: powerName = "Cascade"; break;
    case MagicPower::SUPPORT: powerName = "Support"; break;
    case MagicPower::EARTHQUAKE: powerName = "Earthquake"; break;
    case MagicPower::SHATTER: powerName = "Shatter"; break;
    case MagicPower::BORDERS: powerName = "Borders"; break;
    case MagicPower::AVALANCHE: powerName = "Avalanche"; break;
    case MagicPower::BOULDER: powerName = "Boulder"; break;
    default: powerName = "Unknown Power"; break;
    }
    os << powerName;
    return os;
}