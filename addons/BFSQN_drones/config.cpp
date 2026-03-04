// ============================================================
// BFSQN_drones - config.cpp
//
// SPS Black Hornet with GX-style ACE deployment.
// Fully self-contained - no GX runtime dependency.
//
// GX icon PAAs must be physically copied into:
//   SPS_Black_Hornet\data\ui\
// (see README.txt for exact instructions)
//
// Dependencies:
//   ace_interact_menu  - ACE interaction framework
//   cba_main           - CBA (required by ACE)
// ============================================================

class CfgPatches
{
    class ADDON
    {
        name = SPOKE;
        author = AUTHOR;
		units[]=
		{
			"sps_black_hornet_01_F",
			"sps_black_hornet_01_O_F",
			"sps_black_hornet_01_I_F"
		};
		weapons[]=
		{
			"sps_black_hornet_01_Static_F"
		};
        requiredVersion = REQUIRED_VERSION;
		requiredAddons[]=
		{
			"A3_Data_F_Destroyer_Loadorder",
			"A3_Data_F_Sams_Loadorder",
			"cba_main",
			"BFSQN_core"
		};
	};
};

#include "cfgfunctions.hpp"

// ---- Sensor forward declarations ---------------------------
class SensorTemplatePassiveRadar;
class SensorTemplateAntiRadiation;
class SensorTemplateActiveRadar;
class SensorTemplateIR;
class SensorTemplateVisual;
class SensorTemplateMan;
class SensorTemplateLaser;
class SensorTemplateNV;
class SensorTemplateDataLink;

class DefaultVehicleSystemsDisplayManagerLeft  { class components; };
class DefaultVehicleSystemsDisplayManagerRight { class components; };

// ============================================================
//  CfgVehicles
// ============================================================
class CfgVehicles
{
	class Air;
	class Helicopter: Air
	{
		class Turrets;
		class HitPoints;
	};
	class Helicopter_Base_F: Helicopter
	{
		class Turrets: Turrets { class MainTurret; };
		class HitPoints: HitPoints
		{
			class HitHRotor;
			class HitHull;
		};
		class AnimationSources;
		class EventHandlers;
		class ViewOptics;
		class ViewPilot;
		class Components;
	};
	class UAV_01_base_F: Helicopter_Base_F
	{
		class Turrets: Turrets { class MainTurret; };
		class HitPoints: HitPoints
		{
			class HitHRotor;
			class HitHull;
		};
		class AnimationSources;
		class EventHandlers;
		class ViewOptics;
		class ViewPilot;
		class Components;
		class ACE_Actions;
		class RotorLibHelicopterProperties;
	};

	// --------------------------------------------------------
	//  Base class - scope=0, never appears in editor
	// --------------------------------------------------------
	class sps_black_hornet_01_Base_F: UAV_01_base_F
	{
		// ----------------------------------------------------
		//  ACE interaction on the DRONE itself (nearby player)
		// ----------------------------------------------------
		class ACE_Actions
		{
			class ACE_MainActions
			{
				condition="alive _target";
				displayName="Interactions";
				distance=2.5;
				position="[0,0,0]";
				selection="";
				class BFSQN_SPS_BH_Pickup
				{
					displayName="Pick Up Black Hornet";
					showDisabled=0;
					distance=2.75;
					condition="[_player, _target] call BFSQN_fnc_sps_bh_canPickup";
					statement="[_player, _target] call BFSQN_fnc_sps_bh_pickup";
					icon="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_ca.paa";
					exceptions[]={"isNotInside"};
				};
			};
		};

		// ----------------------------------------------------
		//  PostInit EventHandler
		//  Mirrors GX's per-drone init: calls bis_fnc_initVehicle
		//  which fixes certain texture and vehicle init issues.
		// ----------------------------------------------------
		class EventHandlers: EventHandlers
		{
			class BFSQN_DRONES
			{
				postInit="[_this#0] spawn BFSQN_fnc_sps_bh_postInit;";
			};
		};

