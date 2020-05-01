#include <list>
#include <vector>
#include "conections/Cable.h"
#include <map>

using namespace std;

class Conections {
  private:
    map<long, string> m_varNames;
    vector <Cable> m_cable;
    string toExpresion (const Cable &cable, int &deep) const;
  public:
    Conections() {};
    bool isValid(vector<Cable> &outCable) const;
    vector<string> getFunctions();
    void addCable(const Cable &cable);
    void deleteCable(const Cable &cable);
    void setVarNames(const map<long, string> varNames) {m_varNames = varNames;}
    string parseExpresion(string function);
};
