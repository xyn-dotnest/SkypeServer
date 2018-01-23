#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QThread>

class Rooms;
class Room;
class Server;
class TcpSocket;
class Sox;

class SocketThread : public QThread
{
    Q_OBJECT

public:
    SocketThread(int descriptor, Rooms *rooms, QSqlDatabase db, QList<SocketThread*>* Clients, QObject *parent = nullptr);
    ~SocketThread();

    void run();
    void Authentication(QString login, QString pass);
    void CreateRooms(QString name, QString pass);
    void GetInRoom(QString name, QString pass);
    void writingToFile(QByteArray buffer);
    void removeNoise();
    void gettingFriends();
    void closeRoomFriendHangUp(QString name);
    void sendHistoryMessage(QString idFriend);
    QString getId();

    int numberDisplay = 0;

signals:
    void noiseRemove();

private slots:
    void SlotSendToClient(QString str);
    void OnReadyRead();
    void OnDisconnected();
    void sendSound();
    void checkId(QString testId, QString nameRoom, QString passRoom);
    void checkIdForSendMessage(QString testId, QString message, QString idSender);
    void checkFriendsUpdateOnline(QString testId, QString idFriend, QString status);

private:
    int SocketDescriptor;
    Rooms* AllRooms;
    QSqlDatabase DataBase;
    Room* room = nullptr;
    TcpSocket* Socket;
    Sox *myProcess;
    QString name;
    QString id;
    QList<SocketThread*>* socketClients;
    QThread thread;

};

#endif // SOCKETTHREAD_H
