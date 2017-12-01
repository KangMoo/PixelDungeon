#pragma once
#define TILESIZE 32
#define TILEXMAX 100
#define TILEYMAX 100

enum BUFF {
	BUFF_INVISIBLE,		//����ȭ
	BUFF_NATURAL_HEAL,	//�ڿ��� ȸ��
	BUFF_LEVITATION,	//���ߺξ�
	BUFF_NATURAL_ARMOR	//�ڿ��� ����
};
enum DEBUFF {
	DEBUFF_FIRE,		//����
	DEBUFF_FROZEN,		//����
	DEBUFF_BLEEDING,	//����
	DEBUFF_HUNGER		//�����
};

enum FLOWER {
	FLOWER_FIRE,		//ȭ����
	FLOWER_SUN,			//�¾���
	FLOWER_SNAKE,		//��Ѹ�
	FLOWER_ICE			//��������
};


enum ITEMTYPE {
	TYPE_WEAPON,	//����
	TYPE_ARMOR,		//��
	TYPE_ACC,		//�Ǽ�
	TYPE_POTION,	//������
	TYPE_SCROLL,	//�ֹ���
	TYPE_SEED,		//����
	TYPE_FOOD,		//������
	TYPE_THROW,		//��ô ����
	TYPE_WAND,		//���� ����
	TYPE_SPECIAL	//Ư��
};

enum ITEMNAME {
	NAME_OLD_SHORT_SWORD,	//���� �Ұ�	============ �� �� ==========
	NAME_SHORT_SWORD,		//�Ұ� 
	NAME_SWORD,				//��
	NAME_SPEAR,				//â
	NAME_BATTLE_AXE,		//���� ����
	NAME_CLOTH,				//�Ϲ� ��	============ �� �� �� =======
	NAME_LEATHER,			//�氩
	NAME_MAIL,				//�߰�
	NAME_RING_POWER,		//���� ����	============ �� �� ==========
	NAME_RING_RECHARGE,		//���� ����
	NAME_LIOYDS_BEACON,		//�ϵ�
	NAME_DART,				//��Ʈ		============ �� ô ==========
	NAME_PARALYSIS_DART,	//���� ��Ʈ
	NAME_POISON_DART,		//�� ��Ʈ
	NAME_LIGHTNING,			//���� �ϵ�	============ �� �� ==========
	NAME_NORMAL,			//���� �ϵ�
	NAME_POISON,			//�� �ϵ�
	NAME_EMERGENCY,			//���ķ�	============ �� ��===========
	NAME_PASTY,				//�Ľ�Ƽ
	NAME_UNKNOWN_MEAT,		//�˼����� ���
	NAME_COOKED_MEAT,		//�������
	NAME_FROZEN_MEAT,		//�� ��� 
	NAME_IDENTIFY,			//Ȯ��		============ �� �� �� =======
	NAME_UPGRADE,			//��ȭ
	NAME_PURIFY,			//��ȭ
	NAME_MAP,				//����
	NAME_RECHARGE,			//������
	NAME_BOTTLE,			//�̽�		============ �� �� ==========
	NAME_HEAL,				//ȸ��
	NAME_STR,				//��
	NAME_EX,				//���õ�
	NAME_INVISIBLE,			//����ȭ
	NAME_LEVITATION,		//���ߺξ�
	NAME_FROZEN,			//����
	NAME_LIQUID_FIRE,		//��ü ȭ��
	NAME_SEED_HEAL,			//ġ��		============ �� �� ==========
	NAME_SEED_FIRE,			//ȭ����
	NAME_SEED_SNAKE,		//��Ѹ�
	NAME_SEED_FROST,		//����
	NAME_DEW,				//�̽�		============ Ư �� ==========
	NAME_MONEY,				//��!
	NAME_KEY_IRON,			//�� ����	============ �� �� ==========
	NAME_KEY_SILVER,		//�� ����
	NAME_KEY_GOLD,			//�� ����
	NAME_FLOWER_HEAL,		//�¾���
	NAME_FLOWER_FIRE,		//ȭ����
	NAME_FLOWER_FROST,		//��������
	NAME_FLOWER_SNAKE,		//��Ѹ�
	NAME_END				//���� ������ ����

};

enum BUTTONOPTION
{
	BUTTONOPTION_DROP,	 // ����߸���
	BUTTONOPTION_DRINK,	 // ���ô� ( ���ǿ� )
	BUTTONOPTION_THROW,	 // ������
	BUTTONOPTION_READ,	 // �д� ( �ֹ��� )
	BUTTONOPTION_LAUNCH, // �߻��ϴ� ( �ϵ� )
	BUTTONOPTION_EAT,	 // �Դ� ( ���� )
	BUTTONOPTION_PLANT,	 // �ɴ� ( ����)
	BUTTONOPTION_REMEMBER,	// ����ϴ� ( Ư������)
	BUTTONOPTION_WEAR,		// �����ϴ� ( ��� )
	BUTTONOPTION_UNLOCK,
	BUTTONOPTION_END
};

