##pragma once

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
#include <fstream>
#include <sstream>
#include <cstring>

#include <skse/PluginAPI.h>
#include <skse/SKSE.h>
#include <skse/Logging.h>
#include <CommonLibSSE/RE/Skyrim.h>

#include "PrismaUI_API.h"

// Forward declarations
extern PRISMA_UI_API::IVPrismaUI1* PrismaUI;
extern PrismaView g_viewConfig;
extern PrismaView g_viewHUD;
extern bool g_uiVisible;

struct WidgetConfig;
extern WidgetConfig g_config;

// Functions
void InGameLog(const char* msg);
void LoadConfig();
void SaveConfig();
void InitializeUI();
void ToggleUI();
void ApplyConfigToHUD();
void AdminConfig(const char* result);

using namespace std::literals;
