#ifndef MAP_H
#define MAP_H

#include <QtQuickWidgets/QQuickWidget>
#include "video.h"

class MapWidget: public QQuickWidget
{
    Q_OBJECT
public:
    MapWidget(QWidget* parent = 0);
public slots:
    void changeLocation(Video* v);
private:
    struct Location
    {
        std::string name;
        double latitude;
        double longitude;
    };
    QQuickItem* item;
    QObject *object;
    void recenter(double latitude, double longitude);
    std::vector<Location> main_locations;
    void generateCords();
};

#endif // MAP_H
