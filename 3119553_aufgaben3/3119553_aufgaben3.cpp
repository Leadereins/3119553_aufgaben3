// Matr. - Nr: 3119553             ...
//Nachname / Surname : MA
//Vorname / Given name : Yujie
//Uni - Email : yujie.ma@stud.uni-due.de
//Studiengang / Course of studis :metallurgy and metal forming ISE(pop19)
//***************

#include<iostream>
#include<iomanip>
#include <string>
#include <utility>

using namespace std;

enum Use
{
    once,
    daily,
    mo_fr,
    sa_su,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};





// overload
std::ostream& operator<<(std::ostream& os, const Use& use)
{
    switch (use)
    {
    case Use::monday:    os << "Monday"; break;
    case Use::tuesday:   os << "Tuesday"; break;
    case Use::wednesday: os << "Wednesday"; break;
    case Use::thursday:  os << "Thursday"; break;
    case Use::friday:    os << "Friday"; break;
    case Use::saturday:  os << "Saturday"; break;
    case Use::sunday:    os << "Sunday"; break;
    case Use::once:      os << "once"; break;
    case Use::daily:     os << "daily"; break;
    case Use::mo_fr:     os << "Monday to Friday"; break;
    case Use::sa_su:     os << "Saturday and Sunday"; break;
    }
    return os;
}

// Overloaded unary operator ++ for the enumeration values of Use
Use& operator++(Use& use)
{
    // Implement the increment based on the specified order
    switch (use)
    {
    case Use::monday:   use = Use::tuesday; break;
    case Use::tuesday:  use = Use::wednesday; break;
    case Use::wednesday:use = Use::thursday; break;
    case Use::thursday: use = Use::friday; break;
    case Use::friday:   use = Use::saturday; break;
    case Use::saturday: use = Use::sunday; break;
    case Use::sunday:   use = Use::monday; break;
        // For once, daily, mo_fr, keep the same value
    default: break;
    }
    return use;
}

Use input_use(char use)
{


    switch (use)
    {
    case '0': return Use::monday;
    case '1': return Use::tuesday;
    case '2': return Use::wednesday;
    case '3': return Use::thursday;
    case '4': return Use::friday;
    case '5': return Use::saturday;
    case '6': return Use::sunday;
    case 'o': return Use::once;
    case 'd': return Use::daily;
    case 'm': return Use::mo_fr;
    case 's': return Use::sa_su;
    default:
        std::cerr << "Invalid choice. Defaulting to once.\n";
        return Use::once;
    }
}

//////STEP 5:


int COLUMN_WIDTH = 35;

const int daysInYear = 10;
const int quarterHours_InDay = 12;

//const int daysInYear = 365;
//const int quarterHours_InDay = 96;




// Structure definition for year
struct Year
{
    int yearNumber;
    Use firstDay;
    std::string unit;
    float values[daysInYear][quarterHours_InDay]; // 365 days, 96 quarter-hour intervals per day
};

//
//
//float int_to_float(int x)
//{
//    float y = x;
//    return y;
//}
// Inline function zeros
inline Year& zeros(Year& year)
{
    for (int i = 0; i < daysInYear; ++i)
    {
        for (int j = 0; j < quarterHours_InDay; ++j)
        {
            year.values[i][j] = 0.0f;
        }
    }
    return year;
}

// Inline function time
inline int time(int hour, int minute)
{
    return hour * 60 + minute;
}


//
//void print_timetable(Year& year)
//{
//
//    for (int i = 0; i < 10; i++)
//    {
//        std::cout << std::setw(COLUMN_WIDTH) << std::right << "day  " << i << ":"
//            << std::left << year.firstDay << std::endl;
//        for (int j = 0; j < 3; j++)
//        {
//            cout << std::setw(COLUMN_WIDTH) << j << ":00    " << year.values[i][0 + j * 4] << std::right << "    "
//                << year.values[i][1 + j * 4] << std::right << "    "
//                << year.values[i][2 + j * 4] << std::right << "    "
//                << year.values[i][3 + j * 4] << std::right << "    " << endl;
//        }
//        year.firstDay++;
//
//    }
//}



////STEP 9:重载“Year”的二进制输出运算符 << ：
////
////输出年份信息、天数、星期几和四分之一小时值。
ostream& operator<<(ostream& os, const Year& year)
{
    Use use = year.firstDay;

    os << "Year: " << year.yearNumber << endl;

    for (int i = 0.0; i < daysInYear; i++)
    {
        float x = i;
        os << std::setw(COLUMN_WIDTH) << std::right << "day  " << i << ":"
            << std::left << use << std::endl;

        for (int j = 0.0; j < 3; j++)
        {
            float y = j;
            float x = i;
            os << std::setw(COLUMN_WIDTH) << j <</*std::right<<*/ ":00    " << std::fixed << std::setprecision(2) << year.values[i][0 + j * 4] << std::right << "    "
                << std::fixed << std::setprecision(2) << year.values[i][1 + j * 4] << std::right << "    "
                << std::fixed << std::setprecision(2) << year.values[i][2 + j * 4] << std::right << "    "
                << std::fixed << std::setprecision(2) << year.values[i][3 + j * 4] << std::right << "    " << endl;
        }
        ++use;

        /*year.firstDay = use;*/
    }
    return os;
}

//STEP 10:重载“Year”的二进制加法运算符 + ：
//
//按元素相加两个“Year”结构体，并返回结果。

