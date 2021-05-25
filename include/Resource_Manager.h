#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

template <typename T>
class Resource_Manager
{
private:
    static inline std::map<std::string, T> resources{};

    static auto load_file(std::string filename) // Ladda in objektet och returnera det
    {
        T object;   
        if(!object.loadFromFile(filename))
        {
            throw std::logic_error("No asset at location: " + filename);
        }
        return resources.insert(std::pair<std::string, T>(filename, object)).first; // Lägg till nytt object och returnera iterator till det nya elementet
    }

public:
    static T& get_file(std::string filename)
    {
        auto lookup{resources.find(filename)};  // Kolla om sökt objekt (filnamn) finns 
        if(lookup == resources.end())
        {
            lookup = load_file(filename);   // Ladda in fil och få iterator till objektet
        }
        return lookup->second;  // Returnera objektet
    }
};

#endif