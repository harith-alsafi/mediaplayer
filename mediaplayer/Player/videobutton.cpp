#include "videobutton.h"

VideoButton::VideoButton(QWidget *parent, Video *video, DisplayType d_type, MenuType m_type)
    : QPushButton(parent)
{

    // checks the icon conversion worked
    if (!initializeIcon(video->thumbnail, d_type)) {
        qDebug() << "Warning: icon conversion failed" << endl;
        delete (this);
        return;
    }

    // checks the url conversion worked
    if (!initializeUrl(video->path)) {
        qDebug() << "Warning: Url conversion failed" << endl;
        delete (this);
        return;
    }

    // Construct the correct menu for the button.
    setup_menu(m_type);
    setStyleSheet("background-color: rgb(134, 142, 150)");
    parent_video = video;
}

int VideoButton::initializeIcon(string thumbnail, DisplayType type)
{
    QPixmap image_pixmap;

    // no thumbnail path
    if (thumbnail.empty())
        return 0;

    // convert thumbnail path to QString equivalent
    QString image = QString::fromStdString(thumbnail);

    // converts the thumbnail path to an icon
    if (QFile(image).exists()) {
        QImageReader *imageReader = new QImageReader(image);
        // read the image
        QImage sprite = imageReader->read();
        // check the image could be read
        if (!sprite.isNull()) {
            // create pixmap from the thumbnail
            image_pixmap = QPixmap::fromImage(sprite);
        } else {
            qDebug() << "Warning: icon conversion failed" << endl;
            return 0;
        }
    } else {
        qDebug() << "Warning: icon conversion failed" << endl;
        return 0;
    }

    if (type == DisplayType::RECTANGLE) { // rectangle
        video_icon = new QIcon(image_pixmap);
        setIcon(*video_icon);
        setIconSize(QSize(200, 110));
        // set the background of the button to transparent
        setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    } else { // round
        // find the smallest dimension
        int smallest_size = qMin(image_pixmap.width(), image_pixmap.height());

        // fill a transparent square based on the smallest size
        QPixmap elliptical = QPixmap(smallest_size, smallest_size);
        elliptical.fill(Qt::transparent);

        // create a round clip area for the square
        QPainterPath clip_area;
        clip_area.addEllipse(elliptical.rect());

        // create a painter for adding the pixmap
        QPainter painter(&elliptical);
        painter.setClipPath(clip_area);

        // draw the pixmap in the area,
        painter.drawPixmap(0, 0, image_pixmap.width(), image_pixmap.height(), image_pixmap);

        // add the converted round pixmap to the button icon
        video_icon = new QIcon(elliptical);
        setIcon(*video_icon);
        setIconSize(QSize(130, 130));

        // set the background of the button to transparent
        setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    }

    return 1;
}

int VideoButton::initializeUrl(string path)
{
    if (path.empty())
        return 0;

    // convert string path to QUrl form
    video_url = new QUrl(QUrl::fromLocalFile(QString::fromStdString(path)));

    // QUrl member validity checks
    if (video_url->isValid())
        return 1;
    else
        return 0;
}

void VideoButton::setup_menu(MenuType type)
{
    menu = new QMenu("Video", this);

    // This is needed by all menu types.
    remove_act = new QAction("Remove video", this);
    menu->addAction(remove_act);
    connect(remove_act, &QAction::triggered, this, [&]() { emit(remove_video(parent_video)); });

    switch (type) {
    case MenuType::COLLECTION:
        add_tag_act = new QAction("Add tag", this);
        remove_tag_act = new QAction("Remove a tag", this);
        change_loc_act = new QAction("Change location", this);

        menu->addAction(add_tag_act);
        menu->addAction(remove_tag_act);
        menu->addAction(change_loc_act);

        connect(add_tag_act, &QAction::triggered, this, [&]() { emit(add_tag(parent_video)); });

        connect(remove_tag_act, &QAction::triggered, this,
                [&]() { emit(remove_tag(parent_video)); });

        connect(change_loc_act, &QAction::triggered, this,
                [&]() { emit(change_loc(parent_video)); });
        break;

    case MenuType::FOLDER:
        add_to_coll_act = new QAction("Add to collection", this);
        menu->addAction(add_to_coll_act);
        connect(add_to_coll_act, &QAction::triggered, this,
                [&]() { emit(add_to_coll(parent_video)); });
        break;
    }

    QString menuStyle("QMenu::item{"
                      "background-color: rgba(255, 255, 255, 255);"
                      "color: rgb(0, 0, 0);"
                      "}"
                      "QMenu::item:selected{"
                      "background-color: rgb(255, 255, 255, 200);"
                      "color: rgb(0, 0, 0);"
                      "}");
    menu->setStyleSheet(menuStyle);
    this->setMenu(menu);
    this->setToolTip("Double click/Right click");
}

void VideoButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        // Show the menu.
        menu->exec(QCursor::pos());
    }
    if (event->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonDblClick)
        emit play_video(parent_video);
    if (event->button() == Qt::LeftButton) {
        emit vid_selected(parent_video);
    }
}
