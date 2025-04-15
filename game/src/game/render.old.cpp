// if (!Map::getWorldJson().empty()) {
    //     const auto& worldJson = Map::getWorldJson();
    //     const auto& blocks = worldJson["id"];
    
    //     for (const auto& [id, block] : blocks.items()) {
    //         float x = block["x"].get<float>();
    //         float y = block["y"].get<float>();
    //         float z = block["z"].get<float>();
    //         std::string name = block["name"].get<std::string>();
    
    //         bool faces[6] = {
    //             Map::duplicate(worldJson, std::stoi(id), 0),
    //             Map::duplicate(worldJson, std::stoi(id), 1),
    //             Map::duplicate(worldJson, std::stoi(id), 2),
    //             Map::duplicate(worldJson, std::stoi(id), 3),
    //             Map::duplicate(worldJson, std::stoi(id), 4),
    //             Map::duplicate(worldJson, std::stoi(id), 5)
    //         };
    
    //         float texCoords[6] = {
    //             Material::getTexCoordByType(name, 0),
    //             Material::getTexCoordByType(name, 1),
    //             Material::getTexCoordByType(name, 2),
    //             Material::getTexCoordByType(name, 3),
    //             Material::getTexCoordByType(name, 4),
    //             Material::getTexCoordByType(name, 5)
    //         };
    
    //         Render::drawCube(x, y, z, faces[0], faces[1], faces[2], faces[3], faces[4], faces[5],
    //                         texCoords[0], texCoords[1], texCoords[2], texCoords[3], texCoords[4], texCoords[5]);
    //     }
        
    // }