#include "stdafx.h"
#include "MapToolScene.h"


void MapToolScene::input_SelectMapGrid() {

	bool ctrlClicked = KEYMANAGER->isStayKeyDown(VK_LCONTROL);

	if (ctrlClicked && KEYMANAGER->isOnceKeyDown('D')) {
		_vMapSelected.clear();
	}

	if (!ctrlClicked) {
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
			for (int i = 0; i < GRIDNUM; i++) {
				if (PtInRect(&_mapRect[i].rc, _ptMouse)) {
					_vMapSelected.clear();
					_vMapSelected.push_back(_mapRect[i]);
					_selectRangeRect = RectMake(_ptMouse.x, _ptMouse.y, 0, 0);
					_selectRangePoint = { _ptMouse.x, _ptMouse.y };
					break;
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RBUTTON)) {
			int left = (_selectRangePoint.x <= _ptMouse.x) ? _selectRangePoint.x : _ptMouse.x;
			int right = (_selectRangePoint.x > _ptMouse.x) ? _selectRangePoint.x : _ptMouse.x;
			int top = (_selectRangePoint.y <= _ptMouse.y) ? _selectRangePoint.y : _ptMouse.y;
			int bottom = (_selectRangePoint.y > _ptMouse.y) ? _selectRangePoint.y : _ptMouse.y;

			_selectRangeRect = { left, top, right, bottom };

			RECT temp;
			_vMapSelected.clear();

			for (int i = 0; i < GRIDNUM; i++) {
				if (IntersectRect(&temp, &_selectRangeRect, &_mapRect[i].rc))
				{
					_vMapSelected.push_back(_mapRect[i]);
				}
			}
		}
	}
	else {
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
			for (int i = 0; i < GRIDNUM; i++) {
				if (PtInRect(&_mapRect[i].rc, _ptMouse)) {
					for (_viMapSelected = _vMapSelected.begin(); _viMapSelected != _vMapSelected.end();) {
						if (_viMapSelected->index == _mapRect[i].index) {
							_vMapSelected.erase(_viMapSelected);
							break;
						}
						else
							++_viMapSelected;
					}
					_vMapSelected.push_back(_mapRect[i]);
					_selectRangeRect = RectMake(_ptMouse.x, _ptMouse.y, 0, 0);
					_selectRangePoint = { _ptMouse.x, _ptMouse.y };
					break;
				}
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RBUTTON)) {
			int left = (_selectRangePoint.x <= _ptMouse.x) ? _selectRangePoint.x : _ptMouse.x;
			int right = (_selectRangePoint.x > _ptMouse.x) ? _selectRangePoint.x : _ptMouse.x;
			int top = (_selectRangePoint.y <= _ptMouse.y) ? _selectRangePoint.y : _ptMouse.y;
			int bottom = (_selectRangePoint.y > _ptMouse.y) ? _selectRangePoint.y : _ptMouse.y;

			_selectRangeRect = { left, top, right, bottom };

			RECT temp;
			for (int i = 0; i < GRIDNUM; i++) {
				if (IntersectRect(&temp, &_selectRangeRect, &_mapRect[i].rc))
				{
					for (_viMapSelected = _vMapSelected.begin(); _viMapSelected != _vMapSelected.end();) {
						if (_viMapSelected->index == _mapRect[i].index) {
							_vMapSelected.erase(_viMapSelected);
							break;
						}
						else
							++_viMapSelected;
					}
					_vMapSelected.push_back(_mapRect[i]);
				}
			}
		}
	}
}

