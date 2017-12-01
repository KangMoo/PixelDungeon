#pragma once
#define TILESIZE 32
#define TILEXMAX 100
#define TILEYMAX 100

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
	NAME_BOTTLE,			//이슬		============ 포 션 ==========
	NAME_HEAL,				//회복
	NAME_STR,				//힘
	NAME_EX,				//숙련도
	NAME_INVISIBLE,			//투명화
	NAME_LEVITATION,		//공중부양
	NAME_FROZEN,			//서리
	NAME_LIQUID_FIRE,		//액체 화염
	NAME_SEED_HEAL,			//치유		============ 씨 앗 ==========
	NAME_SEED_FIRE,			//화염초
	NAME_SEED_SNAKE,		//뱀뿌리
	NAME_SEED_FROST,		//얼음
	NAME_DEW,				//이슬		============ 특 수 ==========
	NAME_MONEY,				//돈!
	NAME_KEY_IRON,			//쇠 열쇠	============ 열 쇠 ==========
	NAME_KEY_SILVER,		//은 열쇠
	NAME_KEY_GOLD,			//금 열쇠
	NAME_FLOWER_HEAL,		//태양초
	NAME_FLOWER_FIRE,		//화염초
	NAME_FLOWER_FROST,		//얼음송이
	NAME_FLOWER_SNAKE,		//뱀뿌리
	NAME_END				//포문 돌리기 위함

};

enum BUTTONOPTION
{
	BUTTONOPTION_DROP,	 // 떨어뜨리다
	BUTTONOPTION_DRINK,	 // 마시다 ( 포션용 )
	BUTTONOPTION_THROW,	 // 던지다
	BUTTONOPTION_READ,	 // 읽다 ( 주문서 )
	BUTTONOPTION_LAUNCH, // 발사하다 ( 완드 )
	BUTTONOPTION_EAT,	 // 먹다 ( 음식 )
	BUTTONOPTION_PLANT,	 // 심다 ( 씨앗)
	BUTTONOPTION_REMEMBER,	// 기억하다 ( 특수반지)
	BUTTONOPTION_WEAR,		// 착용하다 ( 장비 )
	BUTTONOPTION_UNLOCK,
	BUTTONOPTION_END
};

typedef struct tagPlayerStat {
	int lv;			//레벨
	int hp;			//체력
	int maxhp;		//최대체력
	int str;		//힘
	int exp;		//경험치
	int mindef;		//방어력
	int maxdef;
	float atk_lck;	//명중률
	float avd_lck;	//회피율
	int hunger;		//배고픔
	int mindmg;		//최소데미지
	int maxdmg;		//최대데미지
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
	ENEMYSTATE_DEAD,
	ENEMYSTATE_END
};

typedef struct tagItem {
	image* img;			// 아이템 이미지
	image* throwImg;	// 아이템 투척 이미지
	ITEMTYPE type;		// 아이템 타입
	ITEMNAME name;		// 아이템 이름
	tagPlayerStat stat;	// 스탯 증가
	POINT point;		// 필드위 중심좌표
	POINT initPoint;
	RECT rc;			// 아이템 충돌용 렉트
	float range;		// 완드 스킬 사거리
	bool equip;			// 창착 여부
	bool isCursed;		// 저주 여부
	bool contentsHide;	// 아이템 확인 여부 ( 주문서 , 물약 , 장비 )
	bool drop;
	int tier;			// 아이템 등급 (1,2,3,4 티어)
	int upgrade;		// 강화 횟수
	int Power;			// 필요 힘
	int minPoint;		// 최소 데미지
	int maxPoint;		// 최대 데미지
	int maxCharge;		// 최대 충전 횟수(완드)
	int currentCharge;	// 현재 사용 가능 횟수 ( 완드 )
	int numOfItem;		// 아이템 개수
	int position;		// 포지션 저장용
	int floor;			// 몇층인지
}ITEM;



#define ATTRIBUTE_FLOOR			0x000001		// 기본 idle

#define ATTRIBUTE_UNSIGHT		0x000002		// 시야를 가리는 속성
#define ATTRIBUTE_UNGO			0x000004		// 지나갈 수 없는 속성

#define ATTRIBUTE_DOOR			0x000008		// 열리고 닫히는 속성
#define ATTRIBUTE_WATER			0x000010		// 불을 끈다든가 이것저것 다양한 역할
#define ATTRIBUTE_GRASS			0x000020		// 밟거나 자르면 setTile_GrassCut() 실행
#define ATTRIBUTE_FLAMMABLE		0x000040		// 태우면 setTile_Flame() 실행
#define ATTRIBUTE_CHASM			0x000080		// 빠지면 플레이어는 데미지를 입고, 에너미는 죽는다


#define ATTRIBUTE_TRAP			0x000010		// 트랩 : 밟거나 아이템 던지면 반응 (트랩 종류는 따로 정의)

#define ATTRIBUTE_OBJECT		0x100000		// 오브젝트가 놓이는 타일(오브젝트 그 자체는 아님)

#define ATTRIBUTE_HIDDEN		0x200000		// 히든 : 보이지 않는다. 특정 조건을 만족해야 드러남


// 맵
enum TERRAIN {
	TERRAIN_NULL,

	TERRAIN_FLOOR =				ATTRIBUTE_FLOOR,

	TERRAIN_GRASS =				ATTRIBUTE_FLOOR + ATTRIBUTE_GRASS + ATTRIBUTE_FLAMMABLE,
	TERRAIN_GRASS_UNTOUCHED =	ATTRIBUTE_FLOOR + ATTRIBUTE_GRASS + ATTRIBUTE_FLAMMABLE + ATTRIBUTE_UNSIGHT,

