#include <vector>
#include <unordered_map>
#include <string>
#include <math.h>
#include <iostream>
using namespace std;

/*class Implicant

{
public:
	enum BitState
	{
		ZERO,
		ONE,
		X
	};

	Implicant(int value, int nBits);
	Implicant(vector<Implicant::BitState> bits, int nBits) : m_bits(bits), m_nBits(nBits) {};
	vector<Implicant::BitState> getBits() const;
	int nOnes() const;
	vector<Implicant::BitState> operator^(Implicant imp);
	Implicant operator+(Implicant imp);
	
private:
	vector<Implicant::BitState> m_bits;
	unsigned int m_nBits;

};*/


class Operation
{
protected:
    Operation *m_left;
    Operation *m_right;
public:
    Operation(Operation* left, Operation* right) : m_left(left), m_right(right) {};
    virtual bool eval(const unordered_map<string,bool> &dict) const = 0;
	virtual void getInfo(int* nVars, vector<string>* names) const;
};

class And : public Operation
{
public:
	And(Operation* left, Operation* right) : Operation(left, right) {};
    bool eval(const unordered_map<string,bool> &dict) const;
};

class Or : public Operation
{
public:
	Or(Operation* left, Operation* right) : Operation(left, right) {};
    bool eval(const unordered_map<string,bool> &dict) const;
};

class Xor : public Operation
{
public:
	Xor(Operation* left, Operation* right) : Operation(left, right) {};
    bool eval(const unordered_map<string,bool> &dict) const;
};

class Not : public Operation
{
public:
    Not(Operation* left) : Operation(left, nullptr) {};
    bool eval(const unordered_map<string,bool> &dict) const;
    void getInfo(int* nVars, vector<string>* names) const;
};

class Var : public Operation
{
protected:
    string m_name;
public:
    Var(string name) : Operation(nullptr, nullptr), m_name(name) {};
    bool eval(const unordered_map<string,bool> &dict) const;
	void getInfo(int* nVars, vector<string>* names) const;
};

Operation* parse(string expression, vector<string>* parenthesis = new vector<string>());

vector<bool> getTable(Operation* function, int nVars, vector<string> names);

vector<int> getMinterms(vector<bool> table, int nVars);

vector<string> split(string str, char separator);

bool validInput(string expression, string* msg);

void quitSpaces(string* str);



//string mcCluskey(vector<int> minterms, vector<string> names);
