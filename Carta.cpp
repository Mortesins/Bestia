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

bool Carta::operator>(const Carta& c) // solo se stesso seme
{
	if (seme == c.seme)
	{
		switch (c.valore) // valore di operando destra,  a > b, b
		{
			case 'A':
				//cout << "A" << endl;
				return false;
				break;
			case '3':
				//cout << "3" << endl;
				return valore == 'A';
				break;
			case 'R':
				//cout << "R" << endl;
				return (valore == 'A') || (valore == '3');
				break;
			case 'C':
				//cout << "C" << endl;
				return (valore == 'A') || (valore == '3') || (valore == 'R');
				break;
			case 'F':
				//cout << "F" << endl;
				return (valore == 'A') || (valore == '3') || (valore == 'R') || (valore == 'C');
				break;
			default: // 7,6,5,4,2
				if ((valore == 'A') || (valore == '3') || (valore == 'R') || (valore == 'C') || (valore == 'F'))
					return true;
				return (valore - '0') > (c.valore - '0');
				break;
			
		}
	}	
	return false;
}

bool Carta::operator<(const Carta& c)
{
	return !(this->operator>(c));
}

bool aMAGGIOREb(char a, char b) //valore della carta senza tenere conto del seme
{
   switch (b) // valore di operando destra,  a > b, b
   {
      case 'A': // se b è un asso a non potrà essere più grande
         //cout << "A" << endl;
         return false;
         break;
      case '3':
         //cout << "3" << endl;
         return a == 'A';
         break;
      case 'R':
         //cout << "R" << endl;
         return (a == 'A') || (a == '3');
         break;
      case 'C':
         //cout << "C" << endl;
         return (a == 'A') || (a == '3') || (a == 'R');
         break;
      case 'F':
         //cout << "F" << endl;
         return (a == 'A') || (a == '3') || (a == 'R') || (a == 'C');
         break;
      default: // 7,6,5,4,2
         if ((a == 'A') || (a == '3') || (a == 'R') || (a == 'C') || (a == 'F'))
            return true;
         return (a - '0') > (b - '0');
         break;
   }
}

bool aMINOREb(char a, char b) //valore della carta senza contare il seme
{
   return aMAGGIOREb(b,a);
}

unsigned ilTerzoNumero(unsigned a, unsigned b)
{
   if (a == 0)
   {
      if (b == 1)
         return 2;
      else
         return 1;
   }
   if (a == 1)
   {
      if (b == 0)
         return 2;
      else
         return 0;
   }
   if (a == 2)
   {
      if (b == 0)
         return 1;
      else
         return 0;
   }
   return 4; //ERRORE
}
