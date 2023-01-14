#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
// function to read in nelem,ndim,npoin,nface,time,ntype

class mymatrix{
  public:
    int rows;
    int cols;
    int offset;

    void m_vec(int data)// function to get the vector for a matrix/array
    {

      
      std::vector<std::vector<int>> v;  //initialize an empty vector    
      for(int i=0;i<rows;i++){
        std::vector<int> tempvec;  //initialize an empty temp vector
        for (int j = 0;j<cols;j++){
         tempvec.push_back(data);  // push in data for each col at the end
        }
        v.push_back(tempvec);

      }
    }



};

// function to read the connectivity matrix from the input data
void inpoel_read(){
int nelem = 1559;
int npoin = 839;
int nface = 117;
int ntype = 3;
int ndimn = 2;
int inpoel[nelem][ntype];// array to represent connectivity matrix

}
// function to read in the co-ordinates of the points
void coord_read(){


}
// function to write the data in .msh ASCII format for gmsh to read 
void gmsh_write(){

}

int main(){
  return 0;
}

