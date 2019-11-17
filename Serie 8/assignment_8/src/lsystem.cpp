
#include "lsystem.h"
#include <stack>
#include <memory>
#include <iostream>

std::string LindenmayerSystemDeterministic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 1.1
		For a given symbol in the sequence, what should it be replaced with after expansion?

		You may find useful:
			map.find: Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
			http://en.cppreference.com/w/cpp/container/unordered_map/find
	*/

	auto const search = rules.find(sym);
	if (search != rules.end()) return search->second;
	else return {char(sym)};
}

std::string LindenmayerSystem::expandOnce(std::string const& symbol_sequence) {
    /*============================================================
        TODO 1.2
        Perform one iteration of grammar expansion on `symbol_sequence`.
        Use the expandSymbol method
    */
    std::string result;
	for (int i = 0; i < symbol_sequence.length(); i++) result += expandSymbol(symbol_sequence.at(i));
    return result;

}

std::string LindenmayerSystem::expand(std::string const& initial, uint32_t num_iters) {
    /*============================================================
        TODO 1.3
        Perform `num_iters` iterations of grammar expansion (use expandOnce)
    */
	std::string result = initial;
	for (int i = 0; i < num_iters; i++) result = expandOnce(result);
	//Debugging: result-string seems correct
	//printf("%s\n", result.c_str());
    return result;
}

std::vector<Segment> LindenmayerSystem::draw(std::string const& symbols) {
    std::vector<Segment> lines; // this is already initialized as empty vector
    /*============================================================
        TODO 2
        Build line segments according to the sequence of symbols
        The initial position is (0, 0) and the initial direction is "up" (0, 1)
        Segment is std::pair<vec2, vec2>

        you can create a Segment as {p1, p2}, where p1 and p2 are vec2, e.g.:
        lines.push_back({p1, p2});

        You may also find std::stack useful:

        https://en.cppreference.com/w/cpp/container/stack

        There also is a mat2 class in utils/vec.* you may find useful for
        implementing rotations.
    */

    //============================================================
	std::stack<vec2> dirToJumpBack;             
	std::stack<vec2> posToJumpBack;
	vec2 pos = vec2(0, 0);
	vec2 dir = vec2(0, 1);
	// Debugging
	//std::cout << dir << "\n";
	for (int i = 0; i < symbols.length(); i++) {
		// Debugging
		//std::cout << dir << "\n";
		if (symbols.at(i) == '+') dir = changeDir(this->rotation_angle_deg, dir);
		if (symbols.at(i) == '-') dir = changeDir(-this->rotation_angle_deg, dir);
		if (symbols.at(i) == 'F') {
			vec2 start = pos;
			vec2 end = start + dir;
			lines.push_back({start, end});
			//std::cout << start << " -> " << end;
			pos = end;
		}
		if (symbols.at(i) == '[') {
			dirToJumpBack.push(dir);
			posToJumpBack.push(pos);
		}
		if (symbols.at(i) == ']') {
			pos = posToJumpBack.top();
			posToJumpBack.pop();
			dir = dirToJumpBack.top();
			dirToJumpBack.pop();
		}
	}
	
	return lines;
}

vec2 changeDir(float _angle, vec2 dir) {
	float angle_rad = _angle * M_PI / 180.0;
	mat2 rotation = mat2(cos(angle_rad),-sin(angle_rad),
					sin(angle_rad),cos(angle_rad));
	return rotation * dir;
}


std::string LindenmayerSystemStochastic::expandSymbol(unsigned char const& sym) {
    /*============================================================
        TODO 4
        For a given symbol in the sequence, what should it be replaced with after expansion?
        (stochastic case)

        Use dice.roll() to get a random number between 0 and 1
    */

	
	auto const search = rules.find(sym);
	if (search == rules.end()) {
		return { char(sym) };
	};

	auto iteration = this->rules.begin();
	auto secondIteration = iteration->second.begin();
	double diceroll = dice.roll();

	for (iteration; iteration != this->rules.end(); iteration++) {
		if (sym == iteration->first) {
			for (secondIteration; secondIteration != iteration->second.end(); secondIteration++) {
				if (diceroll <= secondIteration->probability) {
					return secondIteration->expansion;
				}
			}
		}
	}

	return { char(sym) };
    
}

void LindenmayerSystemDeterministic::addRuleDeterministic(unsigned char sym, std::string const& expansion) {
    rules[sym] = expansion;
}

void LindenmayerSystemStochastic::addRuleStochastic(unsigned char sym, std::vector<StochasticRule> expansions_with_ps) {
    rules[sym] = expansions_with_ps;
}
