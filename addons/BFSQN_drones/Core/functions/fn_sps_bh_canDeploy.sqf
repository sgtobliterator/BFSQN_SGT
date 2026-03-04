/* =================================================
   Author:
      BFSQN (adapted from GX Drones - fn_drone_canSelfInteract by HBTurpin)
   Description:
      Returns true if the player is eligible to deploy the SPS Black
      Hornet from their inventory via the ACE self-interact menu.

      Conditions (matching GX's fn_drone_canSelfInteract exactly,
      plus an item-in-inventory check):
        - Player is not inside a vehicle
        - Player is not actively remote-controlling a drone
        - Player is not a UAV themselves
        - Player has the SPS BH item in their inventory

   Arguments:
      0: OBJECT - The player to check (usually _player in ACE context)
   Returns:
      BOOL
* =================================================*/

params [
    ["_player", player, [objNull]]
];

// Not inside a vehicle
if (!isNull objectParent _player) exitWith { false };

// Not remote controlling another drone
if (isRemoteControlling _player) exitWith { false };

// Not a UAV unit
if (unitIsUAV _player) exitWith { false };

// Has the item in inventory
if !("sps_black_hornet_01_Static_F" in items _player) exitWith { false };

true
