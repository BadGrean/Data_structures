#ifndef HASHMAP_CPP
#define HASHMAP_CPP

#include "HashMap.h"
#include <iostream>

template<typename Key, typename Value>
std::size_t HashMap<Key, Value>::hash(const Key& key) const {
    // Preprocess the key by removing whitespace characters
    std::string processedKey;
    for (const auto& c : key) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            processedKey += c;
        }
    }
    
    std::hash<std::string> hasher;
    return hasher(processedKey) % capacity;
}

template <typename Key, typename Value>
std::size_t HashMap<Key, Value>::findIndex(const Key& key) const {
    long long int index = hash(key);

    while (entries[index].occupied) {
        if (!entries[index].deleted && entries[index].key == key) {
            return index;
        }

        index = (index + 1) % capacity;
    }

    return index;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::checkResize() {
    if (size >= capacity / 2) {
        std::size_t newCapacity = capacity * 2;
        rehash(newCapacity);
    }
}

template <typename Key, typename Value>
void HashMap<Key, Value>::rehash(std::size_t newCapacity) {
    std::vector<Entry> newEntries(newCapacity, { Key(), Value(), false, false });
    capacity = newCapacity;
    for (const auto& entry : entries) {
        if (entry.occupied && !entry.deleted) {
            std::size_t newIndex = hash(entry.key);

            while (newEntries[newIndex].occupied) {
                newIndex = (newIndex + 1) % newCapacity;
            }

            newEntries[newIndex] = entry;
        }
    }

    entries = std::move(newEntries);
    //capacity = newCapacity;//here possible mistake idk if i rewrite new indexes for old capacity after calculating with new capacity they can be different
}

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(std::size_t initialCapacity)
    : capacity(initialCapacity), size(0) {
    entries.resize(capacity, { Key(), Value(), false, false });
}

template <typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& key, const Value& value) {
    checkResize();
    std::size_t index = findIndex(key);

    if (entries[index].occupied && !entries[index].deleted) {
        entries[index].value = value;
    }
    else {
        entries[index] = { key, value, true, false };
        size++;
    }
}

template <typename Key, typename Value>
void HashMap<Key, Value>::remove(const Key& key) {
    std::size_t index = findIndex(key);

    if (entries[index].occupied && !entries[index].deleted) {
        entries[index].deleted = true;
        size--;
    }
}

template <typename Key, typename Value>
Value HashMap<Key, Value>::get(const Key& key) const {
    std::size_t index = findIndex(key);

    if (entries[index].occupied && !entries[index].deleted) {
        return entries[index].value;
    }

    return Value();
}

template<typename Key, typename Value>
void HashMap<Key, Value>::get_show(const Key& key)
{
    Value value = get(key);
    std::cout << value << std::endl;
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::contains(const Key& key) const {
    std::size_t index = findIndex(key);
    return entries[index].occupied && !entries[index].deleted;
}

template <typename Key, typename Value>
std::size_t HashMap<Key, Value>::getSize() const {
    return size;
}

#endif // HASHMAP_INL