#define STB_PERLIN_IMPLEMENTATION
#include "mapSystem.h"
#include "../../../stb/stb_perlin.h"
#include "render.h"
// using json = nlohmann::json;

json worldJson;
std::unordered_set<uint64_t> Map::block_positions;
Map::binMap Map::MEMMap;

uint64_t Map::hash_func(int x, int y, int z) {
    int64_t sx = static_cast<int64_t>(x);
    int64_t sy = static_cast<int64_t>(y);
    int64_t sz = static_cast<int64_t>(z);

    uint64_t ux = static_cast<uint64_t>(sx + (1LL << 20));
    uint64_t uy = static_cast<uint64_t>(sy + (1LL << 20));
    uint64_t uz = static_cast<uint64_t>(sz + (1LL << 20));

    return (ux << 42) | (uy << 21) | uz;
}

void Map::rebuild_hash_map(const json& data) {
    Map::block_positions.clear();
    for (const auto& [id, block] : data["id"].items()) {
        Map::block_positions.insert(hash_func(block["x"].get<int>(), block["y"].get<int>(), block["z"].get<int>()));
    }
}

bool Map::duplicate(const json& data, const int& target_id, int index) {
    const auto& target_block = data["id"].find(std::to_string(target_id));
    if (target_block == data["id"].end()) return false;

    int x = target_block->at("x").get<int>();
    int y = target_block->at("y").get<int>();
    int z = target_block->at("z").get<int>();

    static const int dx[] = { 0, 0, 0, 0, -1, 1 };
    static const int dy[] = { 1, -1, 0, 0, 0, 0 };
    static const int dz[] = { 0, 0, 1, -1, 0, 0 };

    int nx = x + dx[index];
    int ny = y + dy[index];
    int nz = z + dz[index];

    return Map::block_positions.find(hash_func(nx, ny, nz)) == Map::block_positions.end();
}

json& Map::getWorldJson() {
    return worldJson;
};

