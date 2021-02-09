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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
