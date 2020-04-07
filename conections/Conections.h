#include <list>
#include <vector>
#include "conections/Cable.h"

using namespace std;

class Conections {
  private:
    vector <Cable> m_cable;
    string toExpresion (const Cable &cable) const;
  public:
    Conections() {};
    bool isValid(vector<Cable> &outCable) const;
    vector<string> getFunctions();
    void addCable(const Cable &cable);
    void deleteCable(const Cable &cable);
};
