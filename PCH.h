#pragma once

// This file is required.

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "PrismaUI_API.h"

// Global variables
// P
namespace globals {  
    extern PRISMA_UI_API::IVPrismaUI1* PrismaUI;  
    extern PrismaView g_viewConfig;  
    extern PrismaView g_viewHUD;  
    extern WidgetConfig g_config;  
    extern bool g_uiVisible;
}

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

using namespace std::literals;
