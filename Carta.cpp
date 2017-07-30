#include "Carta.hpp"

Carta::Carta(char s, char v)
   :seme(s), valore(v)
{   
}

ostream& operator<<(ostream& os, const Carta& c)
{
   char s = c.getSeme();
   char v = c.getValore();
   switch (v)
   {
      case 'A':
         os << "Asso";
         break;
      case '3':
         os << "Tre";
         break;
      case 'R':
         os << "Re";
         break;
      case 'C':
         os << "Cavallo";
         break;
      case 'F':
         os << "Fante";
         break;
      default:
         os << v;
         break;
   }
   os << " di ";
   switch (s)
   {
      case 'B':
         os << "Bastoni";
         break;
      case 'C':
         os << "Coppe";
         break;
      case 'D':
         os << "Denari";
         break;
      case 'S':
         os << "Spade";
         break;
   }
   return os;
}
