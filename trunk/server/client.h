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
#ifndef CLIENT_H
#define CLIENT_H

#include "parser/parser.h"
#include "playerctrl.h"
#include "gameeventhandler.h"

#include <QObject>
#include <QPointer>

class QTcpSocket;


/**
 * The client class provides a adaptor between the parser and the player
 * control. The remote client sends requests that are handled and provided
 * by the Parser class and this class uses these requests to control the player
 * through the PlayerCtrl interface.
 *
 * Lifetime is controled by object itself.
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Client : public QObject, public GameEventHandler
{
Q_OBJECT
public:
    /**
     * Constructs the client object.
     * \param parent The parent QObject.
     * \param id The client id.
     * \param socket The opened QTcpSocket to the client.
     */
    Client(QObject* parent, int id, QTcpSocket* socket);
    virtual ~Client();

    /**
     * Returns the id of the client.
     * \note The id = 0 is reserved and cannot be used.
     */
    int id() const;


public slots: // These slots are connected to parser
    void onActionCreateGame(const StructGame& structGame, const StructPlayer& structPlayer);
    void onActionJoinGame(int gameId, const StructPlayer& structPlayer);
    void onActionLeaveGame();
    void onActionStartGame();
    void onActionDrawCard(int numCards, bool revealCard);
    void onActionPlayCard(const ActionPlayCardData&);
    void onActionEndTurn();
    void onActionPass();
    void onActionDiscard(int cardId);

    void onQueryServerInfo(QueryResult result);
    void onQueryGame(int gameId, QueryResult result);
    void onQueryGameList(QueryResult result);

public: /* The GameEventHandler interface */
    virtual void onIncomingMessage(const PublicPlayerView& publicPlayerView, const QString& message);
    virtual void onPlayerInit(PlayerCtrl* playerCtrl);
    virtual void onGameSync();
    virtual void onPlayerExit();
    virtual void onPlayerJoinedGame(const PublicPlayerView& publicPlayerView);
    virtual void onPlayerLeavedGame(const PublicPlayerView&);
    virtual void onPlayerDied(const PublicPlayerView&);
    virtual void onGameStartabilityChanged(bool isStartable);
    virtual void onGameStarted();
    virtual void onPlayerDrawedCard(int playerId, const PlayingCard*);
    virtual void onPlayerDiscardedCard(int playerId, PocketType pocket, const PlayingCard* card);
    virtual void onPlayerPlayedCard(int playerId, const PlayingCard* card);
    virtual void onPlayerPlayedOnTable(int playerId, PocketType pocketFrom, const PlayingCard* card, int targetPlayerId);
    virtual void onPlayerCheckedCard(int playerId, const PlayingCard* card, const PlayingCard* checkedCard, bool checkResult);
    virtual void onPlayerStealedCard(int stealerId, int stealedId, PocketType pocketFrom, const PlayingCard* card);
    virtual void onDrawIntoSelection(const PlayingCard* card);
    virtual void onPlayerDrawedFromSelection(int playerId, const PlayingCard* card);
    virtual void onPlayedCardsCleared();
    virtual void onLifePointsChange(const PublicPlayerView&, int oldLifePoints, int newLifePoints);
    virtual void onGameContextChange(const GameContextData&);

    virtual void onActionRequest(ActionRequestType requestType);


public slots:
    void startAI();

signals:
    void disconnected(int clientId);


private:
    bool isInGame() const;



private:
    const int           m_id;
    Parser*             mp_parser;
    PlayerCtrl*         mp_playerCtrl;
};

#endif