void MapToolScene::input_ModeChange() {
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) { _inputLayer = LAYER_TILE;		_inputMode = MODE_FLOOR; }
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) { _inputLayer = LAYER_DECO;		_inputMode = MODE_NULL; }
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) { _inputLayer = LAYER_OBJ;		_inputMode = MODE_CHEST; }
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) { _inputLayer = LAYER_ITEM;		_inputMode = MODE_NULL; }
	if (KEYMANAGER->isOnceKeyDown(VK_F5)) { _inputLayer = LAYER_MONSTER;	_inputMode = MODE_NULL; }

	switch (_inputLayer) {
	case LAYER_TILE:
		if (KEYMANAGER->isOnceKeyDown('1')) {
			switch (_inputMode) {
			case MODE_FLOOR: _inputMode = MODE_WATER; break;
			case MODE_WATER: _inputMode = MODE_CHASM; break;
			default: _inputMode = MODE_FLOOR; break;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('2')) {
			switch (_inputMode) {
			case MODE_WALL: _inputMode = MODE_BARRICADE; break;
			case MODE_BARRICADE: _inputMode = MODE_STATUE; break;
			default: _inputMode = MODE_WALL; break;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('3')) {
			switch (_inputMode) {
			case MODE_DOOR: _inputMode = MODE_DOOR_LOCKED; break;
			default: _inputMode = MODE_DOOR; break;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('4')) {
			switch (_inputMode) {
			case MODE_GRASS: _inputMode = MODE_GRASS_UN; break;
			default: _inputMode = MODE_GRASS; break;
			}
		}		
		
		break;
	case LAYER_DECO:
		break;
		
	case LAYER_OBJ:
		if (KEYMANAGER->isOnceKeyDown('1')) {
			_inputMode = MODE_CHEST;

		}
		if (KEYMANAGER->isOnceKeyDown('2')) {
			switch (_inputMode) {
			case MODE_STAIR_START: _inputMode = MODE_STAIR_END; break;
			default: _inputMode = MODE_STAIR_START; break;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('3')) {
			_inputMode = MODE_POT;

		}
		if (KEYMANAGER->isOnceKeyDown('4')) {
			_inputMode = MODE_WELL;
		}
		if (KEYMANAGER->isOnceKeyDown('5')) {
			_inputMode = MODE_TRAP;
		}
		break;
	case LAYER_ITEM:
		break;
	case LAYER_MONSTER:
		break;
		
	}


	if (KEYMANAGER->isOnceKeyDown('0')) {
		switch (_inputMode) {
		case MODE_VIEWING: _inputMode = MODE_VIEWING_TILE; break;
		default: _inputMode = MODE_VIEWING; break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E')) _inputMode = MODE_DELET;
	
}

void MapToolScene::input_AddTile() {

	for (int i = 0; i < GRIDNUM; i++) {
		if (PtInRect(&_mapRect[i].rc, _ptMouse)) {

			//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _vMapSelected.size != 0) {
			//		if (_sele 
			//	}

			if (_inputMode == MODE_DELET) {			//지우기 모드 : 이미 있는 경우를 확인, 지운다.
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					int indexX = i % GRIDX + _cameraX;
					int indexY = i / GRIDX + _cameraY;
					switch (_inputLayer) {
					case LAYER_TILE:
						for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
							if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
								_viMapTile = _vMapTile.erase(_viMapTile);
								return;
							}
							else
								_viMapTile++;
						}
						break;
					case LAYER_DECO:
						for (_viDecoTile = _vDecoTile.begin(); _viDecoTile != _vDecoTile.end();) {
							if (_viDecoTile->destX == indexX && _viDecoTile->destY == indexY) {
								_viDecoTile = _vDecoTile.erase(_viDecoTile);
								return;
							}
							else
								_viDecoTile++;
						}
						break;
					case LAYER_OBJ:
						for (_viObj = _vObj.begin(); _viObj != _vObj.end();) {
							if (_viObj->destX == indexX && _viObj->destY == indexY) {
								_viObj = _vObj.erase(_viObj);
								return;
							}
							else
								_viObj++;
						}
						break;
					case LAYER_ITEM:
						for (_viItem = _vItem.begin(); _viItem != _vItem.end();) {
							if (_viItem->destX == indexX && _viItem->destY == indexY) {
								_viItem = _vItem.erase(_viItem);
								return;
							}
							else
								_viItem++;
						}

						break;

					}
				}
				break;
			}

			if (!_paletSelected.empty()) {
				if (_inputMode == MODE_VIEWING || _inputMode == MODE_VIEWING_TILE) return; //읽기 모드   : 아무것도 못한다

				_showTile = true;					// 현재 선택한 타일을 보여주기
				_showTileIndex = i;



				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					int indexX = i % GRIDX + _cameraX;
					int indexY = i / GRIDX + _cameraY;
					int paletIndex = _paletSelected[0].index;

					//팔레트 사이즈보다 큰걸 선택했으면 입력 못한다
					if (paletIndex > _vPaletTile.size()) return;




					//선택한 타일이 있다면 그 타일을 모두 채운다
					if (!_vMapSelected.empty()) {

						//선택한 범위 안쪽만 반응
						for (int j = 0; j < _vMapSelected.size(); j++) {
							if (_vMapSelected[j].index == _mapRect[i].index)
								break;
							if (j == _vMapSelected.size() - 1)
								return;
						}


						// 이미지 추가 모드
						if (_inputLayer == LAYER_DECO) {
							//이미 타일이 있는 경우 지운다
							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;
								for (_viDecoTile = _vDecoTile.begin(); _viDecoTile != _vDecoTile.end();) {
									if (_viDecoTile->destX == indexX && _viDecoTile->destY == indexY) {
										_viDecoTile = _vDecoTile.erase(_viDecoTile);
									}
									else
										_viDecoTile++;
								}
							}


							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;
								TILE inputTile;
								ZeroMemory(&inputTile, sizeof(TILE));
								inputTile.img = _vPaletTile[paletIndex].img;
								inputTile.sourX = _vPaletTile[paletIndex].sourX;
								inputTile.sourY = _vPaletTile[paletIndex].sourY;
								inputTile.destX = indexX;
								inputTile.destY = indexY;

								inputTile.terrain = TERRAIN_NULL;

								_vDecoTile.push_back(inputTile);
							}
						}

						//타일 추가 모드
						else if (_inputLayer == LAYER_TILE) {
							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;
								for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
									if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
										_viMapTile = _vMapTile.erase(_viMapTile);
									}
									else _viMapTile++;
								}
							}

							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;

								TILE inputTile;
								ZeroMemory(&inputTile, sizeof(TILE));
								inputTile.img = _vPaletTile[paletIndex].img;
								inputTile.sourX = _vPaletTile[paletIndex].sourX;
								inputTile.sourY = _vPaletTile[paletIndex].sourY;
								inputTile.destX = indexX;
								inputTile.destY = indexY;

								switch (_inputMode)
								{
								case MODE_FLOOR:		inputTile.terrain = TERRAIN_FLOOR;				break;
								case MODE_WATER:		inputTile.terrain = TERRAIN_WATER;				break;
								case MODE_CHASM:		inputTile.terrain = TERRAIN_CHASM;				break;
								case MODE_GRASS:		inputTile.terrain = TERRAIN_GRASS;				break;
								case MODE_GRASS_UN:		inputTile.terrain = TERRAIN_GRASS_UNTOUCHED;	break;
								case MODE_WALL:			inputTile.terrain = TERRAIN_WALL;				break;
								case MODE_BARRICADE:	inputTile.terrain = TERRAIN_BARRICADE;			break;
								case MODE_STATUE:		inputTile.terrain = TERRAIN_STATUE;				break;
								case MODE_DOOR:			inputTile.terrain = TERRAIN_DOOR_CLOSED;		break;
								case MODE_DOOR_LOCKED:	inputTile.terrain = TERRAIN_DOOR_LOCKED;		break;
								}
								_vMapTile.push_back(inputTile);
							}
						}

						else if (_inputLayer == LAYER_OBJ) {
							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;
								for (_viObj = _vObj.begin(); _viObj != _vObj.end();) {
									if (_viObj->destX == indexX && _viObj->destY == indexY) {
										_viObj = _vObj.erase(_viObj);
									}
									else _viObj++;
								}
							}

							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;

								GAMEOBJECT inputObj;
								ZeroMemory(&inputObj, sizeof(GAMEOBJECT));
								inputObj.img = _vPaletTile[paletIndex].img;
								inputObj.sourX = _vPaletTile[paletIndex].sourX;
								inputObj.sourY = _vPaletTile[paletIndex].sourY;
								inputObj.destX = indexX;
								inputObj.destY = indexY;

								switch (_inputMode)
								{
								case MODE_CHEST:			inputObj.obj = OBJ_CHEST;				break;
								case MODE_STAIR_START:		inputObj.obj = OBJ_STAIR_START;			break;
								case MODE_STAIR_END:		inputObj.obj = OBJ_STAIR_END;			break;
								case MODE_POT:				inputObj.obj = OBJ_POT;					break;
								case MODE_WELL:				inputObj.obj = OBJ_WELL;				break;
								case MODE_TRAP:				inputObj.obj = OBJ_TRAP;				break;
								}
								_vObj.push_back(inputObj);
							}
						}

						//타일 추가 모드
						else if (_inputLayer == LAYER_ITEM) {
							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;
								for (_viItem = _vItem.begin(); _viItem != _vItem.end();) {
									if (_viItem->destX == indexX && _viItem->destY == indexY) {
										_viItem = _vItem.erase(_viItem);
									}
									else _viItem++;
								}
							}

							for (int j = 0; j < _vMapSelected.size(); j++) {
								int indexX = _vMapSelected[j].index % GRIDX + _cameraX;
								int indexY = _vMapSelected[j].index / GRIDX + _cameraY;

								TILE inputTile;
								ZeroMemory(&inputTile, sizeof(TILE));
								inputTile.img = _vPaletTile[paletIndex].img;
								inputTile.destX = indexX;
								inputTile.destY = indexY;

								_vItem.push_back(inputTile);
							}
						}
					}

					else {

						// 이미지 추가 모드
						if (_inputLayer == LAYER_DECO) {

							//이미 타일이 있는 경우 지운다
							for (_viDecoTile = _vDecoTile.begin(); _viDecoTile != _vDecoTile.end();) {
								if (_viDecoTile->destX == indexX && _viDecoTile->destY == indexY) {
									_viDecoTile = _vDecoTile.erase(_viDecoTile);
								}
								else
									_viDecoTile++;
							}

							TILE inputTile;
							ZeroMemory(&inputTile, sizeof(TILE));
							inputTile.img = _vPaletTile[paletIndex].img;
							inputTile.sourX = _vPaletTile[paletIndex].sourX;
							inputTile.sourY = _vPaletTile[paletIndex].sourY;
							inputTile.destX = indexX;
							inputTile.destY = indexY;

							inputTile.terrain = TERRAIN_NULL;

							_vDecoTile.push_back(inputTile);
						}


						// 타일 추가 모드
						else if (_inputLayer == LAYER_TILE) {
							//이미 타일이 있는 경우 지운다
							for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
								if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
									_viMapTile = _vMapTile.erase(_viMapTile);
								}
								else
									_viMapTile++;
							}

							TILE inputTile;
							ZeroMemory(&inputTile, sizeof(TILE));
							inputTile.img = _vPaletTile[paletIndex].img;
							inputTile.sourX = _vPaletTile[paletIndex].sourX;
							inputTile.sourY = _vPaletTile[paletIndex].sourY;
							inputTile.destX = indexX;
							inputTile.destY = indexY;

							switch (_inputMode)
							{
							case MODE_FLOOR:		inputTile.terrain = TERRAIN_FLOOR;				break;
							case MODE_WATER:		inputTile.terrain = TERRAIN_WATER;				break;
							case MODE_CHASM:		inputTile.terrain = TERRAIN_CHASM;				break;
							case MODE_GRASS:		inputTile.terrain = TERRAIN_GRASS;				break;
							case MODE_GRASS_UN:		inputTile.terrain = TERRAIN_GRASS_UNTOUCHED;	break;
							case MODE_WALL:			inputTile.terrain = TERRAIN_WALL;				break;
							case MODE_BARRICADE:	inputTile.terrain = TERRAIN_BARRICADE;			break;
							case MODE_STATUE:		inputTile.terrain = TERRAIN_STATUE;				break;
							case MODE_DOOR:			inputTile.terrain = TERRAIN_DOOR_CLOSED;		break;
							case MODE_DOOR_LOCKED:	inputTile.terrain = TERRAIN_DOOR_LOCKED;		break;
							}
							
							_vMapTile.push_back(inputTile);
						}

						else if (_inputLayer == LAYER_OBJ) {
							
							//이미 타일이 있는 경우 지운다
							for (_viObj = _vObj.begin(); _viObj != _vObj.end();) {
								if (_viObj->destX == indexX && _viObj->destY == indexY) {
									_viObj = _vObj.erase(_viObj);
								}
								else _viObj++;
							}

							GAMEOBJECT inputObj;
							ZeroMemory(&inputObj, sizeof(GAMEOBJECT));
							inputObj.img = _vPaletTile[paletIndex].img;
							inputObj.sourX = _vPaletTile[paletIndex].sourX;
							inputObj.sourY = _vPaletTile[paletIndex].sourY;
							inputObj.destX = indexX;
							inputObj.destY = indexY;

							switch (_inputMode)
							{
							case MODE_CHEST:			inputObj.obj = OBJ_CHEST;				break;
							case MODE_STAIR_START:		inputObj.obj = OBJ_STAIR_START;			break;
							case MODE_STAIR_END:		inputObj.obj = OBJ_STAIR_END;			break;
							case MODE_POT:				inputObj.obj = OBJ_POT;					break;
							case MODE_WELL:				inputObj.obj = OBJ_WELL;				break;
							case MODE_TRAP:				inputObj.obj = OBJ_TRAP;				break;
							}
							_vObj.push_back(inputObj);
						}


						// 타일 추가 모드
						else if (_inputLayer == LAYER_ITEM) {
							//이미 타일이 있는 경우 지운다
							for (_viItem = _vItem.begin(); _viItem != _vItem.end();) {
								if (_viItem->destX == indexX && _viItem->destY == indexY) {
									_viItem = _vItem.erase(_viItem);
								}
								else
									_viItem++;
							}

							TILE inputTile;
							ZeroMemory(&inputTile, sizeof(TILE));
							inputTile.img = _vPaletTile[paletIndex].img;
							inputTile.destX = indexX;
							inputTile.destY = indexY;

							_vItem.push_back(inputTile);
						}
					}
				}
				//_vMapSelected.clear();
				//_vMapSelected.push_back(_mapRect[i]);
				break;
			}
		}
		else _showTile = false;		// 현재 선택한 타일을 보여주지 않음
	}
}

