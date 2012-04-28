#include <iostream>
#include <vector>
#include <stdint.h>

enum Type {
	Lit, Opt
};

struct Match {
	Type T;
	union {
		char c;
		uint32_t set;
	};
	Match(Type Ty, char c) : T(Ty), c(c) {}
	Match(Type Ty, uint32_t c) : T(Ty), set(c) {}

	bool matches(char ca) {
		switch(T) {
		case Lit: return c == ca;
		case Opt: return (set & (1 << (ca - 'a'))) != 0;
		}
	}
};

std::vector<Match> parse(std::string &s) {
	std::vector<Match> matchers;
	int size = s.length();
	matchers.reserve(size);
	for(int i = 0; i < size; i++) {
		char c = s.at(i);
		if('(' == c) {
			uint32_t set = 0;
			c = s[++i];
			while(c != ')') {
				set |= (1 << (c - 'a'));
				c = s[++i];
			}
			matchers.push_back(Match(Opt, set));
		} else {
			matchers.push_back(Match(Lit, c));
		}
	}
	return matchers;
}

bool matchesWord(std::vector<Match> &M, std::string &word) {
	int wsize = word.size();
	for(int i = 0; i < wsize; ++i) {
		if(!M[i].matches(word[i])) return false;
	}
	return true;
}

int main() {
	int L, D, N;
	std::cin >> L >> D >> N;
	std::vector<std::string> Words;
	Words.reserve(D);
	std::string line;
	for(int i = 0; i < D; ++i){
		std::cin >> line;
		Words.push_back(line);
	}
	int casen = 0;
	for(int i = 0; i < N; ++i) {
		std::cin >> line;
		int matched = 0;
		std::vector<Match> Pattern = parse(line);
		int Ws = Words.size();
		for(int w = 0; w < Ws; ++w) {
			if(matchesWord(Pattern, Words[w])) ++matched;
		}
		++casen;
		std::cout << "Case #" << casen << ": " << matched << '\n';
	}
}