		class AnimationSources;
		class RotorLibHelicopterProperties: RotorLibHelicopterProperties
		{
			defaultCollective=0.34999999;
		};
		class CargoTurret;
		class MarkerLights {};

		faction="BLU_F";
		side=1;
		crew="B_UAV_AI";
		audible=0.0085000005;
		camouflage=0.025;
		author="SPS Team / BFSQN";
		mainBladeCenter="main_rotor_axis";
		tailBladeCenter="tail_rotor_axis";
		_generalMacro="";
		armor=1;
		altFullForce=1000;
		altNoForce=1250;
		maxSpeed=50;
		mainBladeRadius=0.061500002;
		tailBladeRadius=0.025;
		liftForceCoef=1.75;
		cyclicAsideForceCoef=0.059999999;
		cyclicForwardForceCoef=0.039999999;
		bodyFrictionCoef=17;
		backRotorForceCoef=1.5;
		airFrictionCoefs0[]={0,0,0};
		airFrictionCoefs1[]={0.1,0.050000001,0.0040000002};
		airFrictionCoefs2[]={0.001,0.00050000002,3.9999999e-005};
		washDownDiameter="0.12f";
		washDownStrength="0.005f";
		maxGForce=5;
		startDuration=2;
		fuelCapacity=30;
		fuelConsumptionRate=0.0099999998;
		accuracy=1;
		visualTargetSize=0.0049999999;
		threat[]={0.0099999998,0.0049999999,0.0049999999};
		displayName="Black Hornet";
		model="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\sps_blackhornet.p3d";
		driveOnComponent[]={"gear1","gear2"};
		icon="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_map_icon_ca.paa";
		picture="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_ca.paa";
		insideSoundCoef=0.015;
		minTotalDamageThreshold=1;
		radarTarget=0;
		spotableDarkNightLightsOff=9.9999997e-005;
		spotableNightLightsOff=0.0020000001;
		spotableNightLightsOn=0.0040000002;
		uavCameraDriverPos="pip_pilot_pos";
		uavCameraDriverDir="pip_pilot_dir";
		uavCameraGunnerPos="PiP0_pos";
		uavCameraGunnerDir="PiP0_dir";
		memoryPointDriverOptics="pip_pilot_pos";
		driverOpticsModel="A3\drones_f\Weapons_F_Gamma\Reticle\UGV_01_Optics_Driver_F.p3d";
		driverForceOptics=1;
		extCameraPosition[]={0,1.4,-5};
		class ViewPilot: ViewPilot
		{
			minFov=0.25;
			maxFov=1.25;
			initFov=0.75;
			initAngleX=0;
			minAngleX=-65;
			maxAngleX=85;
			initAngleY=0;
			minAngleY=-150;
			maxAngleY=150;
			minMoveX=0;
			maxMoveX=0;
			minMoveY=0;
			maxMoveY=0;
			minMoveZ=0;
			maxMoveZ=0;
		};
		class Viewoptics: ViewOptics
		{
			initAngleX=0;
			minAngleX=-30;
			maxAngleX=30;
			initAngleY=0;
			minAngleY=-30;
			maxAngleY=30;
			minFov=0.25;
			maxFov=1.25;
			initFov=0.75;
			visionMode[]={"Normal","NVG","Ti"};
			thermalMode[]={0,1};
		};
		class Turrets: Turrets
		{
			class MainTurret: MainTurret
			{
				isCopilot=0;
				minElev=-75;
				maxElev=30;
				initElev=-3;
				minTurn=-65;
				maxTurn=65;
				initTurn=0;
				// Rotation speed from GX RQ-11B (was 10, RQ-11 uses 2.6666667 for smoother camera control)
				maxHorizontalRotSpeed=2.6666667;
				maxVerticalRotSpeed=2.6666667;
				body="mainTurret";
				gun="mainGun";
				animationSourceBody="mainTurret";
				animationSourceGun="mainGun";
				class OpticsIn
				{
					class Wide
					{
						opticsDisplayName="W";
						initAngleX=0;
						minAngleX=-45;
						maxAngleX=45;
						initAngleY=0;
						minAngleY=-90;
						maxAngleY=30;
						initFov=0.5;
						minFov=0.5;
						maxFov=0.5;
						directionStabilized=1;
						visionMode[]={"Normal","NVG","Ti"};
						thermalMode[]={0,1};
						gunnerOpticsModel="A3\drones_f\Weapons_F_Gamma\Reticle\UAV_Optics_Gunner_wide_F.p3d";
					};
					class Medium: Wide
					{
						opticsDisplayName="M";
						initFov=0.1;
						minFov=0.1;
						maxFov=0.1;
						gunnerOpticsModel="A3\drones_f\Weapons_F_Gamma\Reticle\UAV_Optics_Gunner_medium_F.p3d";
					};
					class Narrow: Wide
					{
						opticsDisplayName="N";
						initFov=0.0286;
						minFov=0.0286;
						maxFov=0.0286;
						gunnerOpticsModel="A3\drones_f\Weapons_F_Gamma\Reticle\UAV_Optics_Gunner_narrow_F.p3d";
					};
				};
				class OpticsOut
				{
					class Monocular
					{
						initAngleX=0;
						minAngleX=-30;
						maxAngleX=30;
						initAngleY=0;
						minAngleY=-100;
						maxAngleY=100;
						initFov=1.1;
						minFov=0.133;
						maxFov=1.1;
						visionMode[]={"Normal","NVG"};
						gunnerOpticsModel="";
						gunnerOpticsEffect[]={};
					};
				};
				class Components
				{
					class VehicleSystemsDisplayManagerComponentLeft: DefaultVehicleSystemsDisplayManagerLeft
					{
						class components
						{
							class EmptyDisplay   { componentType="EmptyDisplayComponent"; };
							class MinimapDisplay { componentType="MinimapDisplayComponent"; resource="RscCustomInfoMiniMap"; };
							class UAVDisplay     { componentType="UAVFeedDisplayComponent"; };
							class SensorDisplay  { componentType="SensorsDisplayComponent"; range[]={800,400,200,1600}; resource="RscCustomInfoSensors"; };
						};
					};
					class VehicleSystemsDisplayManagerComponentRight: DefaultVehicleSystemsDisplayManagerRight
					{
						defaultDisplay="SensorDisplay";
						class components
						{
							class EmptyDisplay   { componentType="EmptyDisplayComponent"; };
							class MinimapDisplay { componentType="MinimapDisplayComponent"; resource="RscCustomInfoMiniMap"; };
							class UAVDisplay     { componentType="UAVFeedDisplayComponent"; };
							class SensorDisplay  { componentType="SensorsDisplayComponent"; range[]={800,400,200,1600}; resource="RscCustomInfoSensors"; };
						};
					};
				};
				inGunnerMayFire=1;
				outGunnerMayFire=1;
				commanding=-1;
				primaryGunner=1;
				memoryPointGun="PiP0_dir";
				memoryPointGunnerOptics="PiP0_pos";
				gunnerOpticsModel="A3\drones_f\Weapons_F_Gamma\Reticle\UGV_01_Optics_Gunner_F.p3d";
				gunnerForceOptics=1;
				turretInfoType="RscOptics_UAV_gunner";
				stabilizedInAxes=3;
				weapons[]={"Laserdesignator_mounted_blank"};
				magazines[]={"Laserbatteries"};
				soundServo[]=
				{
					"A3\Sounds_F\vehicles\air\noises\servo_drone_turret_2",
					0.0099999998,
					0.064999998,
					4
				};
				soundServoVertical[]=
				{
					"A3\Sounds_F\vehicles\air\noises\servo_drone_turret_2",
					0.0099999998,
					0.064999998,
					4
				};
				GunnerCompartments="Compartment1";
				LODTurnedIn=-1;
				LODTurnedOut=-1;
			};
		};
		class TransportItems {};
		hiddenSelections[]={"camo"};
		soundEngineOnInt[]=  {"A3\Sounds_F\air\Uav_01\quad_start_full_int",  0.062341329, 0.15000001, 8};
		soundEngineOnExt[]=  {"A3\Sounds_F\air\Uav_01\quad_start_full_01",   0.062341329, 0.15000001, 8};
		soundEngineOffInt[]= {"A3\Sounds_F\air\Uav_01\quad_stop_full_int",   0.062341329, 0.15000001, 8};
		soundEngineOffExt[]= {"A3\Sounds_F\air\Uav_01\quad_stop_full_01",    0.062341329, 0.15000001, 8};
		soundBushCollision1[]={"A3\Sounds_F\vehicles\crashes\helis\Heli_coll_bush_int_1", 0.15000001, 1, 10};
		soundBushCollision2[]={"A3\Sounds_F\vehicles\crashes\helis\Heli_coll_bush_int_2", 0.15000001, 1, 10};
		soundBushCollision3[]={"A3\Sounds_F\vehicles\crashes\helis\Heli_coll_bush_int_3", 0.15000001, 1, 10};
		soundBushCrash[]={"soundBushCollision1",0.133,"soundBushCollision2",0.133,"soundBushCollision3",0.133};
		soundWaterCollision1[]={"A3\Sounds_F\vehicles\crashes\helis\Heli_coll_water_ext_1",0.15000001,1,10};
		soundWaterCollision2[]={"A3\Sounds_F\vehicles\crashes\helis\Heli_coll_water_ext_2",0.15000001,1,10};
		soundWaterCrashes[]={"soundWaterCollision1",0.15000001,"soundWaterCollision2",0.15000001};
		Crash0[]={"A3\Sounds_F\vehicles\crashes\cars\cars_coll_big_default_ext_1",0.15000001,1,12.5};
		Crash1[]={"A3\Sounds_F\vehicles\crashes\cars\cars_coll_big_default_ext_2",0.15000001,1,12.5};
		Crash2[]={"A3\Sounds_F\vehicles\crashes\cars\cars_coll_big_default_ext_3",0.15000001,1,12.5};
		Crash3[]={"A3\Sounds_F\vehicles\crashes\cars\cars_coll_big_default_ext_4",10.15,1,12.5};
		class Sounds
		{
			class Engine     { sound[]={"A3\Sounds_F\air\Uav_01\quad_engine_full_01",1.2724668,0.15000001,7.5};   frequency="rotorSpeed";   volume="camPos*((rotorSpeed-0.72)*1.75)"; };
			class RotorLowOut{ sound[]={"A3\Sounds_F\air\Uav_01\blade",              1.2723162,0.30000001,3.5};   frequency="rotorSpeed";   volume="camPos*(0 max (rotorSpeed-0.1)*.25)"; cone[]={1.6,3.1400001,1.6,0.94999999}; };
			class RotorHighOut{ sound[]={"A3\Sounds_F\air\Uav_01\blade_high",        1.2723162,0.30000001,7.5};   frequency="rotorSpeed";   volume="camPos*10*(0 max (rotorThrust-0.9)*.275)"; cone[]={1.6,3.1400001,1.6,0.94999999}; };
			class EngineIn   { sound[]={"A3\Sounds_F\air\Uav_01\quad_engine_full_int",0.15623413,0.075000003};    frequency="rotorSpeed*5"; volume="(1-camPos)*((rotorSpeed-0.75)*1.5)"; };
			class RotorLowIn { sound[]={"A3\Sounds_F\air\Uav_01\blade_int",          0.17562342,0.30000001};      frequency="rotorSpeed*3"; volume="(1-camPos)*0.25*(0 max (rotorSpeed-0.1))"; };
			class RotorHighIn{ sound[]={"A3\Sounds_F\air\Uav_01\blade_high_int",     0.17562342,0.30000001};      frequency="rotorSpeed*3"; volume="(1-camPos)*0.75*(rotorThrust-0.9)"; };
		};
		class Library
		{
			libTextDesc="The Black Hornet PRS is a micro remote-controlled UAV equipped with a FLIR camera. It is perfect for reconnaissance and surveillance. Black Hornets are agile, silent and hard to detect.";
		};
		class TextureSources {};
		class DustEffects {};
		class Exhausts {};
		dustEffect="";
		leftDustEffects[]={};
		rightDustEffects[]={};
		vehicleClass="BlackHornetUAV";
	};

