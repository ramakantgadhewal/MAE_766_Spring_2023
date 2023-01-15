#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

std::vector<int> strconv(std::string s) // function to get row of the matrix from one line of the text file
{
  stringstream ss; //declaration of string stream object
  ss << s; //push string to stringstream object
  std::vector<int> tempvec; //declare an empty vector
  std::string tempstr; //declare an empty string
  int val; // val to be pushed to tempvec
  while(!ss.eof())
  {
    ss >> tempstr; //push string to temp string word by word
    if(stringstream(tempstr)>>val)
    {
      tempvec.push_back(val);
    }
  
  }
  return tempvec; //return val of the function, is the row of the matrix
}


std::vector<std::vector<int>> main_vec(std::string s1)
{
  std::vector<std::vector<int>> mainvec; //main_vec
  std::ifstream file(s1); // file object 
  if (file.is_open())
  {
    std::string line;
    while(std::getline(file,line))
    {
      std::vector<int> tempv;
      tempv = strconv(line);
      mainvec.push_back(tempv);
    }
   
  }

  
  

  return mainvec;
}


int main()
{
  std::vector<std::vector<int>> mm;
mm = main_vec("shri.txt");
std::cout<<mm[35][0];
return 0;

}

