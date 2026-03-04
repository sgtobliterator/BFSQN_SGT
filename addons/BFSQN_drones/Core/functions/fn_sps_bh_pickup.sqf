/* =================================================
   Author:
      BFSQN
   Description:
      Picks up a deployed SPS Black Hornet drone and returns the
      inventory item to the player. Re-runs canPickup as a safety
      guard (ACE can fire statements on a slight delay).

   Arguments:
      0: OBJECT - The player picking up the drone
      1: OBJECT - The drone vehicle to retrieve
   Returns:
      BOOL - true if pickup succeeded, false otherwise
* =================================================*/

params [
    ["_player", player,  [objNull]],
    ["_drone",  objNull, [objNull]]
];

// Re-validate before acting
if !([_player, _drone] call BFSQN_fnc_sps_bh_canPickup) exitWith { false };

deleteVehicle _drone;
_player addItem "sps_black_hornet_01_Static_F";

true
