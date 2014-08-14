#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "IRCStatus.h"
#include "ircconnection.h"
#include "serversetup.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectToServer();
    void commandRecv(QString command, QStringList params, QString prefix);
    void messageRecv(QString src, QString channel, QString message);
    void sendRaw();

private:
    Ui::MainWindow *ui;
    IRCConnection *connection;
};

#endif // MAINWINDOW_H
