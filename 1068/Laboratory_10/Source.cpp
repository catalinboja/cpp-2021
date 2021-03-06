#include <iostream>
#include <string>
using namespace std;

class DailySalesData {
	string productName = "";
	char* productDescription = nullptr;
	const int barCodeNumber;

	int* itemsPerDay = nullptr;
	int noDays = 0;

public:

	//constructor
	DailySalesData(string name, const char* description, int barCode)
		: barCodeNumber(barCode), productName(name) {
		//this->productName = name;

		//redundant - it will use the default from the definition
		//this->noDays = 0;

		//don't do the shallow copy
		//this->productDescription = description;

		this->productDescription = new char[strlen(description) + 1];
		strcpy_s(this->productDescription, strlen(description) + 1, description);
	}

	//default constructor
	DailySalesData(): barCodeNumber(0) {
		//we can reuse the default values from the definition

		//redundant if you have your own defaults in the definition
		//mandatory if you didn't use default values in the definition
		//this->noDays = 0;
		//this->itemsPerDay = nullptr;
		//this->productDescription = nullptr;
	}

	//destructor
	~DailySalesData() {
		cout << endl << "The class destructor";
		delete[] this->productDescription;
		delete[] this->itemsPerDay;
	}


	//copy constructor
	DailySalesData(const DailySalesData& object) :barCodeNumber(object.barCodeNumber) {
		this->productName = object.productName;
		//don't do the shallow copy
		//this->productDescription = object.productDescription;

		this->productDescription = new char[strlen(object.productDescription) + 1];
		strcpy_s(this->productDescription, strlen(object.productDescription) + 1, object.productDescription);

		this->itemsPerDay = new int[object.noDays];
		for (int i = 0; i < object.noDays; i++) {
			this->itemsPerDay[i] = object.itemsPerDay[i];
		}
		this->noDays = object.noDays;
	}

	//operator =
	DailySalesData operator=(const DailySalesData& source) {

		//!!!! for operator = that receives source by reference
		if (this == &source) {
			//return source;
			return *this;
		}

		//this->barCodeNumber = source.barCodeNumber;

		if (this->productDescription == source.productDescription) {
			return source;
		}

		delete[] this->productDescription;
		this->productDescription = new char[strlen(source.productDescription) + 1];
		strcpy_s(this->productDescription, strlen(source.productDescription) + 1, source.productDescription);

		delete[] this->itemsPerDay;
		this->itemsPerDay = new int[source.noDays];
		for (int i = 0; i < source.noDays; i++) {
			this->itemsPerDay[i] = source.itemsPerDay[i];
		}

		this->productName = source.productName;
		this->noDays = source.noDays;

		return source;
	}

	explicit operator int() {
		int total = 0;
		for (int i = 0; i < this->noDays; i++) {
			total += this->itemsPerDay[i];
		}
		return total;
	}

	int& operator[](int index) {
		if (index < 0 || index >= this->noDays)
		{
			throw exception("Wrong index");
		}
		return this->itemsPerDay[index];
	}

	DailySalesData operator*(int value) {
		DailySalesData copy = *this;

		for (int i = 0; i < copy.noDays; i++) {
			copy.itemsPerDay[i] *= value;
		}

		return copy;
	}

	int getNoDays() {
		return this->noDays;
	}

	friend DailySalesData operator*(int value, DailySalesData object);
	friend void print(DailySalesData data);
};

DailySalesData operator*(int value, DailySalesData object) {
	DailySalesData copy = object;

	for (int i = 0; i < copy.getNoDays(); i++) {
		copy.itemsPerDay[i] *= value;
	}

	return copy;
}

void print(DailySalesData data) {
	cout << endl << "Product name " << data.productName;
}


//operator +
//operator *
//operator []
//cast operator

int main() {
	DailySalesData laptopData("Laptop", "Gaming laptop with 8 GB of RAM", 224589);
	DailySalesData pcData("Desktop PC", "Gaming PC with 8 GB of RAM", 224589);
	DailySalesData smartphoneData("Smartphone", "S20", 123765);

	DailySalesData* newObject = new DailySalesData("Smartphone", "Some smartphone", 23);
	delete newObject;

	DailySalesData* productsData = new DailySalesData[5];

	DailySalesData laptopCopy = laptopData;

	cout << endl << "The end of the example";

	smartphoneData = laptopData;		//operator=(DailySalesData&, DailySalesData)

	smartphoneData = laptopData = pcData;

	smartphoneData = pcData;
	laptopData = pcData;

	smartphoneData = smartphoneData;

	//smartphoneData = smartphoneData + 20;

	int totalSoldItems = (int)smartphoneData;

	int firstDaySoldItems = smartphoneData[0];

	smartphoneData[0] = 100;

										//operator*(DailySalesData, int)
	laptopData = smartphoneData * 2;	//we want to multiply the sold items

	laptopData = 2 * smartphoneData;	//operator*(int, DailySalesData)

}