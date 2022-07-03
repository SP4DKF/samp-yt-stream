#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>

#include "sdk/plugin.h"
#include "gdk/sampgdk.h"

using namespace std;
void **ppPluginData;
extern void *pAMXFunctions;
AMX * a;

// Nie zmieniaæ autora (!)
#define AUTOR				"Dawid"
#define DATA_KOMPILACJI		"18.06.2017"
#define WERSJA				"0.2"

#define CONVERSION_SUCCESSFUL		0 // Wszystko OK
#define ERR_INCOMPATIBILITY_HASH	1 // Niezgodnoœæ hashy
#define ERR_INVALID_LINK			2 // Podany link nie jest linkiem YouTube
#define ERR_INVALID_CODEC			3 // Wyst¹pi³ b³¹d podczas konwersji pliku (nieznany kodek)
#define ERR_LIMIT_EXCEEDED			4 // Podany klip jest za d³ugi
#define ERR_UNKNOWN_ERROR			5 // Wyst¹pi³ nieznany b³¹d
#define ERR_SERVER_NOTFOUND			6 // Nieznaleziono serwera konwersji

// Zmienne konfiguracyjne
bool ENABLED = false;
char* IP = NULL;
char* MAXSIZE = NULL;
char* HASH = NULL;

int vw = -1, interior = -1;
float posx = 0.000f, posy = 0.000f, posz = 0.000f, radius = 0.000f;

cell AMX_NATIVE_CALL yt_init(AMX* amx, cell* params)
{
	// native yt_init(const ip[], const hash[] const maxsize[]);

	if (ENABLED)
	{
		sampgdk_logprintf("[YT] !!! Wywolano yt_init() a plugin jest juz zainicjowany !!!");
		return false;
	}

	int len1 = NULL, len2 = NULL, len3 = NULL;
	cell *addr1 = NULL, *addr2 = NULL, *addr3 = NULL;

	amx_GetAddr(amx, params[1], &addr1);
	amx_StrLen(addr1, &len1);

	amx_GetAddr(amx, params[2], &addr2);
	amx_StrLen(addr2, &len2);

	amx_GetAddr(amx, params[3], &addr3);
	amx_StrLen(addr3, &len3);

	if (len1 && len2 && len3)
	{
		IP = new char[len1 + 1];
		HASH = new char[len2 + 1];
		MAXSIZE = new char[len3 + 1];

		amx_GetString(IP, addr1, 0, len1 + 1);
		amx_GetString(HASH, addr2, 0, len2 + 1);
		amx_GetString(MAXSIZE, addr3, 0, len3 + 1);
		ENABLED = true;

		sampgdk_logprintf("[YT] Plugin zostal zainicjowany (IP: %s HASH: %s MAXSIZE: %s)", IP, HASH, MAXSIZE);
	}
	else
	{
		ENABLED = false;
		sampgdk_logprintf("[YT] !!! Wystapil blad podczas inicjowania pluginu !!!");
		return false;
	}
	return true;
}

cell AMX_NATIVE_CALL yt_stop(AMX* amx, cell* params)
{
	// native yt_stop(playerid);

	if (!ENABLED)
	{
		sampgdk_logprintf("[YT] !!! Plugin nie jest zainicjowany najpierw uzyj yt_init(...) !!!");
		return false;
	}

	StopAudioStreamForPlayer(params[1]);
	return true;
}

cell AMX_NATIVE_CALL yt_play(AMX* amx, cell* params)
{
	// native yt_play(playerid, const link[]);

	if (!ENABLED)
	{
		sampgdk_logprintf("[YT] !!! Plugin nie jest zainicjowany najpierw uzyj yt_init(...) !!!");
		return false;
	}

	int len, playerid = params[1];
	cell *addr = NULL;

	amx_GetAddr(amx, params[2], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		char* link = new char[len + 1];
		amx_GetString(link, addr, 0, len + 1);

		char string[200];
		sprintf_s(string, "%s/yt/convert.php?link=%s&maxsize=%s&hash=%s", IP, link, MAXSIZE, HASH);

		HTTP(playerid, HTTP_GET, string, "");
	}
	else
	{
		sampgdk_logprintf("[YT] !!! Drugi parametr w funkcji yt_play(...) jest pusty !!!");
		return false;
	}

	StopAudioStreamForPlayer(params[1]);
	return true;
}

cell AMX_NATIVE_CALL yt_play_all(AMX* amx, cell* params)
{
	// native yt_play_all(const link[], Float:posx = 0.0, Float:posy = 0.0, Float:posz = 0.0, Float:radius = 0.0, vw = -1, interior = -1);

	if (!ENABLED)
	{
		sampgdk_logprintf("[YT] !!! Plugin nie jest zainicjowany najpierw uzyj yt_init(...) !!!");
		return false;
	}

	int len;
	char* link;
	cell *addr;

	amx_GetAddr(amx, params[1], &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		link = new char[len + 1];

		amx_GetString(link, addr, 0, len + 1);	// link
		posx = amx_ctof(params[2]);				// Float:posx
		posy = amx_ctof(params[3]);				// Float:posy
		posz = amx_ctof(params[4]);				// Float:posz
		radius = amx_ctof(params[5]);			// Float:radius
		vw = params[6];							// vw
		interior = params[7];					// interior

		char string[200];
		sprintf_s(string, "%s/yt/convert.php?link=%s&maxsize=%s&hash=%s", IP, link, MAXSIZE, HASH);
		HTTP(INVALID_PLAYER_ID, HTTP_GET, string, "");
	}
	else
	{
		sampgdk_logprintf("[YT] !!! Pierwszy parametr w funkcji yt_play_all(...) jest pusty !!!");
		return false;
	}
	return true;
}

