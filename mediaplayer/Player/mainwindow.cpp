#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prompt.h"
#include <cmath>
#include "playeroverlay.h"

void MainWindow::setupWidgets()
{
    player = new QMediaPlayer(this);
    videoframe = new QVideoWidget(this);
    leftside = new LeftSide(&collection);
    rightside = new RightSide();
    locationPrompt = new LocationPrompt(this);
    tagPrompt = new TagPrompt(this);
    removeTagPrompt = new RemoveTagPrompt();

    ui->setupUi(this);

    ui->elapsed_label->setText("0:00:00");
    ui->duration_label->setText("0:00:00");

    ui->TopRightContainer->layout()->addWidget(rightside);
    ui->TopRightContainer->show();

    player->setVideoOutput(videoframe);
    ui->VideoContainer->layout()->addWidget(videoframe);

    ui->TopLeftContainer->layout()->addWidget(leftside);
    ui->TopLeftContainer->show();

    ui->MainWidget->show();

    locationOverlay = new PlayerOverlay(videoframe, "");
    locationOverlay->setGeometry(10, 10, locationOverlay->width(), locationOverlay->height());
    locationOverlay->hide();

    ui->add_location_button->setEnabled(false);
    ui->add_location_button->setShortcut(QKeySequence(tr("Ctrl+L")));
    ui->open_button->setShortcut(QKeySequence::Open);
    ui->add_tag_button->setEnabled(false);
    ui->add_tag_button->setShortcut(QKeySequence::AddTab);
    ui->remove_from_coll_button->setEnabled(false);
    ui->remove_from_coll_button->setShortcut(QKeySequence(tr("Ctrl+Shift+V")));
    ui->remove_tag_button->setEnabled(false);
    ui->remove_tag_button->setShortcut(QKeySequence(tr("Ctrl+Shift+T")));
    ui->add_to_coll_button->setEnabled(false);
    ui->add_to_coll_button->setShortcut(QKeySequence(tr("Ctrl+V")));
    ui->save_button->setShortcut(QKeySequence::Save);
    ui->help_button->setShortcut(QKeySequence(tr("Ctrl+H")));

    ui->save_button->setEnabled(false);
    ui->ControlBarContainer->setStyleSheet("background-color: rgb(134, 142, 150)");
}

void MainWindow::makeConnections()
{
    // Connect the video player to the controls.
    connect(player, &QMediaPlayer::positionChanged,
            this, &MainWindow::on_PositionChanged);
    connect(player, &QMediaPlayer::durationChanged,
            this, &MainWindow::on_DurationChanged);

    // Display the full duration of the video.
    connect(player, &QMediaPlayer::durationChanged,
            this, [&](qint64 dur) { ui->duration_label->setText(
            getLength(dur)); });

    // Display the time elapsed of the video.
    connect(player, &QMediaPlayer::positionChanged,
            this, [&]() {ui->elapsed_label->setText(
            getLength(timer.count<std::chrono::milliseconds>()));});

    // play-pause
    connect(ui->PlayButton, &QPushButton::clicked,
            this, &MainWindow::playPause);

    // load video from the right side to the player
    connect(rightside, &RightSide::jumpTo,
            this, [&](Video *vid) {
        // If the vid already exists in the collection, we want to use that instead.
        int index = collection.checkVideo(vid->path);
        if (index != -1)
            vid = collection[index];
        loadVideo(vid);});

    connect_top_menu_widgets();
    connect_left_side_widgets();

    connect(locationOverlay, &PlayerOverlay::clicked,
            locationPrompt, [&]() {
            locationPrompt->setVideo(current_video);
            locationPrompt->exec();});

    // previous and next vid aassignment
    connect(ui->NextButton, &QPushButton::clicked,
            this, [&](){
            if(current_video != NULL){
            emit(goNext(current_video));}});

    connect(ui->PreviousButton, &QPushButton::clicked,
            this, [&](){
            if(current_video != NULL){
            emit(goPrev(current_video));}});

    // next and prev buttons
    connect(this, &MainWindow::goNext,
            leftside, &LeftSide::getNext);


    connect(this, &MainWindow::goPrev,
            leftside, &LeftSide::getPrev);

    // full screen
    connect(ui->fullscreen, &QPushButton::clicked,
            this, [&](){this->hide(); videoframe->setFullScreen(true);});
    // esc key
    QShortcut *esc = new QShortcut(QKeySequence("Esc"), videoframe);
    connect(esc, &QShortcut::activated,
            this, [&](){this->show(); videoframe->setFullScreen(false);});

    // space to play pause
    QShortcut *space = new QShortcut(QKeySequence("Space"), ui->PlayButton);
    connect(space, &QShortcut::activated,
            this, [&](){playPause();});

    QShortcut *f12 = new QShortcut(QKeySequence("Ctrl+Shift+F"), this);
    connect(f12, &QShortcut::activated,
            this, [&](){this->hide(); videoframe->setFullScreen(true);});
}

