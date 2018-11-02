#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#define index 10 //size of array

/////////////FRACTION CLASS////////////

class fraction {
private:
	// int nume,demo;
	// string array[index];
public:
	int nume,demo;
	fraction():nume(1),demo(1){
	// 	for(int i = 0; i < index ; i++)
	// 		array[i] = "1/2";
	}
	fraction(int n,int m):nume(n),demo(m){reduce_fraction();}
	~fraction(){
		nume = 0;
		demo = 0;
	}

/////initialize function "get fraction (1/2) from user"/////

	void initialize(){
		string a , N, D;
		cin>>a;

////IF USER ENTER ONLY NUMENATOR////

		int check = 0;
		for(int i = 0; i< a.length() ; i++){
			if (a[i] == '/'){check +=1;}
		}
		if(check == 1){
			int i = 0;
			while(a[i] != '/'){
				N = N + a[i];
				i++;
			}
			i++;
			while(i < a.size()){
				D = D + a[i];
				i++;
			}
			demo = atoi(D.c_str());
			nume = atoi(N.c_str());
			if(demo == 0){
				cout<<"Invaled Syntex denomenator is != 0,\n, Enter the number again\n";
				initialize();
			}
			reduce_fraction();
		}
		else{
			nume = atoi(a.c_str());
		}
	}

//////////print the fraction on console///////////

	void show(){
		reduce_fraction();
		if(nume == 0){
			cout<<nume<<endl;
			return;
		}
		if(demo == 1){
			cout<<nume<<endl;
			return;
		}
		cout<<nume<<"/"<<demo<<endl;
	}

//////Binary operators "+,-,*,/"  //////

	fraction operator + (const fraction f )const{
		fraction f1;
		f1.demo = demo * f.demo;
		f1.nume = ((f1.demo / demo) * nume)+(f1.demo / f.demo) * f.nume;
		f1.reduce_fraction();
		return f1;
	}
	fraction operator - (const fraction f )const{
		fraction f1;
		f1.demo = demo * f.demo;
		f1.nume = ((f1.demo / demo) * nume)-(f1.demo / f.demo) * f.nume;
		f1.reduce_fraction();
		return f1;
	}
	fraction operator * (const fraction f )const{
		fraction f1;
		f1.nume = nume * f.nume;
		f1.demo = demo * f.demo;
		f1.reduce_fraction();
		return f1;
	}

	fraction operator / (const fraction f )const{
		fraction f1;
		f1.nume = nume * f.demo;
		f1.demo = demo * f.nume;
		f1.reduce_fraction();
		return f1;
	}

////Rational Operators "==,>=,<=,<,>" /////

	bool operator == (const fraction f )const{
		return ((float)nume / (float)demo == (float)f.nume / (float)f.demo)?true:false;
	}
	bool operator != (const fraction f )const{
		return ((float)nume / (float)demo != (float)f.nume / (float)f.demo)?true:false;
	}
	bool operator >= (const fraction f )const{
		return ((float)nume / (float)demo >= (float)f.nume / (float)f.demo)?true:false;
	}
	bool operator <= (const fraction f )const{
		return ((float)nume / (float)demo <= (float)f.nume / (float)f.demo)?true:false;
	}
	bool operator < (const fraction f )const{
		return ((float)nume / (float)demo < (float)f.nume / (float)f.demo)?true:false;
	}
	bool operator > (const fraction f )const{
		return ((float)nume / (float)demo) >((float)f.nume / (float)f.demo)?true:false;
	}

////Unary Operators "++x , x++ , x-- , --x " ///////

	fraction operator ++(){
		nume = nume + demo ;
		return fraction(nume,demo);
	}
	fraction operator ++(int){
		int a = nume;
		int b = demo;
		nume = nume + demo ;
		return fraction(a,b);
	}
	fraction operator --(){
		nume = nume - demo;
		return fraction(nume,demo);
	}
	fraction operator --(int){
		int a = nume;
		int b = demo;
		nume = nume + demo ;
		return fraction(a,b);
	}

/////Assignment Operator overloading "+=,"////

	void operator += (const float f ){
		nume = (nume) + ((demo/1)*f);
		reduce_fraction();
	}
	void operator += (const fraction f){
		int a = demo;
		demo = demo * f.demo;
		nume = ((demo/a)*nume) + ((demo/f.demo)*f.nume);
		reduce_fraction();
	}
	void operator -= (const float f ){
		nume = (nume) - ((demo/1)*f);
		reduce_fraction();
	}
	void operator -= (const fraction f){
		int a = demo;
		demo = demo * f.demo;
		nume = ((demo/a)*nume) - ((demo/f.demo)*f.nume);
		reduce_fraction();
	}
	void operator *= (const float f ){
		nume *= f;
		reduce_fraction();
	}
	void operator *= (const fraction f){
		nume *= f.nume;
		demo *= f.demo;
		reduce_fraction();
	}
	void operator /=(const fraction f){
		nume *= f.demo;
		demo *= f.nume;
		reduce_fraction();
	}
	void operator /= (const float f ){
		demo *= f;
		reduce_fraction();
	}

	// float operator = (fraction &f){
	// 	float var = nume/demo;
	// 	return var;
	// }

///////REduce Fraction ("simplify")//////

	void reduce_fraction (){
		for (int i = abs(demo) * abs(nume); i > 1; i--) {
            if ((demo % i == 0) && (nume % i == 0)) {
		        demo /= i;
                nume /= i;
	       	}
	    }
	}
////FRIEND FUNCTIONS/////////

	friend istream & operator >>(istream &a , fraction & f);
	friend ostream & operator >>(ostream &a , fraction & f);

// ////ARRAY OPERATOR [] OVER LOADING//////////
//
// 	string & operator[](int i){
// 		if(i < 0 or i > index){
// 			cout<<"Index outside the array"<<endl;
// 			return array[0];
// 		}
// 	return array[i];
// 	}
};


            ////////FRIEND FUNCTION///////////////
/////INSERTION AND EXTRACTION OPERATOR OVERLOADING "cin>> & cou<< "////

	istream & operator >>(istream &a , fraction & f){
		f.initialize();
		return a;
	}
	ostream & operator <<(ostream &a , fraction& f){
		f.show();
		return a;
	}

	//////////////////Extra /////////////////
/* we make ARRAY of fraction class , so we can perform alloperators
	like 'f[1] + f[2]'*/

class fractionArray  {
private:
	fraction arr[index];
public:

/////ARRAY [] OPERATOR OVERLOADING //////

	fraction & operator[](int i){
		if(i < 0 or i > index){
			cout<<"Index outside the array"<<endl;
			return arr[0];
		}
	return arr[i];
	}
	friend istream & operator >>(istream &a , fraction & f);
	friend ostream & operator >>(ostream &a , fraction & f);
};



// int main (){
// 	fraction f[10];
// 	// cin>>f[5];
// 	// cin>>f[3];
// 	int var = 7;
// 	f[3].nume = var;
// 	//x = f[3];
// 	cout<<f[3];
// 	return 0;
// }
