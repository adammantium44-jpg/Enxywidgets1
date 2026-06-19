#include "PCH.h"

void ApplyConfigToHUD()
{
    if (!PrismaUI || !PrismaUI->IsValid(g_viewHUD))
        return;

    std::string args = "showHP:" + std::string(g_config.showHP ? "true" : "false") + ",";
    args += "showStamina:" + std::string(g_config.showStamina ? "true" : "false") + ",";
    args += "showMagicka:" + std::string(g_config.showMagicka ? "true" : "false") + ",";
    args += "posX:" + std::to_string(g_config.posX) + ",";
    args += "posY:" + std::to_string(g_config.posY);

    PrismaUI->InteropCall(g_viewHUD, "UpdateLayout", args.c_str());

    SKSE::log::info("HUD config applied");
}

void InitializeHUD()
{
    InGameLog(">>> Creating HUD View...");
    
    auto onDomReadyHUD = [](PrismaView view) {
        SKSE::log::info("HUD DOM ready");
        ApplyConfigToHUD();
    };

    g_viewHUD = PrismaUI->CreateView("EnxyAbilities/hud.html", onDomReadyHUD);

    if (!PrismaUI->IsValid(g_viewHUD)) {
        InGameLog(">>> HUD View INVALID");
        SKSE::log::error("HUD View invalid");
        return;
    }

    char buffer[64];
    sprintf_s(buffer, ">>> HUD View ID: %llu", g_viewHUD);
    InGameLog(buffer);

    PrismaUI->Show(g_viewHUD);
    PrismaUI->Unfocus(g_viewHUD);

    InGameLog(">>> HUD VIEW CREATED");
}

// Optional: Update real stats from game
void UpdateHUDStats()
{
    if (!PrismaUI || !PrismaUI->IsValid(g_viewHUD))
        return;

    auto player = RE::PlayerCharacter::GetSingleton();
    if (!player)
        return;

    float hp = player->GetCurrentHealth();
    float maxHp = player->GetStatValue(RE::WEAPON_TYPE::kNone); // dapat diganti
    float stamina = player->GetCurrentStamina();
    float magicka = player->GetCurrentMagicka();

    std::string args = "hp:" + std::to_string(hp) + 
                       ",maxHp:" + std::to_string(maxHp) +
                       ",stamina:" + std::to_string(stamina) +
                       ",magicka:" + std::to_string(magicka);

    PrismaUI->InteropCall(g_viewHUD, "setStats", args.c_str());
}