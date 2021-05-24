#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

template <typename T>
class Resource_Manager
{
private:
    static inline std::map<std::string, T> resources{};

    static T load_file(std::string filename)
    {
        T object;
        if(!object.loadFromFile(filename))
        {
            throw std::logic_error("No asset at location: " + filename);
        }
        return object;
    }

public:
    Resource_Manager() = delete;

    static T& get_file(std::string filename)
    {
        auto lookup{resources.find(filename)};
        if(lookup == resources.end())
        {
            T object{load_file(filename)};
            lookup = resources.insert(std::pair<std::string, T>(filename, object)).first;
        }
        return lookup->second;
    }
};

#endif