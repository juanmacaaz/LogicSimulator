#include "parser.h"

/*Implicant::Implicant(int value, int nBits)
{
	int res;
	m_nBits = nBits;
	for (int i = 0; i < nBits; i++)

	{
		res = value % 2;
		value /= 2;
		if (res == 0)
			m_bits.push_back(Implicant::ZERO);
		else
			m_bits.push_back(Implicant::ONE);
	}
}

vector<Implicant::BitState> Implicant::getBits() const
{
	return m_bits;
}


int Implicant::nOnes() const
{
	int counter = 0;
	for (Implicant::BitState bit : m_bits)
		if (bit == Implicant::ONE)
			counter++;
	return counter;
}

vector<Implicant::BitState> Implicant::operator^(Implicant imp)
{
	vector<Implicant::BitState> bits = imp.getBits();
	vector<Implicant::BitState> ret;
	for (unsigned int i = 0; i < m_nBits; i++)
		if (m_bits[i] == bits[i])
			ret.push_back(Implicant::ONE);
		else
			ret.push_back(Implicant::ZERO);
	}

	return ret;
}

Implicant Implicant::operator+(Implicant imp)
{
	vector<Implicant::BitState> bits = imp.getBits();
	vector<Implicant::BitState> ret;
	for (unsigned int i = 0; i < m_nBits; i++)
		if (m_bits[i] == bits[i])
			ret.push_back(Implicant::ONE);
		else
			ret.push_back(Implicant::ZERO);
	}

	Implicant result(ret, m_nBits);
	return result;
}*/


//Estas funciones permiten que las expresiones se evaluen recursivamente ejecutando la operacion
//necesaria en cada caso. El caso limite es la clase "Var", donde simplemente devuelve el valor
//de esa variable mirandola en un diccionario que recive como parametro.
bool And::eval(const unordered_map<string,bool> &dict) const
{
    return ((m_left->eval(dict))&&(m_right->eval(dict)));
}

bool Or::eval(const unordered_map<string,bool> &dict) const
{
    return ((m_left->eval(dict))||(m_right->eval(dict)));
}

bool Xor::eval(const unordered_map<string,bool> &dict) const
{
    return ((m_left->eval(dict))!=(m_right->eval(dict)));
}

bool Not::eval(const unordered_map<string,bool> &dict) const
{
    return !(m_left->eval(dict));
}

bool Var::eval(const unordered_map<string,bool> &dict) const
{
    return dict.at(m_name);
}

//Esta funcion obtiene el numero de variables y sus nombres de forma recursiva
void Operation::getInfo(int* nVars, vector<string>* names) const
{
	m_left->getInfo(nVars, names);
	m_right->getInfo(nVars, names);
}

void Not::getInfo(int* nVars, vector<string>* names) const
{
    m_left->getInfo(nVars, names);
}

void Var::getInfo(int* nVars, vector<string>* names) const
{
	bool eq = false;

    for (string name : *names)
        if (name == m_name)
            eq = true;

	if (!eq)
	{
		(*nVars)++;
		names->push_back(m_name);
	}
}


//Esta funcion toma como argumento una string con una expresion logica y la parsea a un arbol 
//de objetos "Operation" de forma recursiva.
Operation* parse(string expression, vector<string>* parenthesis)
{
	vector<string> splitted;
	int position, counter;

	counter = 0;
	position = expression.find('(');
	do {
		if (position != string::npos)
		{
			for (unsigned int i = position + 1; i < expression.length(); i++)
			{
				if (expression[i] == '(')
					counter++;

				if (expression[i] == ')')
				{
					if (counter == 0)
					{
						parenthesis->push_back(expression.substr(position + 1, i - position - 1));
						expression.replace(position, i - position + 1, to_string(parenthesis->size()-1));
					}
					else
						counter--;
				}
			}
			position = expression.find('(');
		}
		
	} while (position != string::npos);

	if (expression.find('+') != string::npos)
	{
		splitted = split(expression, '+');
		return new Or(parse(splitted[0], parenthesis), parse(splitted[1], parenthesis));
	}
	else if (expression.find('*') != string::npos)
	{
		splitted = split(expression, '*');
		return new And(parse(splitted[0], parenthesis), parse(splitted[1], parenthesis));
	}
	else if (expression.find('-') != string::npos)
	{
		splitted = split(expression, '-');
		return new Xor(parse(splitted[0], parenthesis), parse(splitted[1], parenthesis));
	}
	else
	{
		if (expression[0] == '!')
		{
			if (expression[1] >= 47 && expression[1] <= 57)
				return new Not(parse((*parenthesis)[stoi(expression.substr(1, expression.length() - 1))], parenthesis));
			else
				return new Not(new Var(expression.substr(1, expression.length() - 1)));
		}
		else
		{
			if (expression[0] >= 47 && expression[0] <= 57)
				return parse((*parenthesis)[stoi(expression)]);
			else
				return new Var(expression);
		}
	}
}

//Esta funcion recibe una funcion logica, el numero de variables y un vector con el nombre de las variables
//y devuelve la tabla de verdad de la funcion, siendo la primera variable del vector el bit menos significante.
vector<bool> getTable(Operation* function, int nVars,  vector<string> names)
{
	vector<bool> table;
    unordered_map<string,bool> dict;
    for (string name : names)
    {
        dict.emplace(name, true);
    }
	
	for (int i = 0; i < pow(2, nVars); i++)
	{
		for (int j = 0; j < nVars; j++)
			if (i % ((int)pow(2, j)) == 0)
				dict[names[nVars - j - 1]] = !(dict[names[nVars - j - 1]]);
		table.push_back(function->eval(dict));
	}
	return table;
}

//Esta funcion recive una tabla de verdad y el numero de variables y devuelve un vector con los minterms.
vector<int> getMinterms(vector<bool> table, int nVars)
{
    vector<int> minterms;
    for (int i = 0; i < pow(2, nVars); i++)
    {
        if (table[i])
            minterms.push_back(i);
    }
    return minterms;
}

//Funcion auxiliar para separar una string en dos desde un caracter.
vector<string> split(string str, char separator)
{
	vector<string> sp = {};

	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == separator)
		{
			sp.push_back(str.substr(0, i));
			sp.push_back(str.substr(i + 1, str.length() - 1));
			break;
		}
	}

	return sp;
}

//Comprueba si una expresion es valida, es decir, los parentesis estan bien puestos,
//el nombre de las variables no comienza por un numero y no esta vacia.
bool validInput(string expression, string* msg)
{
	int parenthesis = 0;

	if (expression.length() == 0)
	{
		*msg = "Error, string vacia.";
		return false;
	}
	
	for (unsigned int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == '(')
			parenthesis++;
		else if (expression[i] == ')')
			parenthesis--;

		if ((expression[i] <= 90 && expression[i] >= 65
			|| expression[i] <= 122 && expression[i] >= 97) && i != 0)
			if (expression[i - 1] <= 57 && expression[i - 1] >= 48)
			{
				*msg = "Error, el nombre de las variables no puede comenzar por un numero.";
			}
	}

	if (parenthesis != 0)
	{
		*msg = "Error, parentesis mal colocados.";
		return false;
	}

	return true;
}

//Funcion para limpiar el string de espacios
void quitSpaces(string* str)
{
	for (unsigned int i = str->length() - 1; i > 0; i--)
		if ((*str)[i] == ' ')
			str->replace(i, 1, "");
}

/*
//Reduccion por el metodo de Quine-McCluskey
string mcCluskey(vector<int> minterms, int nVars, vector<string> names)
{
	vector<Implicant> primes;
	Implicant matrix[100][100];
}*/

