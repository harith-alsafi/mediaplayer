#ifndef VIDEOBUTTON_H
#define VIDEOBUTTON_H

#include <QPushButton>
#include <QUrl>
#include <QFile>
#include <QImageReader>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include "video.h"

using namespace std;

class VideoButton : public QPushButton {
    Q_OBJECT

public:
    // The shape of the button when it's displayed.
    enum class DisplayType { ROUND, RECTANGLE };

    // What menu options this button should provide.
    enum class MenuType {
        // This button represents a video in a collection.
        COLLECTION,
        // This button represents a video in a file explorer.
        FOLDER
    };

    // takes in reference to video, type 1: rectangle, 2: round
    VideoButton(QWidget *parent, Video *video, DisplayType d_type, MenuType m_type);

private:
    // icon properties and initialization
    int initializeIcon(string thumbnail, DisplayType type);
    int initializeUrl(string path);
    void setup_menu(MenuType type);

    Video *parent_video;
    // thumbnail of the video
    QIcon *video_icon;
    // URL of the video file
    QUrl *video_url;
    // icon type
    DisplayType display_type;

    // Right click menu.
    MenuType menu_type;
    QMenu *menu;
    QAction *remove_act;

    // Collection Menu Actions.
    QAction *add_tag_act;
    QAction *remove_tag_act;
    QAction *change_loc_act;

    // Folder Menu Actions.
    QAction *add_to_coll_act;

private slots:
    // click and right click event handling
    void mousePressEvent(QMouseEvent *event);

signals:
    // signal for the main video player
    void play_video(Video *parent_video);

    // emits a vid signal of currently selected item (used by left side)
    void vid_selected(Video *vid);

    // Menu signals.
    void remove_video(Video *vid);
    void add_tag(Video *vid);
    void remove_tag(Video *vid);
    void change_loc(Video *vid);
    void add_to_coll(Video *vid);
};

#endif // VIDEOBUTTON_H
