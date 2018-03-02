#include "string"
#include "vector"
#include "list"
#include "iostream"

using namespace std;

class THashTable {
	private:
		vector<list<pair<int, string> > > m[100];
		int  hashFunc( int x){
			int res;
			res = (x*x*x + x%2*(x*x) + x)+100;
			return res;
		}
	public:
//		TFunc() {}
	/*	TFunc( int i, string j ){
			x = i;
			s = j;
		}*/
		void set(int i, string j){
			int hf = hashFunc(i)%100;
			pair<int, string> p({i, j});
			m[hf].push_back(p);

		}
		string get(int j) { 
			int k = hashFunc(j)%100;
			for (const auto& i : m[k]){
				cout << i;
			//	cout << i.first << " " << i.second << endl;
			}
	//	TFunc hashFunc( int x ){
	//		TFunc res;
	//		res.x = x * x * x + x%2*(x * x) + x;
		}
};
int main() {
//vector<list<int, string>> m;
//c.hashFunc (12)
THashTable a;
a.set(1, "one");
THashTable b;
b.set(1, "onetwothree");
a.get(1);
b.get(1);
return 0;
}
