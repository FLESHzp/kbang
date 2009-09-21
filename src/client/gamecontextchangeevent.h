/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#ifndef GAMEFOCUSCHANGEEVENT_H
#define GAMEFOCUSCHANGEEVENT_H

#include "gameeventcmd.h"      // inheritance

namespace client
{
/**
 * The GameContextChangeEvent class represents the game-context game event.
 */
class GameContextChangeEvent: public GameEventCmd
{
Q_OBJECT;
public:
    /**
     * Constructs a GameContextChangeEvent related to <i>game</i>, according to
     * given GameContextData.
     */
    GameContextChangeEvent(GameEvent*, GameContextCmdDataPtr);

    /**
     * Destroys the GameContextChangeEvent.
     */
    virtual ~GameContextChangeEvent();

    virtual void doEventCmd(GameEvent::ExecutionMode);

    virtual void undoEventCmd(GameEvent::ExecutionMode);

private:
    GameContextData m_newContext;
    GameContextData m_oldContext;
};
}
#endif // GAMEFOCUSCHANGEEVENT_H
