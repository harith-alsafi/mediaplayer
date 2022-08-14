#ifndef COLLECTION_DISPLAY_H
#define COLLECTION_DISPLAY_H

#include <QtWidgets/QtWidgets>
#include "video.h"
#include "metadata.h"
#include "videobutton.h"

/**
 * @brief The CollectionDisplay class
 *
 * This displays the videos in the current collection.
 * A user can search,sort add tags or a location to each video.
 */
class CollectionDisplay : public QTableWidget {
    Q_OBJECT
public:
    CollectionDisplay(MetaData *metadata);
    ~CollectionDisplay() { }
    void reset();

    Video* getNext(Video* v);
    Video* getPrev(Video* v);

public slots:
    void update();
    void filter(const QString &, bool, bool);

    // sets the sort (by length, path, location)
    void setSort(int logicalIndex);

    // used to emit the sendVideo() signal
    // called when any item is selected
    void setVideo();



    // used to emit sendVideo() signal
    // called when item is double clicked
    void setDoubleClick(const QModelIndex &index);

signals:
    // sends signal of selected video for selection not playing
    // (first selected one only)
    void sendVideo(Video *v);

    // sends signal of double clicked vid
    void sendDoubleClickVid(Video *v);

    // Relay signals from the video button.
    void remove_video(Video *vid);
    void add_tag(Video *vid);
    void remove_tag(Video *vid);
    void change_loc(Video *vid);

    void sendPrevious(Video* v);
    void sendNext(Video* v);

private:
    // This is where references to videos that meet the search criteria will be kept.
    // It uses pointers so that we still have access to the original version of each video.
    MetaData filteredVideos;

    // This is a reference to the original metadata.
    MetaData *originalVideos;
    void addRow(int r, Video &vid);
    void makeConnection();
    void choseSort(MetaData::Sort s);
    bool chosesort;
    int row;
};

#endif // COLLECTION_DISPLAY_H
