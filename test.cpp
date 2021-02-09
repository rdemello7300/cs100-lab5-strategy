#include "spreadsheet.hpp"
#include "select.hpp"
#include "spreadsheet.cpp"
#include "gtest/gtest.h"
#include <iostream>

TEST(NotTest, evaluatingNot){
   Spreadsheet sheet;
   sheet.set_column_names({"First", "Last", "MonthOfBirth"});
   sheet.add_row({"Orlean", "Lazaro", "10"});
   sheet.add_row({"Carl", "Evans", "5"});
   sheet.add_row({"Harold", "Jenkins", "12"});
   sheet.add_row({"Mat", "Hunter", "5"});

   Spreadsheet checker;
   checker.set_column_names({"First", "Last", "MonthOfBirth"});
   checker.add_row({"Orlean", "Lazaro", "10"});
   checker.add_row({"Harold", "Jenkins", "12"});

   std::stringstream ss;

   sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "MonthOfBirth", "5")));

   std::stringstream oss;
   sheet.print_selection(oss);
   checker.print_selection(ss);
   EXPECT_EQ(ss.str(), oss.str());
}

TEST(AndTest, evaluatingAnd){
   Spreadsheet sheet;
   sheet.set_column_names({"First", "Last", "MonthOfBirth"});
   sheet.add_row({"Orlean", "Lazaro", "10"});
   sheet.add_row({"Carl", "Evans", "5"});
   sheet.add_row({"Harold", "Jenkins", "12"});
   sheet.add_row({"Mat", "Hunter", "5"});

   Spreadsheet checker;
   checker.set_column_names({"First", "Last", "MonthOfBirth"});
   checker.add_row({"Mat", "Hunter", "5"});

   std::stringstream ss;

   sheet.set_selection(new Select_And(new Select_Contains(&sheet, "MonthOfBirth", "5"), 
			new Select_Contains(&sheet, "First", "Mat")));

   std::stringstream oss;
   sheet.print_selection(oss);
   checker.print_selection(ss);
   EXPECT_EQ(ss.str(), oss.str());
}

TEST(OrTest, evaluatingOr){
   Spreadsheet sheet;
   sheet.set_column_names({"First", "Last", "MonthOfBirth"});
   sheet.add_row({"Orlean", "Lazaro", "10"});
   sheet.add_row({"Carl", "Evans", "5"});
   sheet.add_row({"Harold", "Jenkins", "12"});
   sheet.add_row({"Mat", "Hunter", "5"});

   Spreadsheet checker;
   checker.set_column_names({"First", "Last", "MonthOfBirth"});
   checker.add_row({"Carl", "Evans", "5"});
   checker.add_row({"Harold", "Jenkins", "12"});
   checker.add_row({"Mat", "Hunter", "5"});

   std::stringstream ss;

   sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "MonthOfBirth", "5"),
                        new Select_Contains(&sheet, "First", "Harold")));

   std::stringstream oss;
   sheet.print_selection(oss);
   checker.print_selection(ss);
   EXPECT_EQ(ss.str(), oss.str());
}

TEST(Similarities1, AlmostSameInput1){
   Spreadsheet sheet;
   sheet.set_column_names({"Animal"});
   sheet.add_row({"cat"});
   sheet.add_row({"dog"});
   sheet.add_row({"Dog"});
   sheet.add_row({"cats"});

   Spreadsheet checker;
   checker.set_column_names({"Animal"});
   checker.add_row({"cat"});
   checker.add_row({"dog"});
   checker.add_row({"cats"});


   std::stringstream ss;

   sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Animal", "cat"), 
		new Select_Contains(&sheet, "Animal", "dog")));
   std::stringstream oss;
   sheet.print_selection(oss);
   checker.print_selection(ss);
   EXPECT_EQ(ss.str(), oss.str());
}

TEST(Similarities2, AlmostSameInput2){
   Spreadsheet sheet;
   sheet.set_column_names({"Fruits"});
   sheet.add_row({"apple"});
   sheet.add_row({"orange"});
   sheet.add_row({"apples"});
   sheet.add_row({"Snapple"});

   Spreadsheet checker;
   checker.set_column_names({"Fruits"});
   checker.add_row({"apple"});
   checker.add_row({"apples"});
   checker.add_row({"Snapple"});


   std::stringstream ss;

   sheet.set_selection(new Select_Contains(&sheet, "Fruits", "apple"));
   std::stringstream oss;
   sheet.print_selection(oss);
   checker.print_selection(ss);
   EXPECT_EQ(ss.str(), oss.str());
}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
