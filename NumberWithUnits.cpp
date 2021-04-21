#include "NumberWithUnits.hpp"

namespace ariel{

  unordered_map<string,unordered_map<string ,double>> map;

  double convert(const string& t ,const string& f , double val){
    if(f==t){
      return val;
    }
      return map[f][t] * val;
  }

  bool check( NumberWithUnits const & l, NumberWithUnits const & r ) {
    if((l.str==r.str) && map.find(l.str) != map.end()) {return false;}
    if ( map.find(l.str) != map.end() && (map[l.str].find(r.str) != map[l.str].end())) {
                    return false;
            }
    return true;
  }


  void casting(const string &str1 ,const string &str2){
    for (auto& p : map[str1]){
      double cast=map[str2][str1] * p.second;
      map[str2][p.first]= cast;
      map[p.first][str2]= 1/cast;
  }
    for (auto& p : map[str2]){
      double cast=map[str1][str2] * p.second;
      map[str1][p.first]= cast;
      map[p.first][str1]= 1/cast;
  }
  }

  void NumberWithUnits::read_units(ifstream& input){
        string other;
        string str1;
        string str2;
        double val1= 0;
        double val2=0;
        while(input >> val1 >> str1 >> other >> val2 >> str2){
            map[str1][str2]=val2;
            map[str2][str1]=1/val2;

            casting(str1,str2);
    }
  }

  //************* + , =+ , + unry , - , =- , - unry  ,* left, right * ****************
   NumberWithUnits operator+( NumberWithUnits const & l, NumberWithUnits const & r ){
     if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}
     else{
       double conv=convert(l.str,r.str,r.val);
       return NumberWithUnits(l.val+conv,l.str);
     }
   }

   NumberWithUnits operator+( NumberWithUnits & val ){
     if(val.val<0){
        return NumberWithUnits((-1*val.val),val.str);
      }
        return NumberWithUnits(val.val,val.str);

   }

   NumberWithUnits operator+=( NumberWithUnits& l, const NumberWithUnits& r ){
      if(check(l,r)){  __throw_invalid_argument("Eror not same type");}
       double conv=convert(l.str,r.str,r.val);
       l.val+= conv;
       return l;
   }

   NumberWithUnits operator-( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}
       double conv=convert(l.str,r.str,r.val);
       return NumberWithUnits(l.val-conv,l.str);
   }

   NumberWithUnits operator-(NumberWithUnits & val) {
     return NumberWithUnits(-1*(val.val),val.str);
   }

   NumberWithUnits operator-=( NumberWithUnits & l, NumberWithUnits const & r ){
     if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}
      double conv=convert(l.str,r.str,r.val);
      l.val-= conv;
      return l;
   }

   NumberWithUnits operator*(NumberWithUnits& l, double val){
      return NumberWithUnits(l.val*val,l.str);
   }

   NumberWithUnits operator*(double val, NumberWithUnits& r){
     return NumberWithUnits(r.val*val,r.str);
   }

  //***************** > >= < <= == !=  ***************************


   bool operator==( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}
       double conv=convert(l.str,r.str,r.val);
       const double eps =0.0001;
       if (std::abs(l.val - conv) < eps){
         return true;  return false;
       }
         return false;
   }

   bool operator!=( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}

       double conv=convert(l.str,r.str,r.val);
       if(l.val != conv){
         return true; return false;
       }
         return false;

   }

   bool operator<( NumberWithUnits const & l, NumberWithUnits const & r ){
     if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}

       double conv=convert(l.str,r.str,r.val);
       if(l.val < conv){
         return true;  return false;
       }
         return false;
   }

   bool operator<=( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)) {  __throw_invalid_argument("Eror not same type");}

       double conv=convert(l.str,r.str,r.val);
       if(l.val <= conv){
         return true;  return false;
       }
         return false;

   }

   bool operator>( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)){  __throw_invalid_argument("Eror not same type");}

       double conv=convert(l.str,r.str,r.val);
       if(l.val > conv){
         return true;  return false;
       }
         return false;

   }

   bool operator>=( NumberWithUnits const & l, NumberWithUnits const & r ){
      if(check(l,r)) {         __throw_invalid_argument("Eror not same type");}

       double conv=convert(l.str,r.str,r.val);
       if(l.val >= conv){
         return true;  return false;

       }
         return false;


   }
  //********************** ++ -- *******************************

     //val--
    NumberWithUnits operator--( NumberWithUnits & val, int ){
        return NumberWithUnits(val.val--,val.str);
    }
    //--val
    NumberWithUnits & operator--( NumberWithUnits & val ){
      val.val--;
      return val;
    }

    NumberWithUnits & operator++( NumberWithUnits & val ){
         val.val++;
        return val;
    }
    NumberWithUnits operator++( NumberWithUnits & val, int ){
        return NumberWithUnits(val.val++,val.str);
    }

// ****************** << >> ***************************
    ostream& operator<<(ostream& out, const NumberWithUnits& val){
        return out<<val.val<<"["<<val.str<<"]";
        //2[km]
    }
   istream& operator>>(istream& input, NumberWithUnits& val){
     string t;
     input >> val.val>> t >> val.str;
     return input;
   }
}