Year operator+(const Year& year1, const Year& year2)
{
    if (year1.yearNumber == year2.yearNumber && year1.firstDay == year2.firstDay && year1.unit == year2.unit)
    {
        Year result = { year1.yearNumber, year1.firstDay, year1.unit };
        for (int i = 0; i < daysInYear; ++i)
        {
            for (int j = 0; j < quarterHours_InDay; ++j)
            {
                result.values[i][j] = year1.values[i][j] + year2.values[i][j];
            }
        }
        return result;
    }
    else
    {
        std::cerr << "Mismatch in year details. Returning a default year.\n";
        return Year{ 0, Use::once, "", {} };
    }
}



//step 11 :实现“add_consumption”函数：
//
//重载函数以添加特定日期和指定频率的消耗。
void add_consumption(Year& year, int day, int fromMinute, int toMinute, float wattage)
{

    for (int minute = fromMinute; minute < toMinute; ++minute)
    {
        int interval = minute / 15;
        year.values[day][interval] += wattage / 60.0;
    }
}



////STEP 12:实现“sum”函数：
//
//计算一年中所有四分之一小时间隔值的总和。
//

float sum(const Year& year)
{
    double total = 0.0;
    for (int i = 0; i < daysInYear; ++i)
    {
        for (int j = 0; j < quarterHours_InDay; ++j)
        {
            total += year.values[i][j];
        }

    }
    return total;
}



int main(void)
{
    int COLUMN_WIDTH = 35;
    // Define actual and total
    Year actual = { 2024, Use::monday, "Watt" };
    Year total = { 2024, Use::monday, "Watt" };

    // Initialize actual and total
    zeros(actual);
    zeros(total);

    // Set kWh price
    float  kWhPrice = 0.30; // 30 ct/kWh

    // 小型菜单
    char choice;
    do {
        cout << "\nMenu:\n";
        cout << "q - Quit\n";
        cout << "a add actual to total (using operator +)\n";
        cout << "c annual consumption and cost (price for one kWh: 30.00 ct/kWh; calling function sum)\n";
        cout << "o output actual (using operator <<)\n";
        cout << "t output total (using operator <<)\n";
        cout << "u add consumption according to frequency of use (call functions add_consumption)\n";
        cout << "z set actual to zeros (call function zeros)";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 'a':
            total = total + actual;
            break;
        case 'c':
            cout << "sum actual = " << sum(actual) << " Watt" << "(costs:" << kWhPrice * sum(actual) * 0.0010f << "EUR)" << endl;
            cout << "sum total = " << sum(total) << " Watt" << "(costs:" << kWhPrice * sum(total) * 0.0010f << "EUR)" << endl;
            break;
        case 'o':
            cout << actual;
            break;
        case 't':
            cout << total;
            break;
        case 'u':
        {
            cout << "how often it will be used?\n"
                << "Monday(0)\n"
                << "Tuesday(1)\n"
                << "Wednesday(2)\n"
                << "Thursday(3)\n"
                << "Friday(4)\n"
                << "Saturday(5)\n"
                << "Sunday(6)\n"
                << "daily(d)\n"
                << "mo_fr(m)\n"
                << "once(o)\n"
                << "sa_su(s) ? ";
            char frequency;
            Use useage;
            int certain_day;
            cin >> frequency;
            useage = input_use(frequency);

            int from_minute, to_minute;
            int from_hour, to_hour;
            float wattage;

            /*cout << "from hour:minute?  " << endl;
            cout << "input hour:" << endl;
            cin >> from_hour;
            cout << "input minute:" << endl;
            cin >>  from_minute;
            from_minute = time(from_hour, from_minute);*/

            /*cout << "to hour:minute?  " << endl;
            cout << "input hour:" << endl;
            cin >> to_hour;
            cout << "input minute:" << endl;
            cin >> to_minute;
            to_minute = time(to_hour, to_minute);*/

            char str;
            cout << "form hour:minute" << endl;
            cin >> from_hour >> str >> from_minute;
            from_minute = time(from_hour, from_minute);


            cout << "to hour:minute?  " << endl;
            cin >> to_hour >> str >> to_minute;
            to_minute = time(to_hour, to_minute);

            /*cout << "from_minute:" << from_minute << endl;
            cout << "to_minute:" << to_minute << endl;*/



            cout << "Enter wattage: ";
            cin >> wattage;

            switch (useage)
            {


            case monday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 0)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case tuesday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 1)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case wednesday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 2)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case thursday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 3)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case friday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 4)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case saturday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 5)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case sunday:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 6)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case daily:
                for (int j = 0; j < daysInYear; j++)
                {

                    add_consumption(actual, j, from_minute, to_minute, wattage);

                }
                break;
            case mo_fr:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 != 5 && j % 7 != 6)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;
            case once:
                cout << "which day?" << endl;
                cin >> certain_day;
                certain_day = 0; add_consumption(actual, certain_day, from_minute, to_minute, wattage);
                break;
            case sa_su:
                for (int j = 0; j < daysInYear; j++)
                {
                    if (j % 7 == 5 || j % 7 == 6)
                    {
                        add_consumption(actual, j, from_minute, to_minute, wattage);
                    }
                }
                break;

            }

            break;
        }
        case 'z':
            zeros(actual);
            break;
        case 'q':
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 'q');


    return 0;
}