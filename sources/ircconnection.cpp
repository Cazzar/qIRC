#include "ircconnection.h"

IRCConnection::IRCConnection()
{
    socket = new QTcpSocket;
    QObject::connect(socket, &QTcpSocket::readyRead, //connect to
                     this, &IRCConnection::readyToRead);

    QObject::connect(socket, &QTcpSocket::connected,
                     this, &IRCConnection::connected);

    //    QObject::connect(this, &IRCConnection::message,
    //                     this, &IRCConnection::messageRecieved);
}

void IRCConnection::setup(QString server, qint16 port, QString nickname, QStringList chans, QString realname, QString pass)
{
    this->chans = chans;
    this->server = server;
    this->port = port;
    this->nickname = nickname;
    this->realname = realname;
    this->pass = pass;
}

void IRCConnection::connect(bool wait)
{
    this->socket->connectToHost(QString("irc.esper.net"), 6667);
    if (wait)
        this->socket->waitForConnected();
}

void IRCConnection::connected()
{
    //RFC 1459 order.
    if (!pass.isEmpty())
        this->sendRaw(QString("PASS :%1").arg(pass));

    this->sendRaw(QString("NICK %1").arg(nickname));
    this->sendRaw(QString("USER %1 8 * :%2").arg(nickname, realname));
}

void IRCConnection::readyToRead()
{
    while (socket->canReadLine())
    {
        QString line = socket->readLine().split('\r').first();
        qDebug() << "<<< " << line;
        QString prefix;
        QString command;
        QString trailing;
        QStringList params;

        this->handleLine(line, prefix, command, trailing, params);

        this->handleCommand(command, params, prefix);
    }
}

bool IRCConnection::sendRaw(QString message)
{
    qDebug() << ">>> " << message;

    this->socket->write(QString("%1\r\n").arg(message).toStdString().c_str());
    return this->socket->flush();
}

void IRCConnection::send(QString channel, QString message)
{
    this->sendRaw(QString("PRIVMSG %1 :%2").arg(channel, message));
}

void IRCConnection::handleLine(QString str, QString &prefix, QString &command, QString &trailing, QStringList &params)
{
    int prefixEnd = -1, trailingStart = str.length();

    trailing = "";
    prefix = command = "";


    //prefix if present
    if (str.startsWith(":"))
    {
        prefixEnd = str.indexOf(" ");
        prefix = str.left(prefixEnd);
    }

    // Grab the trailing if it is present. If a message contains
    // a space immediately following a colon, all characters after
    // the colon are the trailing part.
    trailingStart = str.indexOf(" :");
    if (trailingStart >= 0)
        trailing = str.mid(trailingStart + 2);
    else
        trailingStart = str.length();


    // Use the prefix end position and trailing part start
    // position to extract the command and parameters.
    QStringList cmdAndParams = str.mid(prefixEnd + 1, trailingStart - prefixEnd - 1).split(" ");

    //oh, stacks
    command = cmdAndParams.first();
    cmdAndParams.pop_front();

    params = cmdAndParams;

    if (!trailing.isEmpty())
        params.append(trailing);
}

void IRCConnection::handleCommand(QString command, QStringList params, QString prefix)
{
    if (command == "PING")
    {
        QString command("PONG :%1");
        this->sendRaw(command.arg(params.last()));
    }
    else if (command == "004")
    {
        for (int i = 0; i < this->chans.size(); i++)
        {
            this->sendRaw(QString("JOIN %1").arg(this->chans.at(i)));
        }
    }
    else if (command == "PRIVMSG")
    {
        emit this->message(prefix, params.first(), params.last());
    }

    emit this->command(command, params, prefix);
}
