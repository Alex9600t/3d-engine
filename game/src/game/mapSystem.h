#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <tuple>
#include <memory>
#include <filesystem>


using json = nlohmann::json;

namespace Map {
    json& getWorldJson();
    json gen(int id, float scale, float riverScale, float biomeScale, int worldHeightScale, int seaHeight, int maxHeight, int minHeight, int seed, int mapX, int mapY, int chunkX, int chunkY);
    void loadMapFromFile(std::string);
    void loadMapToMEMFromFile(std::string, int x, int y);
    json getAllMap();

    void createNewWorld(std::string name, int seed, int x, int y);

    void NewFunction(std::string &name, int &seed);

    extern std::unordered_set<uint64_t> block_positions;
    
    uint64_t hash_func(int x, int y, int z);
    
    void rebuild_hash_map(const json& data);
    
    bool duplicate(const json& data, const int& target_id, int index);

    bool random(int a, int num);

    bool worldHasExist(std::string);

    struct binMapBlock {
        int id, x, y, z, type, tex;
    };
    struct binMapChunk {
        int x, y;
        std::vector<binMapBlock> blocks;
    };
    
    struct binMap {
        std::vector<binMapChunk> chunk;
    };

    extern binMap MEMMap;
}

