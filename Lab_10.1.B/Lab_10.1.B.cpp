#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

// Перелік спеціальностей
enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAVCH };

// Структура для Рівня В (з анонімним об'єднанням)
struct Student
{
    string prizv;
    unsigned kurs;
    Specialnist spec;
    int fizyka;
    int matematyka;
    union
    {
        int programuvannya;
        int chyselni_metody;
        int pedagogika;
    };
};

// Прототипи функцій
void Create(Student* s, const int N);
void Print(const Student* s, const int N, const string* specStr);
void PrintExcellentStudents(const Student* s, const int N);
double CalcPercentHighAvg(const Student* s, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string specStr[] = {
        "Комп. науки",
        "Інформатика",
        "Мат. та екон.",
        "Фіз. та інф.",
        "Труд. навч."
    };

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    if (N <= 0)
    {
        cout << "Кількість студентів має бути більшою за 0." << endl;
        return 1;
    }

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N, specStr);

    PrintExcellentStudents(s, N);

    double percent = CalcPercentHighAvg(s, N);
    cout << fixed << setprecision(2);
    cout << "\nПроцент студентів, у яких середній бал більший за 4.5: "
        << percent << "%" << endl;

    delete[] s;
    return 0;
}

// 1. Формування масиву структур з об'єднаннями
void Create(Student* s, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << "  прізвище: ";
        getline(cin, s[i].prizv);
        cout << "  курс: ";
        cin >> s[i].kurs;
        cout << "  спеціальність (0 - Комп. науки, 1 - Інформатика, "
            << "2 - Мат. та екон., 3 - Фіз. та інф., 4 - Труд. навч.): ";
        cin >> spec;
        s[i].spec = (Specialnist)spec;

        cout << "  оцінка з фізики: ";
        cin >> s[i].fizyka;
        cout << "  оцінка з математики: ";
        cin >> s[i].matematyka;

        switch (s[i].spec)
        {
        case KOMP_NAUKY:
            cout << "  оцінка з програмування: ";
            cin >> s[i].programuvannya;
            break;
        case INFORMATYKA:
            cout << "  оцінка з чисельних методів: ";
            cin >> s[i].chyselni_metody;
            break;
        case MAT_EKON:
        case FIZ_INF:
        case TRUD_NAVCH:
            cout << "  оцінка з педагогіки: ";
            cin >> s[i].pedagogika;
            break;
        }
        cout << endl;
    }
}

// 2. Вивід масиву у вигляді таблиці (9 стовпців)
void Print(const Student* s, const int N, const string* specStr)
{
    cout << "\nСписок студентів (Рівень В):" << endl;
    cout << "======================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс | Спеціальність | Фізика | Математика | Програм. | Чис. мет. | Педагогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " "
            << "| " << setw(12) << left << s[i].prizv << " "
            << "| " << setw(4) << right << s[i].kurs << " "
            << "| " << setw(13) << left << specStr[s[i].spec] << " "
            << "| " << setw(6) << right << s[i].fizyka << " "
            << "| " << setw(10) << right << s[i].matematyka << " ";

        switch (s[i].spec)
        {
        case KOMP_NAUKY:
            cout << "| " << setw(8) << right << s[i].programuvannya << " |"
                << setw(11) << right << "|" << setw(13) << right << "|" << endl;
            break;
        case INFORMATYKA:
            cout << "|" << setw(12) << right << "| " << setw(8) << right << s[i].chyselni_metody << " |"
                << setw(13) << right << "|" << endl;
            break;
        case MAT_EKON:
        case FIZ_INF:
        case TRUD_NAVCH:
            cout << "|" << setw(11) << right << "|" << setw(12) << right << "| "
                << setw(10) << right << s[i].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "======================================================================================================" << endl;
}

// 3. Вивід прізвищ студентів-відмінників (Пункт 1 варіанта)
void PrintExcellentStudents(const Student* s, const int N)
{
    cout << "\nПрізвища студентів, які вчаться на \"відмінно\":" << endl;
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        int thirdMark = 0;
        switch (s[i].spec)
        {
        case KOMP_NAUKY:
            thirdMark = s[i].programuvannya;
            break;
        case INFORMATYKA:
            thirdMark = s[i].chyselni_metody;
            break;
        default:
            thirdMark = s[i].pedagogika;
            break;
        }

        if (s[i].fizyka == 5 && s[i].matematyka == 5 && thirdMark == 5)
        {
            count++;
            cout << setw(3) << right << count << ". " << s[i].prizv << endl;
        }
    }

    if (count == 0)
    {
        cout << "  Відмінників немає." << endl;
    }
}

// 4. Обчислення проценту студентів із середнім балом > 4.5 (Пункт 2 варіанта)
double CalcPercentHighAvg(const Student* s, const int N)
{
    if (N == 0) return 0.0;

    int count = 0;
    for (int i = 0; i < N; i++)
    {
        int thirdMark = 0;
        switch (s[i].spec)
        {
        case KOMP_NAUKY:
            thirdMark = s[i].programuvannya;
            break;
        case INFORMATYKA:
            thirdMark = s[i].chyselni_metody;
            break;
        default:
            thirdMark = s[i].pedagogika;
            break;
        }

        double avg = (s[i].fizyka + s[i].matematyka + thirdMark) / 3.0;
        if (avg > 4.5)
        {
            count++;
        }
    }

    return (100.0 * count) / N;
}