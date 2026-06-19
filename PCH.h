#pragma once

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#include <Windows.h>
#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstring>

// CommonLibSSE NG (baru, bukan CommonLibSSE lama)
#include <CommonLibSSE/PluginAPI.h>
#include <CommonLibSSE/SKSE.h>
#include <CommonLibSSE/Logging.h>
#include <CommonLibSSE/RE/Skyrim.h>

// PrismaUI
#include "PrismaUI_API.h"

// Global variables
namespace globals {
    extern PRISMA_UI_API::IVPrismaUI1* PrismaUI;
    extern PrismaView g_viewConfig;
    extern PrismaView g_viewHUD;
    extern bool g_uiVisible;

    struct WidgetConfig {
        bool showHP = true;
        bool showStamina = true;
        bool showMagicka = true;
        float posX = 0.5f;
        float posY = 0.9f;
    };
    extern WidgetConfig g_config;
}

// Function declarations
void InGameLog(const char* msg);
void LoadConfig();
void SaveConfig();
void InitializeUI();
void ToggleUI();
void ApplyConfigToHUD();
void AdminConfig(const char* result);
void InitializeHUD();
void InitializeConfig();
void UpdateHUDStats();