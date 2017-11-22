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
	NAME_BOTTLE,				//�̽�		============ �� �� ==========
	NAME_HEAL,				//ȸ��
	NAME_STR,				//��
	NAME_EX,				//���õ�
	NAME_INVISIBLE,			//����ȭ
	NAME_LEVITATION,		//���ߺξ�
	NAME_FORZEN,			//����
	NAME_LIQUID_FIRE,		//��ü ȭ��
	NAME_SEED_HEAL,			//ġ��		============ �� �� ==========
	NAME_SEED_FIRE,			//ȭ����
	NAME_SEED_SNAKE,		//��Ѹ�
	NAME_SEED_FROST,		//����
	NAME_DEW			//�̽�		============ Ư �� ==========

};

enum ITEMUSEMETHOD 
{
	ITEM_DROP,	//����߸���
	ITEM_THROW,	//������
	ITEM_PLANT,	//�ɴ� (���ѿ�)
	ITEM_DRINK, //���ô�(����)
	ITEM_READ,	//�д� (�ֹ���)
	ITEM_EAT	//�Դ� ( ����)

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
	PLAYERSTATE_DEAD,
	PLAYERSTATE_END
};
typedef struct tagEnemyStat {
	int hp;			//ü��
	int str;		//��
	float atk_lck;	//���߷�
	float avd_lck;	//ȸ����
}ENEMYSTAT;

typedef struct tagItem {
	image* img;			// ������ �̹���
	image* throwImg;	// ������ ��ô �̹���
	ITEMTYPE type;		// ������ Ÿ��
	ITEMNAME name;		// ������ �̸�
	tagPlayerStat stat;	
	POINT point;
	RECT rc;			// ������ �浹�� ��Ʈ
	float range;		// �ϵ� ��ų ��Ÿ�
	bool equip;			// â�� ����
	bool isCursed;		// ���� ����
	bool contentsHide;	// ������ Ȯ�� ���� ( �ֹ��� , ���� , ��� )
	int tier;			// ������ ��� (1,2,3,4 Ƽ��)
	int upgrade;		// ��ȭ Ƚ��
	int Power;			// �ʿ� ��
	int minPoint;		// �ּ� ������
	int maxPoint;		// �ִ� ������
	int maxCharge;		//�ִ� ���� Ƚ��(�ϵ�)
	int currentCharge;	//���� ��� ���� Ƚ�� ( �ϵ� )
	int numOfItem;		// ������ ����
	int position;
}ITEM;