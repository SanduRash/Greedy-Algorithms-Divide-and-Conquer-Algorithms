//Sandu Galbokka Hewa
//April, 12 2025
//Project 3 Data Structures and Algorithms: Working with Greedy Algorithms

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cmath>

using namespace std;

float minDiff = INT_MAX; //Make minimum differece / closest match to big positive number
string minName1; // Client 1 name
string minName2; // Client 2 name

string sortType; // Sort type if it's 1/ 2/ b

class info{     // Class called info which is about each client's information.
private:
  string _name;// store name
  float _score1; // store score #1
  float _score2; // store score #2

public:
  info(): _name(""), _score1(0), _score2(0) {}
  info(string name, float score1, float score2): _name(name), _score1(score1), _score2(score2) {}

  string name() const{return _name;}
  string& name() {return _name;}

  float score1() const{return _score1;}
  float score1() {return _score1;}

  float score2() const{return _score2;}
  float score2() {return _score2;}

   std::ostream& print(std::ostream &toStream) const
  {
    toStream << _name << "  "<< _score1 << "  " << _score2 << endl;

    return toStream;
  }
  
};

// These for merge sort
void merge(int lowest, int middle, int highest, info arr[]);
void mergeSort(int lowest, int highest, info arr[]);

// Functions to find closest match
void findClosestPair(info arr[], int low, int mid, int high);
void closestPair(info arr[], int low, int high);


int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  string name;
  float score1;
  float score2;

  sortType = argv[2];

  info arr[100000];
  int lenOfinfo = 0;

  ifile >>name;// read each name
  ifile >>score1;// read each score 1
  ifile >>score2;// read each score 2

  while(ifile)
	{
	  arr[lenOfinfo] = info(name,score1,score2);// store in objects each information
	  lenOfinfo++;// count how many people have done the survey
	  
	  ifile >>name;
	  ifile >>score1;
	  ifile >>score2;
	}

  int lowest;
  
   if(sortType != "b")
     {
       lowest = 1;
       mergeSort(lowest, lenOfinfo, arr); // Sort by either score 1 or score 2
       
       lowest = 0;
       closestPair(arr, lowest, lenOfinfo-1);
     }
   else /// sortType = "b"
     {

       sortType = "1";
       lowest = 1;
       mergeSort(lowest, lenOfinfo, arr); // sort by score 1


       sortType = "b";
       lowest = 0;

       closestPair(arr, lowest, lenOfinfo-1);
       
     }
   
   cout<<minName1<< " "<<minName2<< " "<<minDiff<<endl;
   
  return 0;
}



void closestPair(info arr[], int low, int high) {
    if (low+1>= high)
        return;

    int mid = (low + high) / 2;

    // Recursively find in left and right halves
    closestPair(arr, low, mid);
    closestPair(arr, mid + 1, high);

    // Find closest pair between the halves
    findClosestPair(arr, low, mid, high);
      
}




