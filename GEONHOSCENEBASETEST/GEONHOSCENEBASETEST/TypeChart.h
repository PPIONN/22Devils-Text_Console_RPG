#include <string>
#include <unordered_map>
#include <vector>

class TypeChart {
public:
	static float getEffectiveness(std::string atk, std::string def) {
		// [공격 타입] 기준 -> [방어 타입] 배율
		if (atk == "Normal") { if (def == "Rock" || def == "Steel") return 0.5f; if (def == "Ghost") return 0.0f; }
		if (atk == "Fire") { if (def == "Grass" || def == "Ice" || def == "Bug" || def == "Steel") return 2.0f; if (def == "Fire" || def == "Water" || def == "Rock" || def == "Dragon") return 0.5f; }
		if (atk == "Water") { if (def == "Fire" || def == "Ground" || def == "Rock") return 2.0f; if (def == "Water" || def == "Grass" || def == "Dragon") return 0.5f; }
		if (atk == "Grass") { if (def == "Water" || def == "Ground" || def == "Rock") return 2.0f; if (def == "Fire" || def == "Grass" || def == "Poison" || def == "Flying" || def == "Bug" || def == "Dragon" || def == "Steel") return 0.5f; }
		if (atk == "Electric") { if (def == "Water" || def == "Flying") return 2.0f; if (def == "Electric" || def == "Grass" || def == "Dragon") return 0.5f; if (def == "Ground") return 0.0f; }
		if (atk == "Ice") { if (def == "Grass" || def == "Ground" || def == "Flying" || def == "Dragon") return 2.0f; if (def == "Fire" || def == "Water" || def == "Ice" || def == "Steel") return 0.5f; }
		if (atk == "Fighting") { if (def == "Normal" || def == "Ice" || def == "Rock" || def == "Dark" || def == "Steel") return 2.0f; if (def == "Poison" || def == "Flying" || def == "Psychic" || def == "Bug") return 0.5f; if (def == "Ghost") return 0.0f; }
		if (atk == "Poison") { if (def == "Grass") return 2.0f; if (def == "Poison" || def == "Ground" || def == "Rock" || def == "Ghost") return 0.5f; if (def == "Steel") return 0.0f; }
		if (atk == "Ground") { if (def == "Fire" || def == "Electric" || def == "Poison" || def == "Rock" || def == "Steel") return 2.0f; if (def == "Grass" || def == "Bug") return 0.5f; if (def == "Flying") return 0.0f; }
		if (atk == "Flying") { if (def == "Grass" || def == "Fighting" || def == "Bug") return 2.0f; if (def == "Electric" || def == "Rock" || def == "Steel") return 0.5f; }
		if (atk == "Psychic") { if (def == "Fighting" || def == "Poison") return 2.0f; if (def == "Psychic" || def == "Steel") return 0.5f; if (def == "Dark") return 0.0f; }
		if (atk == "Bug") { if (def == "Grass" || def == "Psychic" || def == "Dark") return 2.0f; if (def == "Fire" || def == "Fighting" || def == "Poison" || def == "Flying" || def == "Ghost" || def == "Steel") return 0.5f; }
		if (atk == "Rock") { if (def == "Fire" || def == "Ice" || def == "Flying" || def == "Bug") return 2.0f; if (def == "Fighting" || def == "Ground" || def == "Steel") return 0.5f; }
		if (atk == "Ghost") { if (def == "Psychic" || def == "Ghost") return 2.0f; if (def == "Dark") return 0.5f; if (def == "Normal") return 0.0f; }
		if (atk == "Dragon") { if (def == "Dragon") return 2.0f; if (def == "Steel") return 0.5f; }
		if (atk == "Dark") { if (def == "Psychic" || def == "Ghost") return 2.0f; if (def == "Fighting" || def == "Dark") return 0.5f; }
		if (atk == "Steel") { if (def == "Ice" || def == "Rock") return 2.0f; if (def == "Fire" || def == "Water" || def == "Electric" || def == "Steel") return 0.5f; }

		return 1.0f; // 기본 무상성
	}
};
