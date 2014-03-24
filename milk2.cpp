/*
ID: mousepad
PROB: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Time {
  int begin;
  int end;
};

vector<Time> times;

int main() {
  int begin, end, maxMilking = 0, maxNonMilking = 0;

  ifstream fin("milk2.in");
  ofstream fout("milk2.out");

  unsigned int farmers;

  fin >> farmers;

  Time t, tSorted;
  for (int i = 0; i < farmers; i++) {
    fin >> t.begin >> t.end;
    times.push_back(t);
  }

  for (int i = 0; i < farmers; i++) {
    for (int j = 0; j < farmers - 1; j++) {
      if (times.at(j).begin > times.at(j + 1).begin) {
	int temp = times.at(j + 1).begin;
	times.at(j + 1).begin = times.at(j).begin;
	times.at(j).begin = temp;

	temp = times.at(j + 1).end;
	times.at(j + 1).end = times.at(j).end;
	times.at(j).end = temp;
      }
    }
  }

  // SO:275994
  //  for (vector<Time>::iterator it = times.begin(); it != times.end(); ++it) {
  //    cout << it->begin << " " << it->end << endl;
  //  }

  begin = times.at(0).begin;
  end = times.at(0).end;
  maxMilking = end - begin;

  for (int i = 1; i < farmers; i++) {
    // Add overlapping milkings
    if (times.at(i).begin <= end && end <= times.at(i).end) {
	end = times.at(i).end;

	if (end - begin > maxMilking)
	  maxMilking = end - begin;
    }

    // Not an overlapping milking
    if (times.at(i).begin > end) {
      if (end - begin > maxMilking)
	maxMilking = end - begin;

      if (times.at(i).begin - end > maxNonMilking)
	maxNonMilking = times.at(i).begin - end;

      begin = times.at(i).begin;
      end = times.at(i).end;
    }
  }

  fout << maxMilking << " " << maxNonMilking << "\n";

  return EXIT_SUCCESS;
}
