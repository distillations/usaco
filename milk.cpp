/*
ID: mousepad
PROB: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Farmer {
  int price;
  int quantity;
};

vector<Farmer> farmers;

int main() {
  ifstream fin("milk.in");
  ofstream fout("milk.out");

  int demand, farmerCount, minPrice;
  Farmer f;

  fin >> demand >> farmerCount;

  while (fin >> f.price >> f.quantity) {
    farmers.push_back(f);
  }

  // Bubble sort vector of prices and quantities
  for (int i = 0; i < farmerCount; i++) {
    for (int j = 0; j < farmerCount - 1; j++) {
      if (farmers.at(j).price > farmers.at(j + 1).price) {
	int temp = farmers.at(j + 1).price;
	farmers.at(j + 1).price = farmers.at(j).price;
	farmers.at(j).price = temp;

	temp = farmers.at(j + 1).quantity;
	farmers.at(j + 1).quantity = farmers.at(j).quantity;
	farmers.at(j).quantity = temp;
      }
    }
  }

  for (vector<Farmer>::iterator it = farmers.begin(); it != farmers.end(); ++it) {
    cout << it->price << " " << it->quantity << endl;
  }

  int k = 0;
  while (demand > 0) {
    if (demand > farmers.at(k).quantity) {
      demand -= farmers.at(k).quantity;
      minPrice += farmers.at(k).quantity * farmers.at(k).price;
    } else {
      minPrice += demand * farmers.at(k).price;
      demand = 0;
    }
    k++;
  }

  cout << minPrice;

  return EXIT_SUCCESS;
}
