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
	virtual int eval() const = 0;
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
	Expr(const string &op ,Expr left,Expr middle,Expr right);
	Expr(const Expr& t)
	{
		p = t.p;
		++p->use;
	}
	Expr& operator=(const Expr&);
	~Expr(){if(--(p->use) == 0)delete p;}

	int eval()const{return p->eval();}
//add
};


class Int_node:public Expr_node{
	friend class Expr;
	int n;
	Int_node(int k):n(k){}
	void print(ostream &o) const{ o << n ;}
	int eval()const {return n;}
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
	int eval ()const
	{
		if(op == "-")
			return -opnd.eval();
		throw "error,bad op";
	}

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
	int eval()const
	{
		int op1 = left.eval();
		int op2 = right.eval();
		if(op == "-")return op1 - op2;
		if(op == "+")return op1 + op2;
		if(op == "*")return op1 * op2;
		if(op == "/" && op2 != 0 )return op1 / op2;
		throw "error, bad op";
	}
	~Binary_node(){}

};

class Ternary_node:public Expr_node{
	friend class Expr;
	string op;
	Expr left;
	Expr middle;
	Expr right;
	Ternary_node(const string &a ,Expr b, Expr c,Expr d):
		op(a),left(b),middle(c),right(d){}
	void print(ostream &o) const
	{
		o << "("<<left<<"?"<<middle<< ":"<<right <<")";
	}
	int eval()const
	{
		if(left.eval())
			return middle.eval();
		else
			return right.eval();
	}

};






#endif 
