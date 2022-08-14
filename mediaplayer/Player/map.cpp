#include "map.h"
#include <QQuickItem>
#include <sstream>


void MapWidget::recenter(double latitude, double longitude){
    QVariant posx = QVariant(latitude);
    QVariant posy = QVariant(longitude);

    if(object != NULL){
        QMetaObject::invokeMethod(object, "recenter",
                                  Q_ARG(QVariant, posx),
                                  Q_ARG(QVariant, posy));
    }
}
MapWidget::MapWidget(QWidget* parent): QQuickWidget(parent)
{
    setSource(QUrl(QStringLiteral("../Player/map.qml")));
    setResizeMode(QQuickWidget::SizeRootObjectToView);

    item = rootObject();
    object = item->findChild<QObject*>("mapItem");

    recenter(53.7974185, -1.5437941);
    generateCords();
}

void MapWidget::generateCords()
{
    main_locations.push_back({"leeds", 53.7974185, -1.5437941});
    main_locations.push_back({"london", 51.509865, -0.118092});
    main_locations.push_back({"nottingham", 52.950001, -1.150000});
    main_locations.push_back({"cambridge", 52.205276, 0.119167});
    main_locations.push_back({"oxford", 51.752022, -1.257677});
    main_locations.push_back({"manchester", 53.483959, -2.244644});
    main_locations.push_back({"beijing", 39.916668, 116.383331});
    main_locations.push_back({"dubai", 25.088907, 55.148571});
    main_locations.push_back({"cardiff", 51.481583, -3.179090});
}

void MapWidget::changeLocation(Video* v)
{
    for(int i = 0; i < (int) main_locations.size(); i++){
        if(main_locations[i].name == v->location){
            recenter(main_locations[i].latitude,
                     main_locations[i].longitude);
        }
    }
}
