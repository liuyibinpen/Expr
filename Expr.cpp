#include <iostream>
#include "Expr.h"

using namespace std;



ostream& operator<<(ostream &o,const Expr_node& e)
{
	e.print(o);
	return o;
}


Expr::Expr(int n)
{
	p = new Int_node(n);
}
Expr::Expr(const string &op ,Expr t)
{
	p = new Unary_node(op,t);
}
Expr::Expr(const string &op ,Expr left,Expr right)
{
	p = new Binary_node(op,left,right);
}
Expr& Expr::operator=(const Expr& rhs)
{
	rhs.p->use++;
	if(--p->use == 0)
		delete p;
	p = rhs.p;
	return *this;
}

ostream& operator<<(ostream &o,const Expr&t)
{
	t.p->print(o);
	return o;
}


int main()
{
	Expr t = Expr("*",Expr("-",5),Expr("+",3,4));
	cout<< t << endl;

	t = Expr("*",t,t);
	cout<< t << endl;

}