void MainWindow::connect_left_side_widgets()
{
    // Connect the leftside so it can load videos into the player.
    connect(leftside, &LeftSide::playVideo, this, &MainWindow::loadVideo);
    connect(leftside, &LeftSide::playVideo, rightside, &RightSide::changeLocation);

    // Change location.
    connect(leftside, &LeftSide::change_loc, locationPrompt, [&](Video *vid) {
        locationPrompt->setVideo(vid);
        locationPrompt->exec();
    });

    // Add tag.
    connect(leftside, &LeftSide::add_tag, tagPrompt, [&](Video *vid) {
        tagPrompt->setVideo(vid);
        tagPrompt->exec();
    });

    // Remove tag.
    connect(leftside, &LeftSide::remove_tag, this, [&](Video *vid) { showRemoveTagPrompt(vid); });

    // Remove video from collection.
    connect(leftside, &LeftSide::remove_video, this,
            [&](Video *vid) { removeFromCollection(vid); });
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setupWidgets();
    makeConnections();
    playstate = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_top_menu_widgets()
{
    // Save button.
    connect(ui->save_button, &QPushButton::clicked, this, &MainWindow::saveCollection);

    // Open button.
    connect(ui->open_button, &QPushButton::clicked, this, &MainWindow::openCollection);
    // Tell leftside to re-render the collection.
    connect(this, &MainWindow::collectionLoaded, leftside, &LeftSide::updateDisplay);
    connect(this, &MainWindow::collectionLoaded, this, &MainWindow::setCollectionButtons);

    // Change Location button.
    connect(ui->add_location_button, &QPushButton::clicked, locationPrompt, [&]() {
        locationPrompt->setVideo(current_video);
        locationPrompt->exec();
    });

    // Tag buttons.
    connect(ui->add_tag_button, &QPushButton::clicked, tagPrompt, [&]() {
        tagPrompt->setVideo(current_video);
        tagPrompt->exec();
    });

    // Add to collection button.
    connect(ui->add_to_coll_button, &QPushButton::clicked, this,
            [&]() { addToCollection(current_video); });

    // Remove from collection.
    connect(ui->remove_from_coll_button, &QPushButton::clicked, this,
            [&]() { removeFromCollection(current_video); });

    // Help button.
    connect(ui->help_button, &QPushButton::clicked, this, &MainWindow::launchBrowser);

    connect(ui->remove_tag_button, &QPushButton::clicked, this,
            [&]() { showRemoveTagPrompt(current_video); });

    connect(tagPrompt, &TagPrompt::newLocation, this, &MainWindow::addTag);
    connect(locationPrompt, &LocationPrompt::newLocation, this, &MainWindow::changeLocation);
}

void MainWindow::removeFromCollection(Video *vid)
{
    if (collection.checkVideo(vid->path) == -1)
        return;

    collection.removeVideo(vid->path);

    // Display a different video.
    if (collection.size() > 0)
        loadVideo(collection.at(0));

    emit(collectionLoaded());
}

void MainWindow::addToCollection(Video *vid)
{

    if (collection.checkVideo(vid->path) != -1)
        return;

    collection.addVideo(*vid);

    // Re-load the video using the new pointer to it.
    loadVideo(collection.at(collection.size() - 1));
    emit(collectionLoaded());
}

void MainWindow::showRemoveTagPrompt(Video *vid)
{
    if (vid == NULL) {
        QMessageBox::information(this, "Failure", "No video selected.");
        return;
    }
    removeTagPrompt->setVideo(vid);
    removeTagPrompt->displayCurrentTags();
    removeTagPrompt->exec();

    emit(collectionLoaded());
    generateOverlays();
}

void MainWindow::launchBrowser()
{
    QDesktopServices::openUrl(QUrl("../Player/help.html"));
}

void MainWindow::changeLocation(std::string location, Video *vid)
{
    if (vid == NULL) {
        QMessageBox::information(this, "Failure", "You must load a video first.");
        return;
    }
    vid->location = location;

    QMessageBox::information(this, "Success", "Location added successfully.");

    emit(collectionLoaded());
    generateOverlays();
}
void MainWindow::addTag(std::string tag, Video *video)
{
    if (video == NULL) {
        QMessageBox::information(this, "Failure", "You must load a video first.");
        return;
    }
    video->tags.push_back(tag);
    QMessageBox::information(this, "Success", "Tag added successfully.");
    emit(collectionLoaded());
    generateOverlays();
}

void MainWindow::saveCollection()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Workspace"), "",
                                                    tr("Text file (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    } else {
        if (collection.saveFile(fileName.toStdString())) {
            QMessageBox::information(this, tr("Success"), tr("File saved successfully."));

        } else {
            QFile ffile(fileName);
            QMessageBox::information(this, tr("Unable to open file"), ffile.errorString());
        }
    }
}

