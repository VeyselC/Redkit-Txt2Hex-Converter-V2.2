#include "dialog.h"
#include "ui_dialog.h"


dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
}

dialog::~dialog()
{
    delete ui;
}

void dialog::openingslot()
{
//	LoadSettings();
}
