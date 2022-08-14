#ifndef RIGHTSIDE_H
#define RIGHTSIDE_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "metadata.h"
#include <QFileDialog>
#include <QMessageBox>
#include "videobutton.h"
#include <QDir>
#include <QDirIterator>
#include "map.h"

using namespace std;

class RightSide : public QWidget {
    Q_OBJECT
public:
    explicit RightSide(QWidget *parent = nullptr);

private:
    void createWidgets();
    void widgetLayout();
    void makeConnections();

    // add video buttons to the right side
    int addVideos();

    // widget and layouts for the right side
    QVBoxLayout *right_layout;
    MapWidget *mapwidget;
    QScrollArea *video_scroll;
    QWidget *video_widget;
    QVBoxLayout *scroll_layout;
    QPushButton *open_files;
    // video thumbnails that act as buttons
    vector<VideoButton *> video_buttons;
    // collection of videos for the right side
    MetaData opened_videos;

private slots:
    // takes in open_folder signal to open videos
    void openFrom();
    // removes the video from the opened list
    void removeVideo(Video* parent_video);

public slots:
    void changeLocation(Video* v);

signals:
    // signal for the main video player
    void jumpTo(Video* parent_video);
};

#endif // RIGHTSIDE_H
