#pragma once



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
	TYPE_WAND		//마법 막대
};

enum ITEMNAME {
	NAME_SWORD,			//일반 칼	============ 무 기 ==========
	NAME_LONGSWORD,		//긴 칼 
	NAME_SCIMITAR,		//시미터
	NAME_SPEAR,			//창
	NAME_HAMMER,		//둔기
	NAME_CLOTH,			//일반 옷	============ 방 어 구 =======
	NAME_LIGHT_ARMOR,	//경갑
	NAME_HEAVY_ARMOR,	//중갑
	NAME_RING_RESIST,	//저항 반지	============ 악 세 ==========
	NAME_RING_RECHARGE,	//충전 반지
	NAME_WAND,			//완드
	NAME_DART,			//다트		============ 투 척 ==========
	NAME_PARALYSIS_DART,//마비 다트
	NAME_POISON_DART,	//독 다트
	NAME_LIGHTNING,		//전기 완드	============ 완 드 ==========
	NAME_NORMAL,		//마법 완드
	NAME_POISON,		//독 완드
	NAME_EMERGENCY,		//비상식량	============ 음 식===========
	NAME_PASTY,			//파스티
	NAME_UNKNOWN_MEAT,	//알수없는 고기
	NAME_COOKED_MEAT,	//익힌고기
	NAME_FROZEN_MEAT,	//얼린 고기 
	NAME_IDENTIFY,		//확인		============ 주 문 서 =======
	NAME_UPGRADE,		//강화
	NAME_PURIFY,		//정화
	NAME_MAP,			//지도
	NAME_RECHARGE,		//재충전
	NAME_DEW,			//이슬		============ 포 션 ==========
	NAME_HEAL,			//회복
	NAME_STR,			//힘
	NAME_EX,			//숙련도
	NAME_INVISIBLE,		//투명화
	NAME_LEVITATION,	//공중부양
	NAME_FORZEN,		//서리
	NAME_LIQUID_FIRE,	//액체 화염
	NAME_SEED_HEAL,		//치유		============ 씨 앗 ==========
	NAME_SEED_FIRE,		//화염초
	NAME_SEED_SNAKE,	//뱀뿌리
	NAME_SEED_FROST,	//얼음

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

typedef struct tagEnemyStat {
	int hp;			//체력
	int str;		//힘
	float atk_lck;	//명중률
	float avd_lck;	//회피율
}ENEMYSTAT;

typedef struct tagItem {
	image* image;
	ITEMTYPE type;
	ITEMNAME name;
	POINT point;
	RECT rc;
	float range;
	bool equip;
	int upgrade;
	int minDmg;
	int maxDmg;
	int maxCharge;
	int currentCharge;
	int numOfItem;
	int position;
}ITEM;