	// --------------------------------------------------------
	//  BLUFOR variant
	// --------------------------------------------------------
	class sps_black_hornet_01_F: sps_black_hornet_01_Base_F
	{
		scope=2;
		scopeCurator=2;
		side=1;
		faction="BLU_F";
		crew="B_UAV_AI";
		typicalCargo[]={"B_UAV_AI"};
		hiddenSelections[]={"camo"};
		hiddenSelectionsTextures[]=
		{
			"x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\standard\SPS_BH_low_CO.paa"
		};
		displayName="Black Hornet";
		descriptionShort="Micro UAV";
		displaynameshort="Black Hornet";
		picture="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_ca.paa";
		// Vanilla scroll-wheel pickup when drone is landed nearby
		class UserActions
		{
			class BFSQN_SPS_BH_Pickup
			{
				displayNameDefault="Pick Up Black Hornet";
				priority=6;
				showWindow=1;
				hideOnUse=1;
				displayName="Pick Up Black Hornet";
				position="action";
				radius=6.5;
				onlyForPlayer=1;
				condition="this == cursorObject && SPS_BlackHornet_EnableVanillaScrollWheel && alive this && player == vehicle player && player canadd ""sps_black_hornet_01_Static_F""";
				statement="[player, this] call BFSQN_fnc_sps_bh_pickup";
			};
		};
	};

