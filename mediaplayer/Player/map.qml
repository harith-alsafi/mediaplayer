import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    visible: true

    Plugin {
        id: mapPlugin
        name: "esri" // "mapboxgl", "esri", ...

    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 14
        objectName: "mainMap"

        MapCircle {
          id: marker
          objectName: "mapItem"
          center:  {latitude: 59.91
                     longitude: 10.75}
          radius: 50.0
          color: 'green'
          border.width: 3

                function recenter(lat,lng) {
                      map.clearMapItems();
                      marker.center.latitude = lat;
                      marker.center.longitude = lng;
                      map.addMapItem(marker);
                      map.center.latitude = lat;
                      map.center.longitude = lng;
                      map.update();
                }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
