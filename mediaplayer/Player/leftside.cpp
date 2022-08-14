#include "leftside.h"
#include <QUrl>

LeftSide::LeftSide(MetaData *m) : QWidget()
{
    collection = m;
    createMenus();
    makeConnections();
}

LeftSide::~LeftSide()
{
    delete searchBox;
    delete lay;
    delete collectionDisplay;
}

void LeftSide::createMenus()
{
    searchBox = new SearchBox();
    collectionDisplay = new CollectionDisplay(collection);

    lay = new QVBoxLayout();
    lay->addWidget(searchBox);
    lay->addWidget(collectionDisplay);
    setLayout(lay);
}

void LeftSide::makeConnections()
{

    // Update the display when we are told to by another widget.
    connect(this, &LeftSide::updateDisplay,
            collectionDisplay, &CollectionDisplay::reset);

    connect(collectionDisplay, &CollectionDisplay::sendVideo,
            this, &LeftSide::setSelectedVideo);

    // Filter the video info displayed when the user enters a search query.
    connect(searchBox, &SearchBox::searchEntered,
            collectionDisplay, &CollectionDisplay::filter);

    // used for mainwindow
    connect(collectionDisplay, &CollectionDisplay::sendDoubleClickVid,
            this, &LeftSide::setDoubleClickVideo);

    // Bubble up the menu signals.
    connect(collectionDisplay, &CollectionDisplay::add_tag,
            this, &LeftSide::add_tag);
    connect(collectionDisplay, &CollectionDisplay::remove_tag,
            this, &LeftSide::remove_tag);
    connect(collectionDisplay, &CollectionDisplay::change_loc,
            this, &LeftSide::change_loc);
    connect(collectionDisplay, &CollectionDisplay::remove_video,
            this, &LeftSide::remove_video);
}


void LeftSide::getNext(Video* v)
{
    emit(playVideo(collectionDisplay->getNext(v)));
}


void LeftSide::getPrev(Video* v)
{
    emit(playVideo(collectionDisplay->getPrev(v)));
}

void LeftSide::setDoubleClickVideo(Video *v)
{
    if(v != NULL){
        setSelectedVideo(v);
        emit(playVideo(v));
    }

}

void LeftSide::setSelectedVideo(Video *vid)
{
    selected_vid = vid;
    emit(videoSelected((vid)));
}

Video *LeftSide::getSelectedVideo()
{
    return selected_vid;
}