	// --------------------------------------------------------
	//  OPFOR variant
	// --------------------------------------------------------
	class sps_black_hornet_01_O_F: sps_black_hornet_01_F
	{
		scope=2;
		scopeCurator=2;
		side=0;
		faction="OPF_F";
		crew="O_UAV_AI";
		typicalCargo[]={"O_UAV_AI"};
	};

	// --------------------------------------------------------
	//  Independent variant
	// --------------------------------------------------------
	class sps_black_hornet_01_I_F: sps_black_hornet_01_F
	{
		scope=2;
		scopeCurator=2;
		side=2;
		faction="IND_F";
		crew="I_UAV_AI";
		typicalCargo[]={"I_UAV_AI"};
	};

	// --------------------------------------------------------
	//  CaManBase - player self-actions and scroll-wheel deploy
	// --------------------------------------------------------
	class Man;
	class CaManbase: Man
	{
		// ----------------------------------------------------
		//  Vanilla scroll-wheel deploy (fallback if ACE not used)
		// ----------------------------------------------------
		class UserActions
		{
			class BFSQN_SPS_BH_Deploy
			{
				displayNameDefault="Launch Black Hornet";
				priority=-10;
				showWindow=0;
				hideOnUse=1;
				displayName="Launch Black Hornet";
				position="action";
				radius=5;
				onlyForPlayer=1;
				condition="this == player && SPS_BlackHornet_EnableVanillaScrollWheel && alive this && isPlayer this && this == vehicle this && ""sps_black_hornet_01_Static_F"" in (items this)";
				// Uses FLY method (hand deploy) to match GX's default
				statement="[player, 'FLY'] spawn BFSQN_fnc_sps_bh_deploy";
			};
		};

