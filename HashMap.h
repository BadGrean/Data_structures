#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>

template <typename Key, typename Value>
class HashMap {
private:
    struct Entry {
        Key key;
        Value value;
        bool occupied;
        bool deleted;
    };

    std::vector<Entry> entries;
    std::size_t capacity;
    std::size_t size;

    std::size_t hash(const Key& key) const;
    std::size_t findIndex(const Key& key) const;
    void checkResize();
    void rehash(std::size_t newCapacity);

public:
    HashMap(std::size_t initialCapacity = 8);
    ~HashMap() = default;

    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    Value get(const Key& key) const;
    void get_show(const Key& key);
    bool contains(const Key& key) const;
    std::size_t getSize() const;
};

#include "HashMap.cpp"

#endif // HASHMAP_H
