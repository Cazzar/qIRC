#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connection(new IRCConnection)
{
    this->ui->setupUi(this);
    QObject::connect(this->ui->actionConnect, SIGNAL(triggered()),
                    this, SLOT(connectToServer()));

    QObject::connect(this->connection, SIGNAL(command(QString,QStringList,QString)),
                     this, SLOT(commandRecv(QString,QStringList,QString)));
    QObject::connect(this->connection, SIGNAL(message(QString,QString,QString)),
                     this, SLOT(messageRecv(QString,QString,QString)));

    QObject::connect(this->ui->pushButton, SIGNAL(clicked()),
                     this, SLOT(sendRaw()));

}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::connectToServer()
{
    ServerSetup *dialogue = new ServerSetup(this, this->connection);
    dialogue->show();
}

void MainWindow::commandRecv(QString command, QStringList params, QString prefix)
{
    this->ui->textBrowser->append(QString(":%1 %2 Params: %3\n").arg(prefix, command, params.join(' ')));
}

void MainWindow::messageRecv(QString src, QString channel, QString message)
{
    this->ui->textBrowser_2->append(QString("%1 %2: %3\n").arg(channel, src, message));
}

void MainWindow::sendRaw()
{
    this->connection->sendRaw(this->ui->lineEdit->text());

    this->ui->lineEdit->clear();
}
