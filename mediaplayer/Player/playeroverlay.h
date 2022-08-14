#ifndef PLAYEROVERLAY_H
#define PLAYEROVERLAY_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class PlayerOverlay : public QFrame {

    Q_OBJECT

public:
    PlayerOverlay(QWidget *parent = nullptr, std::string text = "");
    ~PlayerOverlay();

    void reset(std::string content);

signals:
    void clicked();

private:
    QHBoxLayout *layout;
    QLabel *contents;
    QPushButton *button;
};

#endif // PLAYEROVERLAY_H
