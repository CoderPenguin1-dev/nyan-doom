//
// Copyright(C) 2022 by Ryan Krafnick
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Penguino Player Speed HUD Component
//

#include "base.h"
#include "../../p_user.h"

#include "player_speed.h"

typedef struct {
  char label[16];
  dsda_text_t component;
} local_component_t;

static local_component_t* local;

static void dsda_UpdateComponentText(char* str, size_t max_size) {
  static int old_gametic;
  double speed, vx, vy, vz;
  const player_t *player = &players[displayplayer];

  // Adapted from International Doom (doom/id_func.c 691-697)
  if (gametic > old_gametic)
  {
    vx = (double) (player->mo->x - player->mo->PrevX) / FRACUNIT;
    vy = (double) (player->mo->y - player->mo->PrevY) / FRACUNIT;
    vz = (double) (player->mo->z - player->mo->PrevZ) / FRACUNIT;

    speed = sqrt(vx * vx + vy * vy + vz * vz) * TICRATE;
    old_gametic = gametic;
  }

  snprintf(
    str,
    max_size,
    "%s%s%.0f",
    local->label,
    dsda_TextColor(penguino_tc_exhud_player_speed),
    speed
  );
}

void penguino_InitPlayerSpeedHC(int x_offset, int y_offset, int vpt, int* args, int arg_count, void** data) {
  *data = Z_Calloc(1, sizeof(local_component_t));
  local = *data;
  snprintf(local->label, sizeof(local->label), "%sPLAYER SPEED ", dsda_TextColor(penguino_tc_exhud_player_speed_label));

  dsda_InitBlockyHC(&local->component, x_offset, y_offset, vpt);
}

void penguino_UpdatePlayerSpeedHC(void* data) {
  local = data;

  dsda_UpdateComponentText(local->component.msg, sizeof(local->component.msg));
  dsda_RefreshHudText(&local->component);
}

void penguino_DrawPlayerSpeedHC(void* data) {
  local = data;

  dsda_DrawBasicShadowedText(&local->component);
}
