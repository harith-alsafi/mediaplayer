#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <vector>
#include <sstream>
#include <QIcon>
#include <QUrl>

class Video {
public:
    Video() { }
    Video(std::string line);
    Video(const Video& video);

    // string equivalent for storing in text
    std::string toString();

    // video tag functions
    int checkTag(std::string t);
    bool removeTag(std::string t);
    bool replaceTag(std::string t);
    std::string getTags();

    // operator overloads
    Video &operator=(const Video &a);
    friend bool operator==(const Video &a, const Video &b) { return (a.path == b.path); }

    // video variables
    static const std::string empty;
    std::string path;
    std::string thumbnail;
    std::string length;
    std::string location;
    std::vector<std::string> tags;
};

#endif // VIDEO_H