json Map::gen(int blockID, float scale, float riverScale, float biomeScale, int worldHeightScale, int seaHeight, int maxHeight, int minHeight, int seed, int mapX, int mapY, int chunkX, int chunkY) {
    json tempMap;
    json biomeMap;

    int id = blockID;

    for (int x = -mapX; x < mapX; x++) {
        for (int y = -mapY; y < mapY; y++) {
            float biomeNoise = stb_perlin_noise3_seed(x * biomeScale, y * biomeScale, 0, 4, 0, 0, seed);
            std::string biomeType = "plains";
            if (biomeNoise < -0.3f) biomeType = "desert";
            else if (biomeNoise > 0.5f) biomeType = "mountains";
            else if (biomeNoise > 0.2f) biomeType = "forest";

            biomeMap[std::to_string(x)][std::to_string(y)] = biomeType;
        }
    }


    for (int x = -mapX + 1; x < mapX - 1; x++) {
        for (int y = -mapY + 1; y < mapY - 1; y++) {
            if (stb_perlin_noise3_seed(x * riverScale, y * riverScale, 0, 4, 0, 0, seed) > 0.4f) continue;

            std::string biome = biomeMap[std::to_string(x)][std::to_string(y)];
            if (biome == "plains" || biome == "forest") continue;

            if (biomeMap[std::to_string(x - 1)][std::to_string(y)] != "river") biomeMap[std::to_string(x - 1)][std::to_string(y)] = "river";
            if (biomeMap[std::to_string(x + 1)][std::to_string(y)] != "river") biomeMap[std::to_string(x + 1)][std::to_string(y)] = "river";
            if (biomeMap[std::to_string(x)][std::to_string(y - 1)] != "river") biomeMap[std::to_string(x)][std::to_string(y - 1)] = "river";
            if (biomeMap[std::to_string(x)][std::to_string(y + 1)] != "river") biomeMap[std::to_string(x)][std::to_string(y + 1)] = "river";
        }
    }


    for (int x = (8 * chunkX - 4); x < (8 * chunkX + 4); x++) {
        for (int y = (8 * chunkY - 4); y < (8 * chunkY + 4); y++) {
            std::string biome = biomeMap[std::to_string(x)][std::to_string(y)];

            if (biome == "plains") {
                float noiseValue = stb_perlin_noise3_seed(x * scale, y * scale, 0, 4, 0, 0, seed);

                float value = (noiseValue + 1) * 0.5f * (maxHeight - minHeight) + minHeight;

                tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
                tempMap["id"][std::to_string(id).c_str()]["y"] = int(value + worldHeightScale);
                tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
                tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
                tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
                tempMap["id"][std::to_string(id).c_str()]["name"] = "block.grass_block";
                id++;

                for (int currentHeight = value - 1; currentHeight > seaHeight - 5; currentHeight--) {
                    tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
                    tempMap["id"][std::to_string(id).c_str()]["y"] = int(currentHeight + worldHeightScale);
                    tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
                    tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
                    tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
                    tempMap["id"][std::to_string(id).c_str()]["name"] = (currentHeight > value - 4) ? "block.dirt" : "block.stone";
                    id++;
                }

            }
            else if (biome == "forest") {
                float noiseValue = stb_perlin_noise3_seed(x * scale, y * scale, 0, 4, 0, 0, seed);

                float value = (noiseValue + 1) * 0.5f * (maxHeight - minHeight) + minHeight;

                for (int currentHeight = value; currentHeight > seaHeight - 5; currentHeight--) {
                    tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
                    tempMap["id"][std::to_string(id).c_str()]["y"] = int(currentHeight + worldHeightScale);
                    tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
                    tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
                    tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
                    tempMap["id"][std::to_string(id).c_str()]["name"] = "block.s";
                    id++;
                }
            }
            else if (biome == "desert") {
                float noiseValue = stb_perlin_noise3_seed(x * scale, y * scale, 0, 4, 0, 0, seed);

                float value = (noiseValue + 1) * 0.5f * (maxHeight - minHeight) + minHeight;

                for (int currentHeight = value; currentHeight > seaHeight - 5; currentHeight--) {
                    tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
                    tempMap["id"][std::to_string(id).c_str()]["y"] = int(currentHeight + worldHeightScale);
                    tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
                    tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
                    tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
                    tempMap["id"][std::to_string(id).c_str()]["name"] = "block.sand";
                    id++;
                }

            }
            else if (biome == "mountains") {

                float noiseValue = stb_perlin_noise3_seed(x * scale, y * scale, 0, 4, 0, 0, seed);

                float value = (noiseValue + 1) * 1.5f * (maxHeight - minHeight) + minHeight;

                for (int currentHeight = value; currentHeight > seaHeight - 5; currentHeight--) {
                    tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
                    tempMap["id"][std::to_string(id).c_str()]["y"] = int(currentHeight + worldHeightScale);
                    tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
                    tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
                    tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
                    tempMap["id"][std::to_string(id).c_str()]["name"] = "block.stone";
                    id++;
                }

            }
            else if (biome == "river") {
                tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
                tempMap["id"][std::to_string(id).c_str()]["y"] = int(seaHeight + worldHeightScale);
                tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
                tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
                tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
                tempMap["id"][std::to_string(id).c_str()]["name"] = "block.water";
                id++;
            }
        }
    }




    // for (float x = -160; x < 160; x += 1.0f) {
    //     for (float y = -160; y < 160; y += 1.0f) {
    //         float biomeNoise = stb_perlin_noise3_seed(x * biomeScale, y * biomeScale, 0, 4, 0, 0, seed);

    //         std::string biomeType;
    //         float height = 5;

    //         if (biomeNoise < -0.3f) {
    //             biomeType = "desert";
    //             height += stb_perlin_noise3_seed(x * 0.01f, y * 0.01f, 0, 4, 0, 0, seed) * 2;
    //         } else if (biomeNoise > 0.5f) {
    //             biomeType = "mountains";
    //             height += stb_perlin_noise3_seed(x * 0.003f, y * 0.003f, 0, 4, 0, 0, seed) * 15;
    //         } else {
    //             biomeType = "plains";
    //             height += stb_perlin_noise3_seed(x * 0.008f, y * 0.008f, 0, 4, 0, 0, seed) * 5;
    //         }

    //         height = std::max(minHeight, std::min(maxHeight, (int)height));

    //         tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
    //         tempMap["id"][std::to_string(id).c_str()]["y"] = int(height);
    //         tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
    //         tempMap["id"][std::to_string(id).c_str()]["physic"] = false;

    //         if (biomeType == "desert") {
    //             tempMap["id"][std::to_string(id).c_str()]["name"] = "block.sand";
    //         } else if (biomeType == "mountains") {
    //             tempMap["id"][std::to_string(id).c_str()]["name"] = "block.stone";
    //         } else {
    //             tempMap["id"][std::to_string(id).c_str()]["name"] = "block.grass_block";
    //         }
    //         id++;


    //         float largeScale = 0.002f;
    // float smallScale = 0.02f;
    // float baseTerrain = stb_perlin_noise3_seed(x * largeScale, y * largeScale, 0, 4, 0, 0, seed);
    // float detail = stb_perlin_noise3_seed(x * smallScale, y * smallScale, 0, 4, 0, 0, seed) * 0.2f;
    // float noiseValue = (baseTerrain + detail + 1) * 0.5f * (maxHeight - minHeight) + minHeight;

    //         float value = (noiseValue + 1) * 0.5f * (maxHeight - minHeight) + minHeight;

    //         float riverNoise = stb_perlin_noise3_seed(x * riverScale, y * riverScale, 0, 4, 0, 0, seed);
    //         int sea = 0;
    //         if (riverNoise < -0.2f) {
    //             value = seaHeight;
    //             sea = 1;
    //         }

            // if (Map::random(30, std::rand() % int(value))) {
            //     const int R2 = 3;
            //     for (int tree1 = 1; tree1 < 6; tree1++){
            //         tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
            //         tempMap["id"][std::to_string(id).c_str()]["y"] = int(value + tree1);
            //         tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
            //         tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
            //         tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
            //         tempMap["id"][std::to_string(id).c_str()]["name"] = "block.log";
            //         id++;
            //     }
            //     for (int tree2y = 0; tree2y < 3; tree2y++){
            //         for (int tree2x = -R2; tree2x <= R2; tree2x++) {
            //             for (int tree2z = -R2; tree2z <= R2; tree2z++) {
            //                 if (tree2x * tree2x + tree2z * tree2z <= R2 * R2) {
            //                     if (tree2x == 0 + 5 && tree2z == 0) {} else {
            //                     tempMap["id"][std::to_string(id).c_str()]["x"] = int(x + tree2x);
            //                     tempMap["id"][std::to_string(id).c_str()]["y"] = int(value + tree2y + 6);
            //                     tempMap["id"][std::to_string(id).c_str()]["z"] = int(y + tree2z);
            //                     tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
            //                     tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
            //                     tempMap["id"][std::to_string(id).c_str()]["name"] = "block.leaves";
            //                     id++;
            //                     }
            //                 }
            //             }
            //         }
            //     }
            // }

            // tempMap["id"][std::to_string(id).c_str()]["x"] = int(x);
            // tempMap["id"][std::to_string(id).c_str()]["y"] = int(value);
            // tempMap["id"][std::to_string(id).c_str()]["z"] = int(y);
            // tempMap["id"][std::to_string(id).c_str()]["physic"] = false;
            // tempMap["id"][std::to_string(id).c_str()]["type"] = "box";
            // tempMap["id"][std::to_string(id).c_str()]["name"] = (sea == 1) ? "block.water" : "block.grass_block";
            // id++;
        // }
    // }
//     for (float x = 0; x < 128; x += 1.0f) {
//         for (float y = 0; y < 128; y += 1.0f) {
//             // Генерация биомов
//             float biomeNoise = stb_perlin_noise3_seed(x * biomeScale, y * biomeScale, 0, 4, 0, 0, seed);
//             std::string biomeType = biomeNoise < -0.3f ? "desert" : (biomeNoise > 0.5f ? "mountains" : "plains");

//             // Генерация высоты (Simplex шум можно заменить)
//             float height = 10 + stb_perlin_noise3_seed(x * scale, y * scale, 0, 4, 0, 0, seed) * 8;

//             // Генерация рек (где шум ≈ 0)
//             float riverNoise = stb_perlin_noise3_seed(x * riverScale, y * riverScale, 0, 4, 0, 0, seed);
//             if (std::abs(riverNoise) < 0.05f) { // Если близко к 0 → река
//                 biomeType = "river";
//             }

//             height = std::max(minHeight, std::min(maxHeight, (int)height));

//             // Записываем блок
//             tempMap["id"][std::to_string(id).c_str()] = {
//                 {"x", int(x)}, {"y", int(height)}, {"z", int(y)}, {"physic", false},
//                 {"name", biomeType == "desert" ? "block.sand"
//                         : (biomeType == "mountains" ? "block.stone"
//                         : (biomeType == "river" ? "block.water"
//                         : "block.grass_block"))}
//             };

// ///..

//             id++;
        // }}
    return tempMap;
}

