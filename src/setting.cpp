#include "PCH.h"

// Callback dari JS -> C++
void AdminConfig(const char* result)
{
    SKSE::log::info("AdminConfig received: %s", result);

    auto showHPPos = strstr(result, "showHP:");
    auto showStamPos = strstr(result, "showStamina:");
    auto showMagPos = strstr(result, "showMagicka:");
    auto posXPos = strstr(result, "posX:");
    auto posYPos = strstr(result, "posY:");

    if (showHPPos) g_config.showHP = (showHPPos[7] == 't');
    if (showStamPos) g_config.showStamina = (showStamPos[10] == 't');
    if (showMagPos) g_config.showMagicka = (showMagPos[11] == 't');

    if (posXPos) {
        posXPos += 5;
        g_config.posX = std::strtod(posXPos, nullptr);
    }

    if (posYPos) {
        posYPos += 5;
        g_config.posY = std::strtod(posYPos, nullptr);
    }

    SaveConfig();
    ApplyConfigToHUD();

    SKSE::log::info("Config applied from JS");
}

void InitializeConfig()
{
    InGameLog(">>> Creating Config View...");
    
    auto onDomReadyConfig = [](PrismaView view) {
        SKSE::log::info("Config DOM ready");
    };

    g_viewConfig = PrismaUI->CreateView("EnxyAbilities/setting.html", onDomReadyConfig);

    if (!PrismaUI->IsValid(g_viewConfig)) {
        InGameLog(">>> Config View INVALID");
        SKSE::log::error("Config View invalid");
        return;
    }

    PrismaUI->Hide(g_viewConfig);

    char buffer[64];
    sprintf_s(buffer, ">>> Config View ID: %llu", g_viewConfig);
    InGameLog(buffer);

    // Register JS listener
    PrismaUI->RegisterJSListener(g_viewConfig, "AdminConfig", AdminConfig);

    InGameLog(">>> CONFIG VIEW CREATED");
}