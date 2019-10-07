#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

template<typename Key, typename Value>
class Map 
{
	int capacity;
	vector<vector<pair<Key, Value>>> buckets;
	function<Key(int)> hash;

public:
	explicit Map(int capacity, function<Key(int)> hash): capacity{capacity}, hash{hash} {
		buckets.resize(capacity);
	}

	void insert(const Key& key, const Value& value) {
		int index = hash(key) % capacity;
		for(auto& p : buckets[index]) {
			if(p.first == key) {
				p.second = value;
				return;
			}
		}
		buckets[index].push_back({key, value});
	}

	void erase(const Key& key) {
		int index = hash(key) % capacity;
		for(auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
			if(it->first == key) {
				buckets[index].erase(it);
				return;
			}
		}
	}

	Value search(const Key& key) const {
		int index = hash(key) % capacity;
		for(const auto& p : buckets[index]) {
			if(p.first == key) {
				return p.second;
			}
		}
		return Value();
	}
};

int main()
{
	Map<int, int> m(100, [](int x) { return x; });
	for(int i = 0; i < 100; ++i) {
		m.insert(i, i);
	}
	for(int i = 0; i < 100; ++i) {
		m.insert(i, 2 * i);
	}
	for(int i = 0; i < 100; i += 2) {
		m.erase(i);
	}
	for(int i = 0; i < 100; ++i) {
		cout << m.search(i);
	}
	return 0;
}
