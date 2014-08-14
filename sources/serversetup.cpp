#include "serversetup.h"
#include "ui_serversetup.h"

ServerSetup::ServerSetup(QWidget *parent, IRCConnection *connection) :
    QDialog(parent),
    ui(new Ui::ServerSetup)
{
    this->connection = connection;
    this->ui->setupUi(this);
}

ServerSetup::~ServerSetup()
{
    delete ui;
}

void ServerSetup::accept()
{
    this->connection->setup(this->ui->lineEdit->text(), qint16(this->ui->spinBox->value()), "Cazzar|Test", QStringList("#cazzar"));
    this->connection->connect();
}

void ServerSetup::deny()
{
    //noop
}
