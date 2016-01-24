
template<class T>
inline void AddItems(std::vector<T>& list, const T& item)
{
    list.push_back(item);
}


template<class T>
inline void AddItems(std::vector<T>& list, const T& item1, const T& items...)
{
    list.push_back(item1);
    AddItems(list, items);
}


template<class T>
inline bool HasValue(const std::vector<T>& list, const T& value)
{
    return std::find(list.begin(), list.end(), value) != list.end();
}


template<class T>
inline void RemoveValue(std::vector<T>& list, const T& value)
{
    auto it = std::find(list.begin(), list.end(), value);
    if (it != list.end())
        list.erase(it);
}
