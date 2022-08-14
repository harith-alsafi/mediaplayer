#ifndef LEFTSIDE_H
#define LEFTSIDE_H
#include <QtWidgets/QtWidgets>
#include "metadata.h"
#include "searchbox.h"
#include "collection_display.h"
#include "prompt.h"

class LeftSide : public QWidget {
    Q_OBJECT
public:
    LeftSide(MetaData *m);
    ~LeftSide();
    Video *getSelectedVideo();

private:
    MetaData *collection;
    void createMenus();
    void makeConnections();

    SearchBox *searchBox;
    CollectionDisplay *collectionDisplay;
    QVBoxLayout *lay;

    Video *selected_vid = NULL; // will be used from main window

public slots:

    // used to emit sendVideo so that it will be used with mainwindow
    // will be called when item is double clicked
    void setDoubleClickVideo(Video *v);
    void setSelectedVideo(Video *v);

    void getNext(Video* v);
    void getPrev(Video* v);

signals:

    void updateDisplay();

    // sends the signal for mainwindow (for playing)
    // using when CollectionDisplay is double clicked
    void playVideo(Video *v);

    // sends current selected vid (single click)
    void videoSelected(Video *v);

    void remove_video(Video *vid);
    void add_tag(Video *vid);
    void remove_tag(Video *vid);
    void change_loc(Video *vid);

    // used to set next vid and previous vid
    void sendNext(Video* vid);
    void sendPrevious(Video* vid);

};

#endif // LEFTSIDE_H