	TERRAIN_WALL =				ATTRIBUTE_FLOOR + ATTRIBUTE_UNGO + ATTRIBUTE_UNSIGHT,
	TERRAIN_BARRICADE =			ATTRIBUTE_FLOOR + ATTRIBUTE_UNGO + ATTRIBUTE_UNSIGHT +  ATTRIBUTE_FLAMMABLE,
	TERRAIN_STATUE =			ATTRIBUTE_FLOOR + ATTRIBUTE_UNGO,

	TERRAIN_DOOR =				ATTRIBUTE_FLOOR + ATTRIBUTE_DOOR,
	TERRAIN_DOOR_OPEN =			ATTRIBUTE_FLOOR + ATTRIBUTE_DOOR + ATTRIBUTE_FLAMMABLE,
	TERRAIN_DOOR_CLOSED =		ATTRIBUTE_FLOOR + ATTRIBUTE_DOOR + ATTRIBUTE_UNSIGHT + ATTRIBUTE_FLAMMABLE,
	TERRAIN_DOOR_LOCKED =		ATTRIBUTE_FLOOR + ATTRIBUTE_DOOR + ATTRIBUTE_UNSIGHT + ATTRIBUTE_UNGO,
	TERRAIN_DOOR_HIDDEN =		ATTRIBUTE_FLOOR + ATTRIBUTE_DOOR + ATTRIBUTE_UNSIGHT + ATTRIBUTE_UNGO + ATTRIBUTE_HIDDEN,

	TERRAIN_WATER =				ATTRIBUTE_FLOOR + ATTRIBUTE_WATER,
	
	TERRAIN_CHASM =				ATTRIBUTE_FLOOR + ATTRIBUTE_CHASM,

	TERRAIN_OBJECT =			ATTRIBUTE_FLOOR + ATTRIBUTE_OBJECT,
	TERRAIN_OBJECT_UNGO =		ATTRIBUTE_FLOOR + ATTRIBUTE_OBJECT + ATTRIBUTE_UNGO,
	TERRAIN_OBJECT_HIDDEN =		ATTRIBUTE_FLOOR + ATTRIBUTE_OBJECT + ATTRIBUTE_HIDDEN
};

enum TRAP {
	TRAP_NONE,

	TRAP_INACTIVE,

	TRAP_GAS,
	TRAP_FIRE,
	TRAP_PARALYZE,
	TRAP_POISON,
	TRAP_ALARM,
	TRAP_LIGHTNING,
	TRAP_GRIPPING,
	TRAP_SUMMONING,
};


#define ATTRIBUTE_CHEST		0x000001		// 보물상자 : 밟거나 조사하면 열린다
#define ATTRIBUTE_STAIR		0x000010		// 계단 속성
#define ATTRIBUTE_POT		0x000100
#define ATTRIBUTE_WELL		0x001000
#define ATTRIBUTE_TRAP		0x010000		

#define ATTRIBUTE_LOCKED	0x000002		// 잠겨있는 상태
#define ATTRIBUTE_CRYSTAL	0x000004		// 크리스탈 상자 : 밟거나 조사하면 내부의 물건을 확인할 수 있다

#define ATTRIBUTE_START		0x000020		// 시작
#define ATTRIBUTE_END		0x000040		// 끝

#define ATTRIBUTE_ACTIVE	0x100000


enum OBJ {
	OBJ_NONE,

	OBJ_CHEST				= ATTRIBUTE_CHEST,
	OBJ_CHEST_LOCKED		= ATTRIBUTE_CHEST + ATTRIBUTE_LOCKED,
	OBJ_CRY_CHEST			= ATTRIBUTE_CHEST + ATTRIBUTE_CRYSTAL,
	OBJ_CRY_CHEST_LOCKED	= ATTRIBUTE_CHEST + ATTRIBUTE_CRYSTAL + ATTRIBUTE_LOCKED,

	OBJ_STAIR_START			= ATTRIBUTE_STAIR + ATTRIBUTE_START,
	OBJ_STAIR_END			= ATTRIBUTE_STAIR + ATTRIBUTE_END,

	OBJ_POT					= ATTRIBUTE_POT,
	
	OBJ_WELL_EMPTY			= ATTRIBUTE_WELL,
	OBJ_WELL				= ATTRIBUTE_WELL + ATTRIBUTE_ACTIVE,

	OBJ_TRAP				= ATTRIBUTE_TRAP,
	OBJ_TRAP_ACTIVE			= ATTRIBUTE_TRAP + ATTRIBUTE_ACTIVE
};



enum TILEVIEW {
	TILEVIEW_NO,
	TILEVIEW_HALF,
	TILEVIEW_ALL,
	TILEVIEW_END
};

typedef struct tagTile {
	image* img; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int destX, destY; //뿌릴 타일 좌표값
	TILEVIEW tileview;
	TERRAIN terrain;
	OBJ obj; // 안씀
	int floor;			// 몇층인지
}TILE;


typedef struct tagGameObject {
	image* img;
	int sourX, sourY; //받아올 타일 좌표값
	int destX, destY; //뿌릴 타일 좌표값
	OBJ obj;
	TRAP trap;
	int floor;			// 몇층인지
}GAMEOBJECT;


typedef struct tagGrid {
	image* img; //들어있는 이미지
	int x, y;
	int index;
	RECT rc;
	bool empty;
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

struct tagDebuff {
	int lefttime;		//잔여시간
	int damage;			//데미지
	DEBUFF type;		//디버프 타입
};