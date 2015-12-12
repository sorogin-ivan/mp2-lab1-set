// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h" 


TBitField::TBitField(int len) 
{ 
if (len < -1) { 
throw 
out_of_range("Out_of_range"); 
} 
MemLen = (len + 15) >> 4; 
pMem = new TELEM[MemLen]; 
for ( int i=0; i < MemLen; i++ ) 
pMem[i] = 0; 
BitLen = len; 
} 

TBitField::TBitField(const TBitField &bf) // конструктор копирования 
{ 
BitLen = bf.BitLen; 
MemLen = bf.MemLen; 
pMem = new TELEM[MemLen]; 
for (int i=0;i<MemLen;i++) 
pMem[i] = bf.pMem[i]; 
} 

TBitField::~TBitField() 
{ 
delete []pMem; 
} 

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{ 
return n >> 4; 
} 

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n 
{ 
return 1 << (n & 15); 
} 

// доступ к битам битового поля 

int TBitField::GetLength(void) const // получить длину (к-во битов) 
{ 
return (BitLen); 
} 

void TBitField::SetBit(const int n) // установить бит 
{ 
int a = GetMemIndex(n); 
if ((n < 0) || (n > BitLen)) 
throw 
out_of_range("Out_of_range"); 
pMem[a] = pMem[a] | GetMemMask(n); 
} 


void TBitField::ClrBit(const int n) // очистить бит 
{ 
int a = GetMemIndex(n); 
if ((n < 0) || (n > BitLen)) 
throw 
out_of_range("Out_of_range"); 
pMem[a] = pMem[a] & ~GetMemMask(n); 

} 

int TBitField::GetBit(const int n) const // получить значение бита 
{ 
int a = GetMemIndex(n); 
if ((n < 0) || (n > BitLen)) 
throw 
out_of_range("Out_of_range"); 
return pMem[a] & GetMemMask(n); 
} 

// битовые операции 

TBitField& TBitField::operator=(const TBitField &bf) // присваивание 
{ 
BitLen = bf.BitLen; 
MemLen = bf.MemLen; 
delete []pMem; 
pMem = new TELEM [MemLen]; 
for (int i=0;i<MemLen;i++) { 
pMem[i] = bf.pMem[i]; 
} 
return *this; 
} 

int TBitField::operator==(const TBitField &bf) const // сравнение 
{ 
int a; 
if (MemLen == bf.MemLen) { 
for (int i=0;i<MemLen;i++) { 
if (pMem[i] != bf.pMem[i]) { 
a = 0; 
break; 
} 
} 
a = 1; 
} 
return a; 
} 

int TBitField::operator!=(const TBitField &bf) const // сравнение 
{ 
int a; 
if (MemLen == bf.MemLen) { 
for (int i=0;i<MemLen;i++) { 
if (pMem[i] = bf.pMem[i]) { 
a = 0; 
break; 
} 
}; 
a = 1; 
} 
return a; 
} 

TBitField TBitField::operator|(const TBitField &bf) // операция "или" 
{ 
int a; 
if (BitLen >= bf.BitLen) a = BitLen; 
else a = bf.BitLen; 
TBitField x(a); 
for (int i=0;i<x.MemLen;i++) { 
x.pMem[i] = bf.pMem[i] | pMem[i]; 
} 
return x; 
} 

TBitField TBitField::operator&(const TBitField &bf) // операция "и" 
{ 
int a; 
if (BitLen >= bf.BitLen) a = BitLen; 
else a = bf.BitLen; 
TBitField x(a); 
for (int i=0;i<x.MemLen;i++) { 
x.pMem[i] = bf.pMem[i] & pMem[i]; 
} 
return x; 
} 

TBitField TBitField::operator~(void) // отрицание 
{ 
int a = BitLen; 
TBitField x(a); 
for (int i=0;i < MemLen;i++) { 
x.pMem[i] = ~pMem[i]; 
} 
return x; 
}