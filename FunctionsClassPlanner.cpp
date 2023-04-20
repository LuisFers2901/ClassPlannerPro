#include <HeadCPP.h>

bool PensumReading(char* &Courses, int* &IDECourses, int* &HRSCourses, int* &IndexCourses, int* &ToolsCourses){

    char PathPensum[] = "D:/DataLuis/Documentos/ClassPlannerPro/Data_Programa/PensumElectronica.txt";
    ifstream FilePensum(PathPensum);
    if (FilePensum.is_open()){
        int NumCourses = 1;
        char LineBreak;
        while(FilePensum.get(LineBreak)){
            if (LineBreak == '\n'){
                NumCourses++;
            }
        }
        FilePensum.clear();
        FilePensum.seekg(0, std::ios::beg);

        IDECourses = new int [NumCourses];
        IndexCourses = new int [NumCourses];
        HRSCourses = new int [(NumCourses*4)];

        char Character;
        int IDE = 0;
        int SizeCCourses = 0;
        int IndexIDE = 0;
        int IndexHRS = 0;
        while(FilePensum.get(Character)){

            if (Character == '['){
                while(FilePensum.get(Character)){
                    if (Character == ']'){
                        break;
                    }
                    SizeCCourses++;

                }
            }

            else if (Character == '<'){

                for (int i = 0; i < 7; i++){
                    FilePensum.get(Character);
                    IDE += int(Character) - 48;
                    if (i == 6){
                        break;
                    }
                    IDE *= 10;
                }

                IDECourses[IndexIDE] = IDE;
                IDE = 0;
                IndexIDE++;

            }

            else if(Character == '('){
                for (int i = 0; i < 4; i++){
                    FilePensum.get(Character);
                    HRSCourses[IndexHRS] = (int(Character) - 48);
                    IndexHRS++;
                }

            }
        }
        FilePensum.clear();
        FilePensum.seekg(0, std::ios::beg);
        SizeCCourses;
        Courses = new char[(SizeCCourses + 1)];
        int Pos = 1;
        int PosCharacters = 0;
        while(FilePensum.get(Character)){
            if (Character == '['){
                while(FilePensum.get(Character)){
                    if (Character == ']'){
                        break;
                    }
                    Courses[PosCharacters] = Character;
                    PosCharacters++;

                }

                IndexCourses[Pos] = PosCharacters;
                Pos++;

            }
        }
        IndexCourses[0] = 0;
        Courses[PosCharacters] = '\0';
        FilePensum.close();
        ToolsCourses[0] = SizeCCourses;
        ToolsCourses[1] = NumCourses;
        return true;
    }
    else{
        return false;
    }

}

void ViewCourses(char* &Courses, int* &IDECourses, int* &HRSCourses, int* &IndexCourses, int* &ToolsCourses){

    cout << "\n---------------- Lista de Cursos ----------------" << endl;
    for (int i = 0 ; i < ToolsCourses[1]; i++){
        if (i < 10){
            cout << i << ".  (" << HRSCourses[((i*4)+3)] << "C) ";
            NameCourse(Courses, IndexCourses, i);
            cout << " (" << IDECourses[i] << ")" << endl;
        }
        else{
            cout << i << ". (" << HRSCourses[((i*4)+3)] << "C) ";
            NameCourse(Courses, IndexCourses, i);
            cout << " (" << IDECourses[i] << ")" << endl;
        }
    }
    cout << "-------------------------------------------------" << endl;
}

void NameCourse(char* &Courses, int* &IndexCourses, int Index){

    for (int i = IndexCourses[Index]; i < IndexCourses[(Index+1)]; i++){

        cout << Courses[i];
    }
}

