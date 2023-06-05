//COVID TEST SYSTEM
//Authors: Mohammadreza Mordijam, Mehdi Golipoor
//Assignment: Final Project Summer 2022
//Using: NANA Library C++

#include <nana/gui.hpp>              
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/place.hpp>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

using String = std::string;



class Patient {
public:

    String name;
    String age;
    String postal;



    Patient() {

        this->name = "";
        this->age = "";
        this->postal = "";
    }

    Patient(String pname, String page, String ppostal) {

        this->name = pname;
        this->age = page;
        this->postal = ppostal;

    }

    bool random() { return rand() & 1; }

    void performTest(String date) {

        int randNum = random() | random();

        String result;
        if (randNum == 1)
            result = "Positive(+)!";
        else
            result = "Negative(-)";


    }


    void ToString() {

        std::cout << this->name << std::endl;
        std::cout << this->age << std::endl;
        std::cout << this->postal << std::endl;
    }

};

class TestRes {
public:

    String dateOftest;
    String resultOftest;

    TestRes() {
        this->dateOftest = "";
        this->dateOftest = "";
    }
    TestRes(String date, String result) {
        this->dateOftest = date;
        this->resultOftest = result;
    }
};




int main()
{

    using namespace nana;

    std::vector<Patient> patientList;

    Patient* selectedPatient = NULL;

    //Main Form
    form   fm(API::make_center(800, 600), appear::decorate<appear::minimize, appear::maximize>());       // Our main window
    fm.caption("COVID-19 Test System");       // (with this title)



    place fm_place{ fm };


    label  intro{ fm };
    intro.caption(" <size=20 bold color=0xff0000> COVID-19 Test System");
    intro.format(true);


    //Buttons
    button exit{ fm ,"Quit" };
    exit.fgcolor(color_rgb(0x000000));
    exit.bgcolor(color_rgb(0x00FFFF));
    API::effects_bground(exit, effects::bground_transparent(1), 1);

    exit.tooltip("Exit the Application!");

    exit.events().click([&]()
        {

            msgbox m(fm, "Exit Application", msgbox::yes_no);
            m.icon(m.icon_question);
            m << "Are you sure you want to Quit?";
            auto response = m();
            if (response == m.pick_yes) fm.close();   // if yes exit

        });


    button addNew{ fm, "Add +" };
    addNew.fgcolor(color_rgb(0x000000));
    addNew.bgcolor(color_rgb(0x00FFFF));
    API::effects_bground(addNew, effects::bground_transparent(1), 1);

    addNew.tooltip("Add a new test");

    button removeEx{ fm, "Remove -" };
    removeEx.fgcolor(color_rgb(0x000000));
    removeEx.bgcolor(color_rgb(0x00FFFF));
    API::effects_bground(removeEx, effects::bground_transparent(1), 1);



    button calculate{ fm, "Calculate Statistics" };
    calculate.fgcolor(color_rgb(0x000000));
    calculate.bgcolor(color_rgb(0x00FFFF));
    API::effects_bground(calculate, effects::bground_transparent(1), 1);

    calculate.tooltip("Calculate Statistics");


    //Patient Combox 
    combox patientCombox(fm);

    patientCombox.events().selected([&] {
        int selected = patientCombox.option();
        selectedPatient = &patientList.at(selected);
        });


    //Add New Patience Form
    addNew.events().click([&] {

        using namespace nana;
        form fm_modal(fm, API::make_center(800, 600), appear::decorate<appear::minimize, appear::maximize>());
        fm_modal.caption(" + New COVID-19 Test");
        fm_modal.bgcolor(color_rgb(0x00ffff));
        button done{ fm_modal, "Done" };

        //Labels
        label fname{ fm_modal, "Enter Full Name: " };
        label age{ fm_modal, "Enter Date of Birth: " };
        label postal{ fm_modal, "Enter Postal Code: " };

        //textBoxes
        textbox postalCode{ fm_modal },
            Bname{ fm_modal },
            dateBirth{ fm_modal };
        Bname.events().click([&] { Bname.select(true); });


        dateBirth.tip_string("Enter Date Of Birth: ").multi_lines(false);
        Bname.tip_string("Enter Full Name: ").multi_lines(false);
        postalCode.tip_string("Enter Postal Code: ").multi_lines(false);


        fm_modal.div("<><weight=80% vertical<><weight=70% vertical <vertical gap=10 textboxes arrange=[35,35,35]>  <<>weight=35 gap=10 Done> ><>><>");



        fm_modal["textboxes"] << postalCode << Bname << dateBirth;
        fm_modal["Done"] << done;

        fm_modal["Labels"] << postal << fname << age;


        fm_modal.collocate();
        fm_modal.show();


        //(modal form) Done Button event Listener
        done.events().click([&] {

            std::string valName;
            std::string valPostal;
            std::string valAge;

            postalCode.getline(0, valPostal);
            dateBirth.getline(0, valAge);
            Bname.getline(0, valName);


            std::cout << "Patience Name: " << valName << " Date of birth: " << valAge << " Postal Code: " << valPostal << std::endl;



            Patient temp(valName, valAge, valPostal);
            patientList.push_back(temp);
            patientCombox.push_back(temp.name);

            Bname.select(true);
            dateBirth.select(true);
            postalCode.select(true);
            Bname.del();
            dateBirth.del();
            postalCode.del();

            fm_modal.close();


            });


        API::modal_window(fm_modal); //Block execution till modal form is closed
        });

    calculate.events().click([&] {
        auto maxAge = 0;

        std::map<int, int> ageBrackets;
        std::map<String, int> postalBrackets;

        String result = "";

        for (auto singlePerson : patientList)
        {
            if (stoi(singlePerson.age) > maxAge)
                maxAge = stoi(singlePerson.age);

            int ageBracket = stoi(singlePerson.age) / 5;

            auto bracketItr = ageBrackets.find(ageBracket);
            if (bracketItr != ageBrackets.end())
                bracketItr->second++;
            else
                ageBrackets.insert(std::make_pair(ageBracket, 1));

            std::string firstThreeLetters = singlePerson.postal.substr(0, 3);
            auto pcltr = postalBrackets.find(firstThreeLetters);
            if (pcltr != postalBrackets.end())
                pcltr->second++;
            else
                postalBrackets.insert(std::make_pair(firstThreeLetters, 1));
        }

        for (auto pairs : ageBrackets)
        {
            std::cout << "age bracket: " << std::to_string(pairs.first) << " has positive cases : " << std::to_string(pairs.second) << std::endl;
            result.append("Age bracket: ");
            result.append(std::to_string(pairs.first));
            result.append(" has postive case : ");
            result.append(std::to_string(pairs.second));
            result.append("\n");
        }

        for (auto codes : postalBrackets)
        {
            std::cout << "Postal Code: " << codes.first << " has positive cases : " << std::to_string(codes.second) << std::endl;
            result.append("Postal Code: ");
            result.append(codes.first);
            result.append(" has positive cases : ");
            result.append(std::to_string(codes.second));
            result.append("\n");
        }

        form statForm;

        textbox statOut{ statForm, result };

        statForm["stats"] << statOut;



        statForm.collocate();
        statForm.show();
        exec();

        });

    removeEx.events().click([&] {

        int selected = patientCombox.option();
        selectedPatient = &patientList.at(selected);

        int i = 0;
        int index = 0;

        for (auto aPerson : patientList)
        {
            if (aPerson.age == selectedPatient->name && aPerson.age == selectedPatient->age)
            {
                index = i;
            }
            i++;
        }
        i = 0;
        auto it = patientList.begin();
        for (; i < index; ++it, i++);
        std::cout << "Patient successfully removed! \n";
        it->ToString();
        patientList.erase(it);

        patientCombox.erase(selected);
        });
  



    fm_place.div("vertical  <weight=5% margin=10 label>  | 10% <Buttons gap=100 margin=10> ");
    fm_place["label"] << intro;
    fm_place["Buttons"] << addNew << removeEx << calculate << exit;




    fm_place.collocate();
    fm.show();

    paint::image img("C:\\Users\\rezam\\OneDrive\\Pictures\\Saved Pictures\\covid.bmp");

    drawing dw(fm);
    dw.draw([&img](nana::paint::graphics& graph)
        {
            if (img.empty()) return;
            img.paste(graph, nana::point{});
        });
    dw.update();

    exec();
}