void MapToolScene::input_ClickPalet() {

	for (int i = 0; i < PALETTENUM; i++) {
		if (PtInRect(&_paletRect[i].rc, _ptMouse)) {
			if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				S_TILE selectTile;

				int paletIndex = _paletRect[i].index + _paletPage * PALETTENUM;

				if (paletIndex >= _vPaletTile.size()) break;

				selectTile.img = _vPaletTile[paletIndex].img; // 팔레트는 이미지 하나만 갖고 있다
				selectTile.index = paletIndex;
				selectTile.rc = _paletRect[i].rc;

				_paletSelected.clear();
				_paletSelected.push_back(selectTile);
				break;
			}

			else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				S_TILE selectTile;

				int paletIndex = _paletRect[i].index + _paletPage * PALETTENUM;

				if (paletIndex >= _vPaletTile.size()) break;

				selectTile.img = _vPaletTile[paletIndex].img;
				selectTile.index = paletIndex;
				selectTile.rc = _paletRect[i].rc;

				_paletSelected.clear();
				_paletSelected.push_back(selectTile);
				break;
			}

		}
	}
};

void MapToolScene::input_ClickButton() {
	for (int i = 0; i < BUTTONNUM; i++) {
		if (PtInRect(&_buttonRect[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))  _buttonRect[i].isClicked = true;

			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _buttonRect[i].isClicked) {
				switch (i) {
				case 0:
					SCENEMANAGER->changeScene("메인메뉴씬");
					break;

				case 1:	if (_cameraY > 0)	cameraMove(0, -1);	break;
				case 2:						cameraMove(0, 1);	break;
				case 3:	if (_cameraX > 0)	cameraMove(-1, 0);	break;
				case 4:						cameraMove(1, 0);	break;

				case 5:
					if (_paletPage > 0) {
						_paletPage--;
						_paletSelected.clear();
						_showTile = false;
					}
					break;
				case 6:
					_paletPage++;
					_paletSelected.clear();
					_showTile = false;
					break;
				}
				_buttonRect[i].isClicked = false;
			}
		}
		else if (_buttonRect[i].isClicked) _buttonRect[i].isClicked = false;
	}
};