		// ----------------------------------------------------
		//  ACE Self-Actions
		//
		//  Defines Equipment > GX_Drones with displayName/icon
		//  so the category exists and works standalone (no GX).
		//
		//  When GX IS loaded, Arma merges both definitions:
		//    - Scalar values (displayName/icon) last-writer wins
		//      (both set the same thing so no conflict)
		//    - GX's insertChildren (dynamic drone list) and our
		//      static BFSQN_SPS_BlackHornet child both appear
		//
		//  Result in both cases:
		//    Equipment > Drones > Black Hornet (SPS)
		//                           ├── Hand Deploy
		//                           └── Place
		//  With GX also loaded:
		//    Equipment > Drones > Black Hornet 4   (GX dynamic)
		//                       > Black Hornet (SPS) (BFSQN static)
		// ----------------------------------------------------
		class ACE_SelfActions
		{
			class ACE_Equipment
			{
				class ACE_GX_DRONES
				{
					// Class name matches GX's ACE_GX_DRONES exactly so Arma
					// merges both definitions into one "Drones" folder.
					// displayName, icon and exceptions defined here so the
					// category works standalone when GX is NOT loaded.
					displayName="Drones";
					exceptions[]={"isNotDragging","isNotSwimming","notOnMap","isNotInside","isNotSitting"};
					icon="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_ca.paa";

