class CfgPatches
{
	class SimplifiedCarLock_Scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Vehicles_Wheeled",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class SimplifiedCarLock
	{
		dir="SimplifiedCarLock";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="SimplifiedCarLock";
		credits="Jules";
		author="Jules";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"SimplifiedCarLock/scripts/4_World"
				};
			};
		};
	};
};
