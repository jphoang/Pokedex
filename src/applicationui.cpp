#include "applicationui.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/DropDown>
#include <bb/cascades/RadioGroup>
#include <bb/cascades/Label>
#include <bb/cascades/ListView>

#include <iostream>

#include "pokemonlist.h"

using namespace bb::cascades;

using std::cerr;
using std::endl;



ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
QObject(app), m_pokemonList(0)
{


    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    root = qml->createRootObject<AbstractPane>();

    qml->setContextProperty("pokedex", this);

    m_pokemonList = new PokemonList(this);
    qml->setContextProperty("pokemon_list", m_pokemonList);




    // Set created root object as the application scene
    app->setScene(root);
}
void ApplicationUI::init(){
	QString defaultLang = "9"; //Holds default language
    // Populate the dropdown list of types
    DropDown *dropDown(0);	// pointer to hold the DropDown UI object
    // Search the root QML object for a control named "pokemon_types"
    dropDown = root->findChild<DropDown *>("pokemon_types");

    if (dropDown) { // did we succeed in getting a pointer to the drop down UI control?

        QFile types("app/native/assets/data/type_names.csv");

        if(types.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&types);

            while(!in.atEnd()){
                QString line = in.readLine();
                QStringList list = line.split(",");
        					   if(list[1] == defaultLang && list[0].toInt() < 10000){ //finds valid types
        						   dropDown->add(Option::create().text(list[2]).value(list[0])); // Yes. Add a new option
                                }
                            }
                        }
                    }
                    else {
                       cerr << "failed to find type names" << endl;
                       exit(0);
                   }

    // Populate radio buttons for language settings
                   RadioGroup *radio(0);
    // Search the root QML object for a control named "pokemon_types"
                   radio = root->findChild<RadioGroup *>("pokedex_languages");

                   if (radio) {


                    QFile languages("app/native/assets/data/language_names.csv");
                    if(languages.open(QIODevice::ReadOnly | QIODevice::Text)){
                       QTextStream in(&languages);
                       while(!in.atEnd()){
                        QString line = in.readLine();
                        QStringList list = line.split(",");

                        if(defaultLang=="9"){
						if(list[1] == defaultLang && list[0] == defaultLang){ //finds correct default language
							radio->add(Option::create().text(list[2]).value(list[0]).selected(true));
						}else if(list[1] == defaultLang){
							radio->add(Option::create().text(list[2]).value(list[0]));
						}
                    }else if (defaultLang == "1"){
    					if(list[1] == defaultLang && list[0] == defaultLang){ //finds correct default language
    						radio->add(Option::create().text(list[2]).value(list[0]).selected(true));
    					}else if(list[1] == defaultLang){
    						radio->add(Option::create().text(list[2]).value(list[0]));
    					}

    				}

    			}
            }
        }
        else {
           cerr << "failed to find languages_names" << endl;
           exit(0);
       }


    // Set status text
       Label *status(0);
       status = root->findChild<Label *>("pokedex_status");
       if (status) {
           status->setText(QString("Found %1 Pokémon").arg(m_pokemonList->childCount(QVariantList())));
       }
       else {
           cerr << "failed to find status " << endl;
       }

   }

   void ApplicationUI::typeSelected(int type) {
       cerr << "In typeSelected() with " << "type=" << type << endl;
       m_pokemonList->listType=type;
       ListView *pokeList(0);
	pokeList = root->findChild<ListView*>(); //Selects the Listview
	pokeList->resetDataModel(); //unloads the data
	pokeList->setDataModel(m_pokemonList); //reloads the data

    Label *status(0);
    status = root->findChild<Label *>("pokedex_status");
    if (status) {
      status->setText(QString("Found %1 Pokémon").arg(m_pokemonList->childCount(QVariantList())));
  }
  else {
      cerr << "failed to find status " << endl;
  }


}

void ApplicationUI::languageSelected(QString language){
	m_pokemonList->lang=language;
   ListView *pokeList(0);
		pokeList = root->findChild<ListView*>(); //Selects the Listview
		pokeList->resetDataModel(); //unloads the data
		pokeList->setDataModel(m_pokemonList); //reloads the data
    }
