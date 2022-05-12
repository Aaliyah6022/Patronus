#pragma once
#include <windows.h>

class Offsets
{
	DWORD offset_u_world = 0x55a4e90;
	DWORD offset_g_names = 0x5452bc0;
	DWORD offset_camera_manager = 0x2c0; // APlayerController->PlayerCameraManager
	DWORD offset_camera_cache = 0x1ab0; //APlayerCameraManager->CameraCachePrivate
	DWORD offset_persistent_level = 0x30; //UWorld->PersistentLevel
	DWORD offset_game_instance = 0x180; //UWolrd->OwningGameInstance
	DWORD offset_local_players_array = 0x38; //UGameInstance->LocalPlayers
	DWORD offset_player_controller = 0x30; //UPlayer->PlayerController
	DWORD offset_apawn = 0x2a8;  //APlayerController->AcknowledgedPawn
	DWORD offset_root_component = 0x138; //AActor->RootComponent
	DWORD offset_actor_array = 0x98; //UNetConnection->OwningActor
	DWORD offset_actor_count = 0xa0; //UNetConnection->MaxPacket
	DWORD offset_actor_id = 0x18;
	DWORD offset_player_name = 0x308;
	DWORD offset_player_state = 0x248; //APawn->PlayerState
	DWORD offset_actor_mesh = 0x288; //ACharacter->Mesh
	DWORD offset_bone_array = 0x4B0;
	DWORD offset_component_to_world = 0x1c0;
	DWORD offset_ranged_weapon_component = 0x4c8;
	DWORD offset_equipped_weapon_type = 0x170;
	DWORD offset_relative_location = 0x11c; //USceneComponent->RelativeLocation
	DWORD offset_last_submit_time = 0x288;
	DWORD offset_last_render_time = 0x28C;
	DWORD offset_health = 0x688;
	DWORD offset_max_health = 0x56C;
};