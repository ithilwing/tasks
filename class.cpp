#include "iostream"
#include "string"

using namespace std;

class TCmplx {
	private:
		int re, im;
	public:
		TCmplx(){}// Чтобы создавать ТСОМПЛ числа в функциях
		TCmplx( int i, int j) {
			re = i;
			im = j;
		}//Создает ТСмпл переменную
		TCmplx operator+( TCmplx B){// это как вункция в Си: "возвращаемый тип" "название функции" ( то что мы отправляем в функцию )
			TCmplx sum;//ваще как структура
			sum.re = re + B.re;
			sum.im = im + B.im;
			return sum;
			}
		TCmplx operator*( TCmplx B){
			TCmplx mult;
			mult.re = re*B.re - im*B.im;
			mult.im = re*B.im + B.re*im;
			return mult;
		}
		TCmplx operator[](int x){
			TCmplx abs;
			abs.re = re * re + im * im;
			return abs;
		}
		void printabs(string s2){
			cout << s2 << re << endl;
		}
		void print(string s) {
			
			cout << s << re << " + " << im << "i " << endl;
		}
};

int main() {
	int re1, im1, re2, im2;
	cin >> re1 >> im1;
	cin >> re2 >> im2;
	TCmplx a(re1, im1);
	TCmplx b(re2, im2);
	TCmplx c = a + b;
	TCmplx d = a * b;
	TCmplx e = a[0];
	TCmplx f = b[0];
	c.print("sum = ");
	d.print("mult = ");
	e.printabs("abs 1 = ");
	f.printabs("abs 2 = ");
	return 0;
}
