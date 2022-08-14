#include "playeroverlay.h"

#include <string>
#include <QPixmap>
#include <QFontMetrics>
#include <iostream>

PlayerOverlay::PlayerOverlay(QWidget *parent, std::string text) : QFrame(parent)
{
    layout = new QHBoxLayout(this);
    contents = new QLabel(this);
    button = new QPushButton(this);

    int height = fontMetrics().height();
    button->setIcon(QPixmap(":/images/icons/cross.png"));
    button->setFlat(true);
    button->setMaximumSize(QSize(height, height));

    layout->setContentsMargins(9, 0, 9, 0);

    layout->addWidget(contents);
    contents->setStyleSheet("color: white;");
    setStyleSheet("background-color: rgb(145, 55, 230);");
    layout->addStretch(1);
    layout->addWidget(button);

    setLayout(layout);
    connect(button, &QPushButton::clicked, this, &PlayerOverlay::clicked);

    reset(text);
}

void PlayerOverlay::reset(std::string content)
{
    QString qText = QString::fromStdString(content);
    contents->setText(qText);

    setGeometry(x(), y(), layout->sizeHint().width(), fontMetrics().height() + 20);
}

PlayerOverlay::~PlayerOverlay()
{
    delete layout;
    delete contents;
    delete button;
}
