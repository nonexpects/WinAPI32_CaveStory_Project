#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();
	_count = 0;

	return S_OK;
}

void loadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();
	_count++;

	
	if (_loading->loadingDone())
	{
		if (_count % 50 == 0 && _count != 0)
		{
			SCENEMANAGER->loadScene("startScene");
		}
	}
}

void loadingScene::render()
{
	_loading->render();
}

void loadingScene::loadingImage()
{
	//===================================================타 이 틀 씬 관 련====================================================================//
	//BG 이미지
	_loading->loadImage("bg_title", "Images/title/bg_title.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("bg_bossMap", "Images/tile/bkFog.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("bg_title_cloud01", "Images/title/bg_cloud01.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("bg_title_cloud02", "Images/title/bg_cloud02.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("bg_title_cloud03", "Images/title/bg_cloud03.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("bg_title_cloud04", "Images/title/bg_cloud04.bmp", WINSIZEX, WINSIZEY);

	//타이틀 로고
	_loading->loadImage("logo_title", "Images/title/logo_title.bmp", 762, 170);
	//타이틀 메뉴
	_loading->loadImage("title_menu", "Images/title/title_menu.bmp", 450, 350);
	
	//=====================================================맵 툴 관 련======================================================================//
	//맵툴 기본 타일 이미지
	_loading->loadImage("tile_default", "Images/tile/bk0.bmp", 64, 64);

	//맵툴 배경 이미지
	_loading->loadFrameImage("tile_bg_black", "Images/tile/bk0.bmp", 128, 128, 2, 2);
	_loading->loadImage("tile_bg_red", "Images/tile/bkRed.bmp", 64, 64);
	_loading->loadFrameImage("tile_bg_gard", "Images/tile/bkGard.bmp", 128, 128, 2, 2);
	_loading->loadFrameImage("tile_bg_gray", "Images/tile/bkGray.bmp", 128, 128, 2, 2);
	_loading->loadFrameImage("tile_bg_blue", "Images/tile/bkBlue.bmp", 128, 128, 2, 2);
	_loading->loadFrameImage("tile_bg_green", "Images/tile/bkGreen.bmp", 128, 128, 2, 2);
	_loading->loadFrameImage("tile_bg_maze", "Images/tile/bkMaze.bmp", 128, 128, 2, 2);

	//맵툴 타일 선택 이미지
	_loading->loadImage("dragImage", "Images/tile/dragRect.bmp", 64, 64);

	//BGMAP
	_loading->loadImage("bg_blue", "Images/tile/bg_tile_blue.bmp", 1280, 960);
	_loading->loadImage("bg_blue_2", "Images/tile/bg_tile_blue_2.bmp", 3200, 3200);
	_loading->loadImage("bg_black", "Images/tile/bg_tile_black.bmp", 1280, 960);
	_loading->loadImage("bg_green", "Images/tile/bg_tile_green.bmp", 1280, 960);

	//맵툴 샘플 타일 이미지
	_loading->loadFrameImage("sampleTileMap_s", "Images/tile/sampleTileMap.bmp", 256, 544, 16, 34);
	_loading->loadFrameImage("sampleTileMap", "Images/tile/base_tile.bmp", 1024, 2176, 16, 34, true, RGB(0,0,0));
	_loading->loadFrameImage("bgTileMap", "Images/tile/bg_tile.bmp", 384, 128, 6, 2, false);
	_loading->loadFrameImage("collisionMap", "Images/tile/magenta_collision.bmp", 256, 320, 4, 5, true, RGB(0, 0, 0));

	//맵툴 UI BG
	_loading->loadImage("bg_maptool_UI", "Images/mapToolui/bg_mapTool_UI.bmp", 300, WINSIZEY);
	_loading->loadImage("bg_maptool_sample_UI", "Images/mapToolui/bg_mapTool_sample_UI.bmp", 280, 450);
	_loading->loadImage("bg_maptool_subUI", "Images/mapToolui/subui_bg.bmp", 280, 280);
	_loading->loadImage("bg_maptool_subUI_X", "Images/mapToolui/subui_X.bmp", 20, 20);
	_loading->loadImage("bg_maptool_subUI_-", "Images/mapToolui/subui_-.bmp", 20, 20);

	//맵툴 UI 이미지
	_loading->loadFrameImage("maptool_ui_save", "Images/mapToolui/ui_save.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_load", "Images/mapToolui/ui_load.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_erase", "Images/mapToolui/ui_erase.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_bgSelect", "Images/mapToolui/ui_bg.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_reset", "Images/mapToolui/ui_reset.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_terrain", "Images/mapToolui/ui_terrain.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_object", "Images/mapToolui/ui_object.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_enemy", "Images/mapToolui/ui_enemy.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_collision", "Images/mapToolui/ui_collision.bmp", 200, 40, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_black", "Images/mapToolui/ui_bgMap_black.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_red", "Images/mapToolui/ui_bgMap_red.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_blue", "Images/mapToolui/ui_bgMap_blue.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_green", "Images/mapToolui/ui_bgMap_green.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_maze", "Images/mapToolui/ui_bgMap_maze.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_gray", "Images/mapToolui/ui_bgMap_gray.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("maptool_ui_bg_gard", "Images/mapToolui/ui_bgMap_gard.bmp", 64, 32, 2, 1);
	
	//맵툴 화살표
	_loading->loadImage("arrow_left", "Images/mapToolui/arrow_left.bmp", 32, 32);
	_loading->loadImage("arrow_right", "Images/mapToolui/arrow_right.bmp", 32, 32);
	_loading->loadImage("arrow_up", "Images/mapToolui/subui_X.bmp", 32, 32);
	_loading->loadImage("arrow_down", "Images/mapToolui/subui_-.bmp", 32, 32);

	//===================================================플 레 이 어 관 련===================================================================//
	//캐릭터 이미지
	_loading->loadFrameImage("player_idle", "Images/char/Char_idle.bmp", 128, 64, 2, 1);

	//캐릭터 프레임 이미지
	_loading->loadFrameImage("player_jump", "Images/char/Char_Jump.bmp", 128, 128, 2, 2);
	_loading->loadFrameImage("player_run", "Images/char/Char_run.bmp", 256, 128, 4, 2);
	_loading->loadFrameImage("player_run_up", "Images/char/Char_run_up.bmp", 256, 128, 4, 2);
	_loading->loadFrameImage("player_up", "Images/char/char_stay_up.bmp", 64, 128, 1, 2);
	_loading->loadFrameImage("player_down", "Images/char/char_stay_down.bmp", 64, 128, 1, 2);
	_loading->loadFrameImage("player_jump_down", "Images/char/Char_Jump_down.bmp", 64, 128, 1, 2);

	//메뉴용 캐릭터 이미지 
	//_loading->loadFrameImage("player_run_s", "Images/char/Char_run.bmp", 232, 110, 4, 2);

	//===================================================에 너 미 관 련===================================================================//
	
	_loading->loadFrameImage("critter", "Images/mob/mob_1.bmp", 192, 128, 3, 2);
	_loading->loadFrameImage("beetle", "Images/mob/mob_flying_1.bmp", 128, 128, 2, 2);
	_loading->loadFrameImage("beetle_FLY", "Images/mob/mob_flying_1_2.bmp", 192, 128, 3, 2);
	_loading->loadFrameImage("basu", "Images/mob/mob_flying_2.bmp", 258, 192, 3, 2);
	_loading->loadFrameImage("basu_bullet", "Images/mob/mob_flying_bullet.bmp",256, 64, 4, 1);
	_loading->loadFrameImage("behemoth", "Images/mob/mob_2.bmp", 1020, 256, 6, 2);
	_loading->loadFrameImage("basil", "Images/mob/mob_3.bmp", 256, 64, 2, 1);
	//=================================================== 보 스 ===================================================================//

	_loading->loadFrameImage("boss", "Images/boss/boss_1.bmp", 512, 128, 8, 2);
	_loading->loadFrameImage("boss_fade_L", "Images/boss/boss_1_fade_L.bmp", 64, 64, 1, 1);
	_loading->loadFrameImage("boss_fade_R", "Images/boss/boss_1_fade_R.bmp", 64, 64, 1, 1);
	_loading->loadImage("boss_ring", "Images/boss/boss_1_ring.bmp", 64, 64);
	_loading->loadFrameImage("boss_bird", "Images/boss/boss_1_bird.bmp", 192, 128, 3, 2);
	_loading->loadFrameImage("boss_bullet01", "Images/boss/boss_1_bullet01.bmp", 192, 64, 3, 1);
	_loading->loadFrameImage("boss_bullet02", "Images/boss/boss_1_bullet02.bmp", 192, 64, 3, 1);
	_loading->loadFrameImage("boss_bullet03", "Images/boss/boss_1_bullet02_1.bmp", 64, 128, 1, 1);

	//==================================================================================================================================//

	_loading->loadFrameImage("ui_weapon", "Images/ui/ui_arms.bmp", 384, 64, 6, 1);
	_loading->loadFrameImage("weapon", "Images/char/arms.bmp", 576, 384, 6, 6);
	_loading->loadImage("ui_hp_bar_back", "Images/ui/ui_hp_bar_back.bmp", 150, 32);
	_loading->loadImage("ui_hp_bar_front", "Images/ui/ui_hp_bar_front.bmp", 147, 32);
	_loading->loadImage("ui_boss_hp_bar_back", "Images/ui/ui_hp_bar_back.bmp", 850, 32);
	_loading->loadImage("ui_boss_hp_bar_front", "Images/ui/ui_hp_bar_front.bmp", 850, 32);
	_loading->loadImage("ui_boss_bar_middle", "Images/ui/ui_bar_middle.bmp", 850, 32);
	_loading->loadImage("ui_lv", "Images/ui/ui_Lv.bmp", 60, 32);
	_loading->loadImage("ui_hp", "Images/ui/ui_Hp.bmp", 90, 32);
	_loading->loadImage("ui_exp_bar_back", "Images/ui/ui_exp_bar_back.bmp", 150, 32);
	_loading->loadImage("ui_exp_bar_front", "Images/ui/ui_exp_bar_front.bmp", 150, 32);
	_loading->loadImage("ui_exp_max", "Images/ui/ui_max.bmp", 150, 32);
	_loading->loadImage("ui_bar_middle", "Images/ui/ui_bar_middle.bmp", 150, 32);
	_loading->loadImage("ui_slash", "Images/ui/ui_slash.bmp", 32, 32);
	_loading->loadImage("ui_bullet_count", "Images/ui/ui_bullet_count.bmp", 64, 32);

	_loading->loadImage("textBox", "Images/ui/TextBox.bmp", 800, 200);
	_loading->loadImage("bossBox", "Images/ui/TextBox.bmp", 1000, 50);
	_loading->loadImage("bossHp", "Images/ui/boss_hp.bmp", 128, 32);
	_loading->loadImage("choiceBox", "Images/ui/choiceBox.bmp", 308, 104);
	_loading->loadImage("choiceArrow", "Images/ui/choiceArrow.bmp", 52, 40);
	_loading->loadImage("gameClear", "Images/clearImage.bmp", WINSIZEX, WINSIZEY);
	
	//숫자 이미지
	_loading->loadFrameImage("damage_numbers", "Images/ui/damage_numbers.bmp", 330, 60, 11, 2);
	_loading->loadFrameImage("ui_numbers", "Images/ui/ui_numbers.bmp", 300, 60, 10, 2);

	//==================================================================================================================================//
	
	_loading->loadFrameImage("pollyStar_lv1", "Images/bullets/b_pollyStar_lv1.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("pollyStar_lv2", "Images/bullets/b_pollyStar_lv2.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("pollyStar_lv3", "Images/bullets/b_pollyStar_lv3.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("fireball_lv1", "Images/bullets/b_fireball_lv1.bmp", 200, 100, 4, 2);
	_loading->loadFrameImage("fireball_lv2", "Images/bullets/b_fireball_lv2-3_base.bmp", 192, 64, 3, 1);
	_loading->loadFrameImage("missile_lv1", "Images/bullets/b_missile_lv1.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("missile_lv2", "Images/bullets/b_missile_lv2.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("missile_lv3", "Images/bullets/b_missile_lv3.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("machine_lv1", "Images/bullets/b_machine_lv1.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("machine_lv2", "Images/bullets/b_machine_lv2.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("machine_lv3", "Images/bullets/b_machine_lv3.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("blade_lv1", "Images/bullets/b_blade_lv1.bmp", 512, 64, 8, 1);

	//===============================================아 이 템 관 련============================================================================//

	_loading->loadFrameImage("i_exp", "Images/item/i_exp.bmp", 384, 64, 6, 1);
	_loading->loadFrameImage("i_life_1", "Images/item/i_getlife_1.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("i_life_3", "Images/item/i_getlife_3.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("i_missile_1", "Images/item/i_getmissile_1.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("i_missile_3", "Images/item/i_getmissile_3.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("i_lifefill", "Images/item/i_lifefill.bmp", 128, 64, 2, 1);
	_loading->loadFrameImage("i_save", "Images/item/i_save.bmp", 512, 64, 8, 1);
	_loading->loadFrameImage("i_computer", "Images/item/i_computer.bmp", 510, 128, 3, 1);
	_loading->loadFrameImage("i_log_computer", "Images/item/i_log_computer.bmp", 128, 96, 2, 1);
	_loading->loadFrameImage("i_teleporter", "Images/item/i_teleporter.bmp", 192, 128, 2, 1);
	_loading->loadImage("i_door", "Images/item/i_door.bmp", 64, 96);
	//===============================================이 펙 트 관 련============================================================================//

	_loading->loadFrameImage("fx_smoke1", "Images/effect/fx_smoke.bmp", 256, 32, 8, 1);
	_loading->loadFrameImage("fx_smoke1_B", "Images/effect/fx_smoke.bmp", 512, 64, 8, 1);
	_loading->loadFrameImage("fx_smoke2", "Images/effect/fx_smoke2.bmp", 384, 64, 6, 1);
	_loading->loadFrameImage("fx_shoot", "Images/effect/fx_shoot.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("fx_collision", "Images/effect/fx_collision.bmp", 256, 64, 4, 1);
	_loading->loadFrameImage("fx_lv_down", "Images/effect/fx_level_down.bmp", 224, 32, 2, 1);
	_loading->loadFrameImage("fx_lv_up", "Images/effect/fx_level_up.bmp", 224, 32, 2, 1);
	_loading->loadFrameImage("fx_empty", "Images/effect/fx_empty.bmp", 320, 32, 2, 1);
	_loading->loadFrameImage("fx_damaged", "Images/effect/fx_damaged.bmp", 224, 32, 7, 1);
	_loading->loadFrameImage("fx_dead", "Images/effect/fx_dead.bmp", 256, 128, 2, 1);
	_loading->loadFrameImage("fx_dead_B", "Images/effect/fx_dead.bmp", 512, 256, 2, 1);
	_loading->loadFrameImage("fx_booster", "Images/effect/fx_booster.bmp", 224, 32, 7, 1);
	_loading->loadFrameImage("fx_head", "Images/effect/fx_head.bmp", 64, 32, 2, 1);
	_loading->loadFrameImage("fx_question", "Images/effect/fx_questionMark.bmp", 64, 64, 1, 1);
	_loading->loadFrameImage("fx_water", "Images/effect/fx_water.bmp", 128, 160, 4, 5);

	_loading->loadFrameImage("fx_fireball_lv2", "Images/bullets/b_fireball_lv2.bmp", 192, 192, 3, 3);
	_loading->loadFrameImage("fx_fireball_lv3", "Images/bullets/b_fireball_lv3.bmp", 192, 192, 3, 3);
	_loading->loadFrameImage("fx_machine_lv2_w", "Images/bullets/b_machine_lv2_trail_left.bmp", 128, 64, 3, 1);
	_loading->loadFrameImage("fx_machine_lv2_h", "Images/bullets/b_machine_lv2_trail_up.bmp", 64, 128, 1, 3);
	_loading->loadFrameImage("fx_machine_lv3", "Images/bullets/b_machine_lv3_base.bmp", 256, 64, 2, 1);
	_loading->loadFrameImage("fx_machine_lv3_1", "Images/bullets/b_machine_lv3_base_UD.bmp", 128, 128, 2, 1);
}

void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("start_intro", "SOUND/curly_intro.ogg", false, false);
	SOUNDMANAGER->addSound("start_loop", "SOUND/curly_loop.ogg", false, true);
	SOUNDMANAGER->addSound("wanpaku_intro", "SOUND/wanpaku_intro.ogg", false, false);
	SOUNDMANAGER->addSound("wanpaku_loop", "SOUND/wanpaku_loop.ogg", false, true);
	SOUNDMANAGER->addSound("anzen_intro", "SOUND/anzen_intro.ogg", false, false);
	SOUNDMANAGER->addSound("anzen_loop", "SOUND/anzen_loop.ogg", false, true);
	SOUNDMANAGER->addSound("lastcave2_intro", "SOUND/lastcave2_intro.ogg", false, false);
	SOUNDMANAGER->addSound("lastcave2_loop", "SOUND/lastcave2_loop.ogg", false, true);
	SOUNDMANAGER->addSound("ending", "SOUND/curly.ogg", false, true);
//================================sound effect======================================//
	SOUNDMANAGER->addSound("shootingSound1", "SOUND/shooting.mp3", true, false);
	SOUNDMANAGER->addSound("shootingSound_polar", "SOUND/polarStar_shoot.mp3", true, false);
	SOUNDMANAGER->addSound("hitSound1", "SOUND/wallColl.mp3", true, false);
	SOUNDMANAGER->addSound("hitSound_all", "SOUND/hit_wall.mp3", true, false);
	SOUNDMANAGER->addSound("hitSound_exp", "SOUND/explosion.mp3", true, false);
	SOUNDMANAGER->addSound("fill", "SOUND/Fill.mp3", true, false);
	SOUNDMANAGER->addSound("getExp", "SOUND/getExp.mp3", true, false);
	SOUNDMANAGER->addSound("jump", "SOUND/jump.mp3", true, false);
	SOUNDMANAGER->addSound("expColl", "SOUND/expColl2.mp3", true, false);
	SOUNDMANAGER->addSound("LevelUp", "SOUND/LevelUp.mp3", true, false);
	SOUNDMANAGER->addSound("LevelDown", "SOUND/LevelDown.mp3", true, false);
	SOUNDMANAGER->addSound("teleport", "SOUND/teleport.mp3", true, false);
	SOUNDMANAGER->addSound("player_dead", "SOUND/player_dead.mp3", true, false);
	SOUNDMANAGER->addSound("enemy_dead", "SOUND/enemy_dead.mp3", true, false);
	SOUNDMANAGER->addSound("enemy_damaged", "SOUND/enemy_damaged.mp3", true, false);
	SOUNDMANAGER->addSound("walksound", "SOUND/walksound.mp3", true, false);
	SOUNDMANAGER->addSound("select", "SOUND/select.mp3", true, false);
	SOUNDMANAGER->addSound("behemoth_angry", "SOUND/behemoth_angry.mp3", true, false);

}
