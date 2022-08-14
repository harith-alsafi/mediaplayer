#ifndef METADATA_H
#define METADATA_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "video.h"

class MetaData : public std::vector<Video *> {
public:
    enum Sort {
        location,
        name,
        length,
        // tag
    };

    MetaData() { }
    bool removeVideo(std::string path);
    bool addVideo(const Video &video);

    bool contains(Video *vid);

    /**
     * @return
     * 1: everything is good
     * 0: path doesnt exits
     * -1: tag already exits
     */
    int addTag(std::string path, std::string tag);
    /**
     * @return
     * 1: all is good
     * 0: no path
     * -1: old tag doesnt exist;
     */
    int replaceTag(std::string path, std::string old, std::string updated);
    /**
     * @return
     * 1: all is good
     * 0: no path
     * -1: no tag
     */
    int removeTag(std::string path, std::string tag);

    /**
     * @return
     * 0: no path
     * 1: path exists
     */
    int addLocation(std::string path, std::string location);
    /**
     * @return
     * 0: path doesnt exist
     * -1: location doesnt exist
     * 1: all is good
     */
    int removeLocation(std::string path, std::string location);

    bool readFile(std::string f);
    bool saveFile(std::string f);
    bool readFolder(std::string f);

    // all vids with certain location
    MetaData getLocationVids(std::string location);
    // all vids with certain tag
    MetaData getTagVids(std::string tag);
    // all vids with same name
    MetaData getNameVids(std::string name);
    // all vids with certain length
    MetaData getLengthVids(std::string length);

    void swapVid(std::string path1, std::string path2);

    MetaData sortAscend(Sort s);
    MetaData sortDescend(Sort s);

    static std::string getName(std::string const &pathname);

    MetaData &operator+=(const MetaData &copy);

    int checkVideo(std::string path);

protected:
    struct MatchPathSeparator {
        bool operator()(char ch) const { return (ch == '\\' || ch == '/'); }
    };
    //

    std::string toSmall(std::string);
    std::vector<std::string> getVect(Sort s);
    std::vector<std::string> sortAsc(std::vector<std::string> a, bool len);
    std::vector<std::string> sortDes(std::vector<std::string> a, bool len);
    void removeDuplicate();
};

#endif // METADATA_H
