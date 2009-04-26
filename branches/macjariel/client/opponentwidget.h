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
#ifndef OPPONENTWIDGET_H
#define OPPONENTWIDGET_H

#include <QWidget>
#include "ui_opponentwidget.h"
#include "playerwidget.h"

#include "parser/parserstructs.h"

namespace client {
class CardWidget;
class CardList;
class PlayerCharacterWidget;

/**
 * @author MacJariel <MacJariel@gmail.com>
 */
class OpponentWidget: public PlayerWidget, public Ui::OpponentWidget {

public:
    OpponentWidget(QWidget *parent);
    ~OpponentWidget();

    virtual void init(GameObjectClickHandler*, CardWidgetFactory*);

    virtual void paintEvent(QPaintEvent* event);

    virtual void setFromPublicData(const PublicPlayerData&);
    virtual void dieAndRevealRole(const PlayerRole& role);
    virtual void clear();

    virtual void setActive(uint8_t progress);

    virtual CardList*               hand()            { return mp_hand; }
    virtual CardList*               table()           { return mp_table; }
    virtual PlayerCharacterWidget*  characterWidget() { return mp_characterWidget; }
    virtual bool                    isLocalPlayer()   { return 0; }
    virtual QSize                   sizeHint() const;




private:
    void updateWidgets();
    void setSeriff(bool isSheriff);

private:
    QString m_baseStyleSheet;
    QPixmap m_sheriffBadgePixmap;
    QLabel* mp_sheriffBadge;

    bool        m_isDead;
    PlayerRole  m_role;
    CardWidget* mp_roleCard;
};
}
#endif
