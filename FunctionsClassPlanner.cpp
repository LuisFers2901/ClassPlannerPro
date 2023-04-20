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

        /*for(int i = 0; i < SizeCCourses; i++){            //Imprimir todas las horas
            cout << Courses[i];
        }

        cout<<endl<<endl;

        for (int i = 0; i<NumCourses; i++){                 //Imprimir posicion de curso
            cout << IndexCourses[i]<< endl;
        }
        cout<<endl<<endl;

        for (int i = 0; i<NumCourses; i++){                 //Imprimir IDE
            cout << IDECourses[i]<< endl;
        }

        cout<<endl<<endl;

        for(int i = 0; i < NumCourses*4; i++){            //Imprimir todas las horas
            cout << HRSCourses[i];
            if ((i+1)%4 == 0){
                cout << endl;
            }
        }
        */
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
        cout << "\033[F\033[K"; // Mover el cursor a la línea anterior y borrarla

        while(IndexM < 0 || IndexM > (ToolsCourses[1] - 1)){
            cout << "Opcion Invalida, use los indice de la lista: ";
            cin >> IndexM;
            cin.ignore();
            cout << "\033[F\033[K"; // Mover el cursor a la línea anterior y borrarla
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

void SaveMatrix(int* ScheduleMatrix, char* outputFilename){
    // ...
    std::ofstream outputFile("sintítulo.txt"); // abrir el archivo de salida
    int Rows = 16;
    int Columns = 7;
    char CenterDivision[] = "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣";
    char LowerDivision[]  = "╚═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╝";

    // escribir la salida en el archivo en lugar de la consola
    outputFile << "╔═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╗\n"
                  "║   HORAS   ║   LUNES   ║  MARTES   ║ MIERCOLES ║  JUEVES   ║  VIERNES  ║  SABADO   ║  DOMINGO  ║\n"
                  "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣";
    for (int i = 0; i < Rows; i++){

        outputFile << "\n║";
        if (i < 4){
            outputFile << "   0" << (6 + i) << ":00   ║";
        }
        else{
            outputFile << "   " << (6 + i) << ":00   ║";
        }

        for(int j = 0; j < Columns; j++){
            int Index = (i* Columns) + j;
            outputFile << "  ";
            if(ScheduleMatrix[Index] == 0){
                outputFile << "         ║";
            }
            else{
                outputFile << ScheduleMatrix[Index]<< "  ║";
            }
        }
        if(i == Rows-1){
            break;
        }

        outputFile << endl << CenterDivision;
    }
    outputFile << endl << LowerDivision;

    outputFile.close(); // cerrar el archivo
}

void PrintMatrix(int* ScheduleMatrix){

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
            int Index = (i* Columns) + j;
            cout << "  ";
            if(ScheduleMatrix[Index] == 0){
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
    cout << endl << Division;
}


/*void PrintMatrix(int* ScheduleMatrix){
    int Rows = 16;
    int Columns = 7;
    char CenterDivision[] = "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣";
    char LowerDivision[]  = "╚═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════╝";
    cout<< "╔═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════╗"
           "║   HORAS   ║   LUNES   ║  MARTES   ║ MIERCOLES ║  JUEVES   ║  VIERNES  ║  SABADO   ║  DOMINGO  ║"
           "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════╣";
    for (int i = 0; i < Rows; i++){
        cout << "\n║";
        for(int j = 0; j < Columns; j++){
            int Index = (i + j) * Rows;
            cout << "  " << ScheduleMatrix[Index]<< "  ║";
        }
        cout << endl << CenterDivision;
    }
    cout << endl << LowerDivision;
}*/
