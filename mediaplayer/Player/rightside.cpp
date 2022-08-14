#include "rightside.h"

RightSide::RightSide(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    widgetLayout();
    makeConnections();
    setStyleSheet("background-color: rgb(134, 142, 150)");
}

void RightSide::makeConnections()
{
    connect(open_files, &QPushButton::pressed, this, &RightSide::openFrom);
}

void RightSide::createWidgets()
{
    mapwidget = new MapWidget(this);
    // collection of videos for the right side
    right_layout = new QVBoxLayout();
    // scroll area widgets and layouts
    video_scroll = new QScrollArea();
    video_widget = new QWidget();
    scroll_layout = new QVBoxLayout();
    // to open videos
    open_files = new QPushButton("Open Videos");

}

void RightSide::changeLocation(Video *v)
{
    mapwidget->changeLocation(v);
}

void RightSide::widgetLayout()
{
    right_layout->addWidget(mapwidget);
    mapwidget->setGeometry(10, 10, 200, 150);

    // scroll area widgets and layouts
    right_layout->addWidget(video_scroll);
    video_scroll->setGeometry(10, 170, 200, 500);
    video_scroll->setWidget(video_widget);
    video_widget->setGeometry(10, 170, 200, 500);
    video_scroll->setWidgetResizable(true);
    video_widget->setMaximumWidth(210);
    video_widget->setLayout(scroll_layout);
    // to open videos
    right_layout->addWidget(open_files);
    setLayout(right_layout);
}

int RightSide::addVideos()
{
    // add all the buttons in the collection
    for (Video *videos : opened_videos) {
        VideoButton *temp = new VideoButton(this, videos, VideoButton::DisplayType::RECTANGLE,
                                            VideoButton::MenuType::FOLDER);
        if (temp != NULL)
            video_buttons.push_back(temp);
    }

    // add all the buttons to the layout
    for (VideoButton *v : video_buttons) {
        scroll_layout->addWidget(v);
        connect(v, &VideoButton::remove_video, this, &RightSide::removeVideo);
        connect(v, &VideoButton::play_video, this, &RightSide::jumpTo);
    }

    // failed to load any videos
    if (video_buttons.empty())
        return 0;
    else
        return 1;
}

void RightSide::openFrom()
{
    QStringList all_files = QFileDialog::getOpenFileNames(this, tr("Select one or more videos"),
                                                          "/home", "Videos (*.MOV *.wmv *.mp4)");

    for (QString &files : all_files) {
        if (files.contains("."))
#if defined(_WIN32)
            if (files.contains(".wmv")) { // windows
#else
            if (files.contains(".mp4") || files.contains("MOV")) { // mac/linux
#endif
                QString thumbnail = files.left(files.length() - 4) + ".png";
                if (QFile(thumbnail).exists()) {
                    Video temp;
                    temp.path = files.toStdString();
                    temp.thumbnail = thumbnail.toStdString();
                    opened_videos.addVideo(temp);
                } else {
                    qDebug() << "Warning: couldn't find thumbnail, skipping video" << endl;
                }
            }
    }
    addVideos();
}

void RightSide::removeVideo(Video *parent_video)
{
    if (opened_videos.size() > 0) {
        int i = opened_videos.checkVideo(parent_video->path);
        scroll_layout->removeWidget(video_buttons.at(i));
        video_buttons.at(i)->hide();

        opened_videos.erase(
                std::remove(opened_videos.begin(), opened_videos.end(), opened_videos.at(i)),
                opened_videos.end());

        video_buttons.erase(
                std::remove(video_buttons.begin(), video_buttons.end(), video_buttons.at(i)),
                video_buttons.end());
    }
}
