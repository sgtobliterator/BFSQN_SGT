// ============================================================
// cfgfunctions.hpp
//
// All BFSQN_drones functions compiled at mission start via CBA.
// Tag: BFSQN  →  accessed as BFSQN_fnc_<name>
// ============================================================

class CfgFunctions
{
	class BFSQN
	{
		tag = "BFSQN";

		class drones
		{
			file = "x\BFSQN_Hub\addons\BFSQN_drones\Core\functions";

			// Per-drone init (called via postInit EventHandler on spawn).
			// Mirrors GX's fn_drone_postInit - calls bis_fnc_initVehicle.
			class sps_bh_postInit {};

			// Returns true if the local player can deploy the SPS BH item.
			class sps_bh_canDeploy {};

			// Main deploy function.
			// Supports "FLY" (hand deploy) and "GROUND" (place) methods.
			// Must be called with 'spawn' - contains a sleep in auto-connect.
			class sps_bh_deploy {};

			// Returns true if the player can pick up a deployed SPS BH drone.
			class sps_bh_canPickup {};

			// Picks up a deployed drone and returns the item to inventory.
			class sps_bh_pickup {};
		};
	};
};