					// Without GX: isNil guard short-circuits to false,
					//             only the BFSQN check runs.
					// With GX:    both checks run, menu shows for either
					//             GX magazines or the SPS BH item.
					condition="(!(isNil 'GX_fnc_drone_canSelfInteract') && {[_player] call GX_fnc_drone_canSelfInteract}) || ([_player] call BFSQN_fnc_sps_bh_canDeploy)";

					// SPS Black Hornet entry - sits alongside GX drone entries
					class BFSQN_SPS_BlackHornet
					{
						displayName="Black Hornet (SPS)";
						icon="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_ca.paa";
						condition="[_player] call BFSQN_fnc_sps_bh_canDeploy";
						exceptions[]={"isNotInside"};
						showDisabled=0;

						class BFSQN_SPS_BH_FlyDeploy
						{
							displayName="Hand Deploy";
							icon="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\interact_hand_deploy_ca.paa";
							condition="[_player] call BFSQN_fnc_sps_bh_canDeploy";
							statement="[_player, 'FLY'] spawn BFSQN_fnc_sps_bh_deploy";
							exceptions[]={"isNotInside"};
							showDisabled=0;
						};

						class BFSQN_SPS_BH_GroundDeploy
						{
							displayName="Place";
							icon="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\interact_place_floor_ca.paa";
							condition="[_player] call BFSQN_fnc_sps_bh_canDeploy";
							statement="[_player, 'GROUND'] spawn BFSQN_fnc_sps_bh_deploy";
							exceptions[]={"isNotInside"};
							showDisabled=0;
						};
					};
				};
			};
		};
	};
};

// ============================================================
//  CfgWeapons - inventory item
// ============================================================
class CfgWeapons
{
	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryOpticsItem_Base_F;
	class CBA_MiscItem;
	class CBA_MiscItem_ItemInfo;
	class sps_black_hornet_01_Static_F: CBA_MiscItem
	{
		scope=2;
		author="SPS Team / BFSQN";
		displayName="Black Hornet";
		scopeArsenal=2;
		model="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\sps_blackhornet_static.p3d";
		descriptionShort="Micro UAV - Deploy via ACE Self-Interact";
		picture="\x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\ui\sps_blackhornet_ca.paa";
		class ItemInfo: CBA_MiscItem_ItemInfo
		{
			mass=0.727525;
			allowedSlots[]={801,701,901};
			type=302;
		};
		hiddenSelections[]={"camo"};
		hiddenSelectionsTextures[]=
		{
			"x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\data\standard\SPS_BH_low_CO.paa"
		};
	};
	class Laserdesignator_mounted;
	class Laserdesignator_mounted_blank: Laserdesignator_mounted
	{
		displayName="Laser Pointer";
		Laser=0;
	};
};

// ============================================================
//  cfgVehicleClasses
// ============================================================
class cfgVehicleClasses
{
	class BlackHornetUAV { displayName="Black Hornet"; };
};

// ============================================================
//  XEH - SPS CBA settings (EnableACEInteraction,
//  EnableVanillaScrollWheel) loaded from SPS preInit
// ============================================================
class Extended_PreInit_EventHandlers
{
	class BFSQN_sps_bh_settings
	{
		init="call compile preprocessFileLineNumbers 'x\BFSQN_Hub\addons\BFSQN_drones\SPS_Black_Hornet\XEH_preInit.sqf'";
	};
};
