#include "skse64/PluginAPI.h"
#include "skse64_common/Relocation.h"
#include "skse64_common/SafeWrite.h"
#include "skse64_common/skse_version.h"
#include <shlobj.h>

IDebugLog   gLog;
PluginHandle    g_pluginHandle = kPluginHandle_Invalid;

const uintptr_t kQuitPromptEnchantingAddr = RelocationManager::s_baseAddr + 0x0086F0E4;  // 1_5_50
const uintptr_t kQuitPromptAlchemyAddr = RelocationManager::s_baseAddr + 0x0086EED2;  // 1_5_50

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

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "NoQuitPrompt plugin";
		info->version = 2;

		g_pluginHandle = skse->GetPluginHandle();

		if (skse->isEditor) {
			_MESSAGE("loaded in editor, marking as incompatible");
			return false;
		}

		if (skse->runtimeVersion != RUNTIME_VERSION_1_5_50) {
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