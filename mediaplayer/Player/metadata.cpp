#include <dirent.h>
#include <cstring>
#include "metadata.h"

int MetaData::checkVideo(std::string path)
{
    for (int i = 0; i < (int)size(); i++) {
        if (at(i)->path == path) {
            return i;
        }
    }
    return -1;
}

bool MetaData::addVideo(const Video &video)
{
    Video *temp = new Video(video);
    push_back(temp);
    return true;
}

bool MetaData::removeVideo(std::string path)
{
    int i = checkVideo(path);

    if (i < 0)
        return false;

    this->erase(std::remove(this->begin(), this->end(), at(i)), this->end());

    return true;
}

bool MetaData::readFile(std::string f)
{
    for (Video *vid : *this) {
        delete vid;
    }

    clear();
    std::ifstream file(f);
    if (file.is_open()) {
        std::string str;
        while (getline(file, str)) {
            Video *v = new Video(str);
            push_back(v);
        }
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool MetaData::saveFile(std::string f)
{
    std::ofstream file(f);
    if (file.is_open()) {
        std::string str;
        for (int i = 0; i < (int)size(); i++) {
            file << at(i)->toString() << "\n";
        }
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool MetaData::readFolder(std::string f)
{
    clear();
    const std::vector<std::string> vid_formats = { "mp4", "wmv", "MOV", "avi" };
    const std::vector<std::string> pic_formats = { "png", "jpeg", "jpg" };
    std::vector<std::string> vid_names;
    std::vector<std::string> image_names;
    auto get_name = [&](std::string name) -> std::string {
        size_t lastindex = name.find_last_of(".");
        return name.substr(0, lastindex);
    };
    auto get_prefix = [&](std::string name) -> std::string {
        size_t lastindex = name.find_last_of(".");
        return name.substr(lastindex + 1);
    };

    /**
     * return 1 -> vid
     * return 0 -> image
     * return -1 -> neither
     **/
    auto check_file = [&](std::string name) -> int {
        for (int i = 0; i < (int)vid_formats.size(); i++) {
            if (vid_formats[i] == get_prefix(name)) {
                return 1;
            }
        }
        for (int i = 0; i < (int)pic_formats.size(); i++) {
            if (pic_formats[i] == get_prefix(name)) {
                return 0;
            }
        }
        return -1;
    };

    auto check_file_image = [&](std::string name1, std::string name2) -> bool {
        return get_name(name1) == get_name(name2);
    };

    DIR *dir;
    struct dirent *diread;

    if ((dir = opendir(f.c_str())) != NULL) {
        while ((diread = readdir(dir)) != NULL) {
            if (strcmp(diread->d_name, ".") != 0 && strcmp(diread->d_name, "..") != 0) {
                if (check_file(diread->d_name) == 1) {
                    vid_names.push_back(diread->d_name);
                } else if (check_file(diread->d_name) == 0) {
                    image_names.push_back(diread->d_name);
                }
            }
        }
        closedir(dir);
    } else {
        perror("opendir");
        return false;
    }
    MetaData m;
    for (int i = 0; i < (int)vid_names.size(); i++) {
        for (int j = 0; j < (int)image_names.size(); j++) {
            if (check_file_image(vid_names[i], image_names[j])) {
                Video *v = new Video();
                v->path = f + vid_names[i];
                v->thumbnail = f + image_names[j];
                push_back(v);
            }
        }
    }
    return true;
}

int MetaData::addTag(std::string path, std::string tag)
{
    int i = checkVideo(path);
    if (i >= 0) {
        if (at(i)->checkTag(tag) < 0) {
            at(i)->tags.push_back(tag);
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

int MetaData::replaceTag(std::string path, std::string old, std::string updated)
{
    int ip = checkVideo(path);
    if (ip >= 0) {
        int it = at(ip)->checkTag(old);
        if (it >= 0) {
            at(ip)->tags[it] = updated;
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

int MetaData::removeTag(std::string path, std::string tag)
{
    int i = checkVideo(path);
    if (i >= 0) {
        if (at(i)->removeTag(tag)) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

int MetaData::addLocation(std::string path, std::string location)
{
    int i = checkVideo(path);
    if (i >= 0) {
        at(i)->location = location;
        return 1;
    }
    return 0;
}

int MetaData::removeLocation(std::string path, std::string location)
{
    int i = checkVideo(path);
    if (i >= 0) {
        if (at(i)->location == location) {
            at(i)->location = Video::empty;
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

MetaData MetaData::getLocationVids(std::string location)
{
    MetaData m;
    for (int i = 0; i < (int)size(); i++) {
        if (at(i)->location == location) {
            m.push_back(at(i));
        }
    }
    return m;
}

MetaData MetaData::getTagVids(std::string tag)
{
    MetaData m;
    for (int i = 0; i < (int)size(); i++) {
        if (at(i)->checkTag(tag) >= 0) {
            m.push_back(at(i));
        }
    }
    return m;
}

MetaData MetaData::getNameVids(std::string name)
{
    MetaData m;
    for (int i = 0; i < (int)size(); i++) {
        if (getName(at(i)->path) == name) {
            m.push_back(at(i));
        }
    }
    return m;
}

MetaData MetaData::getLengthVids(std::string length)
{
    MetaData m;
    for (int i = 0; i < (int)size(); i++) {
        if (at(i)->length == length) {
            m.push_back(at(i));
        }
    }
    return m;
}

void MetaData::swapVid(std::string path1, std::string path2)
{
    int i1 = checkVideo(path1);
    int i2 = checkVideo(path2);
    std::swap(this[i1], this[i2]);
}

std::string MetaData::getName(const std::string &pathname)
{
    return std::string(
            std::find_if(pathname.rbegin(), pathname.rend(), MatchPathSeparator()).base(),
            pathname.end());
}

std::vector<std::string> MetaData::sortAsc(std::vector<std::string> a, bool len)
{
    std::vector<std::string> entries = a;
    std::sort(entries.begin(), entries.end(),
              [&](const std::string &a, const std::string &b) -> bool {
                  for (size_t c = 0; c < a.size() and c < b.size(); c++) {
                      if (!len) {
                          if (std::tolower(a[c]) != std::tolower(b[c])) {
                              return (std::tolower(a[c]) < std::tolower(b[c]));
                          } else {
                              return a[c] < b[c];
                          }
                      } else if (std::tolower(a[c]) != std::tolower(b[c])) {
                          return ((int)a[c] - 48) < ((int)b[c] - 48);
                      }
                  }
                  return a.size() < b.size();
              });
    return entries;
}

std::vector<std::string> MetaData::sortDes(std::vector<std::string> a, bool len)
{
    std::vector<std::string> entries = a;
    std::sort(entries.begin(), entries.end(),
              [&](const std::string &a, const std::string &b) -> bool {
                  for (size_t c = 0; c < a.size() and c < b.size(); c++) {
                      if (!len) {
                          if (std::tolower(a[c]) != std::tolower(b[c])) {
                              return (std::tolower(a[c]) > std::tolower(b[c]));
                          } else {
                              return a[c] > b[c];
                          }
                      } else if (std::tolower(a[c]) != std::tolower(b[c])) {
                          return ((int)a[c] - 48) > ((int)b[c] - 48);
                      }
                  }
                  return a.size() > b.size();
              });
    return entries;
}

std::vector<std::string> MetaData::getVect(Sort s)
{
    std::vector<std::string> a;

    for (int i = 0; i < (int)size(); i++) {
        // loc
        if (s == MetaData::Sort::location) {
            a.push_back(at(i)->location);
        }

        // length
        if (s == MetaData::Sort::length) {
            a.push_back(at(i)->length);
        }

        // name
        if (s == MetaData::Sort::name) {
            a.push_back(getName(at(i)->path));
        }

        // tag
        //        if(s == MetaData::Sort::tag){
        //            a.push_back(at(i).location);
        //        }
    }

    return a;
}

MetaData &MetaData::operator+=(const MetaData &copy)
{
    for (int i = 0; i < (int)copy.size(); i++) {
        push_back(copy.at(i));
    }
    return *this;
}

MetaData MetaData::sortAscend(Sort s)
{
    MetaData m;
    std::vector<std::string> strs = getVect(s);
    if (s == MetaData::Sort::length) {
        strs = sortAsc(strs, true);
    } else {
        strs = sortAsc(strs, false);
    }
    for (int i = 0; i < (int)strs.size(); i++) {
        // loc
        if (s == MetaData::Sort::location) {
            m += getLocationVids(strs.at(i));
            m.erase(std::unique(m.begin(), m.end()), m.end());
        }

        // length
        if (s == MetaData::Sort::length) {
            m += getLengthVids(strs.at(i));
        }

        // name
        if (s == MetaData::Sort::name) {
            m += getNameVids(strs.at(i));
        }
    }
    m.removeDuplicate();
    return m;
}

MetaData MetaData::sortDescend(Sort s)
{
    MetaData m;
    std::vector<std::string> strs = getVect(s);
    if (s == MetaData::Sort::length) {
        strs = sortDes(strs, true);
    } else {
        strs = sortDes(strs, false);
    }
    for (int i = 0; i < (int)strs.size(); i++) {
        // loc
        if (s == MetaData::Sort::location) {
            m += getLocationVids(strs.at(i));
        }

        // length
        if (s == MetaData::Sort::length) {
            m += getLengthVids(strs.at(i));
        }

        // name
        if (s == MetaData::Sort::name) {
            m += getNameVids(strs.at(i));
        }
    }
    m.removeDuplicate();
    return m;
}

void MetaData::removeDuplicate()
{
    int n = (int)size();
    std::vector<std::string> dup;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at(i) == at(j)) {
                dup.push_back(at(i)->path);
            }
        }
    }
    for (int i = 0; i < (int)dup.size(); i++) {
        removeVideo(dup[i]);
    }
}
