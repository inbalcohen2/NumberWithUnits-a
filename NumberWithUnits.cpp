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
    if( (l.str==r.str) 
          || (("km"==l.str&&"m"==r.str) || ("km"==r.str&&"m"==l.str))
          || (("km"==l.str&&"cm"==r.str) || ("km"==r.str&&"cm"==l.str))
          || (("m"==l.str&&"cm"==r.str) || ("m"==r.str&&"cm"==l.str))
          || (("kg"==l.str&&"ton"==r.str) || ("ton"==l.str&&"kg"==r.str))
          || (("kg"==l.str&&"g"==r.str) || ("g"==l.str&&"kg"==r.str))
          || (("g"==l.str&&"ton"==r.str) || ("ton"==l.str&&"g"==r.str))
          ||(("hour"==l.str&&"min"==r.str) || ("min"==l.str&&"hour"==r.str))
          ||(("hour"==l.str&&"sec"==r.str) || ("sec"==l.str&&"hour"==r.str))
          ||(("sec"==l.str&&"min"==r.str) || ("min"==l.str&&"sec"==r.str))){
            return false; return true;
          }
      return true;
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
