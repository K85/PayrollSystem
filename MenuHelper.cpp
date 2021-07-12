#include <stdio.h>
#include <string>
#include "MenuHelper.h"
#include "DataBean.h"
#include "SystemInterface.h"
#define BUFFER_SIZE 1024


#pragma warning (disable:4996)


using namespace std;


int MenuHelper::readIntergerCommand() {
  int command;

  scanf("%d", &command);
  return command;
}

string MenuHelper::readStringCommand() {
  char command[BUFFER_SIZE];

  scanf("%s", &command);

  return string(command);
}

double MenuHelper::readDoubleCommand() {
  double command;

  scanf("%lf", &command);
  return command;
}

void MenuHelper::menu_main() {
  while (true) {
    printf("-> 主菜单\n");
    printf("1. 添加员工\n");
    printf("2. 删除员工\n");
    printf("3. 修改员工\n");
    printf("4. 查询员工\n");
    printf("5. 所有员工\n");
    printf("6. 计算员工\n\n");

    switch (readIntergerCommand()) {
    case 1:
      menu_add_dataBean();
      break;

    case 2:
      menu_delete_dataBean();
      break;

    case 3:
      menu_modify_dataBean();
      break;

    case 4:
      menu_search_dataBean();
      break;

    case 5:
      menu_list_dataBean();
      break;

    case 6:
      menu_calc_dataBean();
      break;

    default:
      printf("错误的输入, 请重试\n");
    }
  }
}

void MenuHelper::menu_add_dataBean() {
  while (true) {
    printf("--> 添加员工\n");
    printf("1. 从控制台, 单个\n");
    printf("2. 从控制台, 批量\n");
    printf("3. 从文件\n");
    printf("4. 返回\n\n");

    switch (readIntergerCommand()) {
    case 1:
      menu_add_dataBean_Single_FromConsole();
      break;

    case 2:
      menu_add_dataBean_Batch_FromConsole();
      break;

    case 3:
      menu_add_dataBean_FromFile();
      break;

    case 4:
      return;

    default:
      printf("错误的输入, 请重试\n");
    }
  }
}

void MenuHelper::menu_add_dataBean_Single_FromConsole() {
  // Construct DataBean.
  DataBean dataBean = DataBean::readDataBean();

  if (SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("添加失败,该员工号已存在!");
    return;
  }

  // Add DataBean.
  SystemInterface::getInstance().addDataBean(dataBean);
}

void MenuHelper::menu_add_dataBean_Batch_FromConsole() {
  printf("批量添加员工(格式): [ID] [基本工资] [津贴] [社保] [医保] [公积金]\n");
  printf("输入 Ctrl + Z结束符进行结束\n");

  // Data Flow.
  int    id;
  char   name_buf[BUFFER_SIZE];
  double baseSalary;
  double allowance;
  double socialInsurance;
  double medicalInsurance;
  double accumulationFund;

  while (scanf("%d %s %lf %lf %lf %lf %lf", &id, &name_buf, &baseSalary,
               &allowance, &socialInsurance, &medicalInsurance,
               &accumulationFund) != EOF) {
    DataBean dataBean = DataBean(id,
                                 string(name_buf),
                                 baseSalary,
                                 allowance,
                                 socialInsurance,
                                 medicalInsurance,
                                 accumulationFund);
    SystemInterface::getInstance().addDataBean(dataBean);
    printf("添加成功, 请输入下一个\n");
  }

  printf("结束批量添加员工\n");
}

void MenuHelper::menu_add_dataBean_FromFile() {
  // Input FileName;
  printf("请输入要添加的文件名\n");
  string fileName = readStringCommand();

  // Read DataBeans from Disk.
  SystemInterface::getInstance().loadDataBeansFromDisk(false, fileName);
  SystemInterface::getInstance().saveDataBeansToDisk();
  printf("从文件批量添加成功\n");
}

void MenuHelper::menu_delete_dataBean() {
  // Construct DataBean.
  printf("请输入要删除的教师号: \n");
  int id = readIntergerCommand();
  DataBean dataBean(id);

  // DataBean ID Exist ?
  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("删除失败, 该员工号不存在!");
    return;
  }

  // Delete DataBean.
  SystemInterface::getInstance().deleteDataBean(dataBean);
  printf("删除成功!");
}

void MenuHelper::menu_modify_dataBean() {
  // Get Operate DataBean ID.
  printf("请输入要修改的员工号: \n");
  int id = readIntergerCommand();
  DataBean dataBean(id);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("员工号不存在.");
    return;
  }

  printf("请输入修改后的新数据: \n");
  dataBean = DataBean::readDataBeanFromID(id);

  SystemInterface::getInstance().modifyDataBean(dataBean);
}

void MenuHelper::menu_search_dataBean() {
  while (true) {
    printf("--> 查询员工\n");
    printf("1. 按工号\n");
    printf("2. 按姓名\n");
    printf("3. 返回\n\n");

    switch (readIntergerCommand()) {
    case 1:
      menu_searchByID_dataBean();
      break;

    case 2:
      menu_searchByName_dataBean();
      break;

    case 3:
      return;

    default:
      printf("错误的输入, 请重试\n");
    }
  }
}

void MenuHelper::menu_list_dataBean() {
  static const int MAX_DATABEANS_PER_PAGE = 10;

  printf("======现在所有的员工======\n");
  int count = 0;

  for (DataBean dataBean : SystemInterface::getInstance().getDataBeans()) {
    if ((count != 0) && (count % MAX_DATABEANS_PER_PAGE == 0)) {
      system("pause");
      system("cls");
    }

    dataBean.printDataBean();
    count++;
  }
}

void MenuHelper::menu_searchByID_dataBean() {
  // Get Operate DataBean ID.
  printf("请输入要查询的员工号: ");
  int id = readIntergerCommand();

  DataBean dataBean(id);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("员工号不存在.\n");
    return;
  }

  list<DataBean>::iterator iter = SystemInterface::getInstance().searchDataBean(
    dataBean);

  iter->printDataBean();
}

void MenuHelper::menu_searchByName_dataBean() {
  // Get Operate DataBean Name.
  printf("请输入要查询的员工姓名: \n");
  string   name = readStringCommand();
  DataBean dataBean(name);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("员工姓名不存在.\n");
    return;
  }

  list<DataBean>::iterator iter = SystemInterface::getInstance().searchDataBean(
    dataBean);

  iter->printDataBean();
}

void MenuHelper::menu_calc_dataBean() {
  // Get Operate DataBean ID.
  printf("请输入要计算的员工号: ");
  int id = readIntergerCommand();
  DataBean dataBean(id);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("员工号不存在.\n");
    return;
  }

  // Calc and Save Results
  list<DataBean>::iterator iter = SystemInterface::getInstance().searchDataBean(
    dataBean);

  iter->calcAndSaveToDisk();

  printf("计算完成, 结果已保存到CalcResults.csv文件.\n");
}
