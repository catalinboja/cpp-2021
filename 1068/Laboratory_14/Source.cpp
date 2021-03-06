#include <iostream>
#include <string>

using namespace std;

class Product {
protected:
	string description;
	float price;

public:
	Product() {
		cout << endl << "Product default ctor";
	}

	Product(string Description, float Price) {
		this->description = Description;
		this->price = Price;
	}

	virtual void printDescription() {
		cout << endl << "Product " << this->description << " with a price of " << this->price;
	}

	float getPrice() {
		return this->price;
	}
};

class ProductWithDiscount : public Product {
	float discountPercentage;

	float getPrice() {
		return this->price * (1 - this->discountPercentage / 100);
	}
};

class Toy: public Product {
protected:
	int minAge;
public:
	Toy() {
		cout << endl << "Toy default ctor";
	}
	Toy(string Description, float Price, int MinAge): Product(Description, Price) {
		//this->description = Description;
		//this->price = Price;
		this->minAge = MinAge;
	}

	//overriding the method inherited from the parent class
	void printDescription() {
		cout << endl << "Toy " << this->description << " with a price of " << this->price <<
			", for kids above " << this->minAge;
	}
};

class Monitor : public Product {
protected:
	int diagonal;
public:
	Monitor() {
		cout << endl << "Monitor default ctor";
	}
	Monitor(string Description, float Price, int Diagonal) 
		:Product(Description, Price),  diagonal(Diagonal){
	}

	void printDescription() {
		//calling the Product version
		this->Product::printDescription();
		cout << endl << "It's a monitor with a diagonal of " << this->diagonal;
	}
};

class TouchScreen : public Monitor {
protected:
	float sensitivity;
public:
	TouchScreen() {
		cout << endl << "TouchScreen default ctor";
	}
	TouchScreen(string Description, float Price, int Diagonal, float Sensitivity)
		:Monitor(Description, Price, Diagonal) {
		this->sensitivity = Sensitivity;
	}
	void printDescription() {
		cout << endl << "It's a touch screen with a sensitivity of " << this->sensitivity;
	}

};

int main() {
	TouchScreen touch("Samsung Screen",1200,24,0.9);
	Monitor monitor("Dell", 540, 19);
	Toy toy("RC Plane", 600, 10);
	Product product("Pepsi", 3.5);

	//UP - casting
	//at object level
	product = touch;

	//at pointer level
	Product* pointerProduct = &product;
	pointerProduct = &touch;

	//an array of pointers to Product to store anything from the framework
	//static array
	Product* products[5];

	//dynamic array
	Product** listOfProducts;

	products[0] = &product;
	products[1] = &monitor;
	products[2] = &toy;
	products[3] = &touch;
	products[4] = new TouchScreen("Generic touch screen", 600, 21, 0.7);

	listOfProducts = new Product * [5];


	listOfProducts[0] = &product;
	listOfProducts[1] = &monitor;
	listOfProducts[2] = &toy;
	listOfProducts[3] = &touch;
	listOfProducts[4] = new Toy("Doll", 75, 10);

	cout << endl << "------------------";

	for (int i = 0; i < 5; i++) {
		products[i]->printDescription();		//EARLY-BINDING
												//LATE - BINDING with virtual methods
	}

	cout << endl << "------------------";
	touch.printDescription();
	toy.printDescription();
}