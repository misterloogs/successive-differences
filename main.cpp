#include <vector>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::stringstream;

bool allEqual(const vector<int>& v)
{
  for (int ii = 0; ii < v.size(); ++ii)
  {
    if (v[ii] != v[0])
      return false;
  }
  return true;
}

int calculateNext(const vector<int>& sequence, int level=1)
{
  // a sequence of length 1 isn't long enough to conclude that
  // there are equal successive differences
  if (sequence.size() == 1) 
    return -1;

  if (allEqual(sequence))
  {
    stringstream ss;
    ss << "seq (level=" << level << "): ";
    ss << sequence[0] << ", ";
    for (int ii = 1; ii < sequence.size(); ++ii)
    {
      ss << sequence[ii] << ", ";
    }
    ss << "*" << sequence[0] << "\n";
    cout << ss.str();

    return sequence[0];
  }

  vector<int> diffs;

  stringstream ss;
  ss << "seq (level=" << level << "): ";
  ss << sequence[0] << ", ";
  for (int ii = 1; ii < sequence.size(); ++ii)
  {
    diffs.push_back(sequence[ii]-sequence[ii-1]);
    ss << sequence[ii] << ", ";
  }

  int nextDiff = calculateNext(diffs, ++level);
  if (-1 == nextDiff)
  {
    ss << "\n";
    cout << ss.str();
    return -1;
  }
  int next = sequence.back() + nextDiff;
  ss << "*" << next << "\n";
  cout << ss.str();

  return next;
}


int main(void)
{
  int a[] = {3, 19, 165, 771, 2503, 6483, 14409};
  int N   = sizeof(a)/sizeof(a[0]);
  vector<int> sequence(a, a+N);

  int next = calculateNext(sequence);
  if (-1 == next)
    cout << "\nThe sequence does *not* converge to equal successive differences" << endl;
  else
    cout << "\nThe next number in the sequence is : " << next << endl;

  return 0;
}
