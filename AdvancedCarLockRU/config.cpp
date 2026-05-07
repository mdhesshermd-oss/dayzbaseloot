class CfgPatches
{
	class ImmobilizerClient_Scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class ImmobilizerClient
	{
		dir="ImmobilizerClient";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="ImmobilizerClient";
		credits="Exiled";
		author="Exiled#5197";
		authorID="0";
		version="1.0";
		extra=0;
		inputs="ImmobilizerClient/assets/inputs/modded_Inputs.xml";
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"ImmobilizerClient/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ImmobilizerClient/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ImmobilizerClient/scripts/5_Mission"
				};
			};
		};
	};
};
