#pragma once


// Manager class to manage collection of
// pointers to some type
// Also provides static method to get a
// static shared manager
template<class T>
class Manager
{
public:
    // On destruction remove all items
    ~Manager()
    {
        for (auto const& it : m_items)
            delete it.second;
    }

    // Add item to a key
    template<class... Args>
    T* Add(const std::string& key, Args... args)
    {
        T* item = new T(args...);
        m_items[key] = item;
        return item;
    }

    template<class T1, class... Args>
    T1* Add(const std::string& key, Args... args)
    {
        T1* item = new T1(args...);
        m_items[key] = item;
        return item;
    }

    // Remove item for a key
    void Remove(const std::string& key)
    {
        auto iterator = m_items.find(key);
        delete iterator->second;
        m_items.erase(iterator);
    }

    // Get item from key
    T* Get(const std::string& key)
    {
        if (m_items.find(key) == m_items.end())
            return 0;
        return m_items[key];
    }

    // Get shared static manager object
    static Manager<T>& GetShared()
    {
        static Manager<T> manager;
        return manager;
    }

private:
    std::map<std::string, T*> m_items;
};
