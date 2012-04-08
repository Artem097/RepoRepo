#include <stdlib.h>
#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <math.h>
#include <time.h>

using namespace std;

template<typename T>
T gcd_search(const T& arg_1, const T& arg_2) {
    T a(arg_1);
    T b(arg_2);
    assert(a != T(0) || b != T(0));

    while (a != T(0) && b != T(0)) {
        a = a % b;
        T temp(b);
        b = a;
        a = temp;
    }
    if (a == T(0)) return b;
    else return a;
}

class Polynom {
private:
    vector<double> _polynom;
public:

    void normalize() {
        vector<double>::iterator it = _polynom.begin();
        while (_polynom.size() != 0 && *it == 0) {
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

    Polynom() {
    }

    Polynom(const double constant) {
        _polynom.push_back(constant);
        normalize();
    }

    Polynom(const vector<double>& poly) {
        for (int i = 0; i < poly.size(); i++) {
            _polynom.push_back(poly[i]);
        }
        normalize();
    }

    Polynom(const Polynom& Poly) {
        for (int i = 0; i <= Poly.get_degree(); i++) {
            _polynom.push_back(Poly[i]);
        }
    }

    double& operator [] (int i) {
        return _polynom[i];
    }

    double operator [] (int i) const {
        return _polynom[i];
    }

    bool operator<(const Polynom& Poly) const {
        if (get_degree() < Poly.get_degree())
            return true;
        else
            return false;
    }

    Polynom& operator =(const Polynom& Poly) {
        _polynom.clear();
        for (int i = 0; i <= Poly.get_degree(); i++) {
            _polynom.push_back(Poly[i]);
        }
        return *this;
    }

    bool operator ==(const Polynom& Poly) const {
        if (_polynom == Poly.get_polynom())
            return true;
        else
            return false;
    }

    bool operator !=(const Polynom& Poly) const {
        if ((*this) < Poly)
            return true;
        else if (Poly < (*this))
            return true;
        else {
            bool is_notequal = false;
            int i = 0;
            while (!(is_notequal) && i < _polynom.size()) {
                if (_polynom[i] != Poly[i])
                    is_notequal = true;
                ++i;
            }
            return is_notequal;
        }
    }

    void print() {
        for (int i = 0; i < _polynom.size(); i++) {
            cout << _polynom[i] << ' ';
        }
        cout << endl;
    }

    ~Polynom() {
        _polynom.clear();
    }
};

Polynom operator +(const Polynom& Poly_1, const Polynom& Poly_2) {
    Polynom Sum;
    int degree_difference = Poly_2.get_degree() - Poly_1.get_degree();
    if (degree_difference > 0) {
        for (int i = 0; i < degree_difference; i++) {
            Sum.get_polynom().push_back(Poly_2[i]);
        }
        for (int i = degree_difference; i <= Poly_2.get_degree(); i++) {
            Sum.get_polynom().push_back(Poly_2[i] + Poly_1[i - degree_difference]);
        }
    } else {
        for (int i = 0; i < -degree_difference; i++) {
            Sum.get_polynom().push_back(Poly_1[i]);
        }
        for (int i = -degree_difference; i <= Poly_1.get_degree(); i++) {
            Sum.get_polynom().push_back(Poly_1[i] + Poly_2[i + degree_difference]);
        }
    }
    Sum.normalize();
    return Sum;
}

Polynom operator -(const Polynom& Poly_1, const Polynom& Poly_2) {
    Polynom Difference;
    int degree_difference = Poly_1.get_degree() - Poly_2.get_degree();
    if (degree_difference > 0) {
        for (int i = 0; i < degree_difference; i++) {
            Difference.get_polynom().push_back(Poly_1[i]);
        }
        for (int i = degree_difference; i <= Poly_1.get_degree(); i++) {
            Difference.get_polynom().push_back(Poly_1[i] - Poly_2[i - degree_difference]);
        }
    } else {
        for (int i = 0; i < -degree_difference; i++) {
            Difference.get_polynom().push_back(-Poly_2[i]);
        }
        for (int i = -degree_difference; i <= Poly_2.get_degree(); i++) {
            Difference.get_polynom().push_back(-Poly_2[i] + Poly_1[i + degree_difference]);
        }
    }
    Difference.normalize();
    return Difference;
}

Polynom operator *(const Polynom& Poly_1, const Polynom& Poly_2) {
    int Product_degree = Poly_1.get_degree() + Poly_2.get_degree();
    if (Product_degree < -1) {
        Product_degree = -1;
    }
    vector<double> _product(Product_degree + 1, 0);
    for (int i = 0; i <= Poly_1.get_degree(); i++) {
        for (int j = 0; j <= Poly_2.get_degree(); j++) {
            _product[i + j] = _product[i + j] + Poly_1[i] * Poly_2[j];
        }
    }
    Polynom Product(_product);
    return Product;
}

Polynom operator *(const Polynom& Poly, double numb) {
    Polynom Product;
    Polynom Numb(numb);
    Product = Poly * Numb;
    return Product;
}

Polynom operator *(double numb, const Polynom& Poly) {
    Polynom Product;
    Polynom Numb(numb);
    Product = Poly * Numb;
    return Product;
}

Polynom operator %(const Polynom& Poly_1, const Polynom& Poly_2) {
    assert(Poly_2 != Polynom(0));
    Polynom Modulo(Poly_1);
    while (!(Modulo < Poly_2)) {
        vector<double> _divider;
        _divider.push_back(Modulo[0] / Poly_2[0]);
        for (int i = 0; i < Modulo.get_degree() - Poly_2.get_degree(); i++) {
            _divider.push_back(0);
        }
        Polynom Divider(_divider);
        Modulo = Modulo - Divider * Poly_2;
    }
    return Modulo;
}

int create_number( int pow_of_2, int pow_of_3, int pow_of_5, int pow_of_7) {
    int number = 1;
    for(int i = 1; i<= pow_of_2; i++) {
        number = number * 2;
    }
    for(int i = 1; i<= pow_of_3; i++) {
        number = number * 3;
    }
    for(int i = 1; i<= pow_of_5; i++) {
        number = number * 5;
    }
    for(int i = 1; i<= pow_of_7; i++) {
        number = number * 7;
    }
    return number;
}
void testForInt() {
    int number_1 = 1;
    int number_2 = 1;
    for(int i = 0; i <= 4; i++){
        for(int j = 0; j <= 4; j++) {
            for(int k = 0; k <= 4; k++) {
                for(int l = 0; l <= 4; l++) {
                    number_1 = create_number(i, j, k, l);
                    
                    for(int a = 0; a <= 4; a++){
                        for(int b = 0; b <= 4; b++) { 
                            for(int c = 0; c <= 4; c++) {
                                for(int d = 0; d <= 4; d++) {
                                    number_2 = create_number(a, b, c, d);
                                    int real_gcd = create_number(min(i,a), min(j,b), min(k,c), min(l, d));
                                    assert(gcd_search(number_1, number_2) == real_gcd);
                                }
                            }
                        }  
                    }

                }
            }
        }
    }
}

Polynom create_Polynom(vector<double> polynom_roots) {
    Polynom Poly(1);
    for(int i = 0; i < polynom_roots.size(); i++) {
        vector<double> factor;
        factor.push_back(1);
        factor.push_back(-polynom_roots[i]);
        Poly = Poly * Polynom(factor);
    }
    return Poly;
}

vector<double> intersection(vector<double> first, vector<double> second) {
    vector<double> intersection;
    vector<double> :: iterator it_1;
    vector<double> :: iterator it_2;
    for(it_1 = first.begin(); it_1 != first.end(); ++it_1) {
        it_2 = second.begin();
        while(it_2 != second.end() && (*it_1) != (*it_2)) {
            ++it_2;
        }
        if(it_2 != second.end()) {
            intersection.push_back(*it_2);
            second.erase(it_2);
        }
    }
    return intersection;
}

void testForPolynom() {
    vector<double> first_polynom_roots;
    vector<double> second_polynom_roots;
    vector<double> gcd_polynom_roots;
    Polynom first_Poly;
    Polynom second_Poly;
    Polynom real_gcd_Poly;
    Polynom gcd_Poly;
    int first_polynom_degree;
    int second_polynom_degree;
    int random_number;
    for(int i = 0; i < 500; i++) {
        first_polynom_degree = rand() % 10; 
        second_polynom_degree = rand() % 10; 
        for(int j = 0; j <= first_polynom_degree; j++) {
            random_number = (rand() % 20) - 10;
	    first_polynom_roots.push_back(random_number);           
        }
        first_Poly = create_Polynom(first_polynom_roots);
        for(int j = 0; j <= second_polynom_degree; j++) {
            random_number = (rand() % 20) - 10;
	    second_polynom_roots.push_back(random_number);           
        }
        second_Poly = create_Polynom(second_polynom_roots);
        gcd_polynom_roots = intersection(first_polynom_roots, second_polynom_roots);
        real_gcd_Poly = create_Polynom(gcd_polynom_roots);
        
        gcd_Poly = gcd_search<Polynom>(first_Poly, second_Poly);
        gcd_Poly = gcd_Poly * (1/gcd_Poly[0]);
        cout << i << '\n';
	assert(real_gcd_Poly == gcd_Poly);
    }
}

int main() {
    // firstly we use simple tests:    
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
    gcd_search<Polynom>(A, C).print();
    gcd_search<Polynom>(O, A).print();
    gcd_search<Polynom>(B, A).print();
    
    // then we use our special testers:
    testForInt();
    testForPolynom();
    return 0;
} 