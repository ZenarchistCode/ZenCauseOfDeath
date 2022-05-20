class CfgPatches
{
	class ZenCauseOfDeath
	{
		requiredVersion = 0.1;
		units[] =
		{
			""
		};
		requiredAddons[] =
		{
			"DZ_Data",
		};
	};
};

class CfgMods
{
	class ZenCauseOfDeath
	{
		dir = "ZenCauseOfDeath";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenCauseOfDeath";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game","World","Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenCauseOfDeath/scripts/3_game"; };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenCauseOfDeath/scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenCauseOfDeath/scripts/5_Mission" };
			};
		};
	};
};