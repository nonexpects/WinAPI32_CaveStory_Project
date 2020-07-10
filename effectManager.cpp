#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

HRESULT effectManager::init()
{
	v_allFx.clear();

	return S_OK;
}

void effectManager::release()
{
	i_fxList i_list;
	for (vi_allFx = v_allFx.begin(); vi_allFx != v_allFx.end(); ++vi_allFx)
	{
		for (i_list = vi_allFx->begin(); i_list != vi_allFx->end(); ++i_list)
		{
			if (i_list->second.size() != 0)
			{
				i_effects i_fx;
				for (i_fx = i_list->second.begin(); i_fx != i_list->second.end(); ++i_fx)
				{
					(*i_fx)->release();
					SAFE_DELETE((*i_fx));
					i_fx = i_list->second.erase(i_fx);
				}
			}
		}
	}
	////////////////////////////effect 여러개 발사하기
	/////////////////////////// 데미지 들어가게 하기 

}

void effectManager::update()
{
	i_fxList i_list;

	for (vi_allFx = v_allFx.begin(); vi_allFx != v_allFx.end(); ++vi_allFx)
	{
		for (i_list = vi_allFx->begin(); i_list != vi_allFx->end(); ++i_list)
		{
			i_effects i_fx;
			for (i_fx = i_list->second.begin(); i_fx != i_list->second.end(); ++i_fx)
			{
				(*i_fx)->updateFX();
			}
		}
	}

}

void effectManager::render(string fxName, HDC hdc)
{
	char str[100];
	i_fxList i_list;

	for (vi_allFx = v_allFx.begin(); vi_allFx != v_allFx.end(); ++vi_allFx)
	{
		for (i_list = vi_allFx->begin(); i_list != vi_allFx->end(); ++i_list)
		{
			if (!(i_list->first == fxName)) break;

			i_effects i_fx;
			for (i_fx = i_list->second.begin(); i_fx != i_list->second.end(); ++i_fx)
			{
				(*i_fx)->render(hdc);
			}
		}
	}
}

void effectManager::play(string fxName, float x, float y, int count, bool loop, float time, float angle, bool movedir)
{
	i_fxList i_list;

	for(vi_allFx = v_allFx.begin(); vi_allFx != v_allFx.end(); ++ vi_allFx)
	{
		for (i_list = vi_allFx->begin(); i_list != vi_allFx->end(); ++i_list)
		{
			if (!(i_list->first == fxName)) break;

			i_effects i_fx;
			for (i_fx = i_list->second.begin(); i_fx != i_list->second.end(); ++i_fx)
			{
				if ((*i_fx)->IsRunning()) continue;
				(*i_fx)->startEffect(x, y, count, loop, time, angle, movedir);
				return;
			}
		}
	}

}

void effectManager::addEffect(string fxName, const char* imageName, float time, int buffer, int startFrameX, int startFrameY, int maxframeX, float speed, bool isTrail)
{
	image* img = IMAGEMANAGER->findImage(imageName);
	effects ef;
	fxList list;
	i_fxList i_list;

	int y = -1;

	for (int i = 0; i < buffer; i++)
	{
		ef.push_back(new effect);
		ef[i]->init(img, time, startFrameX, startFrameY, maxframeX, speed, isTrail);
	}

	list.insert(make_pair(fxName, ef));
	v_allFx.push_back(list);
	
}

void effectManager::offFX(string fxName)
{
	fxList list;
	i_fxList i_list;

	vi_allFx = v_allFx.begin();
	for (; vi_allFx != v_allFx.end(); ++vi_allFx)
	{
		list = *vi_allFx;
		i_list = list.find(fxName);
		if (i_list != list.end())
		{
			i_list->second[0]->FXoff();
			break;
		}
	}
	
}

void effectManager::numberPop(float x, float y, int num, float time)
{
	if (!popOn)
	{
		numberX = x;
		numberY = y;
		endY = y - 10;

		storeNum = num;
		popmaxTime = time;
		popOn = true;
	}
	else
	{
		popTime += TIMEMANAGER->getElapedTime();

		if (numberY > endY)
		{
			numberY--;
		}

		
		if (popTime > popmaxTime)
		{
			popOn = false;
			popTime = 0.f;
			storeNum = 0;
			numberX = numberY = 0.f;
		}
	}
	
}

void effectManager::popRender(HDC hdc)
{
	if (popOn)
	{
		if (storeNum >= 0)
		{
			IMAGEMANAGER->findImage("bg_maptool_subUI_X")->render(hdc, numberX - 20, numberY);
			if (abs(storeNum) > 9)
			{
				IMAGEMANAGER->findImage("ui_numbers")->frameRender(hdc, numberX, numberY, abs(storeNum) / 10, 0);
				IMAGEMANAGER->findImage("ui_numbers")->frameRender(hdc, numberX + 20, numberY, abs(storeNum) % 10, 0);
			}
			else
			{
				IMAGEMANAGER->findImage("ui_numbers")->frameRender(hdc, numberX, numberY, abs(storeNum) % 10, 0);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("bg_maptool_subUI_-")->render(hdc, numberX - 20, numberY);
			if (abs(storeNum) > 9)
			{
				IMAGEMANAGER->findImage("ui_numbers")->frameRender(hdc, numberX, numberY, abs(storeNum) / 10, 1);
				IMAGEMANAGER->findImage("ui_numbers")->frameRender(hdc, numberX + 20, numberY, abs(storeNum) % 10, 1);
			}
			else
			{
				IMAGEMANAGER->findImage("ui_numbers")->frameRender(hdc, numberX, numberY, abs(storeNum) % 10, 1);
			}
		}
	}
}

bool effectManager::getIsRunning(string fxName)
{
	i_fxList i_list;
	i_effects i_fx;

	for (vi_allFx = v_allFx.begin(); vi_allFx != v_allFx.end(); ++vi_allFx)
	{
		for (i_list = vi_allFx->begin(); i_list != vi_allFx->end(); ++i_list)
		{
			if (!(i_list->first == fxName)) break;

			for (i_fx = i_list->second.begin(); i_fx != i_list->second.end(); ++i_fx)
			{
				if ((*i_fx)->IsRunning()) return true;
				else return false;
			}
		}
	}

	return false;
}
