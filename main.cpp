#include "HeadCPP.h"

using namespace std;

int main()
{
    char* Name {};
    char* Courses {};
    int* IDECourses {};
    int* IndexCourses {};
    int* HRSCourses {};
    int* ToolsCourses = new int[2];
    int* ScheduleMatrix = new int[(7*16)];
    bool Run = PensumReading(Courses, IDECourses, HRSCourses, IndexCourses, ToolsCourses);


    if (Run){

        cout << "-------- Bienvenidos a ClassPlannerPro --------\n\n"
                "Como te llamas?\n\n";
        Name = new char[100];
        cin >> Name;
        int Option;
        cout << "Bienvenido " << Name << ".\n\n"
                "Para navegar ingrese el indice de la opcion deseada.\n\n"
                "A que carrera perteneces?\n"
                "1. Ingenieria Electronica.\n\n"
                "Ingrese el indice: ";
        cin >> Option;

        while(Option != 1){
            cout << "Opcion invalida. ingrese un indice valido: ";
            cin >> Option;
        }


        if (Option == 1){

            ViewCourses(Courses, IDECourses, HRSCourses, IndexCourses, ToolsCourses);
        }
    }
    else{
        cout << "Error de Lectura";
    }

    delete[] ToolsCourses;
    delete[] ScheduleMatrix;
    delete[] Name;
    delete[] Courses;
    delete[] IDECourses;
    delete[] IndexCourses;
    delete[] HRSCourses;
}
