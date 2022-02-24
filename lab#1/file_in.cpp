// This file shows basic functions of reading in a CSV file using C++98
// Please add your name to your code! 

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.

All programs must be able to compile in C++98 standard (the default version on Linux Machine). That means you cannot use the new features of C++11! :(

*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>

using namespace std; 

int main() {

  // define variables
  string sku, brand, category, year, price; 
  vector<int>vSKU;
  vector<string>vBrand;
  vector<string>vCategory;
  vector<int>vYear;
  vector<float>vPrice;

  ifstream in_stream;
  in_stream.open("data.csv"); //opening the file.

  if (!in_stream.fail()) { //if the file is open

    string line;
    
    while (getline(in_stream, line)) { //while the end of file is NOT reached
     stringstream eachLine(line);
     // Fields: sku,brand,category,year,price

     getline(eachLine, sku, ',');
     stringstream ssku(sku); 
     int iSKU = 0;
     ssku >> iSKU;
     vSKU.push_back(iSKU);

     getline(eachLine, brand, ',');
     vBrand.push_back(brand);

     getline(eachLine, category, ',');
     vCategory.push_back(category);

     getline(eachLine, year, ','); 
     stringstream syear(year);
     int iYear;
     syear >> iYear;
     vYear.push_back(iYear);

     getline(eachLine, price, '\n'); 
     stringstream sprice(price);
     float fPrice;
     sprice >> fPrice;
     vPrice.push_back(fPrice);
    
    }

    in_stream.close(); //closing the file cout << "Number of entries: " << i-1 << endl;

   } else {
    printf("Unable to open file"); 
   }
 
  //output values 
  //cout << "SKU" << "\t" << "Brand" << "\t"<< "CATEGORY" << "\t" << "Year" << "\t" << "PRICE" << endl;
  printf("SKU\tBrand\tCATEGORY\tYear\tPRICE\n");

  for (int j = 1; j < vSKU.size(); j++) {
    //cout << vSKU[j] << "\t" << vBrand[j] << "\t\t\t" << vCategory[j] << "\t\t" << vYear[j] << "\t" << vPrice[j]  << endl;
    printf("%d\t%s\t\t\t%s\t\t%d\t%g\n", vSKU[j],vBrand[j].c_str(),vCategory[j].c_str(),vYear[j],vPrice[j]);
  }

  ofstream outFile;
  outFile.open("lab1_output.txt"); 

  //Question 2
  //Calculate the average price per band

  vector<string>::iterator b;
  vector<string>uniqueBrand = vBrand;
  uniqueBrand.erase(uniqueBrand.begin()); //Remove the first element which stores header

  //Sorting the array
  std::sort(uniqueBrand.begin(), uniqueBrand.end());
  
  //Make vBrand contains unique values {ABC XYZ * * *}
  // * means undefined
  b = std::unique(uniqueBrand.begin(), uniqueBrand.begin() + uniqueBrand.size());
 
  // Then resize the vector to remove  undefined
  uniqueBrand.resize(std::distance(uniqueBrand.begin(), b));

  float sum;
  int count;
  for (int j = 0; j < uniqueBrand.size(); j++) {
    //cout << uniqueBrand[j] << " ";
    sum = 0;
    count = 0;
    for (int i = 1; i < vBrand.size(); i++) {
      if (vBrand[i] == uniqueBrand[j]) {
        sum += vPrice[i];
        //cout << sum << endl;
        count++;
      }
    }
    outFile << "The average price of Brand " << uniqueBrand[j] << " : " << sum/count << "\n" << endl;
  }

  //Calculator the average price of each category
  vector<string>uniqueCategory = vCategory;

  // Remove the first index which contains header
  uniqueCategory.erase(uniqueCategory.begin());

  sort(uniqueCategory.begin(), uniqueCategory.end());
  
  // Declare a iterator for the vector
  vector<string>::iterator c;
  c = unique(uniqueCategory.begin(), uniqueCategory.end());
  uniqueCategory.resize(distance(uniqueCategory.begin(), c));

  for (int j = 0; j < uniqueCategory.size(); j++) {
    //cout << uniqueCategory[j] << endl;
    sum = 0;
    count = 0;
    for(int i = 1; i < vCategory.size(); i++) {
      if (uniqueCategory[j] == vCategory[i]) {
        sum += vPrice[i];
        count++;
      }
    }
    outFile << "The average price of Category " << uniqueCategory[j] << " : " << sum/count << "\n" << endl;
  }


  //Question 4
  //for each unique year, list the count of skus and also print out the skus as a list 
  //i.e. 2000 (3): 111, 211, 311 and make a new line per year.
  vector<int>uniqueYear = vYear;
  uniqueYear.erase(uniqueYear.begin());
  
  sort(uniqueYear.begin(), uniqueYear.end());

  vector<int>::iterator y;
  y = unique(uniqueYear.begin(), uniqueYear.end());
  uniqueYear.resize(distance(uniqueYear.begin(), y));
  
  
  for (int j = 0; j < uniqueYear.size(); j++) {
    count = 0;
    string list= "";
    for (int i = 1; i < vYear.size(); i++) {
      if (vYear[i] == uniqueYear[j]) {
        count++;
        std::stringstream ss;
        ss << vSKU[i]; 
        list += " " + ss.str() + ",";             
      }
    }

    
    outFile << uniqueYear[j] << " (" << count << "):" << list.substr(0, list.size()-1) << endl;
    // for (int k = 0; k < list.size(); k++) {    
    //   if (k != list.size()-1) {
    //      outFile << list[k] << ", " << " ";
    //   }else {
    //      outFile << list[k] << " ";
    //   }
    // }
    // outFile << endl;
  }

  outFile.close();
  cout << endl;

}
