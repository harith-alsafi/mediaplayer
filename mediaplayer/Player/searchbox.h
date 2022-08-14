#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QtWidgets/QtWidgets>
#include "custommenu.h"

class SearchBox : public QWidget {
    Q_OBJECT
public:
    SearchBox();
    ~SearchBox();
    QPushButton *getSearch() { return search; };
    QLineEdit *getLine() { return line; };

private:
    QHBoxLayout *box;
    QLineEdit *line;
    QPushButton *search;
    QAction *location;
    QAction *tag;
    Menu *search_options;
    QMenuBar* options_bar;

private slots:
    void textChanged();

signals:
    void searchEntered(const QString &, bool, bool);
};

#endif // SEARCHBOX_H
