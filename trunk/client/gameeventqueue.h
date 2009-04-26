#ifndef GAMEEVENTQUEUE_H
#define GAMEEVENTQUEUE_H

#include <QObject>
#include <QQueue>

namespace client
{
class GameEvent;

class GameEventQueue : public QObject
{
Q_OBJECT;
public:
    GameEventQueue(QObject* parent);
    void add(GameEvent*);

public slots:
    void onGameEventFinished(GameEvent*);

private slots:
    void runGameEvent();

private:
    QQueue<GameEvent*> m_queue;

};
}

#endif // GAMEEVENTQUEUE_H
