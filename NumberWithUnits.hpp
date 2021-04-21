#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;

namespace ariel{
        class NumberWithUnits {

        private:
          double val;
          string str;

          double convert(const string& f ,const string& t , double val);
          
          friend bool check( NumberWithUnits const & l, NumberWithUnits const & r );
          public:
          NumberWithUnits(double val ,string str){
            this->val=val;
            this->str = str;
          }

          ~NumberWithUnits(){}
          static void read_units(ifstream& input);

          //************* + , += , + unry , - , -= , - unry  ,* left, right * ****************
          friend NumberWithUnits operator+( NumberWithUnits const & l, NumberWithUnits const & r );

          friend NumberWithUnits operator+( NumberWithUnits & val );

          friend NumberWithUnits operator+=( NumberWithUnits& l, const NumberWithUnits& r );

          friend NumberWithUnits operator-( NumberWithUnits const & l, NumberWithUnits const & r );

          friend NumberWithUnits operator-(NumberWithUnits & val) ;

          friend NumberWithUnits operator-=( NumberWithUnits & l, NumberWithUnits const & r );

          friend NumberWithUnits operator*(NumberWithUnits& l, double val);

          friend NumberWithUnits operator*(double val, NumberWithUnits& r);

          //***************** > >= < <= == !=  ***************************


          friend bool operator==( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator!=( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator<( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator<=( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator>( NumberWithUnits const & l, NumberWithUnits const & r );

          friend bool operator>=( NumberWithUnits const & l, NumberWithUnits const & r );
          //********************** ++ -- *******************************

          friend  NumberWithUnits operator--( NumberWithUnits & val, int );
          friend  NumberWithUnits & operator--( NumberWithUnits & val );
          friend  NumberWithUnits & operator++( NumberWithUnits & val );
          friend  NumberWithUnits operator++( NumberWithUnits & val, int );
          //operator *

          //operator <<
          friend ostream& operator<<(ostream& out, const NumberWithUnits& val);
          friend istream& operator>>(istream& input, NumberWithUnits& val);
        };
}
