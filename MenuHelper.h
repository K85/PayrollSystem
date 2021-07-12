#pragma once

#include <string>
using namespace std;

class MenuHelper {
public:

  static int readIntergerCommand();

public:

  static string readStringCommand();

public:

  static double readDoubleCommand();

public:

  void menu_main();

public:

  void menu_add_dataBean();

public:

  void menu_add_dataBean_Single_FromConsole();

public:

  void menu_add_dataBean_Batch_FromConsole();

public:

  void menu_add_dataBean_FromFile();

public:

  void menu_delete_dataBean();

public:

  void menu_modify_dataBean();

public:

  void menu_search_dataBean();

public:

  void menu_list_dataBean();

public:

  void menu_searchByID_dataBean();

public:

  void menu_searchByName_dataBean();

public:

  void menu_calc_dataBean();
};