void MapToolScene::setItem(tagItem* item, ITEMNAME name)
{
	item->name = name;

	switch (name)
	{
	case NAME_OLD_SHORT_SWORD:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("old_short_sword");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->range = 1;
		item->minPoint = 1 + item->upgrade;
		item->maxPoint = 10 + item->upgrade * 2;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_SHORT_SWORD:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("short_sword");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 2 + item->upgrade;
		item->maxPoint = 15 + item->upgrade * 3;
		item->tier = 2;
		item->Power = 12;
		item->range = 1;
		break;
	case NAME_SWORD:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("sword");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 3 + item->upgrade;
		item->maxPoint = 20 + item->upgrade * 4;
		item->tier = 3;
		item->Power = 14;
		item->range = 1;
		break;
	case NAME_SPEAR:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("spear");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 2 + item->upgrade;
		item->maxPoint = 20 + item->upgrade * 3;
		item->tier = 2;
		item->Power = 12;
		item->range = 2;
		break;
	case NAME_BATTLE_AXE:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("battle_axe");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade;
		item->maxPoint = 20 + item->upgrade * 9;
		item->tier = 4;
		item->Power = 16;
		item->range = 1;
		item->stat.atk_lck = 5;
		break;
	case NAME_CLOTH:
		item->type = TYPE_ARMOR;
		item->img = IMAGEMANAGER->findImage("cloth");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 0 + item->upgrade;
		item->maxPoint = 2 + item->upgrade;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_LEATHER:
		item->type = TYPE_ARMOR;
		item->img = IMAGEMANAGER->findImage("leather");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 0 + item->upgrade;
		item->maxPoint = 4 + item->upgrade * 2;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_MAIL:
		item->type = TYPE_ARMOR;
		item->img = IMAGEMANAGER->findImage("mail");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 0 + item->upgrade;
		item->maxPoint = 6 + item->upgrade * 3;
		item->tier = 3;
		item->Power = 14;
		break;
	case NAME_LIOYDS_BEACON:
		item->type = TYPE_ACC;
		item->img = IMAGEMANAGER->findImage("acc_wand");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_beacon");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->maxCharge = 3 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_DART:						// 투척 무기 : 다트 =========================================== 
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_beacon");

		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_PARALYSIS_DART:
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile");

		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_POISON_DART:
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile");

		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_LIGHTNING:
		item->type = TYPE_WAND;
		item->img = IMAGEMANAGER->findImage("wand_lightning");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_lightning");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade * 2;
		item->maxPoint = 10 + item->upgrade * 2;
		item->maxCharge = 3 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_NORMAL:
		item->type = TYPE_WAND;
		item->img = IMAGEMANAGER->findImage("wand_normal");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade * 2;
		item->maxPoint = 6 + item->upgrade * 2;
		item->maxCharge = 4 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_POISON:
		item->type = TYPE_WAND;
		item->img = IMAGEMANAGER->findImage("wand_poison");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_poison");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade * 2;
		item->maxPoint = 6 + item->upgrade * 2;
		item->maxCharge = 3 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_EMERGENCY:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("emergency_food");
		item->contentsHide = false;
		item->minPoint = 220;
		break;
	case NAME_PASTY:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("pasty");
		item->contentsHide = false;
		item->minPoint = 300;
		break;
	case NAME_UNKNOWN_MEAT:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("meat_unknown");
		item->contentsHide = false;
		item->minPoint = 80;
		break;
	case NAME_COOKED_MEAT:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("meat_cooked");
		item->contentsHide = false;
		item->minPoint = 80;
		break;
	case NAME_FROZEN_MEAT:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("meat_frozen");
		item->contentsHide = false;
		item->minPoint = 80;
		break;
	case NAME_BOTTLE:		// ===============포션 ===================
		item->type = TYPE_POTION;
		item->img = IMAGEMANAGER->findImage("potion_bottle");
		item->equip = false;
		item->contentsHide = false;
		item->maxCharge = 20;
		item->currentCharge = 0;
		break;
	case NAME_SEED_HEAL:	//============ 씨 앗 ==========
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_heal");
		item->equip = false;
		break;
	case NAME_SEED_FIRE:
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_fire");
		item->equip = false;
		break;
	case NAME_SEED_SNAKE:
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_snake");
		item->equip = false;
		break;
	case NAME_SEED_FROST:
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_frost");
		item->equip = false;
		break;
	case NAME_DEW:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("dew");
		break;
	case NAME_MONEY:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("money");
		break;
	case NAME_KEY_IRON:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("key_iron");
		break;
	case NAME_KEY_SILVER:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("key_silver");
		break;
	case NAME_KEY_GOLD:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("key_gold");
		break;
	case NAME_FLOWER_HEAL:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_heal");
		break;
	case NAME_FLOWER_FIRE:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_fire");
		break;
	case NAME_FLOWER_FROST:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_frost");
		break;
	case NAME_FLOWER_SNAKE:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_snake");
		break;
	case NAME_END:
		break;
	}

}