int* CoursesOptions(char* &Courses, int* &IndexCourses, int* &ToolsCourses, int* &HRSCourses){

    int* ChosenCourses = new int[25] {-1};
    int Cont = 0;
    int IndexM;
    int YN;
    int Credits = 0;
    int CreditValue;
    cout << endl;
    while (true){

        cout << "Ingrese la materia a matricular por su indice: ";
        cin >> IndexM;
        cout << "\033[F\033[K";

        while(IndexM < 0 || IndexM > (ToolsCourses[1] - 1)){
            cout << "Opcion Invalida, use los indice de la lista: ";
            cin >> IndexM;
            cin.ignore();
            cout << "\033[F\033[K";
        }

        bool Run = true;

        for (int i = 0; ChosenCourses[i] != -1; i++){
            if (IndexM == ChosenCourses[i]){
                cout << "No puedes repetir cursos ya selecionados\n";
                cout << "Oprima Enter para salir";
                cin.ignore();
                cin.get();
                cout << "\033[F\033[K";
                cout << "\033[F\033[K";
                Run = false;
            }
        }
        if (Run == true){

            cout << "Seguro que desea agregar la siguiente materia: ";
            NameCourse(Courses, IndexCourses, IndexM);
            cout << "\nIngrese 1 para Si, de lo contrario 0: ";
            cin >> YN;
            cin.ignore();
            cout << "\033[F\033[K";
            cout << "\033[F\033[K";

            while(YN != 1 && YN != 0){
                cout << "Opcion Invalida, 1 para Si, de lo contrario 0: ";
                cin >> YN;
                cin.ignore();
                cout << "\033[F\033[K";
            }

            if (YN == 1){
                CreditValue = HRSCourses[((IndexM*4)+3)];
                if ((Credits+CreditValue) < 24){
                    Credits += CreditValue;
                    ChosenCourses[Cont] = IndexM;
                    Cont++;
                    ChosenCourses[Cont] = -1;
                }
                else{
                    cout << "Limite de creditos superados\n";
                }
            }
            int EndFunction = 0;
            cout << "Actualmente cuentas con " << Credits << ". (Maximo de creditos 24)\n"
                    "Deseas agregar otra materia? 1 para Si, de lo contrario 0: ";
            cin >> EndFunction;
            cin.ignore();
            cout << "\033[F\033[K";
            cout << "\033[F\033[K";

            while(EndFunction != 1 && EndFunction != 0){
                cout << "Opcion Invalida, 1 para Si, de lo contrario 0: ";
                cin >> EndFunction;
                cin.ignore();
                cout << "\033[F\033[K";
            }


            cout << "Desea visualizar los cursos actualmente seleccionados?\n"
                    "Ingrese 1 para Si, de lo contrario 0: ";
            cin >> YN;
            cin.ignore();
            while(YN != 1 && YN != 0){
                cout << "Opcion Invalida, 1 para Si, de lo contrario 0: ";
                cin >> YN;
                cin.ignore();
                cout << "\033[F\033[K";
            }
            cout << "\033[F\033[K";
            cout << "\033[F\033[K";
            if (YN == 1){
                int j = 0;
                for (j; ChosenCourses[j] != -1; j++){
                    cout << j + 1 << ". (" << HRSCourses[((ChosenCourses[j]*4)+3)] << ") ";
                    NameCourse(Courses, IndexCourses, ChosenCourses[j]);
                    cout << endl;
                }

                cout << "Total de creditos Actuales: " << Credits << endl;
                cout << "Oprima Enter para salir ";
                cin.ignore();

                for (int i = 0; i < j+2; i++){
                    cout << "\033[F\033[K";
                }
            }

            if(EndFunction == 0){
                break;
            }
        }
    }
    return ChosenCourses;
}

bool ScheduleAvailability(int* ScheduleMatrix, int DayAux, int Hours, int ClassTime){



    int FinalIndex = (DayAux*16) + 16;

    for(int i = 0 ; i < Hours; i ++){
        int Index = ((DayAux*16) + (ClassTime - 6)) + i;
        cout <<ScheduleMatrix[Index];
        if(ScheduleMatrix[Index] != -1){
            cout << "No hay disponibilidad para esas horas";
            return false;
        }
        else if(Index >= FinalIndex){
            cout << "Muy tarde, interfiere con la hora de sueno";
            return false;
        }

    }
    return true;
}

void UpdateMatrix(int* ScheduleMatrix, int* IDECourses, int ChosenCourses, int DayAux, int Hours, int ClassTime){

    for(int i = 0 ; i < Hours; i ++){
        ScheduleMatrix[((DayAux*16) + (ClassTime - 6)) + i] = IDECourses[ChosenCourses];
    }

}

