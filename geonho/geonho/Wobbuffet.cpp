//마자용

class Wobbuffet { // 마자용

public:


	void levelscale(int level) { // 레벨을 받아와서 레벨에 따른 스텟을 계산함
		sethp(level);
		setattack(level);
		setdefense(level);
		setspecailAttack(level);
		setspecailDefense(level);
		setspeed(level);
	}

	void sethp(int level) {
		hp += hpGrowth * level;
	}
	void setattack(int level) {
		attack += attackGrowth * level;
	}
	void setdefense(int level) {
		defense = defenseGrowth * level;
	}
	void setspecailAttack(int level) {
		specailAttack = specailAttackGrowth * level;
	}
	void setspecailDefense(int level) {
		specailDefense = specailDefenseGrowth * level;
	}
	void setspeed(int level) {
		speed = speedGrowth * level;
	}



private:
	int hp = 10;
	int attack = 5;
	int defense = 5;
	int specailAttack = 5;
	int specailDefense = 5;
	int speed = 5;
	int level = 0;
	int exp;

	float hpGrowth = 5.11;
	float attackGrowth = 0.97;
	float defenseGrowth = 1.47;
	float specailAttackGrowth = 0.97;
	float specailDefenseGrowth = 1.47;
	float speedGrowth = 0.97;
	std::string name = "Wobbuffet";


};
int main()
{

	return 0;
}
