#pragma once

#include <iostream>
#include <vector>
#include <list>

template <typename Key, typename Value>
class HashTable
{
private:

	typedef std::pair<Key, Value> Bucket;
	typedef std::list<Bucket> BucketList;
	typedef std::vector<BucketList> BucketArray;

	BucketArray buckets;
	std::size_t numBuckets;

	std::size_t hash(const Key& key) const;

public:

	HashTable(std::size_t size);

	void insert(const Key& key, const Value& value);

	Value get(const Key& key) const;

	bool remove(const Key& key);
};