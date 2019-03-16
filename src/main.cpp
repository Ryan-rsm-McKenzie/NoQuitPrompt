#include "skse64/PluginAPI.h"
#include "skse64_common/Relocation.h"
#include "skse64_common/SafeWrite.h"
#include "skse64_common/skse_version.h"
#include <shlobj.h>
#include "version.h"

IDebugLog		gLog;
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

// 40 57 48 83 EC 30 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 48 48 89 6C 24 50 48 89 74 24 58 48 8B F9 0F B6 81 1D 02 00 00
const uintptr_t kQuitPromptEnchantingAddr = RelocationManager::s_baseAddr + 0x0086F0E4 + 0x74;  // 1_5_62
// 48 8B C4 55 56 57 48 83 EC 60 48 C7 40 C8 FE FF FF FF 48 89 58 08
const uintptr_t kQuitPromptAlchemyAddr = RelocationManager::s_baseAddr + 0x0086EED2 + 0x132;  // 1_5_62

void ApplyPatch(uintptr_t base, UInt8 * buf, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		SafeWrite8(base + i, buf[i]);
	}
}

void GameplayPatches(void)
{
	UInt8 kQuitPromptEnchanting[] =
	{
		0xE9, 0xA4, 0x00, 0x00, 0x00
	};

	UInt8 kQuitPromptAlchemy[] =
	{
		0xE9, 0x72, 0x01, 0x00, 0x00,
		0x90
	};

	ApplyPatch(kQuitPromptEnchantingAddr, kQuitPromptEnchanting, sizeof(kQuitPromptEnchanting));
	ApplyPatch(kQuitPromptAlchemyAddr, kQuitPromptAlchemy, sizeof(kQuitPromptAlchemy));
}

extern "C"
{
	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\NoQuitPrompt.log");

		_MESSAGE("NoQuitPrompt v%s", NOQUITPROMPT_VERSION_VERSTRING);

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "NoQuitPrompt";
		info->version = 2;

		g_pluginHandle = skse->GetPluginHandle();

		if (skse->isEditor) {
			_MESSAGE("loaded in editor, marking as incompatible");
			return false;
		}

		if (skse->runtimeVersion != RUNTIME_VERSION_1_5_73) {
			_MESSAGE("This plugin is not compatible with this versin of game.");
			return false;
		}

		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)
	{
		_MESSAGE("Load");

		GameplayPatches();

		return true;
	}
}
