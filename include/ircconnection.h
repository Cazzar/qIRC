#ifndef IRCCONNECTION_H
#define IRCCONNECTION_H

#include <QObject>
#include <QtNetwork>
#include <iostream>

class IRCConnection : public QObject
{
    Q_OBJECT
public:
    IRCConnection();
    bool sendRaw(QString message);
    void setup(QString server, qint16 port, QString nickname, QStringList chans, QString realname = "qIRC", QString pass = "");
    void connect(bool wait = false);
    void send(QString channel, QString message);

public slots:
    void readyToRead();
    void connected();
    //void messageRecieved(QString sender, QString channel, QString message);
signals:
    void message(QString src, QString channel, QString message);
    void command(QString command, QStringList params, QString prefix);
private:
    void handleLine(QString str, QString &prefix, QString &command, QString &trailing, QStringList &params);
    void handleCommand(QString command, QStringList params, QString prefix);

    QTcpSocket *socket;
    QString server;
    qint16 port; //6667
    QString nickname;
    QStringList chans;
    QString realname; //qIRC
    QString pass; //""
};

#endif // IRCCONNECTION_H
