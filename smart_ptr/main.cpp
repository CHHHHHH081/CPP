#include "smart_ptr.h"

struct Date
{
    int _year;
    int _month;
    int _day;

    Date(int year = 1, int month = 1, int day = 1)
        :_year(year)
        , _month(month)
        , _day(day)
    {}

    ~Date()
    {
        cout << "~Date()" << endl;
    }
};


void test01()
{
    unique_ptr<Date> up1(new Date);
    unique_ptr<Date> up2(move(up1));

    shared_ptr<Date> sp1(new Date);
    shared_ptr<Date> sp2(sp1);
    sp2->_day = 10;
    sp1->_month = 9;
    
    auto sp3 = make_shared<Date>(Date());
}

void test02()
{
    zzt::shared_ptr<Date> msp1(new Date);
    zzt::shared_ptr<Date> msp2(msp1);
    zzt::shared_ptr<Date> msp3 = msp1;
    cout << msp2.use_count() << endl;
    msp3->_year = 9999;
    msp1->_day = 10298; 
    msp2->_month = 114514;
}

int main()
{
    test02();
	return 0;
}