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
        cout << i << ". (" << HRSCourses[((i*4)+3)] << "C) ";
        NameCourse(Courses, IndexCourses, i);
        cout << endl;
    }
    cout << "-------------------------------------------------" << endl;
}

void NameCourse(char* &Courses, int* &IndexCourses, int Index){

    for (int i = IndexCourses[Index]; i < IndexCourses[(Index+1)]; i++){

        cout << Courses[i];
    }

}
