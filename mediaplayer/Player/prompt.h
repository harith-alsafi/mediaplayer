#ifndef PROMPT_H
#define PROMPT_H

#include <QtWidgets/QtWidgets>
#include "video.h"

class LocationPrompt : public QDialog {
    Q_OBJECT
public:
    LocationPrompt(QWidget *parent = 0, QString label_name = "Location");
    ~LocationPrompt();

private:
    QHBoxLayout *lay;
    QPushButton *add;
    QLabel *label;
    QLineEdit *lineEdit;
    QString label_name;
    Video *vid;
public slots:
    void addClicked();
    void enableAddButton(const QString &);
    void setVideo(Video *v);
signals:
    void newLocation(std::string, Video *);
};

class TagPrompt : public LocationPrompt {
    Q_OBJECT
public:
    TagPrompt(QWidget *parent = 0, QString label_name = "Tag");
    ~TagPrompt() { }
};

class RemoveTagPrompt : public QDialog {
    Q_OBJECT
public:
    RemoveTagPrompt();

    ~RemoveTagPrompt();

private:
    std::vector<QRadioButton *> options;
    QVBoxLayout *lay;
    QButtonGroup *options_container;
    QPushButton *remove_button;
    QLabel *label;
    Video *vid;

public slots:
    void removeClicked();
    void enableRemoveButton();
    // used to recieve signal from CollectionDisplay
    // such that it assigns vid
    void setVideo(Video *v);
    void displayCurrentTags();

signals:
    void tagRemoved();
};

#endif // PROMPT_H