void Map::createNewWorld(std::string name, int seed, int x, int y) {
    bool isWorldExists = false;

    for (int id = 0; id < Map::getAllMap().size(); id++) {
        if (name == Map::getAllMap()[id]["name"].get<std::string>()) {
            isWorldExists = true;
            break;
        }
    }

    if (!isWorldExists) {

        std::ifstream confJsonFile("./map/config.json");
        json confJson;
        confJsonFile >> confJson;
        confJsonFile.close();
        confJson[confJson.size()]["name"] = name;
        confJson[confJson.size() - 1]["seed"] = seed;
        std::ofstream confJsonFileWrite("./map/config.json");
        if (!confJsonFileWrite.is_open()) {
            std::cerr << "Не удалось открыть файл!" << std::endl;
        }
        confJsonFileWrite << confJson.dump(4);
        confJsonFileWrite.close();

    std::filesystem::path directory = "./map/world/" + name + "/chunk";
    if (!std::filesystem::exists(std::filesystem::path("./map/world/" + name + "/chunk"))) {
        if (std::filesystem::create_directories(std::filesystem::path("./map/world/" + name + "/chunk"))) {
            std::cout << "Папки созданы: " << std::filesystem::path("./map/world/" + name + "/chunk") << std::endl;
        }
        else {
            std::cerr << "Не удалось создать папки!" << std::endl;
        }
    }

    std::ofstream chunkFile("./map/world/" + name + "/chunk/chunk_00_00.json");
    if (!chunkFile.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
    }

    chunkFile << Map::gen(0, 0.1f, 0.01f, 0.01f, 50, 10, 25, 0, seed, 40, 40, x, y).dump(4);
    chunkFile.close();
    }
}

