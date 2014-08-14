#ifndef SERVERSETUP_H
#define SERVERSETUP_H

#include "ircconnection.h"

#include <QDialog>

namespace Ui {
class ServerSetup;
}

class ServerSetup : public QDialog
{
    Q_OBJECT

public:
    explicit ServerSetup(QWidget *parent, IRCConnection *connection);
    ~ServerSetup();
public slots:
    void accept();
    void deny();

private:
    IRCConnection *connection;
    Ui::ServerSetup *ui;
};

#endif // SERVERSETUP_H
