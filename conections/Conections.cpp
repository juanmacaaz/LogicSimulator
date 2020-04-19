/*
  Clase encargada de pasar de una lista
  de conexiones (cables) a una funcion logica.
*/
#include <string>
#include <algorithm>
#include <cctype>
#include <QtDebug>
#include "Conections.h"

using namespace std;

/*
  Comprueba que el numero de entradas es valido y devuelve una lista de Cables
  que seran las funciones del circuito.
*/
bool Conections::isValid(vector<Cable> &outCable) const {
  int numFunctions = 0;
  for(const Cable &cable : m_cable) {
    if(cable.getB().getElement() == GGate::OUTPUT) {
      outCable.push_back(cable);
      numFunctions++;
    }
  }
  return (numFunctions>0);
}

vector<string> Conections:: getFunctions() {
  vector <Cable> outCable;
  vector <string> functions;
  if(isValid(outCable)){
    for (const Cable &cable : outCable) {
      string function = m_varNames[cable.getB().getPosition()] + " = " + parseExpresion(toExpresion(cable));
      functions.push_back(function);
    }
  }
  return functions;
}

/*
  Pasa la lista a una funcion.
  in1, and1
  in2, and1  --- > (a*b)
  and1, out
  Parte de la salida y va realizando un camino hasta llegar a las entradas
  mediante un algoritmo recursivo.
*/
string Conections::toExpresion (const Cable &cable) const{
  string expresion = "";
  expresion+="(";
  for(const Cable& x : m_cable) {
    if ((x.getB() == cable.getA())
            || (x.getB().getElement() == GGate::OUTPUT
                && cable.getA().getElement() == GGate::INPUT && (cable == x))) {
      if(x.getB().getElement() == GGate::INV) {
         expresion+="!";
      }
      if(x.getA().getElement() == GGate::INPUT) {
        int input = x.getA().getPosition();
        expresion+=to_string(input);
      }else {
        expresion+=toExpresion(x);
      }
      char enumToChar;
      switch(x.getB().getElement()) {
        case GGate::AND: enumToChar='*'; break;
        case GGate::OR:  enumToChar='+'; break;
        case GGate::XOR: enumToChar='-'; break;
        default: enumToChar = ':'; break;
      }
      expresion+=enumToChar;
    }
  }
  expresion = expresion.substr(0,expresion.length()-1);
  expresion+=")";
  return expresion;
}

void Conections::addCable(const Cable &cable) {
  m_cable.push_back(cable);
}

void Conections::deleteCable(const Cable &cable) {
    m_cable.erase(std::remove(m_cable.begin(), m_cable.end(), cable), m_cable.end());
}

string Conections::parseExpresion(string function)
{
    int index = 0;
    string newStr = "";
    for(char x: function){
        if(isdigit(x)){
            string subStr = "";
            int subIndex = index;
            while(isdigit(function[subIndex])){
                subStr+=function[subIndex];
                subIndex++;
            }
            newStr+=m_varNames[atoi(subStr.c_str())];
        }else{
            newStr+=x;
        }
        index++;
    }
    return newStr;
}
