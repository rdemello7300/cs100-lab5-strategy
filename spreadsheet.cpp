#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

Spreadsheet::~Spreadsheet()
{
    delete select;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet:: print_selection(std::ostream& cout) const
{
  if(select == NULL){
    for( int i = 0; i < data.size(); i++)
    {
	for(int k = 0; k < column_names.size(); k++)
	{
	   cout << cell_data(i, k) << " ";
	}
	cout << endl;
    }
  }
  else
  {
    for(int i = 0; i < data.size(); i++){
	if(select -> select(this, i)){
	for(int k = 0; k < column_names.size(); k++){
	
	  cout << cell_data(i, k) << " ";
	}
	cout << endl;
}
    }
  }

}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    column_names=names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}
