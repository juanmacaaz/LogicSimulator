#include "parser.h"
#include "ui_parser.h"

Parser::Parser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Parser)
{
    ui->setupUi(this);
}

Parser::~Parser()
{
    delete ui;
}
