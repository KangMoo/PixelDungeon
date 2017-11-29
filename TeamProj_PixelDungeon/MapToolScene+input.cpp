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

	if (KEYMANAGER->isOnceKeyDown('5')) {
		_inputMode = MODE_TRAP;
	}

	if (KEYMANAGER->isOnceKeyDown('0')) {
		switch (_inputMode) {
		case MODE_VIEWING: _inputMode = MODE_VIEWING_TILE; break;
		default: _inputMode = MODE_VIEWING; break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E')) _inputMode = MODE_DELET;



	if (KEYMANAGER->isOnceKeyDown(VK_F1)) { _inputLayer = LAYER_TILE; }
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) { _inputLayer = LAYER_DECO; }
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) { _inputLayer = LAYER_ITEM; }
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) { _inputLayer = LAYER_MONSTER; }
	
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
					for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
						if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
							_viMapTile = _vMapTile.erase(_viMapTile);
							return;
						}
						else
							_viMapTile++;
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
								case MODE_TRAP:			inputTile.terrain = TERRAIN_TRAP;				break;
								}
								_vMapTile.push_back(inputTile);
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
							case MODE_DOOR_LOCKED:	inputTile.terrain = TERRAIN_DOOR_LOCKED;			break;
							case MODE_TRAP:			inputTile.terrain = TERRAIN_TRAP;				break;
							}
							
							_vMapTile.push_back(inputTile);
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
