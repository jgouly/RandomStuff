#include <iostream>
#include <algorithm>
#include <vector>
#include <stdint.h>

struct Match {
	virtual bool matches(char c) = 0;
	virtual ~Match(){};
};

struct Literal : Match {
	char C;
	Literal(char C) : C(C) {}
	virtual bool matches(char c) {
		return c == C;
	}
};

struct Option : Match {
	uint32_t Set;
	Option() : Set(0) {}

	virtual bool matches(char c) {
		return (Set & (1 << (c - 'a'))) != 0;
	};

	void set(char c) {
		Set |= (1 << (c - 'a'));
	}
};

std::vector<Match*> parse(std::string s) {
	std::vector<Match*> matchers;
	for(int i = 0; i < s.length(); i++) {
		char c = s.at(i);
		switch(c) {
			case '(': {
				Option *O = new Option;
				c = s.at(++i);
				while(c != ')') {
					O->set(c);
					c = s.at(++i);
				}
				matchers.push_back(O);
			}
			break;
			default: {matchers.push_back(new Literal(c));}
		};
	}
	return matchers;
}

bool matchesWord(std::vector<Match*> M, std::string word) {
	for(int i = 0; i < word.size(); ++i) {
		if(!M[i]->matches(word[i])) return false;
	}
	return true;
}

int main() {
	int L, D, N;
	std::cin >> L >> D >> N;
	std::vector<std::string> Words;
	std::vector<std::vector<Match*> > Patterns;
	for(int i = 0; i < D; ++i){
		std::string line;
		std::cin >> line;
		Words.push_back(line);
	}
	for(int i = 0; i < N; ++i){
		std::string line;
		std::cin >> line;
		Patterns.push_back(parse(line));
	}
	int i = 1;
	for(int p = 0; p < Patterns.size(); ++p) {
		std::vector<Match*> Pattern = Patterns[p];
		int matched = 0;
		for(int w = 0; w < Words.size(); ++w) {
			std::string Word = Words[w];
			if(matchesWord(Pattern, Word)) ++matched;
		}
		std::cout << "Case #" << i << ": " << matched << std::endl;
		++i;
	}
}