AMX_NATIVE_INFO projectNatives[] =
{
	{ "yt_init", yt_init },
	{ "yt_stop", yt_stop },
	{ "yt_play", yt_play },
	{ "yt_play_all", yt_play_all },
	{ 0, 0 }
};

PLUGIN_EXPORT void PLUGIN_CALL OnHTTPResponse(int index, int response_code, const char *data)
{
	int idata = atoi(data);
	int amxIndex;

	if (response_code != 200)
	{
		amxIndex = NULL;
		if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
		{
			amx_Push(a, static_cast<cell>(ERR_SERVER_NOTFOUND));
			amx_Push(a, static_cast<cell>(index));
			amx_Exec(a, NULL, amxIndex);
		}
	}
	else
	{
		switch (idata)
		{
			case ERR_INCOMPATIBILITY_HASH:
			{
				amxIndex = NULL;
				if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
				{
					amx_Push(a, static_cast<cell>(ERR_INCOMPATIBILITY_HASH));
					amx_Push(a, static_cast<cell>(index));
					amx_Exec(a, NULL, amxIndex);
				}
				break;
			}
			case ERR_INVALID_LINK:
			{
				amxIndex = NULL;
				if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
				{
					amx_Push(a, static_cast<cell>(ERR_INVALID_LINK));
					amx_Push(a, static_cast<cell>(index));
					amx_Exec(a, NULL, amxIndex);
				}
				break;
			}
			case ERR_INVALID_CODEC:
			{
				amxIndex = NULL;
				if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
				{
					amx_Push(a, static_cast<cell>(ERR_INVALID_CODEC));
					amx_Push(a, static_cast<cell>(index));
					amx_Exec(a, NULL, amxIndex);
				}
				break;
			}
			case ERR_LIMIT_EXCEEDED:
			{
				amxIndex = NULL;
				if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
				{
					amx_Push(a, static_cast<cell>(ERR_LIMIT_EXCEEDED));
					amx_Push(a, static_cast<cell>(index));
					amx_Exec(a, NULL, amxIndex);
				}
				break;
			}
			case ERR_UNKNOWN_ERROR:
			{
				amxIndex = NULL;
				if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
				{
					amx_Push(a, static_cast<cell>(ERR_UNKNOWN_ERROR));
					amx_Push(a, static_cast<cell>(index));
					amx_Exec(a, NULL, amxIndex);
				}
				break;
			}
			default:
			{
				amxIndex = NULL;
				if (!amx_FindPublic(a, "OnYouTubeResponse", &amxIndex))
				{
					amx_Push(a, static_cast<cell>(CONVERSION_SUCCESSFUL));
					amx_Push(a, static_cast<cell>(index));
					amx_Exec(a, NULL, amxIndex);
				}

				if (index != INVALID_PLAYER_ID)
				{
					PlayAudioStreamForPlayer(index, data, 0.0, 0.0, 0.0, 0.0, 0);
				}
				else
				{
					if (posx == 0.000f && posy == 0.000f && posz == 0.000f)
					{
						for (int x = 0, y = GetPlayerPoolSize(); x <= y; x++)
						{
							if (!IsPlayerConnected(x)) continue;
							PlayAudioStreamForPlayer(x, data, 0.0, 0.0, 0.0, 0.0, 0);
						}
					}
					else
					{
						if (vw == -1 && interior == -1)
						{
							for (int x = 0, y = GetPlayerPoolSize(); x <= y; x++)
							{
								if (!IsPlayerConnected(x)) continue;
								PlayAudioStreamForPlayer(x, data, posx, posy, posz, radius, 1);
							}
						}
						else if (vw != -1 && interior == -1)
						{
							for (int x = 0, y = GetPlayerPoolSize(); x <= y; x++)
							{
								if (!IsPlayerConnected(x)) continue;
								if (GetPlayerVirtualWorld(x) != vw) continue;
								PlayAudioStreamForPlayer(x, data, posx, posy, posz, radius, 1);
							}
						}
						else if (vw == -1 && interior != -1)
						{
							for (int x = 0, y = GetPlayerPoolSize(); x <= y; x++)
							{
								if (!IsPlayerConnected(x)) continue;
								if (GetPlayerInterior(x) != interior) continue;
								PlayAudioStreamForPlayer(x, data, posx, posy, posz, radius, 1);
							}
						}
						else if (vw != -1 && interior != -1)
						{
							for (int x = 0, y = GetPlayerPoolSize(); x <= y; x++)
							{
								if (!IsPlayerConnected(x)) continue;
								if (GetPlayerInterior(x) == interior && GetPlayerVirtualWorld(x) == vw)
									PlayAudioStreamForPlayer(x, data, posx, posy, posz, radius, 1);
							}
						}
					}
				}
				break;
			}
		}
	}
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	sampgdk_logprintf("-------------------------------------------------");
	sampgdk_logprintf("-       Odtwarzacz & Streamer YouTube %s       -",WERSJA);
	sampgdk_logprintf("-      Data kompilacji: %s by %s    -",DATA_KOMPILACJI, AUTOR);
	sampgdk_logprintf("-------------------------------------------------");
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	sampgdk::Unload();
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	a = amx;
	return amx_Register(amx, projectNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
}


