#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column
{
protected:
   std::string givenName;
public:
   Select_Contains(const Spreadsheet* sheet, const std::string& c, const std::string& r):Select_Column(sheet,c), givenName(r) { }

   virtual bool select(const std::string& s) const
   {
	if(s.find(givenName)!= std::string::npos) return true;
	return false;	
   }
};

class Select_And: public Select
{
protected:
   Select* obj1 = NULL;
   Select* obj2 = NULL;
public: 
   Select_And(Select* selectObj1, Select* selectObj2)
   {
      obj1 = selectObj1;
      obj2 = selectObj2;
   }

   ~Select_And()
   {  
	delete obj1;
	delete obj2;
   }  

   virtual bool select(const Spreadsheet* sheet, int row) const  //const std::string& s
   {
	if(obj1 -> select(sheet, row) == true &&  obj2 -> select(sheet, row) == true) return true;
	return false;	
   }

};

class Select_Or: public Select
{
protected:
   Select* obj1 = NULL;
   Select* obj2 = NULL;
public:
   Select_Or(Select* selectObj1, Select* selectObj2)
   {
	obj1 = selectObj1;
        obj2 = selectObj2;
   }

   ~Select_Or()
   {
	delete obj1;
	delete obj2;
   }

   virtual bool select(const Spreadsheet* sheet, int row) const
   {
	if(obj1 -> select(sheet, row) == true || obj2 -> select(sheet,row) == true) return true;
	return false;
   }
};

class Select_Not: public Select
{
protected:
   Select* obj = NULL;
public:
   Select_Not(Select* selectObj)
   {
	obj = selectObj;
   }

   ~Select_Not()
   {
	delete obj;
   }

   virtual bool select(const Spreadsheet* sheet, int row) const
   {
        if(obj -> select(sheet, row) == true) return false;
        else return true;
   }
};
#endif //__SELECT_HPP__
