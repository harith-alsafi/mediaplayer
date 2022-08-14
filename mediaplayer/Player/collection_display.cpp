#include <QDesktopServices>
#include "collection_display.h"

/**
 * @brief SearchResults
 */
CollectionDisplay::CollectionDisplay(MetaData *metadata) : QTableWidget()
{
    originalVideos = metadata;
    QStringList labels;
    labels << tr("Thumbnail") << tr("Name") << tr("Length") << tr("Location") << tr("Tag");
    setColumnCount(5);
    setColumnWidth(0, 245);
    setHorizontalHeaderLabels(labels);
    verticalHeader()->setSectionsMovable(true);
    setShowGrid(false);
    makeConnection();
    chosesort = true;
    setStyleSheet("background-color: rgb(134, 142, 150)");
}

Video* CollectionDisplay::getNext(Video *v)
{
    if(filteredVideos.size() > 2){
        int i = filteredVideos.checkVideo(v->path);
        if (i >= 0) {
            if(i == 0){

                return filteredVideos.at(i+1);
            }
            else if(i == (int) filteredVideos.size()-1){
                return filteredVideos.at(0);
            }
            else{
                return filteredVideos.at(i+1);
            }
        }
    }

}

Video* CollectionDisplay::getPrev(Video *v)
{
    if(filteredVideos.size() > 2){
        int i = filteredVideos.checkVideo(v->path);
        if (i >= 0) {
            if(i == 0){
                return filteredVideos.at(filteredVideos.size()-1);
            }
            else if(i == (int) filteredVideos.size()-1){
                return filteredVideos.at(i-1);
            }
            else{
                return filteredVideos.at(i-1);
            }
        }
    }

}

/**
 * @brief CollectionDisplay::filter
 * @param query
 * @param useLocation
 * @param useTags
 * This filters the original videos based on the search query, and stores pointers to the results in
 * filteredVideos.
 */
void CollectionDisplay::filter(const QString &query, bool useLocation, bool useTags)
{
    // makes sort reset once u start typing
    reset();
    update();

    std::string queryString = query.toStdString();
    filteredVideos.clear();

    for (Video *vid : *originalVideos) {
        if (vid->path.find(queryString) != std::string::npos) {
            filteredVideos.push_back(vid);
            continue;
        }

        if (useLocation) {
            if (vid->location.find(queryString) != std::string::npos) {
                filteredVideos.push_back(vid);
                continue;
            }
        }

        if (useTags) {
            for (std::string &tag : vid->tags) {
                if (tag.find(queryString) != std::string::npos) {
                    filteredVideos.push_back(vid);
                    break;
                }
            }
        }
    }

    update();
}

/**
 * @brief CollectionDisplay::addRow
 * @param r
 * @param vid
 *
 * Add a row to the table
 */
void CollectionDisplay::addRow(int r, Video &vid)
{
    setRowHeight(r, 135);
    // makes item uneditable so we can double click
    VideoButton *thumb = new VideoButton(this, &vid, VideoButton::DisplayType::ROUND,
                                         VideoButton::MenuType::COLLECTION);
    setCellWidget(r, 0, thumb);

    // Bubble the signals from the buttons up..
    connect(thumb, &VideoButton::play_video,
            this, &CollectionDisplay::sendDoubleClickVid);
    connect(thumb, &VideoButton::vid_selected,
            this, &CollectionDisplay::sendVideo);
    connect(thumb, &VideoButton::add_tag,
            this, &CollectionDisplay::add_tag);
    connect(thumb, &VideoButton::remove_tag,
            this, &CollectionDisplay::remove_tag);
    connect(thumb, &VideoButton::change_loc,
            this, &CollectionDisplay::change_loc);
    connect(thumb, &VideoButton::remove_video,
            this, &CollectionDisplay::remove_video);

    QTableWidgetItem *name =
            new QTableWidgetItem(QString::fromStdString(MetaData::getName(vid.path)));
    name->setFlags(name->flags()
                   ^ Qt::ItemIsEditable); // makes item uneditable so we can double click
    setItem(r, 1, name);

    QTableWidgetItem *length = new QTableWidgetItem(QString::fromStdString(vid.length));
    length->setFlags(length->flags() ^ Qt::ItemIsEditable);
    setItem(r, 2, length);

    QTableWidgetItem *location = new QTableWidgetItem(QString::fromStdString(vid.location));
    location->setFlags(location->flags() ^ Qt::ItemIsEditable);
    setItem(r, 3, location);

    QTableWidgetItem *tag = new QTableWidgetItem(QString::fromStdString(vid.getTags()));
    tag->setFlags(tag->flags() ^ Qt::ItemIsEditable);
    setItem(r, 4, tag);
}

/**
 * @brief CollectionDisplay::update
 * Draw filteredVideos to the table.
 */
void CollectionDisplay::update()
{
    setRowCount(filteredVideos.size());
    for (int i = 0; i < (int)filteredVideos.size(); i++) {
        addRow(i, *(filteredVideos.at(i)));
    }
}

/**
 * @brief CollectionDisplay::reset
 *
 * This resets filteredVideos to reference all the original videos.
 */
void CollectionDisplay::reset()
{
    filteredVideos.clear();
    for (int i = 0; i < (int)originalVideos->size(); i++) {
        filteredVideos.push_back(originalVideos->at(i));
    }
    update();
}

void CollectionDisplay::choseSort(MetaData::Sort s)
{
    if (chosesort) {
        filteredVideos = filteredVideos.sortAscend(s);
        update();
    } else {
        filteredVideos = filteredVideos.sortDescend(s);
        update();
    }
    chosesort = !chosesort;
}

void CollectionDisplay::setSort(int logicalIndex)
{
    QString type = horizontalHeaderItem(logicalIndex)->text();
    if (type == "Name") {
        choseSort(MetaData::Sort::name);
    } else if (type == "Length") {
        choseSort(MetaData::Sort::length);
    } else if (type == "Location") {
        choseSort(MetaData::Sort::location);
    } else {
        reset();
    }
}

void CollectionDisplay::setVideo()
{
    QModelIndexList selection = this->selectionModel()->selectedIndexes();
    // this fixes a bug where clicking on empty space
    // makes program crash
    if (selection.size() > 0) {
        int indx = selection.at(0).row();
        if (indx < this->rowCount()) {
            emit(sendVideo(filteredVideos.at(indx)));
        }
    }
}

void CollectionDisplay::setDoubleClick(const QModelIndex &index)
{
    // this fixes a bug where clicking on empty space
    // makes program crash
    if (index.row() < this->rowCount()) {
        row = index.row();
        emit(sendDoubleClickVid(filteredVideos.at(row)));
    }
}

void CollectionDisplay::makeConnection()
{
    // used to select the header for sort
    auto header = horizontalHeader();
    connect(header, &QHeaderView::sectionClicked, this, &CollectionDisplay::setSort);

    // used to make any item selected to emit a sendVideo()
    connect(this, &CollectionDisplay::itemSelectionChanged,
            this, &CollectionDisplay::setVideo);

    // used to make a double selection send a sendVideo()
    connect(this, &CollectionDisplay::doubleClicked,
            this, &CollectionDisplay::setDoubleClick);

}
