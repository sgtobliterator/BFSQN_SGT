/* =================================================
   Author:
      BFSQN (adapted from GX Drones - fn_drone_deploy by HBTurpin)
   Description:
      Deploys the SPS Black Hornet from the player's inventory.
      Supports two methods matching GX Drones exactly:

         FLY    - Hand deploy. Stance-aware animation plays,
                  drone spawns 2.4m in front at 1.2m above ASL.
                  Immediately hovers at 1.2m.

         GROUND - Ground place. Same animation plays, drone
                  spawns 2.0m in front at ground level using
                  CAN_COLLIDE. Terrain height safety check
                  prevents underground placement on slopes.

      Post-spawn in both cases:
         - bis_fnc_initVehicle called (via postInit EH)
         - Crew created and joined to a group matching player side
         - Fuel set to full
         - Item removed from inventory
         - Auto-connects UAV terminal if GX_DRONES_AUTOCONNECT
           is enabled (gracefully skipped if GX not loaded)

      Spawned class is side-aware:
         west        -> sps_black_hornet_01_F   (BLUFOR)
         east        -> sps_black_hornet_01_O_F (OPFOR)
         independent -> sps_black_hornet_01_I_F (IND)

   Arguments:
      0: OBJECT - Player deploying the drone
      1: STRING - Method: "FLY" (default) or "GROUND"
   Returns:
      BOOL - true on success, false on failed safety check

   Notes:
      Must be called with 'spawn':
         [player, "FLY"]    spawn BFSQN_fnc_sps_bh_deploy
         [player, "GROUND"] spawn BFSQN_fnc_sps_bh_deploy
* =================================================*/

params [
    ["_player", player, [objNull]],
    ["_method",  "FLY",  [""]]
];

private _item = "sps_black_hornet_01_Static_F";

// ---- Safety checks -----------------------------------------
if (!alive _player)              exitWith { false };
if !(_player == vehicle _player) exitWith { false };
if !(_item in items _player)     exitWith { false };

// ---- Side-aware drone class --------------------------------
private _droneClass = switch (side _player) do
{
    case west:        { "sps_black_hornet_01_F"   };
    case east:        { "sps_black_hornet_01_O_F" };
    case independent: { "sps_black_hornet_01_I_F" };
    default           { "sps_black_hornet_01_F"   };
};

// ---- Stance-aware animation --------------------------------
// Direct port of GX's animation selection.
// remoteExec broadcasts to all machines so every player in
// the session sees the deploy animation.
private _anim = [
    "AinvPknlMstpSrasWrflDnon_Putdown_AmovPknlMstpSrasWrflDnon",
    "AinvPercMstpSrasWrflDnon_Putdown_AmovPercMstpSrasWrflDnon"
] select (stance _player == "STAND");

[_player, _anim] remoteExec ["switchMove", 0];

private _drone = objNull;

// ============================================================
//  FLY - hand deploy (GX "FLY" method)
// ============================================================
if (_method == "FLY") then
{
    private _unitPos  = _player getPos [2.4, getDir _player];
    private _dronePos = [
        _unitPos select 0,
        _unitPos select 1,
        ((getPosASL _player) select 2) + 1.2
    ];

    _drone = createVehicle [_droneClass, _dronePos, [], 0, "FLY"];
    _drone setPosASL _dronePos;
    _drone setVectorDirAndUp [vectorDir _player, vectorUp _player];
    _drone flyInHeight [1.2, true];
    _drone setVelocity [0, 0, 0];
};

// ============================================================
//  GROUND - place on ground (GX "GROUND" method)
// ============================================================
if (_method == "GROUND") then
{
    private _unitPos  = _player getPos [2.0, getDir _player];
    private _dronePos = [
        _unitPos select 0,
        _unitPos select 1,
        (getPosASL _player) select 2
    ];

    _drone = createVehicle [_droneClass, _dronePos, [], 0, "CAN_COLLIDE"];

    // Push drone above terrain if slope would place it underground
    if ((_dronePos select 2) < (getTerrainHeightASL _dronePos)) then
    {
        _dronePos = [
            _unitPos select 0,
            _unitPos select 1,
            (getTerrainHeightASL _dronePos) + 0.05
        ];
    };

    _drone setPosASL _dronePos;
    _drone setVectorDirAndUp [vectorDir _player, vectorUp _player];
};

// ============================================================
//  Post-spawn (both methods)
// ============================================================
createVehicleCrew _drone;
crew _drone join createGroup (side _player);

_drone setFuel 1.0;

_player removeItem _item;

// Auto-connect to UAV terminal.
// GX_DRONES_AUTOCONNECT is a CBA setting defined by GX core.
// The isNil check makes this block safe even when GX is not loaded.
if (!(isNil "GX_DRONES_AUTOCONNECT") && {isNull (remoteControlled _player)} && {GX_DRONES_AUTOCONNECT}) then
{
    [_player, _drone, _method] spawn
    {
        params ["_player", "_drone", "_method"];

        // Brief wait after ground placement for physics to settle
        if (_method == "GROUND") then { sleep 0.5; };

        private _canConnect = _player connectTerminalToUAV _drone;
        if (_canConnect) then
        {
            driver _drone switchCamera "Internal";
            _player remoteControl driver _drone;
        };
    };
};

true
