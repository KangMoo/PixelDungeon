#pragma once



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
	TYPE_WAND		//���� ����
};

enum ITEMNAME {
	NAME_SWORD,			//�Ϲ� Į	============ �� �� ==========
	NAME_LONGSWORD,		//�� Į 
	NAME_SCIMITAR,		//�ù���
	NAME_SPEAR,			//â
	NAME_HAMMER,		//�б�
	NAME_CLOTH,			//�Ϲ� ��	============ �� �� �� =======
	NAME_LIGHT_ARMOR,	//�氩
	NAME_HEAVY_ARMOR,	//�߰�
	NAME_RING_RESIST,	//���� ����	============ �� �� ==========
	NAME_RING_RECHARGE,	//���� ����
	NAME_WAND,			//�ϵ�
	NAME_DART,			//��Ʈ		============ �� ô ==========
	NAME_PARALYSIS_DART,//���� ��Ʈ
	NAME_POISON_DART,	//�� ��Ʈ
	NAME_LIGHTNING,		//���� �ϵ�	============ �� �� ==========
	NAME_NORMAL,		//���� �ϵ�
	NAME_POISON,		//�� �ϵ�
	NAME_EMERGENCY,		//���ķ�	============ �� ��===========
	NAME_PASTY,			//�Ľ�Ƽ
	NAME_UNKNOWN_MEAT,	//�˼����� ���
	NAME_COOKED_MEAT,	//�������
	NAME_FROZEN_MEAT,	//�� ��� 
	NAME_IDENTIFY,		//Ȯ��		============ �� �� �� =======
	NAME_UPGRADE,		//��ȭ
	NAME_PURIFY,		//��ȭ
	NAME_MAP,			//����
	NAME_RECHARGE,		//������
	NAME_DEW,			//�̽�		============ �� �� ==========
	NAME_HEAL,			//ȸ��
	NAME_STR,			//��
	NAME_EX,			//���õ�
	NAME_INVISIBLE,		//����ȭ
	NAME_LEVITATION,	//���ߺξ�
	NAME_FORZEN,		//����
	NAME_LIQUID_FIRE,	//��ü ȭ��
	NAME_SEED_HEAL,		//ġ��		============ �� �� ==========
	NAME_SEED_FIRE,		//ȭ����
	NAME_SEED_SNAKE,	//��Ѹ�
	NAME_SEED_FROST,	//����

};

typedef struct tagPlayerStat {
	int lv;			//����
	int hp;			//ü��
	int str;		//��
	int exp;		//����ġ
	int def;		//����
	float atk_lck;	//���߷�
	float avd_lck;	//ȸ����
}PLAYERSTAT;

typedef struct tagEnemyStat {
	int hp;			//ü��
	int str;		//��
	float atk_lck;	//���߷�
	float avd_lck;	//ȸ����
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