void MainWindow::openCollection()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Workspace"), "",
                                                    tr("Text files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    } else {
        if (collection.readFile(fileName.toStdString())) {
            QMessageBox::information(this, tr("Success"), tr("File loaded successfully."));
            emit(collectionLoaded());

        } else {
            QFile file(fileName);
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        }
    }
}

void MainWindow::playPause()
{
    if (playstate) {
        player->play();
        timer.start();
        ui->PlayButton->setIcon(QPixmap(":/images/icons/icons8-pause-24.png"));
        ui->statusbar->showMessage("Playing");
    } else {
        player->pause();
        timer.stop();
        ui->PlayButton->setIcon(QPixmap(":/images/icons/icons8-play-24.png"));
        ui->statusbar->showMessage("Paused");
    }
    playstate = !playstate;
}

void MainWindow::on_NextButton_clicked() { }

void MainWindow::on_PreviousButton_clicked() { }

void MainWindow::on_StopButton_clicked()
{
    player->stop();
    timer.reset();
    // so resets label right away
    ui->elapsed_label->setText(getLength(timer.count<std::chrono::milliseconds>()));
    ui->statusbar->showMessage("Stopped");
}

QString MainWindow::getLength(qint64 dur)
{
    int duration = (int)std::round(dur / 1000.0); // convert to seconds
    int seconds = duration % 60;
    int full_mins = (duration - seconds) / 60;
    int mins = full_mins % 60;
    int hours = (full_mins - mins) / 60;
    QString str =
            QString::number(hours) + ":" + QString::number(mins) + ":" + QString::number(seconds);
    return str;
}

void MainWindow::generateOverlays()
{
    if (current_video == NULL)
        return;

    // The first overlay is the location, and goes in the top left corner.
    if (!current_video->location.empty()) {
        locationOverlay->reset(current_video->location);
        locationOverlay->show();
    } else {
        locationOverlay->hide();
    }

    // The other overlays are the tags.
    //     Remove the last overlays.
    for (PlayerOverlay *overlay : tagOverlays) {
        overlay->hide();
        delete overlay;
    }
    tagOverlays.clear();

    // Create new overlays for the new video.
    for (std::string tag : current_video->tags) {
        tagOverlays.push_back(new PlayerOverlay(videoframe, tag));
    }

    // Place the overlays.
    auto playerGeometry = videoframe->geometry();
    for (int i = 0; i < (int) tagOverlays.size(); i++) {
        int x;
        if (i == 0)
            x = playerGeometry.width() - tagOverlays[i]->width() - 10;
        else
            x = tagOverlays[i - 1]->x() - tagOverlays[i]->width() - 10;

        tagOverlays[i]->setGeometry(x, 10, tagOverlays[i]->width(), tagOverlays[i]->height());

        connect(tagOverlays[i], &PlayerOverlay::clicked, this,
                [&]() { showRemoveTagPrompt(current_video); });
        tagOverlays[i]->show();
    }
}

void MainWindow::loadVideo(Video *v)
{
    if(v != NULL){
        if(v->length.empty()){
            v->length = ui->duration_label->text().toStdString();
        }
        timer.reset();
        current_video = v;
        on_StopButton_clicked();

        player->setMedia(QUrl::fromLocalFile(v->path.c_str()));

        bool inCollection = collection.checkVideo(current_video->path) != -1;
        ui->remove_from_coll_button->setEnabled(inCollection);
        ui->add_to_coll_button->setDisabled(inCollection);

        ui->add_location_button->setEnabled(inCollection);
        ui->add_tag_button->setEnabled(inCollection);
        ui->remove_tag_button->setEnabled(inCollection);

        generateOverlays();

        playstate = true;
        playPause();
    }

}

void MainWindow::setCollectionButtons()
{
    bool collectionOpen = collection.size() > 0;
    //    ui->open_button->setEnabled(!collectionOpen);
    ui->save_button->setEnabled(collectionOpen);
}

void MainWindow::on_Volume_sliderMoved(int position)
{
    player->setVolume(position);
}

void MainWindow::on_Progress_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_DurationChanged(quint64 position)
{
    ui->Progress->setMaximum(position);
}

void MainWindow::on_PositionChanged(quint64 position)
{
    ui->Progress->setValue(position);
}
