/* =================================================
   Author:
      BFSQN (adapted from GX Drones - fn_drone_postInit by HBTurpin)
   Description:
      Per-drone initialisation. Called via the postInit EventHandler
      on every sps_black_hornet vehicle.

      Calls bis_fnc_initVehicle on the local machine, which resolves
      certain texture and vehicle init issues on spawn (matching GX's
      approach exactly).

   Arguments:
      0: OBJECT - The drone vehicle
   Returns:
      Nothing
* =================================================*/

params ["_drone"];

if (local _drone) then
{
    [_drone, "", [], false] call bis_fnc_initVehicle;
};
