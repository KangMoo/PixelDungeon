#pragma once
#define TILESIZE 32


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

enum FOOD {
	FOOD_EMERGENCY,		//���ķ�
	FOOD_PASTA,			//�Ľ�Ÿ
	FOOD_UNKNOWN_MEAT	//�˼����� ���
};

enum ITEMTYPE {
	ITEMTYPE_EQUIP,		//�����
	ITEMTYPE_POTION,	//������
	ITEMTYPE_SCROLL,	//�ֹ���
	ITEMTYPE_SEED,		//����
	ITEMTYPE_FOOD		//������
};
enum POTION {
	POTION_DEW,			//�̽�
	POTION_HEAL,		//ȸ��
	POTION_STR,			//��
	POTION_EX,			//���õ�
	POTION_INVISIBLE,	//����ȭ
	POTION_LEVITATION,	//���ߺξ�
	POTION_FORZEN,		//����
	POTION_LIQUID_FIRE	//��ü ȭ��
};

enum SCROLL {
	SCROLL_IDENTIFY,	//Ȯ��
	SCROLL_MAP,			//����
	SCROLL_RECHARGE		//������
};

enum ITEMSTATE {
	ITEMSTATE_GROUND,	//�� ���� ����
	ITEMSTATE_INVENTORY,//����ȿ� ����
	ITEMSTATE_EQUIP		//������
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
enum PLAYERSTATE {
	PLAYERSTATE_IDLE,
	PLAYERSTATE_MOVE,
	PLAYERSTATE_ATTACK,
	PLAYERSTATE_EAT,
	PLAYERSTATE_SCROLL,
	PLAYERSTATE_END
};
typedef struct tagEnemyStat {
	int hp;			//ü��
	int str;		//��
	float atk_lck;	//���߷�
	float avd_lck;	//ȸ����
}ENEMYSTAT;

typedef struct tagItem {
	ITEMTYPE type;
	ITEMSTATE state;
	image* image;
}ITEM;