typedef struct tagPlayerStat {
	int lv;			//����
	int hp;			//ü��
	int maxhp;		//�ִ�ü��
	int str;		//��
	int exp;		//����ġ
	int mindef;		//����
	int maxdef;
	float atk_lck;	//���߷�
	float avd_lck;	//ȸ����
	int hunger;		//�����
	int mindmg;		//�ּҵ�����
	int maxdmg;		//�ִ뵥����
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
	int hp;			//ü��
	int str;		//��
	float atk_lck;	//���߷�
	float avd_lck;	//ȸ����

	int def;		//����
	int lv;			//���� ���� = �÷��̾�� ����մϴ�.
	int maxLv;		//�ִ� ����, ���ʹ� �ִ� ������ �ִ� ���Ͱ� �ְ� �ִ� ������ ���� ���Ͱ� �ֽ��ϴ�.
	int exp;		//����� �÷��̾ ������ ����ġ

}ENEMYSTAT;
enum ENEMYSTATE
{
	ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_DEAD,
	ENEMYSTATE_END
};

typedef struct tagItem {
	image* img;			// ������ �̹���
	image* throwImg;	// ������ ��ô �̹���
	ITEMTYPE type;		// ������ Ÿ��
	ITEMNAME name;		// ������ �̸�
	tagPlayerStat stat;	// ���� ����
	POINT point;		// �ʵ��� �߽���ǥ
	POINT initPoint;
	RECT rc;			// ������ �浹�� ��Ʈ
	float range;		// �ϵ� ��ų ��Ÿ�
	bool equip;			// â�� ����
	bool isCursed;		// ���� ����
	bool contentsHide;	// ������ Ȯ�� ���� ( �ֹ��� , ���� , ��� )
	bool drop;
	int tier;			// ������ ��� (1,2,3,4 Ƽ��)
	int upgrade;		// ��ȭ Ƚ��
	int Power;			// �ʿ� ��
	int minPoint;		// �ּ� ������
	int maxPoint;		// �ִ� ������
	int maxCharge;		// �ִ� ���� Ƚ��(�ϵ�)
	int currentCharge;	// ���� ��� ���� Ƚ�� ( �ϵ� )
	int numOfItem;		// ������ ����
	int position;		// ������ �����
	int floor;			// ��������
}ITEM;



#define ATTRIBUTE_FLOOR			0x000001		// �⺻ idle

#define ATTRIBUTE_UNSIGHT		0x000002		// �þ߸� ������ �Ӽ�
#define ATTRIBUTE_UNGO			0x000004		// ������ �� ���� �Ӽ�

#define ATTRIBUTE_DOOR			0x000008		// ������ ������ �Ӽ�
#define ATTRIBUTE_WATER			0x000010		// ���� ���ٵ簡 �̰����� �پ��� ����
#define ATTRIBUTE_GRASS			0x000020		// ��ų� �ڸ��� setTile_GrassCut() ����
#define ATTRIBUTE_FLAMMABLE		0x000040		// �¿�� setTile_Flame() ����
#define ATTRIBUTE_CHASM			0x000080		// ������ �÷��̾�� �������� �԰�, ���ʹ̴� �״´�


#define ATTRIBUTE_TRAP			0x000010		// Ʈ�� : ��ų� ������ ������ ���� (Ʈ�� ������ ���� ����)

#define ATTRIBUTE_OBJECT		0x100000		// ������Ʈ�� ���̴� Ÿ��(������Ʈ �� ��ü�� �ƴ�)

#define ATTRIBUTE_HIDDEN		0x200000		// ���� : ������ �ʴ´�. Ư�� ������ �����ؾ� �巯��


// ��
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


#define ATTRIBUTE_CHEST		0x000001		// �������� : ��ų� �����ϸ� ������
#define ATTRIBUTE_STAIR		0x000010		// ��� �Ӽ�
#define ATTRIBUTE_POT		0x000100
#define ATTRIBUTE_WELL		0x001000
#define ATTRIBUTE_TRAP		0x010000		

#define ATTRIBUTE_LOCKED	0x000002		// ����ִ� ����
#define ATTRIBUTE_CRYSTAL	0x000004		// ũ����Ż ���� : ��ų� �����ϸ� ������ ������ Ȯ���� �� �ִ�

#define ATTRIBUTE_START		0x000020		// ����
#define ATTRIBUTE_END		0x000040		// ��

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
	image* img; //�޾ƿ� �̹���
	int sourX, sourY; //�޾ƿ� Ÿ�� ��ǥ��
	int destX, destY; //�Ѹ� Ÿ�� ��ǥ��
	TILEVIEW tileview;
	TERRAIN terrain;
	OBJ obj; // �Ⱦ�
	int floor;			// ��������
}TILE;


typedef struct tagGameObject {
	image* img;
	int sourX, sourY; //�޾ƿ� Ÿ�� ��ǥ��
	int destX, destY; //�Ѹ� Ÿ�� ��ǥ��
	OBJ obj;
	TRAP trap;
	int floor;			// ��������
}GAMEOBJECT;


typedef struct tagGrid {
	image* img; //����ִ� �̹���
	int x, y;
	int index;
	RECT rc;
	bool empty;
}GRID;

typedef struct tagSelectTile {
	image* img; //�޾ƿ� �̹���
	int sourX, sourY; //�޾ƿ� Ÿ�� ��ǥ��
	int index;
	RECT rc; // ������ �ȷ�Ʈ rect
}S_TILE;

typedef struct tagButton {
	RECT rc;
	char text[128];
	bool isClicked;
}BUTTON;

struct tagDebuff {
	int lefttime;		//�ܿ��ð�
	int damage;			//������
	DEBUFF type;		//����� Ÿ��
};