#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
using namespace std::chrono; //for code profiling

auto strconv(std::string s) // function to get row of the main  matrix from one line of the text file
{
  stringstream ss; //declaration of string stream object
  ss << s; //push string to stringstream object
  std::vector<double> tempvec; //declare an empty vector
  std::string tempstr; //declare an empty string
  double val; // val to be pushed to tempvec
  while(!ss.eof())
  {
    ss >> tempstr; //push string to temp string word by word
    if(stringstream(tempstr)>>val) //attempt to convert to double, if success then push to vec
    {
      tempvec.push_back(val);
    }
  }
  return tempvec; //return val of the function, is the row of the matrix
}

std::vector<std::vector<double>> main_vec(std::string s1) // function to use the string convert function and push the row vec to main vec                                                         
{
  std::vector<std::vector<double>> mainvec; //main_vec
  std::ifstream file(s1); // file object 
  if (file.is_open()) 
  {
    std::string line; //declare an empty string
    while(std::getline(file,line)) // use get line to take line from file push it to the string declared above
    {
      std::vector<double> tempv; //declare a temp vector, input arg to string convert function
      tempv = strconv(line); //call string convert function to take in the line and get vec filled with meaningful values
      mainvec.push_back(tempv); //push the row vec to main vect, repeated line by line for each line of the text file
    }
  }
 return mainvec; //big vector containing every number in the text file in double format
}

struct vs // struct definition for the two main arrays to be used 
{

   int ndimn; // #of dimensions
   int ntype; // #of nodes in an element
   int nelem; // #of elems in mesh
   int npoin; // #of of points making up elems
   int nface;
   int time;
   std::vector<std::vector<double>> intpoel;//connectivity matrix
   std::vector<std::vector<double>> coords;// location of points
};


vs trimvec(std::vector<std::vector<double>> vec1) // function to get two vecvecs  from big vecvec return type is struct vs
{
  //nelem 7,0 npoin 7,1 nface 7,2 ndimn 5,0 ntype 5,1 intpoel starts from 9, locations from Dr H file
  vs vs1;
  vs1.ndimn = vec1[5][0];
  vs1. ntype = vec1[5][1];
  vs1.nelem = vec1[7][0];
  vs1.npoin = vec1[7][1];
  for(int i=0;i<vs1.nelem;i++)
  {
    std::vector<double> tempvec;
    for(int j=0;j<vs1.ntype+1;j++)
    {
      tempvec.push_back(vec1[i+9][j]);
    }
    vs1.intpoel.push_back(tempvec);
  }
  for(int i = 0;i<vs1.npoin;i++)
  {
    std::vector<double> tempvec1;
    for(int j=0;j<vs1.ndimn+1;j++)
    {
      tempvec1.push_back(vec1[i+10+vs1.nelem][j]);
    }
    vs1.coords.push_back(tempvec1);
  } 
  return vs1;
}

void writegmsh(std::vector<std::vector<double>> i,std::vector<std::vector<double>> c) //function to write out data for gmsh to read
{
  int nelem = i.size(); //number of lines for for loop to write element data in gmsh file
  int npoin = c.size(); //number of lines for for loopt to write node data in gmsh file
  int ntype = c[0].size()-1; //type 2 is for triangle
  ofstream file1 ("feflo.msh"); //name of .msh file 
  if (file1.is_open())
  {
    file1 << "$MeshFormat\n2.0 0 8\n$EndMeshFormat\n$Nodes\n"<< npoin <<"\n";
    //begin for loop to write out node numbers and coords
    for(int i = 0;i<npoin;i++)
    {
      file1 <<i+1<<" "<<c[i][1]<<" "<<c[i][2]<<" "<<"0 \n";
    }
    file1 << "$EndNodes \n$Elements\n"<<nelem<<"\n";
    //begin for loop to write out element connectivity in gmsh format.
    for(int k =0;k<nelem;k++)
    {
      file1<<i[k][0]<<" "<<" "<<ntype<<" "<<" 0 "<<i[k][1]<<" "<<i[k][2]<<" "<<i[k][3]<<"\n";
    }
    file1<<"$EndElements";
  }
  file1.close();
}

int main()
{
  auto start = high_resolution_clock::now(); //start clock
  std::vector<std::vector<double>> mm; //initialize vector to store in data from file.
  mm = main_vec("shri.txt"); // function call to get entire numerical data from file stored in one big vector.
  vs vss = trimvec(mm); //trim the vector down to get only two matrices
  /*std::cout<<vss.coords[11][1]<<"this shit"<<mm[1586][1]<<endl;*/ //used to check code
  writegmsh(vss.intpoel,vss.coords); //function call that writes out feflo.msh file for gmsh to read
  auto stop = high_resolution_clock::now(); //stop clock
  auto duration = duration_cast<microseconds>(stop - start);//get run time
  cout << duration.count()<< endl;
  return 0;
}


