#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
 // Это наша тестовая функция(функтор)

template <class T> class Function
{
public:
	Function() {}
	T operator () (const T x) {
		return (37 * x + x * x + 7);
	}
};

 // Класс целых чисел

class Number
{
private:
	int num;
    int mod;
public:
    Number() {
		num = 0;
		mod = 1;
	}
	Number(int n, int m) {
		mod = m;
		num = n % m;

	}
    int GetNum() const {
		return num % mod;
	}
	int GetMod() const {
		return mod;
	}
    Number operator = (const Number x) {
		mod = x.GetMod();
		num = x.GetNum() % mod;
        return *this;
	}
    Number& operator = (const int& x) {
		    num = x % mod;
			return *this;
	}
    bool operator == (const Number& x) {
		    return (mod == x.GetMod() && num == x.GetNum());
	}
	bool operator != (const Number& x) {
            return (mod != x.GetMod() || num != x.GetNum());
	}
};

 // Далее перечислены основные операторы, которые нужны для правильной	 работы функции precycle_length

Number operator + (const Number& x, const Number& y) {
	return  Number(x.GetNum() + y.GetNum(), x.GetMod());
}

Number operator + (const Number& x, const int y) {
	return Number(x.GetNum() + y, x.GetMod());
}

Number operator + (const int x, const Number& y) {
	return Number(x + y.GetNum(), y.GetMod());
}

Number operator * (const Number& x, const Number& y) {
	return  Number(x.GetNum() * y.GetNum(), x.GetMod());
}

Number operator * (const Number& x, const int y) {
	return  Number(x.GetNum() * y, x.GetMod());
}

Number operator * (const int x, const Number& y) {
	return  Number(x * y.GetNum(), y.GetMod());
}

 // Реализация функции поиска длины предцикла
 // Требование к шабTлонному типу : типом Т может быть лишь класс, у которого есть поле с названием mod и реализован метод GetMod()
template <typename T, template <typename> class Transformation> int precycle_length(const T& x, Transformation<T> f)
{
	// сначала найдем произвольный элемент цикла, назовем его с.

	T c(x);
	for(int i = 1; i <= x.GetMod() + 1; i++) {
		c = f(c);
	}

	// Теперь можно найти длину цикла, пользуясь элементом цикла с.

	int cycle_length = 1;
	T current(f(c));
    while(current != c) {
		current = f(current);
		cycle_length++;
	}

	// А теперь, пользуясь длиной цикла, мы знаем, как найти первый элемент цикла

	T first_cycle_element(x);
	T cycle_distance_element(x);
	for(int i = 1; i <= cycle_length; i++) {
		cycle_distance_element = f(cycle_distance_element);
	}
	while(first_cycle_element != cycle_distance_element) {
		first_cycle_element = f(first_cycle_element);
		cycle_distance_element = f(cycle_distance_element);
	}

	// Итак, first_cycle_element - первый элемент цикла, теперь можно определить длину предцикла
	// как число шагов от начального элемента до первого элемента цикла

	int precycle_length = 0;
	T cur(x);
	while(cur != first_cycle_element) {
		cur = f(cur);
		precycle_length++;
	}
	return precycle_length;
}

#define REQUIRE(cond, message) \
	if (!(cond)) { cerr << message << endl; assert(false); }

int main()
{
	Function<Number> f;
	Number argument(7, 10);
	int etalon_1 = 0;
	int result_1 = precycle_length<Number>(argument,  f);
	REQUIRE(result_1 == etalon_1, "Result " << result_1 << " does not coinside with etalon " << etalon_1);

	argument = Number(4, 10);
	int etalon_2 = 2;
	int result_2 = precycle_length<Number>(argument,  f);
	REQUIRE(result_2 == etalon_2, "Result " << result_2 << " does not coinside with etalon " << etalon_2);

    argument = Number(5, 7);
	int etalon_3 = 1;
	int result_3 = precycle_length<Number>(argument,  f);
	REQUIRE(result_3 == etalon_3, "Result " << result_3 << " does not coinside with etalon " << etalon_3);
    return 0;
}