void findClosestPair(info arr[], int low, int mid, int high) {
  // [ [0 1] [ 2 2] ]
  
  int leftleft = low; // first item's index in left half
  int leftright = mid; // last item's index in left half
  int rightleft = mid+1; // first item's index in right half
  int rightright = high; // last item's index in right half

  float minLeft = INT_MAX; // make minimum difference in left half to big positive number
  string leftMinName1; // relevant client 1 in left half
  string leftMinName2; // relevant client 2 in right half

  float minRight = INT_MAX; // make minimum difference in right half to big positive number
  string rightMinName1; // relevant client 1 in right half
  string rightMinName2; // relevant client 1 in right half
  
  //cout<<leftleft<<" "<<leftright<<" "<<rightleft<<" "<<rightright<<endl;
  
  if(leftright-leftleft==1) // if difference is one, there are two items in left half [0 1]
    {
      // calculate the minimum difference using two items
      if (sortType=="1")
	{
	   minLeft = abs(arr[leftleft].score1()-arr[leftright].score1());
	}

      if (sortType=="2")
	{
	   minLeft = abs(arr[leftleft].score2()-arr[leftright].score2());
	}

      if (sortType=="b")
	{
	  minLeft =sqrt(pow(arr[leftleft].score1()-arr[leftright].score1(),2)+pow(arr[leftleft].score2()-arr[leftright].score2(),2));
	}
     
      leftMinName1 = arr[leftleft].name();
      leftMinName2 = arr[leftright].name();
    }

  
  if(rightright-rightleft==1) // if difference is one, there are two items in right half, otherwise minimum is big positive number.
    {
      // calculate the minimum difference using two items
      if (sortType=="1")
	{
	  minRight = abs(arr[rightright].score1()-arr[rightleft].score1());
	}

      if (sortType=="2")
	{
	  minRight = abs(arr[rightright].score2()-arr[rightleft].score2());
	}

      if (sortType=="b")
	{
	  minRight = sqrt(pow(arr[rightright].score1()-arr[rightleft].score1(),2)+pow(arr[rightright].score2()-arr[rightleft].score2(),2));
	}
      
      rightMinName1= arr[rightright].name();
      rightMinName2 = arr[rightleft].name();
    }

  

  if (minRight>minLeft && minLeft<minDiff) // if minimum in left is smaller than minimum in right and minimum of whole data, make min in left to min  in whole data.
    {
      minDiff = minLeft;
      minName1=leftMinName1;
      minName2=leftMinName2;
    }
  else if (minRight<minDiff) // Likewise
    {
      minDiff = minRight;
      minName1=rightMinName1;
      minName2=rightMinName2;
    }


  if(sortType != "b") // If they only consider one survey, then sort it by relevant score.
    {
      float minInJoint; // Since ealier find min in each half, now will find the difference between joint of left and right half
      
      if (sortType=="1")
	{
	  minInJoint = arr[rightleft].score1()-arr[leftright].score1();
	}
      
      if (sortType=="2")
	{
	  minInJoint = arr[rightleft].score2()-arr[leftright].score2();
	}
      
      if(minInJoint<minDiff) // if min in joint less than min in whole data, make min in joint to min in whole data
	{
	  minDiff = minInJoint;
	  minName1=arr[rightleft].name();
	  minName2=arr[leftright].name();	  
	}
    }


  if(sortType == "b") // If they consider both surveys, use following steps
    {//Here i have sorted first by score 1.
      
      float middleLine = (arr[rightleft].score1()+arr[leftright].score1())/2; // find the middle score in between left and right halves.
     
      info arrStrip[100000];
      
      bool isLessMin = true;
      int j = 0;
      int numPoints = 0; //numOfPointsInStrip 
      
      while(isLessMin) // find the scores located between [middleLine - minDiff] to middleLine, and fill the arrStrip array using those scores 1.
	{
	  if((middleLine - arr[leftright-j].score1() < minDiff) && (j <=leftright - leftleft))
	    {
	      arrStrip[numPoints]= arr[leftright-j];
	      numPoints++;
	      j++;
	    }
	  else
	    isLessMin = false;
	}
      
      j = 0;
      isLessMin = true;
      
      while(isLessMin) // find the scores located between middleLine to  [middleLine + minDiff], and fill the arrStrip array using those scores 1.
	{
	  if((arr[rightleft+j].score1() - middleLine < minDiff) && (j <= rightright -rightleft))
	    {
	      arrStrip[numPoints]= arr[rightleft+j];
	      numPoints++;
	      j++;
	    }
	  else
	    isLessMin = false;
	}
      
      sortType = "2";
      int lowest = 1;
      mergeSort(lowest, numPoints, arrStrip); // Then sort arrStrip by score 2.
      sortType = "b";
      
      // Now, check only the neighboring points in arrStrip for possible closer pairs
      for(int k=0;k<numPoints;k++)
	{
	  bool canCheck = true;
	  int next = 1;
	  
	  while(canCheck && k+next < numPoints)
	    {
	      float distance = sqrt(pow(arrStrip[k].score1() - arrStrip[k+next].score1(), 2)+ pow(arrStrip[k].score2() - arrStrip[k+next].score2(), 2));
	      
	      // If this distance is less than the current minimum, update the closest pair
	      if(distance < minDiff)
		{
		  minDiff = distance;
		  minName1 = arrStrip[k].name();
		  minName2 = arrStrip[k+next].name();
		  next++;// Keep checking next point
		}
	      else
		canCheck = false; // Since sorted by score2, further points will be farther away
	    }
	}
      
    }
}



void merge(int lowest, int middle, int highest, info arr[])
{
  int leftSize = middle - lowest + 1;
  int rightSize = highest - middle;

  // Temporary arrays for left and right halves
  info* leftarr = new info[leftSize];
  info* rightarr = new info[rightSize];

  for(int i=0; i<leftSize; i++)  // Copy elements to left array
    leftarr[i] = arr[lowest - 1 + i];

  for(int i=0; i<rightSize; i++)  // Copy elements to right array
    rightarr[i] = arr[middle + i];

  int i = 0;
  int j = 0;
  int k = lowest - 1;
  
  // Merge elements back into the original array in sorted order
  while(!(i == leftSize || j == rightSize))
    {
      if (sortType=="1"){
	if (leftarr[i].score1() == rightarr[j].score1())
	  {
	    arr[k] = leftarr[i];
	    k++; i++;
	    arr[k] = rightarr[j];
	    k++; j++;
	  }
	else if (leftarr[i].score1() > rightarr[j].score1())
	  {
	    arr[k] = rightarr[j];
	    k++; j++;
	  }
	else
	  {
	    arr[k] = leftarr[i];
	    k++; i++;
	  }
      }

      if (sortType=="2"){
	if (leftarr[i].score2() == rightarr[j].score2())
	  {
	    arr[k] = leftarr[i];
	    k++; i++;
	    arr[k] = rightarr[j];
	    k++; j++;
	  }
	else if (leftarr[i].score2() > rightarr[j].score2())
	  {
	    arr[k] = rightarr[j];
	    k++; j++;
	  }
	else
	  {
	    arr[k] = leftarr[i];
	    k++; i++;
	  }
      }
    }

  // Copy any remaining elements from left and right arrays
  while(!(i >= leftSize))
    {
      arr[k] = leftarr[i];
      k++; i++;
    }

  while(!(j >= rightSize))
    {
      arr[k] = rightarr[j];
      k++; j++;
    }
  
}



// Recursively sorts an array using merge sort
void mergeSort(int lowest, int highest, info arr[])
{
  
  if (lowest < highest)
    {
      int middle = (lowest + highest)/2 ;
     
      mergeSort(lowest, middle, arr);
      mergeSort(middle+1, highest, arr);
      merge(lowest, middle, highest, arr);
    }
  
 }
