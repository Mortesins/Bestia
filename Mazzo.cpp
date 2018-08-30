#include "Mazzo.hpp"

Mazzo::Mazzo()
{
   unsigned j = 0;
   // BASTONI
   mazzo[j] = new Carta('B','2');
   j++;
   for (unsigned i = 4; i <= 7 ; i++)
   {
      mazzo[j] = new Carta('B',i+'0');
      j++;
   }
   mazzo[j] = new Carta('B','F');
   j++;
   mazzo[j] = new Carta('B','C');
   j++;
   mazzo[j] = new Carta('B','R');
   j++;
   mazzo[j] = new Carta('B','3');
   j++;
   mazzo[j] = new Carta('B','A');
   j++;
   // COPPE
   mazzo[j] = new Carta('C','2');
   j++;
   for (unsigned i = 4; i <= 7 ; i++)
   {
      mazzo[j] = new Carta('C',i+'0');
      j++;
   }
   mazzo[j] = new Carta('C','F');
   j++;
   mazzo[j] = new Carta('C','C');
   j++;
   mazzo[j] = new Carta('C','R');
   j++;
   mazzo[j] = new Carta('C','3');
   j++;
   mazzo[j] = new Carta('C','A');
   j++;
   // DENARI
   mazzo[j] = new Carta('D','2');
   j++;
   for (unsigned i = 4; i <= 7 ; i++)
   {
      mazzo[j] = new Carta('D',i+'0');
      j++;
   }
   mazzo[j] = new Carta('D','F');
   j++;
   mazzo[j] = new Carta('D','C');
   j++;
   mazzo[j] = new Carta('D','R');
   j++;
   mazzo[j] = new Carta('D','3');
   j++;
   mazzo[j] = new Carta('D','A');
   j++;
   // SPADE
   mazzo[j] = new Carta('S','2');
   j++;
   for (unsigned i = 4; i <= 7 ; i++)
   {
      mazzo[j] = new Carta('S',i+'0');
      j++;
   }
   mazzo[j] = new Carta('S','F');
   j++;
   mazzo[j] = new Carta('S','C');
   j++;
   mazzo[j] = new Carta('S','R');
   j++;
   mazzo[j] = new Carta('S','3');
   j++;
   mazzo[j] = new Carta('S','A');
   j++;
}

Mazzo::~Mazzo()
{
   for (unsigned i = 0; i < 40; i++)
      delete mazzo[i];
}

Carta* Mazzo::getCartaPointer(char s, char v) const
{
   for (unsigned i = 0; i < 40; i++)
   {
      if (s == mazzo[i]->getSeme() && v == mazzo[i]->getValore())
         return mazzo[i];
   }
   return NULL;
}

Carta* Mazzo::getCartaPointer(unsigned i) const
{
   if (i >= 0 && i < 40)
      return mazzo[i];
   else
      return NULL;
}

ostream& operator<<(ostream& os, const Mazzo& m)
{
   for (unsigned i = 0; i < 40; i++)
   {
      if (m.mazzo[i] != NULL)
      {
         os << "[" << i+1 << "]: " <<  *(m.mazzo[i]) << endl;
      }
   }
   return os;
}
