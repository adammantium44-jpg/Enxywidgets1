// plugin.cpp  
#include "PCH.h"

namespace globals {  
    PRISMA_UI_API::IVPrismaUI1* PrismaUI = nullptr;  
    PrismaView g_viewConfig;  
    PrismaView g_viewHUD;  
    WidgetConfig g_config;  
}

// ... sisanya kode inisialisasi Anda ...  
static void InGameLog(const char* msg)
{
    if (RE::ConsoleLog::GetSingleton()) {
        RE::ConsoleLog::GetSingleton()->Print(msg);
    }
}

// =========================
// INPUT HANDLER
// =========================
class InputHandler : public RE::BSTEventSink<RE::InputEvent*>
{
public:
    static InputHandler* GetSingleton()
    {
        static InputHandler instance;
        return &instance;
    }

    RE::BSEventNotifyControl ProcessEvent(
        RE::InputEvent* const* a_events,
        RE::BSTEventSource<RE::InputEvent*>*) override
    {
        if (!a_events)
            return RE::BSEventNotifyControl::kContinue;

        for (auto event = *a_events; event; event = event->next)
        {
            auto button = event->AsButtonEvent();
            if (!button || !button->IsDown() || button->GetDevice() != RE::INPUT_DEVICE::kKeyboard)
                continue;

            if (button->GetIDCode() == 0x40) // F6
            {
                ToggleUI();
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }
};

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message);

// =========================
// SKSE LOAD ENTRY POINT
// =========================
SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    SKSE::Init(skse);

    auto messaging = SKSE::GetMessagingInterface();
    if (messaging) {
        messaging->RegisterListener(SKSEMessageHandler);
    } else {
        SKSE::log::error("Messaging interface not found");
        return false;
    }

    SKSE::log::info("EnxyAbilities loaded successfully");
    return true;
}

// =========================
// MESSAGE HANDLER
// =========================
static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message)
{
    if (!message)
        return;

    switch (message->type)
    {
        case SKSE::MessagingInterface::kDataLoaded:
        {
            InGameLog(">>> kDataLoaded OK");
            SKSE::log::info("kDataLoaded OK");

            InGameLog(">>> Checking PrismaUI...");

            PrismaUI = static_cast<PRISMA_UI_API::IVPrismaUI1*>(
                PRISMA_UI_API::RequestPluginAPI<PRISMA_UI_API::IVPrismaUI1>()
            );

            if (!PrismaUI) {
                InGameLog(">>> PrismaUI NOT FOUND");
                SKSE::log::error("PrismaUI FAILED");
                return;
            }

            InGameLog(">>> PrismaUI CONNECTED");
            SKSE::log::info("PrismaUI FOUND");

            auto input = RE::BSInputDeviceManager::GetSingleton();
            if (input)
            {
                input->AddEventSink(InputHandler::GetSingleton());
                InGameLog("Input Handler Registered");
            }

            InitializeUI();
            break;
        }

        default:
            break;
    }
}

void InitializeUI()
{
    InGameLog(">>> InitializeUI START");
    SKSE::log::info("InitializeUI START");

    if (!PrismaUI) {
        InGameLog(">>> PrismaUI NULL in InitUI");
        return;
    }

    LoadConfig();

    InitializeConfig();  // dari setting.cpp
    InitializeHUD();     // dari hud.cpp

    InGameLog(">>> UI INITIALIZED");
    SKSE::log::info("UI initialized");
}
