#ifndef EXPR_H_
#define EXPR_H_

#include <iostream>
#include <string>
using namespace std;

class Expr_node{
	friend ostream& operator<<(ostream &,const Expr_node&);
	friend class Expr;

protected:
	Expr_node():use(1){}
public:
	virtual void print(ostream &) const =0;
	virtual ~Expr_node(){}
private:
	int use;
	
};

class Expr{
	friend ostream& operator<<(ostream &o,const Expr&);
	Expr_node *p;

public:
	Expr(int);
	Expr(const string&,Expr);
	Expr(const string&,Expr,Expr);
	Expr(const Expr& t)
	{
		p = t.p;
		++p->use;
	}
	Expr& operator=(const Expr&);
	~Expr(){if(--(p->use) == 0)delete p;}

};


class Int_node:public Expr_node{
	friend class Expr;
	int n;
	Int_node(int k):n(k){}
	void print(ostream &o) const{ o << n ;}
	~Int_node(){}

};


class Unary_node : public Expr_node{
	friend class Expr;
	string op;
	Expr opnd;
	Unary_node(const string &a,Expr b):
		op(a),opnd(b)  {}
	void print(ostream & o)const
		{o<<"("<<op<<opnd<<")";}
	~Unary_node(){}

};

class Binary_node :public Expr_node{
	friend class Expr;
	string op;
	Expr left;
	Expr right;
	Binary_node(const string &a,Expr b,Expr c):
		op(a),left(b),right(c){}
	void print(ostream & o)const
	{
		o << "(" << left << op << right << ")";
	}
	~Binary_node(){}

};







#endif 
