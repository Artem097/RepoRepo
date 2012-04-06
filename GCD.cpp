#include <stdlib.h>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

template<typename T> 
T gcd_search(const T& arg_1, const T& arg_2) 
{
	T a(arg_1); 
	T b(arg_2);
	assert(a != T(0) || b != T(0));

	while(a!= T(0) && b!= T(0)) {
		a = a%b;
		T temp(b);
		b = a;
		a = temp;
	}
	if(a == T(0)) return b;
	else return a;
}

class Polynom 
{
private:
	vector<double> _polynom;
public:
	void normalize() {
		vector<double>:: iterator it = _polynom.begin();
		while(it != _polynom.end() && *it == 0) {
			_polynom.erase(it);
		}
	}
	vector<double>& get_polynom() {
		return _polynom;
	}
	const vector<double>& get_polynom() const {
		return _polynom;
	}
	int get_degree() const {
		return _polynom.size() - 1;
	}
	Polynom() {}
	Polynom(const double constant) {
		_polynom.push_back(constant);
	    normalize();
	}
	Polynom(const vector<double>& poly) {
		for(int i = 0; i < poly.size(); i++) {
			_polynom.push_back(poly[i]);
		}
		normalize();
	}
	Polynom(const Polynom& Poly) {
		for(int i = 0; i <= Poly.get_degree(); i++) {
			_polynom.push_back(Poly[i]);
		}
	}
	double& operator [] (int i) {
		return _polynom[i];
	}
    double operator [] (int i) const {
		return _polynom[i];
	}
	bool operator < (const Polynom& Poly) const {
		if(get_degree() < Poly.get_degree())
			return true;
		else 
			return false;
	}       
	Polynom& operator = (const Polynom& Poly) {
		_polynom.clear();
		for(int i = 0; i <= Poly.get_degree(); i++) {
		    _polynom.push_back(Poly[i]);
		}
		return *this;
	}
	bool operator == (const Polynom& Poly) const {
		if(_polynom == Poly.get_polynom())
			return true;
		else 
			return false;
	}
	bool operator != (const Polynom& Poly) const {
		if((*this) < Poly) 
			return true;
		else if(Poly < (*this)) 
			return true;
		else {
			bool is_notequal = false;
			int i = 0;
			while(!(is_notequal) && i < _polynom.size()) {
				if(_polynom[i] != Poly[i]) 
					is_notequal = true;
				++i;
			}
			return is_notequal;
		}
	}
	void print() {
		for(int i = 0; i < _polynom.size(); i++) {
			cout << _polynom[i] << ' ';
		}
		cout << endl;
	}
	~Polynom() {
		_polynom.clear();
	}
}; 

Polynom  operator + (const Polynom& Poly_1, const Polynom& Poly_2)
{
	Polynom Sum;
	int degree_difference = Poly_2.get_degree() - Poly_1.get_degree();
	if(degree_difference > 0) {
		for(int i = 0; i < degree_difference; i++) {
			Sum.get_polynom().push_back(Poly_2[i]);
		}
		for(int i = degree_difference; i <= Poly_2.get_degree() ; i++) {
			Sum.get_polynom().push_back(Poly_2[i] + Poly_1[i - degree_difference]);
		}
	}
	else {
		for(int i = 0; i < -degree_difference; i++) {
			Sum.get_polynom().push_back(Poly_1[i]);
		}
		for(int i = -degree_difference; i <= Poly_1.get_degree() ; i++) {
			Sum.get_polynom().push_back(Poly_1[i] + Poly_2[i + degree_difference]);
		}
	}
	Sum.normalize();
	return Sum;
}

Polynom  operator - (const Polynom& Poly_1, const Polynom& Poly_2)
{
	Polynom Difference;
	int degree_difference = Poly_1.get_degree() - Poly_2.get_degree();
	if(degree_difference > 0) {
		for(int i = 0; i < degree_difference; i++) {
			Difference.get_polynom().push_back(Poly_1[i]);
		}
		for(int i = degree_difference; i <= Poly_1.get_degree() ; i++) {
			Difference.get_polynom().push_back(Poly_1[i] - Poly_2[i - degree_difference]);
		}
	}
	else {
		for(int i = 0; i < -degree_difference; i++) {
			Difference.get_polynom().push_back(-Poly_2[i]);
		}
		for(int i = -degree_difference; i <= Poly_2.get_degree() ; i++) {
			Difference.get_polynom().push_back(-Poly_2[i] + Poly_1[i + degree_difference]);
		}
	}
	Difference.normalize();
	return Difference;
}

Polynom  operator * (const Polynom& Poly_1, const Polynom& Poly_2)
{
	int Product_degree = Poly_1.get_degree() + Poly_2.get_degree();
	if(Product_degree < -1) {
		Product_degree = -1;
	}
	vector<double> _product(Product_degree + 1, 0);
	for(int i = 0; i <= Poly_1.get_degree(); i++) {
		for(int j = 0; j <= Poly_2.get_degree(); j++) {
			_product[i+j] = _product[i+j] + Poly_1[i] * Poly_2[j];
		}
	}
	Polynom Product(_product);
	return Product;
}

Polynom  operator * (const Polynom& Poly, double numb)
{
	Polynom Product;
	Polynom Numb(numb);
	Product = Poly * Numb;
	return Product;
}

Polynom  operator * (double numb, const Polynom& Poly)
{
	Polynom Product;
	Polynom Numb(numb);
	Product = Poly * Numb;
	return Product;
}

Polynom  operator % (const Polynom& Poly_1, const Polynom& Poly_2)
{
	assert( Poly_2 != Polynom(0));
	Polynom Modulo(Poly_1);
	while(!(Modulo < Poly_2)) {
		vector<double> _divider;
		_divider.push_back(Modulo[0]/Poly_2[0]);
		for(int i = 0; i < Modulo.get_degree() - Poly_2.get_degree(); i++) {
			_divider.push_back(0);
		}
		Polynom Divider(_divider);
		Modulo = Modulo - Divider * Poly_2;
	}
	return Modulo;
}

int main() {
	int a = 14;
	int b = 21;
	cout << gcd_search(a, b) << endl;
	cout << gcd_search(a, 0) << endl;
	vector<double> _A;
	vector<double> _B;
	vector<double> _C;
	vector<double> _O;
	_A.push_back(1);
	_A.push_back(1);
	_B.push_back(1);
	_B.push_back(-1);
	_C.push_back(1);
	_C.push_back(0);
	_C.push_back(-1);
	Polynom A(_A);
	Polynom B(_B);
	Polynom C(_C);
	Polynom O(_O);
	Polynom Product = A*B;
	Product.print();
	gcd_search(A, C).print();
	gcd_search(O, A).print();
	gcd_search(B, A).print();
	return 0;
}