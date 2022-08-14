#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QDebug>

#include "leftside.h"
#include "rightside.h"
#include "playeroverlay.h"
#include "timer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_NextButton_clicked();

    void on_PreviousButton_clicked();

    void on_StopButton_clicked();

    void on_Volume_sliderMoved(int position);

    void on_Progress_sliderMoved(int position);

    void on_PositionChanged(quint64 position);

    void on_DurationChanged(quint64 position);

    void loadVideo(Video *v);
    void playPause();

    void openCollection();
    void saveCollection();

    void changeLocation(std::string location, Video *vid);
    void addTag(std::string tag, Video *vid);

    void launchBrowser();

    void showRemoveTagPrompt(Video *vid);

    void addToCollection(Video *vid);
    void removeFromCollection(Video *vid);

    void setCollectionButtons();


signals:
    void collectionLoaded();

    void goNext(Video *v);
    void goPrev(Video* v);

private:
    void setupWidgets();
    void connect_top_menu_widgets();
    void connect_left_side_widgets();
    void makeConnections();

    void generateOverlays();

    QString getLength(qint64 dur);

    Ui::MainWindow *ui;

    QMediaPlayer *player;
    QVideoWidget *videoframe;
    QSlider *slider;

    Video *current_video = NULL;
    Video *next_video = NULL;
    Video* previous_video = NULL;

    // Custom Widgets
    LeftSide *leftside;
    RightSide *rightside;
    LocationPrompt *locationPrompt;
    TagPrompt *tagPrompt;
    RemoveTagPrompt *removeTagPrompt;

    PlayerOverlay *locationOverlay;
    std::vector<PlayerOverlay *> tagOverlays;

    cxxtimer::Timer timer;
    bool playstate;
    MetaData collection;
};
#endif // MAINWINDOW_H
