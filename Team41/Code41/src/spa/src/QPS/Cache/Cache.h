#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

using Mapping = unordered_map<string, unordered_set<string>>;

class Cache {
private:
    Mapping forwardMapping;
    Mapping backwardMapping;
    Mapping booleanMapping;

    vector<pair<string, string>> allMapping; // only populated when getAll* is being called

    unordered_set<string> getMapping(Mapping map, const string &key);

public:
    /**
     * Register key-value pair in forward mapping
     */
    void registerForwardMapping(const string &key, const string &value);

    /**
     * Register key-value pair in backward mapping
     */
    void registerBackwardMapping(const string &key, const string &value);

    /**
     * Register key-value pair in boolean mapping
     */
    void registerBooleanMapping(const string &key, const string &value);

    /**
     * Retrieves the forward mapping for certain key
     */
    unordered_set<string> getForwardMapping(const string &key);

    /**
     * Retrieves the backward mapping for certain key
     */
    unordered_set<string> getBackwardMapping(const string &key);

    /**
     * Checks if key value pair exist in boolean mapping
     */
    bool getBooleanMapping(const string &key, const string &value);

    /**
     * Retrieves all mapping
     */
    vector<pair<string, string>> getAllMapping();

    /**
     * Add a pair into the vector of mappings
     */
    void addAllMappingPair(const pair<string, string> &pair);
};

