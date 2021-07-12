#pragma once

#include <string>
using namespace std;

class MenuHelper {
 public:
  static int readIntergerCommand();

  static string readStringCommand();

  static double readDoubleCommand();

  void menu_main();

  void menu_add_dataBean();

  void menu_add_dataBean_Single_FromConsole();

  void menu_add_dataBean_Batch_FromConsole();

  void menu_add_dataBean_FromFile();

  void menu_delete_dataBean();

  void menu_modify_dataBean();

  void menu_list_dataBean();

  void menu_search_dataBean();

  void menu_searchByID_dataBean();

  void menu_searchByName_dataBean();

  void menu_calc_dataBean();
};
