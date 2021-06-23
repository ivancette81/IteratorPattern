#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
#define MAX_NUM_PRECIOS 5
class Precio 
{
	int value;
	std::string currency;
public:
	Precio(int value, std::string currency)
	{
		this->value = value;
		this->currency = currency;
	}

	int getValue()
	{
		return value;
	}
};


class IIterator
{
public:
	virtual bool hasNext() = 0;
	virtual void* next() = 0;
};
class ListaPreciosIterator : public IIterator
{
	Precio** listaPrecios;
	int numPrecios;
public:
	ListaPreciosIterator(Precio** listaPrecios)
	{
		this->listaPrecios = listaPrecios;
		numPrecios = 0;
	}
	bool hasNext()
	{
		return numPrecios < MAX_NUM_PRECIOS;
	}
	void* next()
	{
		return listaPrecios[numPrecios++];
	}
};

class IListaGenerica 
{
public:
		virtual void add(void* element) = 0;
		virtual IIterator *getIterator() = 0;
};


class ListaPrecios : public IListaGenerica
{
	Precio * listaPrecios[MAX_NUM_PRECIOS];
	int numElementos;
public:
	ListaPrecios(){
		numElementos = 0;
	}

	void add(void* element)
	{
		listaPrecios[numElementos++] = (Precio*)element;
	}
	IIterator * getIterator() {
		return new ListaPreciosIterator(listaPrecios);
	}
};



TEST(TestHappyPath, HappyPath) {

	IListaGenerica *listaPrecios = new ListaPrecios();
	listaPrecios->add(new Precio(2, "EUR"));
	listaPrecios->add(new Precio(4, "EUR"));
	listaPrecios->add(new Precio(6, "EUR"));
	listaPrecios->add(new Precio(8, "EUR"));
	listaPrecios->add(new Precio(10, "EUR"));

	IIterator *it = listaPrecios->getIterator();
	
	int i = 1;
	while (it->hasNext())
	{
		EXPECT_EQ(2*i++, ((Precio *)(it->next()))->getValue());
	}
}