#include "PCH.h"

void LoadConfig()
{
    std::filesystem::path configPath = SKSE::GetConfigDirectory() / "EnxyAbilities_Config.json";
    
    if (!std::filesystem::exists(configPath)) {
        SKSE::log::info("No config file, using defaults");
        return;
    }

    std::ifstream file(configPath);
    if (!file.is_open()) {
        SKSE::log::error("Failed to open config file");
        return;
    }

    std::string jsonStr((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    g_config.showHP = (jsonStr.find(""showHP":true") != std::string::npos);
    g_config.showStamina = (jsonStr.find(""showStamina":true") != std::string::npos);
    g_config.showMagicka = (jsonStr.find(""showMagicka":true") != std::string::npos);

    auto posXPos = jsonStr.find(""posX":");
    auto posYPos = jsonStr.find(""posY":");
    
    if (posXPos != std::string::npos) {
        posXPos += 7;
        g_config.posX = std::strtod(jsonStr.c_str() + posXPos, nullptr);
    }

    if (posYPos != std::string::npos) {
        posYPos += 7;
        g_config.posY = std::strtod(jsonStr.c_str() + posYPos, nullptr);
    }

    SKSE::log::info("Config loaded: HP=%d, Stam=%d, Mag=%d, X=%f, Y=%f",
        g_config.showHP, g_config.showStamina, g_config.showMagicka,
        g_config.posX, g_config.posY);
}

void SaveConfig()
{
    std::filesystem::path configPath = SKSE::GetConfigDirectory() / "EnxyAbilities_Config.json";
    
    std::ofstream file(configPath);
    if (!file.is_open()) {
        SKSE::log::error("Failed to save config file");
        return;
    }

    std::string json = "{";
    json += ""showHP":" + std::string(g_config.showHP ? "true" : "false") + ",";
    json += ""showStamina":" + std::string(g_config.showStamina ? "true" : "false") + ",";
    json += ""showMagicka":" + std::string(g_config.showMagicka ? "true" : "false") + ",";
    json += ""posX":" + std::to_string(g_config.posX) + ",";
    json += ""posY":" + std::to_string(g_config.posY);
    json += "}";

    file << json;
    file.close();

    SKSE::log::info("Config saved");
}