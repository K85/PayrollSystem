#include "MenuHelper.h"

#include <stdio.h>

#include <string>

#include "DataBean.h"
#include "SystemInterface.h"
#define BUFFER_SIZE 1024

#pragma warning(disable : 4996)

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
    printf("-> ���˵�\n");
    printf("1. ���Ա��\n");
    printf("2. ɾ��Ա��\n");
    printf("3. �޸�Ա��\n");
    printf("4. ��ѯԱ��\n");
    printf("5. ����Ա��\n");
    printf("6. ����Ա��\n\n");

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
        printf("���������, ������\n");
    }
  }
}

void MenuHelper::menu_add_dataBean() {
  while (true) {
    printf("--> ���Ա��\n");
    printf("1. �ӿ���̨, ����\n");
    printf("2. �ӿ���̨, ����\n");
    printf("3. ���ļ�\n");
    printf("4. ����\n\n");

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
        printf("���������, ������\n");
    }
  }
}

void MenuHelper::menu_add_dataBean_Single_FromConsole() {
  // Construct DataBean.
  DataBean dataBean = DataBean::readDataBean();

  if (SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("���ʧ��,��Ա�����Ѵ���!\n");
    return;
  }

  // Add DataBean.
  SystemInterface::getInstance().addDataBean(dataBean);
}

void MenuHelper::menu_add_dataBean_Batch_FromConsole() {
  printf("�������Ա��(��ʽ): [ID] [��������] [����] [�籣] [ҽ��] [������]\n");
  printf("���� Ctrl + Z���������н���\n");

  // Data Flow.
  int id;
  char name_buf[BUFFER_SIZE];
  double baseSalary;
  double allowance;
  double socialInsurance;
  double medicalInsurance;
  double accumulationFund;

  while (scanf("%d %s %lf %lf %lf %lf %lf", &id, &name_buf, &baseSalary,
               &allowance, &socialInsurance, &medicalInsurance,
               &accumulationFund) != EOF) {
    DataBean dataBean =
        DataBean(id, string(name_buf), baseSalary, allowance, socialInsurance,
                 medicalInsurance, accumulationFund);
    SystemInterface::getInstance().addDataBean(dataBean);
    printf("��ӳɹ�, ��������һ��\n");
  }

  printf("�����������Ա��\n");
}

void MenuHelper::menu_add_dataBean_FromFile() {
  // Input FileName;
  printf("������Ҫ��ӵ��ļ���\n");
  string fileName = readStringCommand();

  // Read DataBeans from Disk.
  SystemInterface::getInstance().loadDataBeansFromDisk(false, fileName);
  SystemInterface::getInstance().saveDataBeansToDisk();
  printf("���ļ�������ӳɹ�\n");
}

void MenuHelper::menu_delete_dataBean() {
  // Construct DataBean.
  printf("������Ҫɾ���Ľ�ʦ��: \n");
  int id = readIntergerCommand();
  DataBean dataBean(id);

  // DataBean ID Exist ?
  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("ɾ��ʧ��, ��Ա���Ų�����!\n");
    return;
  }

  // Delete DataBean.
  SystemInterface::getInstance().deleteDataBean(dataBean);
  printf("ɾ���ɹ�!\n");
}

void MenuHelper::menu_modify_dataBean() {
  // Get Operate DataBean ID.
  printf("������Ҫ�޸ĵ�Ա����: \n");
  int id = readIntergerCommand();
  DataBean dataBean(id);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("Ա���Ų�����.\n");
    return;
  }

  printf("�������޸ĺ��������: \n");
  dataBean = DataBean::readDataBeanFromID(id);

  SystemInterface::getInstance().modifyDataBean(dataBean);
}

void MenuHelper::menu_search_dataBean() {
  while (true) {
    printf("--> ��ѯԱ��\n");
    printf("1. ������\n");
    printf("2. ������\n");
    printf("3. ����\n\n");

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
        printf("���������, ������\n");
    }
  }
}

void MenuHelper::menu_list_dataBean() {
  static const int MAX_DATABEANS_PER_PAGE = 10;

  printf("======�������е�Ա��======\n");
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
  printf("������Ҫ��ѯ��Ա����: ");
  int id = readIntergerCommand();

  DataBean dataBean(id);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("Ա���Ų�����.\n");
    return;
  }

  list<DataBean>::iterator iter =
      SystemInterface::getInstance().searchDataBean(dataBean);

  iter->printDataBean();
}

void MenuHelper::menu_searchByName_dataBean() {
  // Get Operate DataBean Name.
  printf("������Ҫ��ѯ��Ա������: \n");
  string name = readStringCommand();
  DataBean dataBean(name);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("Ա������������.\n");
    return;
  }

  list<DataBean>::iterator iter =
      SystemInterface::getInstance().searchDataBean(dataBean);

  iter->printDataBean();
}

void MenuHelper::menu_calc_dataBean() {
  // Get Operate DataBean ID.
  printf("������Ҫ�����Ա����: ");
  int id = readIntergerCommand();
  DataBean dataBean(id);

  if (!SystemInterface::getInstance().existDataBean(dataBean)) {
    printf("Ա���Ų�����.\n");
    return;
  }

  // Calc and Save Results
  list<DataBean>::iterator iter =
      SystemInterface::getInstance().searchDataBean(dataBean);

  iter->calcAndSaveToDisk();

  printf("�������, ����ѱ��浽CalcResults.csv�ļ�.\n");
}
