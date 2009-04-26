 /***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "player.h"
#include "game.h"
#include "client.h"
#include "cards.h"
#include "playerctrl.h"


#include "gameinfo.h"
#include "gamecycle.h"


Player::Player(Game* game,
               int id,
               const QString& name,
               const QString& password,
               GameEventHandler* gameEventHandler):
        QObject(game),
        m_id(id),
        m_name(name),
        m_password(password),
        m_role(ROLE_UNKNOWN),
        m_isAlive(1),
        mp_game(game),
        mp_gameEventHandler(gameEventHandler),
        m_weaponRange(1),
        m_distanceIn(0),
        m_distanceOut(0),
        m_lastBangTurn(-1),
        m_unlimitedBangs(0),
        m_publicPlayerView(this),
        m_privatePlayerView(this)
{
    mp_playerCtrl = new PlayerCtrl(this);
    mp_gameEventHandler->onPlayerInit(mp_playerCtrl);
    m_predrawChecks.append(0);
}


bool Player::isCreator() const
{
    return (mp_game->gameInfo().creatorId() == m_id);
}

bool Player::isOnTurn() const
{
    return (mp_game->gameCycle().currentPlayer() == this);
}

bool Player::isRequested() const
{
    return (mp_game->gameCycle().requestedPlayer() == this);
}

bool Player::hasIdenticalCardOnTable(PlayingCard* card) const
{
    foreach(PlayingCard* c, m_table) {
        if (card->type() == c->type())
            return 1;
    }
    return 0;
}

bool Player::canPlayBang() const
{
    return (m_unlimitedBangs > 0 || m_lastBangTurn != mp_game->gameCycle().turnNumber());
}

void Player::modifyLifePoints(int x, Player* shooter, bool disableBeerRescue)
{
    int oldLifePoints = m_lifePoints;
    m_lifePoints += x;
    if (m_lifePoints > m_maxLifePoints)
        m_lifePoints = m_maxLifePoints;

    if (oldLifePoints != m_lifePoints) {
        foreach (Player* p, mp_game->playerList()) {
            p->gameEventHandler()->onLifePointsChange(publicView(), oldLifePoints, m_lifePoints);
        }
    }
    if (m_lifePoints <= 0) {
        if (disableBeerRescue) 
            mp_game->buryPlayer(this, shooter);
        else
            mp_game->beerRescue()->allowSaveWithBeer(shooter, this, 1 - m_lifePoints);
    }
}

void Player::modifyDistanceIn(int delta)
{
    m_distanceIn += delta;
}

void Player::modifyDistanceOut(int delta)
{
    m_distanceOut += delta;
}

void Player::modifyUnlimitedBangs(int delta)
{
    m_unlimitedBangs += delta;
}

void Player::setWeaponRange(int weaponRange)
{
    m_weaponRange = weaponRange;
}

void Player::setAlive(bool isAlive)
{
    m_isAlive = isAlive;
}

void Player::appendCardToHand(PlayingCard * card)
{
    m_hand.append(card);
}

void Player::appendCardToTable(PlayingCard* card)
{
    m_table.append(card);
}

void Player::appendCardToSelection(PlayingCard* card)
{
    m_selection.append(card);
}

bool Player::removeCardFromHand(PlayingCard* card)
{
    return m_hand.removeOne(card);
}

PlayingCard* Player::getRandomCardFromHand()
{
    int size = m_hand.size();
    if (size == 0) return 0;
    return m_hand[rand() % size];
}

bool Player::removeCardFromTable(PlayingCard* card)
{
    return m_table.removeOne(card);
}

bool Player::removeCardFromSelection(PlayingCard* card)
{
    return m_selection.removeOne(card);
}

void Player::setRole(const PlayerRole& role)
{
    m_role = role;
    if (m_role == ROLE_SHERIFF) {
        m_maxLifePoints = 5;
    } else {
        m_maxLifePoints = 4;
    }
    // TODO: character can influence maxLifePoints


    m_lifePoints = m_maxLifePoints;
//    if (!isCreator())
//        m_lifePoints = 1;
}

void Player::registerPredrawCheck(int priority)
{
    m_predrawChecks.append(priority);
    qSort(m_predrawChecks.begin(), m_predrawChecks.end());
}

void Player::unregisterPredrawCheck(int priority)
{
    m_predrawChecks.removeAll(priority);
}

void Player::predrawCheck(int checkId)
{
    if (m_currentPredraw != checkId)
        throw BadPredrawException();
    if (checkId == 0)
        return;
    int index = m_predrawChecks.indexOf(checkId);
    Q_ASSERT(index > 0);
    m_currentPredraw = m_predrawChecks[index - 1];
}

void Player::onBangPlayed()
{
    m_lastBangTurn = mp_game->gameCycle().turnNumber();
}

void Player::onTurnStart()
{
    m_currentPredraw = m_predrawChecks.last();
}


/*-- DEPRECATED
StructPlayer Player::structPlayer(bool returnPrivateInfo)
{
    StructPlayer x;
    x.id = m_id;
    x.name = m_name;
    x.password = m_password;
    if (returnPrivateInfo || x.role == ROLE_SHERIFF)
    {
        x.role = m_role;
    } else {
        x.role = ROLE_UNKNOWN;
    }
    return x;
}
*/




