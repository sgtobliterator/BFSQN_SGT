/* =================================================
   Author:
      BFSQN (adapted from GX Drones - fn_drone_canPickup by HBTurpin)
   Description:
      Returns true if the player is eligible to pick up a deployed
      SPS Black Hornet drone.

      All conditions are a direct port of GX's fn_drone_canPickup:
        - Player is alive
        - Player is a human player (not AI)
        - Drone is alive
        - Player is not inside a vehicle
        - Player is not actively remote-controlling a drone
        - Player is not a UAV themselves
        - Player is on foot (objectParent check, second pass)
        - Player and drone are on the same side
        - Drone is stationary (speed < 5 km/h)

   Arguments:
      0: OBJECT - The player attempting the pickup
      1: OBJECT - The drone vehicle to retrieve
   Returns:
      BOOL
* =================================================*/

params [
    ["_player", player,  [objNull]],
    ["_drone",  objNull, [objNull]]
];

// Player alive
if !(alive _player) exitWith { false };

// Must be a human player, not AI
if !(isPlayer _player) exitWith { false };

// Drone must be alive
if !(alive _drone) exitWith { false };

// Player must be on foot
if !(isNull objectParent _player) exitWith { false };

// Player must not be remote-controlling another drone
if (isRemoteControlling _player) exitWith { false };

// Player must not be a UAV unit
if (unitIsUAV _player) exitWith { false };

// Second on-foot check (matches GX's duplicate - keeps parity)
if !(isNull objectParent _player) exitWith { false };

// Player and drone must be on the same side
if (side _player != side _drone) exitWith { false };

// Drone must be stationary (not in flight or moving fast)
if (abs (speed _drone) > 5) exitWith { false };

true
