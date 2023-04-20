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
    int* ScheduleMatrix = new int[(7*16)] {};

    for(int i = 0; i < 7*16; i++) {
            ScheduleMatrix[i] = -1;
    }
    bool Run = PensumReading(Courses, IDECourses, HRSCourses, IndexCourses, ToolsCourses);


    if (Run){

        cout << "--------- Bienvenidos a ClassPlannerPro ---------\n\n"
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
            int* ChosenCourses = CoursesOptions(Courses, IndexCourses, ToolsCourses, HRSCourses);
            int Credits = 0;
            for (int i = 0; ChosenCourses[i] != -1; i++){
                Credits += HRSCourses[(ChosenCourses[i]*4) + 3];
            }
            cout << "\033c";
            //char X[] = "D:/DataLuis/Documentos/Extra/Sin título.txt";
            int* HRS = new int[4];
            int* HoursStudy = new int[112] {-1};
            int Ind = 0;
            for (int x = 0; x < 2; x++){

                for (int i = 0; ChosenCourses[i] != -1; i++){
                    for (int l = 0; l < 4; l++){
                        HRS[l] = HRSCourses[(ChosenCourses[i]*4) + l];
                    }
                    int TotalHours = 0;
                    if (x == 0){
                        for (int j = 0; j < 3; j++){
                            TotalHours += HRS[j];
                        }
                    }
                    else{
                        for (int j = 0; j < 3; j++){
                            TotalHours += HRS[j];
                        }
                        TotalHours = (((HRS[3] * 48)/16) - TotalHours);
                    }

                    while(TotalHours > 0){
                        cout << "-------------------------------------- Selector de Horarios --------------------------------------\n\n";
                        PrintMatrix(ScheduleMatrix, HoursStudy);
                        cout << endl;
                        //cout << "Que horarios deseas para ";
                        NameCourse(Courses, IndexCourses, ChosenCourses[i]);
                        cout << endl;
                        ClassSchedules(HRS);
                        char Day;
                        if (x == 0){
                            cout << "\nTienes " << TotalHours << " hora(s) de clase disponible(s) actualmente\n"
                                    "\nL(Lunes), M(Martes), W(Miercoles), J (Jueves), V(Viernes), S(Sabado), D(Domingo)\n"
                                    "En que dia tienes la clase?: ";
                        }
                        else{
                            cout << "\nTienes " << TotalHours << " hora(s) de estudio disponible(s) actualmente\n"
                                    "\nL(Lunes), M(Martes), W(Miercoles), J (Jueves), V(Viernes), S(Sabado), D(Domingo)\n"
                                    "En que dia quieres estudiar?: ";
                        }
                        cin >> Day;
                        cout << "\033[F\033[K\033[F\033[K\033[F\033[K\033[F\033[K";
                        int DayAux = DayInt(Day);
                        int Hours;
                        cout << "Cuantas horas?: ";
                        cin >> Hours;
                        cout << "\033[F\033[K";
                        while(Hours < 0 || Hours > TotalHours){
                            cout << "Horas fuera de rango. Ingrese cantidad\nde horas adecuada. Max " << TotalHours << ": ";
                            cin >> Hours;
                            cout << "\033[F\033[K\033[F\033[K";
                        }
                        int ClassTime;
                        cout << "A que hora del dia?\nEjemplo 06:00 -> 6 : ";
                        cin >> ClassTime;
                        cout << "\033[F\033[K\033[F\033[K";
                        bool Available = true;
                        Available = ScheduleAvailability(ScheduleMatrix, DayAux, Hours, ClassTime);

                        if (Available){
                            if (x == 1){
                                for(int y = 0 ; y < Hours; y ++){
                                    HoursStudy[Ind] = ((DayAux*16) + (ClassTime - 6)) + y;
                                    Ind++;
                                    HoursStudy[Ind] = -1;
                                }

                            }
                            UpdateMatrix(ScheduleMatrix, IDECourses, ChosenCourses[i], DayAux, Hours, ClassTime);
                            cout << "Cambio exitoso";
                            TotalHours -= Hours;
                        }

                        cout << "\033c";
                    }

                }
            }

            delete[] HRS;
            SaveMatrix(ScheduleMatrix, HoursStudy);

            delete[] ChosenCourses;
        }
    }
    else{
        cout << "Error de Lectura. Contactese con el programador, o verifique la ruta del archvo Pensum";
    }

    delete[] ToolsCourses;
    delete[] ScheduleMatrix;
    delete[] Name;
    delete[] Courses;
    delete[] IDECourses;
    delete[] IndexCourses;
    delete[] HRSCourses;
}
