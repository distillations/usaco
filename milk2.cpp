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
using std::sort;

struct Time {
  int begin;
  int end;

  // SO:1380463
  bool operator < (const Time& str) const {
    return (begin < str.begin);
      }
};

vector<Time> times;


int main() {
  int begin, end, maxMilking, maxNonMilking;

  ifstream fin("milk2.in");
  ofstream fout("milk2.out");

  unsigned int farmers;

  fin >> farmers;

  Time t;
  for (int i = 0; i < farmers; i++) {
    fin >> t.begin >> t.end;
    times.push_back(t);
  }

  sort(times.begin(), times.end());
  
  // SO:275994
  for (vector<Time>::iterator it = times.begin(); it != times.end(); ++it) {
    cout << it->begin << " " << it->end << endl;
  }

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

  fout << maxMilking << " " << maxNonMilking;

  return EXIT_SUCCESS;
}
