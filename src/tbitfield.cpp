// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{

	this -> BitLen=len;


	pMem=new TELEM [len];


}

TBitField::TBitField(const TBitField & pMem1 ) // конструктор копирования
{

   TBitField pMem1(BitLen);


   for (int i=1; i < BitLen; i++)

	   pMem1[i]=pMem[i];


}

TBitField::~TBitField()
{

	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int k = n/16;
	
	int MemIndex = n - 16 * k;

    return MemIndex;

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

	int k=1;
	
	int i=0;


	while (i < n )

    k >> 1;

	i++;


}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen ;
}

void TBitField::SetBit(const int n) // установить бит
{

	int a = GetMemIndex(n);


    if ((n >= 0) && (n < BitLen)) 

    pMem[a] = pMem[a] | GetMemMask(n); 


}

void TBitField::ClrBit(const int n) // очистить бит
{

	int a = GetMemIndex(n); 


    if ((n >= 0) && (n < BitLen))

   pMem[a] = pMem[a] & ~GetMemMask(n); 


}

int TBitField::GetBit(const int n) const // получить значение бита
{

	int a = GetMemIndex(n); 


   if ((n >= 0) && (n < BitLen)) 

     return pMem[a] & GetMemMask(n); 

  }

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

	BitLen = bf.BitLen; 

    MemLen = bf.MemLen; 

   pMem = new TELEM [MemLen]; 

   for (int i=0;i<MemLen;i++) { 
      
	   pMem[i] = bf.pMem[i]; 

} 


return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen!=bf.MemLen){
	
	return 0;
		
	}

	for (int i=0; i<MemLen; i++){
	
		if(pMem[i]!=bf.pMem[i]){
		
		return 0;

		break;
		
		} 
	
	return 1;


	} 


}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (MemLen!=bf.MemLen){
	
	return 1;
		
	}
   

	for (int i=0; i<MemLen; i++){
	
		if(pMem[i]==bf.pMem[i]){
		
		return 0;

		break;
		
		} 
	
	return 1;


	} 
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	int len; 



      if (BitLen >= bf.BitLen) len = BitLen; 

     else len = bf.BitLen; 

TBitField or(len); 


     for (int i=0;i<or.MemLen;i++) { 

		 or.pMem[i] = bf.pMem[i] | pMem[i]; 
} 

	 return or; 


}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

    int len; 

	if (BitLen >= bf.BitLen) len = BitLen; 

	else len = bf.BitLen; 

	TBitField and(len); 

	for (int i=0;i<and.MemLen;i++) { 

		and.pMem[i] = bf.pMem[i] & pMem[i]; 

	} 

	return and; 



}

TBitField TBitField::operator~(void) // отрицание
{


	int len = BitLen; 

	TBitField not(len); 

	for (int i=0;i < MemLen;i++) { 

		not.pMem[i] = ~pMem[i]; 

	} 

	return not; 

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{


for (int i=0;i<bf.MemLen;i++) { 

	istr >> bf.pMem[i]; 

} 


return istr; 

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{


	for (int i=0; i<bf.MemLen;i++) { 

		ostr << bf.pMem[i]; 

	} 

	
	return ostr; 

}
