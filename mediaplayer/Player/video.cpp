#include "video.h"

const std::string Video::empty = "N/A";

Video::Video(std::string line)
{
    std::vector<std::string> v;
    std::stringstream ss(line);
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }
    path = v[0];
    thumbnail = v[1];
    length = v[2];
    location = v[3];
    for (int i = 4; i < (int)v.size(); i++) {
        tags.push_back(v[i]);
    }
}

Video::Video(const Video &video)
{
    this->path = video.path;
    this->thumbnail = video.thumbnail;
    this->length = video.length;
    this->location = video.location;
    for (auto &string : video.tags) {
        this->tags.push_back(string);
    }
}

int Video::checkTag(std::string t)
{
    for (int i = 0; i < (int)tags.size(); i++) {
        if (tags[i] == t) {
            return i;
        }
    }
    return -1;
}

bool Video::removeTag(std::string t)
{
    int i = checkTag(t);
    if (i >= 0) {
        if (t.size() > 1) {
            tags.erase(tags.begin() + i);
        } else if (tags.size() == 1) {
            tags[0] = empty;
        }
        return true;
    }
    return false;
}

std::string Video::toString()
{
    std::string t = "";
    for (int i = 0; i < (int)tags.size(); i++) {
        t = t + "," + tags[i];
    }
    std::string all = path + "," + thumbnail + "," + length + "," + location + t;
    return all;
}

Video &Video::operator=(const Video &a)
{
    path = a.path;
    length = a.length;
    location = a.location;
    tags.clear();
    for (int i = 0; i < (int)a.tags.size(); i++) {
        tags.push_back(a.tags[i]);
    }
    return *this;
}

bool Video::replaceTag(std::string t)
{
    int i = checkTag(t);
    if (i >= 0) {
        tags[i] = t;
        return true;
    }
    return false;
}

std::string Video::getTags()
{
    std::string str;
    for (int i = 0; i < (int)tags.size(); i++) {
        if (i != (int)tags.size() - 1) {
            str += tags[i] + ",";
        } else {
            str += tags[i];
        }
    }
    return str;
}
