#include <iostream>
#include <list>
using namespace std;

class HashTable {
private:
    int hashGroupsNumber;
    list<pair<string, string> > *hashTable;

    int hash(string key) {
        unsigned long h = 0;
        for (char c: key) {
            h = h * 31 + c;
        }
        return h % hashGroupsNumber;
    }

public:
    HashTable(int hashGroups = 20): hashGroupsNumber(hashGroups),
                                    hashTable(new list<pair<string, string> >[hashGroupsNumber]) {
    }

    ~HashTable() {
        delete[] hashTable;
    }

    void insert(string key, string value) {
        int index = hash(key);
        cout << "Inserting " << key << " at " << index << endl;
        hashTable[index].push_back({key, value});
    }

    pair<string, string> lookup(string key) {
        int index = hash(key);
        auto &list = hashTable[index];
        for (auto it: list) {
            if (it.first == key) {
                return it;
            }
        }
        cout << "Not found" << endl;
        return {"Empty", "Empty"};
    }

    void print() {
        for (int i = 0; i < hashGroupsNumber; i++) {
            cout << "List " << i << endl;
            for (auto list: hashTable[i]) {
                cout << "Key: " << list.first << " - Value: " << list.second << endl;
            }
        }
    }
};
