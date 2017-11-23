#pragma once
#define TILESIZE 32


enum BUFF {
	BUFF_INVISIBLE,		//투명화
	BUFF_NATURAL_HEAL,	//자연의 회복
	BUFF_LEVITATION,	//공중부양
	BUFF_NATURAL_ARMOR	//자연의 갑옷
};
enum DEBUFF {
	DEBUFF_FIRE,		//연소
	DEBUFF_FROZEN,		//빙결
	DEBUFF_BLEEDING,	//출혈
	DEBUFF_HUNGER		//배고픔
};

enum FLOWER {
	FLOWER_FIRE,		//화염초
	FLOWER_SUN,			//태양초
	FLOWER_SNAKE,		//뱀뿌리
	FLOWER_ICE			//얼음송이
};


enum ITEMTYPE {
	TYPE_WEAPON,	//무기
	TYPE_ARMOR,		//방어구
	TYPE_ACC,		//악세
	TYPE_POTION,	//포션템
	TYPE_SCROLL,	//주문서
	TYPE_SEED,		//씨앗
	TYPE_FOOD,		//먹을거
	TYPE_THROW,		//투척 무기
	TYPE_WAND,		//마법 막대
	TYPE_SPECIAL	//특수
};

enum ITEMNAME {
	NAME_OLD_SHORT_SWORD,	//낡은 소검	============ 무 기 ==========
	NAME_SHORT_SWORD,		//소검 
	NAME_SWORD,				//검
	NAME_SPEAR,				//창
	NAME_BATTLE_AXE,		//전투 도끼
	NAME_CLOTH,				//일반 옷	============ 방 어 구 =======
	NAME_LEATHER,			//경갑
	NAME_MAIL,				//중갑
	NAME_RING_POWER,		//저항 반지	============ 악 세 ==========
	NAME_RING_RECHARGE,		//충전 반지
	NAME_LIOYDS_BEACON,		//완드
	NAME_DART,				//다트		============ 투 척 ==========
	NAME_PARALYSIS_DART,	//마비 다트
	NAME_POISON_DART,		//독 다트
	NAME_LIGHTNING,			//전기 완드	============ 완 드 ==========
	NAME_NORMAL,			//마법 완드
	NAME_POISON,			//독 완드
	NAME_EMERGENCY,			//비상식량	============ 음 식===========
	NAME_PASTY,				//파스티
	NAME_UNKNOWN_MEAT,		//알수없는 고기
	NAME_COOKED_MEAT,		//익힌고기
	NAME_FROZEN_MEAT,		//얼린 고기 
	NAME_IDENTIFY,			//확인		============ 주 문 서 =======
	NAME_UPGRADE,			//강화
	NAME_PURIFY,			//정화
	NAME_MAP,				//지도
	NAME_RECHARGE,			//재충전
	NAME_BOTTLE,				//이슬		============ 포 션 ==========
	NAME_HEAL,				//회복
	NAME_STR,				//힘
	NAME_EX,				//숙련도
	NAME_INVISIBLE,			//투명화
	NAME_LEVITATION,		//공중부양
	NAME_FORZEN,			//서리
	NAME_LIQUID_FIRE,		//액체 화염
	NAME_SEED_HEAL,			//치유		============ 씨 앗 ==========
	NAME_SEED_FIRE,			//화염초
	NAME_SEED_SNAKE,		//뱀뿌리
	NAME_SEED_FROST,		//얼음
	NAME_DEW,				//이슬		============ 특 수 ==========
	NAME_END				//포문 돌리기 위함
};

enum BUTTONOPTION
{
	BUTTONOPTION_DROP,
	BUTTONOPTION_DRINK,
	BUTTONOPTION_THROW,
	BUTTONOPTION_READ,
	BUTTONOPTION_LAUNCH,
	BUTTONOPTION_EAT,
	BUTTONOPTION_PLANT,
	BUTTONOPTION_REMEMBER,
	BUTTONOPTION_WEAR,
	BUTTONOPTION_END,
};

