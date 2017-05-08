#include <iostream>
#include <array>
struct Top2Info {
	int first = 0;
	int max = 0, secondMax = 0;
};

Top2Info examineTop2(const std::array<int, 26>& candidates);

int main() {
	int n;
	while (std::cin >> n && n) {
		std::array<int, 26> candidates{0};
		bool isOk = false;
		for (int i = 0; i < n && !isOk; i++) {
			char vote;
			std::cin >> vote;
			vote -= 'A';
			candidates[vote]++;

			//トップ2の票数と、トップの人の候補者を調べる
			auto&& top2 = examineTop2(candidates);

			//残りの票を全て2番目に入れてみる
			int assumedMax = top2.secondMax + (n - i - 1);

			//確定
			if (top2.max > assumedMax) {
				std::cout << static_cast<char>(top2.first + 'A') << " " << i + 1 << std::endl;
				isOk = true;
				//余ってる入力を入れる
				for (int j = i; j < n - 1; j++) std::cin >> vote;
				break;
			}
		}
		//確定しなかった
		if (!isOk) {
			std::cout << "TIE" << std::endl;
		}
	}

	return 0;
}

Top2Info examineTop2(const std::array<int, 26>& candidates)
{
	Top2Info info;

	//取り敢えずトップ探す
	for (int i = 0; i < candidates.size(); i++) {
		if (info.max < candidates[i]) {
			info.max = candidates[i];
			info.first = i;
		}
	}

	//2番目
	for (int i = 0; i < candidates.size(); i++) {
		if (info.secondMax < candidates[i] && info.first != i) {
			info.secondMax = candidates[i];
		}
	}
	return info;
}
