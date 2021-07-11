#pragma once
#include "DataBean.h"
#include <vector>
#include <string>
using namespace std;
class SystemInterface {

private:
    vector<DataBean> dataBeans;

// Singleton
public:
    static SystemInterface & getInstance();
public:
    vector<DataBean> & getDataBeans();

public:
    void addDataBean(DataBean dataBean);

public:
    void deleteDataBean(DataBean dataBean);

public:
    void modifyDataBean(DataBean dataBean);

public:
    vector<DataBean>::iterator searchDataBean(DataBean dataBean);

public:
    bool existDataBean(DataBean dataBean);

public:
    void saveDataBeansToDisk();

public:
    void loadDataBeansFromDisk();

public:
    void loadDataBeansFromDisk(bool clearDetaBeansInMemory, string fileName);
};