enum ITEMUSEMETHOD 
{
	ITEM_DROP,	//떨어뜨리다
	ITEM_THROW,	//던지다
	ITEM_PLANT,	//심다 (씨앗용)
	ITEM_DRINK, //마시다(포션)
	ITEM_READ,	//읽다 (주문서)
	ITEM_EAT	//먹다 ( 음식)

};

typedef struct tagPlayerStat {
	int lv;			//레벨
	int hp;			//체력
	int str;		//힘
	int exp;		//경험치
	int def;		//방어력
	float atk_lck;	//명중률
	float avd_lck;	//회피율
}PLAYERSTAT;
enum PLAYERSTATE {
	PLAYERSTATE_IDLE,
	PLAYERSTATE_MOVE,
	PLAYERSTATE_ATTACK,
	PLAYERSTATE_EAT,
	PLAYERSTATE_SCROLL,
	PLAYERSTATE_DEAD,
	PLAYERSTATE_END
};
typedef struct tagEnemyStat {
	int hp;			//체력
	int str;		//힘
	float atk_lck;	//명중률
	float avd_lck;	//회피율

	int def;		//방어력
	int lv;			//현재 레벨 = 플레이어와 비례합니다.
	int maxLv;		//최대 레벨, 몬스터는 최대 레벨이 있는 몬스터가 있고 최대 레벨이 없는 몬스터가 있습니다.
	int exp;		//사망시 플레이어에 전달할 경험치

}ENEMYSTAT;
enum ENEMYSTATE
{
	ENEMYSTATE_SLEEP,	//플레이어를 찾지 못한상태/수면상태
	ENEMYSTATE_IDLE,	//플레이어를 찾은 상태에서의 기본
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END
};

typedef struct tagItem {
	image* img;			// 아이템 이미지
	image* throwImg;	// 아이템 투척 이미지
	ITEMTYPE type;		// 아이템 타입
	ITEMNAME name;		// 아이템 이름
	tagPlayerStat stat;	
	POINT point;
	RECT rc;			// 아이템 충돌용 렉트
	float range;		// 완드 스킬 사거리
	bool equip;			// 창착 여부
	bool isCursed;		// 저주 여부
	bool contentsHide;	// 아이템 확인 여부 ( 주문서 , 물약 , 장비 )
	int tier;			// 아이템 등급 (1,2,3,4 티어)
	int upgrade;		// 강화 횟수
	int Power;			// 필요 힘
	int minPoint;		// 최소 데미지
	int maxPoint;		// 최대 데미지
	int maxCharge;		//최대 충전 횟수(완드)
	int currentCharge;	//현재 사용 가능 횟수 ( 완드 )
	int numOfItem;		// 아이템 개수
	int position;
}ITEM;




// 맵
enum TERRAIN {
	TERRAIN_NULL = 0,
	TERRAIN_FLOOR,

	TERRAIN_WALL,

	TERRAIN_TRAP,

	TERRAIN_GRASS
};

enum OBJ {
	OBJ_NONE,

	OBJ_TRAP,
	OBJ_TRAP_UNSIGHT,
	OBJ_TRAP_ACTIVATE
};


typedef struct tagTile {
	image* img; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int destX, destY; //뿌릴 타일 좌표값
	int index;

	TERRAIN terrain;
	OBJ obj;
}TILE;

typedef struct tagSaveTile {
	//string imgName; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int destX, destY; //뿌릴 타일 좌표값
	int index;

	TERRAIN terrain;
	OBJ obj;
}SAVETILE;

typedef struct tagSaveMap {
	int size;
	SAVETILE* tiles;
}SAVEMAP;

typedef struct tagGrid {
	image* img; //들어있는 이미지
	int x, y;
	int index;
	RECT rc;
}GRID;

typedef struct tagSelectTile {
	image* img; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int index;
	RECT rc; // 선택한 팔레트 rect
}S_TILE;

typedef struct tagButton {
	RECT rc;
	char text[128];
	bool isClicked;
}BUTTON;