void Map::loadMapFromFile(std::string map) {
    std::ifstream worldFile("./map/world/" + map + "/chunk/chunk_00_00.json");
    // worldFile >> Map::world;

    worldFile >> worldJson;
    // std::cout << worldJson["id"] << std::endl;
    std::ifstream configFile("./map/config.json");
    json tmpConfigFile;
    configFile >> tmpConfigFile;
    for (int id = 0; id < tmpConfigFile.size(); id++) {
        if (map == tmpConfigFile[id]["name"].get<std::string>()) {
            // std::cout << id << std::endl;
            // Render::Camera::camera.pos = sf::Vector3f(tmpConfigFile[id]["pos"]["x"].get<float>(), tmpConfigFile[id]["pos"]["y"].get<float>(), tmpConfigFile[id]["pos"]["z"].get<float>());
        }
    }
    worldFile.close();
    configFile.close();
    rebuild_hash_map(Map::getWorldJson());
}

void Map::loadMapToMEMFromFile(std::string map, int x, int y) {
    std::ifstream worldFile("./map/world/" + map + "/chunk/chunk_" + std::to_string(x) + "_" + std::to_string(y) +".bin");
    if (!worldFile) {
        return;
    }

    std::string worldData((std::istreambuf_iterator<char>(worldFile)), std::istreambuf_iterator<char>());

    std::stringstream ss(worldData);
    std::string item;

    while (std::getline(ss, item, ';')) {
        std::stringstream line(item);
        std::string val;
        Map::binMapBlock b;
        std::getline(line, val, ','); b.id = std::stoi(val);
        std::getline(line, val, ','); b.x = std::stoi(val);
        std::getline(line, val, ','); b.y = std::stoi(val);
        std::getline(line, val, ','); b.z = std::stoi(val);
        std::getline(line, val, ','); b.type = std::stoi(val);
        std::getline(line, val, ','); b.tex = std::stoi(val);
        // Map::MEMMap.push_back({x, y, b});
    }

    worldFile.close();
}

json Map::getAllMap() {
    std::ifstream confJsonFile("./map/config.json");
    json confJson;
    confJsonFile >> confJson;
    confJsonFile.close();
    return confJson;
}

bool Map::random(int a, int num) {
    return (std::rand() % a + 1) == num;
}

bool Map::worldHasExist(std::string name) {
    std::ifstream configFile("./map/config.json");
    json tmpConfigFile;
    configFile >> tmpConfigFile;

    for (int id = 0; id < tmpConfigFile.size(); id++) {
        if (tmpConfigFile[id]["name"].get<std::string>() == name) {
            return true;
        }
    }
    return false;
}