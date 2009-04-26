#include "cardbarrel.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"
#include "gameexceptions.h"

CardBarrel::CardBarrel(Game *game, int id, CardSuit suit, CardRank rank):
        TableCard(game, id, CARD_BARREL, suit, rank)
{
}

CardBarrel::~CardBarrel()
{
}

void CardBarrel::play()
{
    gameCycle()->assertTurn();
    assertInHand();
    if (owner()->hasIdenticalCardOnTable(this))
        throw TwoSameOnTableException();
    gameTable()->playOnTable(this);
}


void CardBarrel::registerPlayer(Player* player)
{
}

void CardBarrel::unregisterPlayer(Player* player)
{
}


bool CardBarrel::check()
{
    return gameTable()->checkCard(owner(), this, *CardBarrel::checkBarrel);
}

bool CardBarrel::checkBarrel(PlayingCard* card)
{
    return  (card->suit() == SUIT_HEARTS);
}
