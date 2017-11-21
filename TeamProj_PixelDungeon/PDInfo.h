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

enum FOOD {
	FOOD_EMERGENCY,		//비상식량
	FOOD_PASTA,			//파스타
	FOOD_UNKNOWN_MEAT	//알수없는 고기
};

enum ITEMTYPE {
	ITEMTYPE_EQUIP,		//장비템
	ITEMTYPE_POTION,	//포션템
	ITEMTYPE_SCROLL,	//주문서
	ITEMTYPE_SEED,		//씨앗
	ITEMTYPE_FOOD		//먹을거
};
enum POTION {
	POTION_DEW,			//이슬
	POTION_HEAL,		//회복
	POTION_STR,			//힘
	POTION_EX,			//숙련도
	POTION_INVISIBLE,	//투명화
	POTION_LEVITATION,	//공중부양
	POTION_FORZEN,		//서리
	POTION_LIQUID_FIRE	//액체 화염
};

enum SCROLL {
	SCROLL_IDENTIFY,	//확인
	SCROLL_MAP,			//지도
	SCROLL_RECHARGE		//재충전
};

enum ITEMSTATE {
	ITEMSTATE_GROUND,	//땅 위에 있음
	ITEMSTATE_INVENTORY,//가방안에 있음
	ITEMSTATE_EQUIP		//착용중
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
	PLAYERSTATE_END
};
typedef struct tagEnemyStat {
	int hp;			//체력
	int str;		//힘
	float atk_lck;	//명중률
	float avd_lck;	//회피율
}ENEMYSTAT;

typedef struct tagItem {
	ITEMTYPE type;
	ITEMSTATE state;
	image* image;
}ITEM;