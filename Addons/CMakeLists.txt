option(OGREKIT_ADDON_GAMEADDON "COMPILE GAME-ADDON"  OFF)
if (OGREKIT_ADDON_GAMEADDON)
    subdirs(Addon)
endif()

option(OGREKIT_ADDON_ADDONTHRIFT "COMPILE THRIFT-ADDON"  OFF)
if (OGREKIT_ADDON_ADDONTHRIFT)
    subdirs(AddonThrift)
endif()

option(OGREKIT_ADDON_ADDONDEFAULT "COMPILE DEFAULT-ADDON"  OFF)
if (OGREKIT_ADDON_ADDONDEFAULT)
    subdirs(DefaultAddon)
endif()

option(OGREKIT_ADDON_ADDTRIQUACIR "COMPILE TRIQUACIR-ADDON"  OFF)
if (OGREKIT_ADDON_ADDTRIQUACIR)
    subdirs(TriQuaCir)
endif()