void ClassSchedules(int* &HRS){

    cout << "\nHoras Teoricas: " << HRS[0];
    cout << "\nHoras Practicas: " << HRS[1];
    cout << "\nHoras Teorico-Practicas: " << HRS[2];
    cout << endl;

}

void SaveMatrix(int* ScheduleMatrix, int* HoursStudy){

    ofstream ScheduleFile("sintítulo.txt");
    int Rows = 16;
    int Columns = 7;
    char CenterDivision[] = "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣";
    char LowerDivision[]  = "╚═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╝";


    ScheduleFile << "╔═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╗\n"
                    "║   HORAS   ║   LUNES   ║  MARTES   ║ MIERCOLES ║  JUEVES   ║  VIERNES  ║  SABADO   ║  DOMINGO  ║";
    for (int i = 0; i < Rows; i++){
        ScheduleFile << endl << CenterDivision;

        ScheduleFile << "\n║";
        if (i < 4){
            ScheduleFile << "   0" << (6 + i) << ":00   ║";
        }
        else{
            ScheduleFile << "   " << (6 + i) << ":00   ║";
        }

        for(int j = 0; j < Columns; j++){
            int Index = j * Rows + i;

            ScheduleFile << "  ";
            for (int k = 0; HoursStudy[k] != -1; k++){
                if (Index == HoursStudy[k]){
                    ScheduleFile.seekp(-1, std::ios::cur);
                    ScheduleFile <<"*";
                    break;
                }
            }
            if(ScheduleMatrix[Index] == -1){
                ScheduleFile << "         ║";
            }
            else{
                ScheduleFile << ScheduleMatrix[Index]<< "  ║";
            }

        }
    }
    ScheduleFile << endl << LowerDivision << endl;
    ScheduleFile << endl << "Codigo  : Horas de clase\n*Codigo : Horas de estudio";

    ScheduleFile.close();
}

void PrintMatrix(int* ScheduleMatrix, int* HoursStudy){

    int Rows = 16;
    int Columns = 7;
    char Division[] = "+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+";

    cout << "+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+\n"
            "|   HORAS   |   LUNES   |  MARTES   | MIERCOLES |  JUEVES   |  VIERNES  |  SABADO   |  DOMINGO  |\n"
            "+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+";
    for (int i = 0; i < Rows; i++){

        cout << "\n|";
        if (i < 4){
            cout << "   0" << (6 + i) << ":00   |";
        }
        else{
            cout << "   " << (6 + i) << ":00   |";
        }

        for(int j = 0; j < Columns; j++){
            int Index = j * Rows + i;
            cout << "  ";

            for (int k = 0; HoursStudy[k] != -1; k++){
                if (Index == HoursStudy[k]){
                    cout << "\033[D" << "*";
                    break;
                }
            }

            if(ScheduleMatrix[Index] == -1){
                cout << "         |";
            }
            else{
                cout << ScheduleMatrix[Index]<< "  |";
                }
        }
        if(i == Rows-1){
            break;
        }

        cout << endl << Division;
    }
    cout << endl << Division << endl;
}

int DayInt(char Day){

    int DayAux;

    do{
    if (Day == 'L' || Day == 'l'){
        DayAux = 0;
        break;
    }
    else if (Day == 'M' || Day == 'm'){
        DayAux = 1;
        break;
    }
    else if (Day == 'W' || Day == 'w'){
        DayAux = 2;
        break;
    }
    else if (Day == 'J' || Day == 'j'){
        DayAux = 3;
        break;
    }
    else if (Day == 'V' || Day == 'v'){
        DayAux = 4;
        break;
    }
    else if (Day == 'S' || Day == 's'){
        DayAux = 5;
        break;
    }
    else if (Day == 'D' || Day == 'd'){
        DayAux = 6;
        break;
    }
    else{
        cout << "L(Lunes), M(Martes), W(Miercoles), J (Jueves), V(Viernes), S(Sabado), D(Domingo)\nOpcion erronea. Ingrese nuevamente: ";
        cin >> Day;
        cout << "\033[F\033[K\033[F\033[K";

    }
    }while(true);

    return DayAux;
}















