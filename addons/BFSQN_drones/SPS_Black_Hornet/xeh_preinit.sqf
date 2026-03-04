[
    "SPS_BlackHornet_EnableACEInteraction",
    "CHECKBOX",
    "Enables ACE Interaction for Black Hornet",
    "SPS Black Hornet Settings",
    true,
    false,
    {  
        params ["_value"];
        SPS_BlackHornet_EnableACEInteraction = _value;
    }
] call CBA_Settings_fnc_init;

[
    "SPS_BlackHornet_EnableVanillaScrollWheel",
    "CHECKBOX",
    "Enables Scrollwheel actions for Black Hornet",
    "SPS Black Hornet Settings",
    true,
    false,
    {  
        params ["_value"];
        SPS_BlackHornet_EnableVanillaScrollWheel = _value;
    }
] call CBA_Settings_fnc_init;
diag_log "SPS BlackHornet: Loaded CBA settings";