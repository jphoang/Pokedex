
#include "pokemonlist.h"
#include <QStringList>
#include <string>
#include <iostream>
#include <bb/cascades/DataModelChangeType>
using namespace bb::cascades;

using std::cerr;
using std::endl;



QStringList pokemon_list;


int psc = -1;
QStringList pokemon_species_names;
QStringList pokemon_types;
QStringList type_names;
QStringList type_names_default;
QStringList filtered_type_names;
QStringList ability_names;
QStringList keep;
QStringList default_ability_names;
QStringList filter_split;
QStringList pl_split;
QStringList pokemon_abilities;
QString debug;
QStringList pokemon_stats;
int current_species = 1;
QString current = "#001";
bool first = true, searching = true;
int tn_count(0), psn_count(0), ps_count(0), pt_count(0), count(-1);
QString temp_lang = "9";
int track = 0;



PokemonList::PokemonList(QObject* parent) : bb::cascades::DataModel(parent) {
	listType = -1;
}

int PokemonList::childCount(const QVariantList& indexPath) {
	QFile Fpokemon_species_names("app/native/assets/data/pokemon_species_names.csv");
	QFile Ftypes_names("app/native/assets/data/type_names.csv");
	QFile Fpokemon_types("app/native/assets/data/pokemon_types.csv");
	QFile Fability_names("app/native/assets/data/ability_names.csv");
	QFile Fpokemon_species_flavor_text("app/native/assets/data/pokemon_species_flavor_text.csv");
	QFile Fpokemon_stats("app/native/assets/data/pokemon_stats.csv");
	QFile Fpokemon("app/native/assets/data/pokemon.csv");
	QFile Fpokemon_abilities("app/native/assets/data/pokemon_abilities.csv");
	pokemon_types.clear();
	type_names.clear();
	pokemon_species_names.clear();
	pokemon_list.clear();
	pokemon_stats.clear();
	count = -1;
	psc = -1;


	//read in pokemons_species_names*************************************************************************
	if(Fpokemon_species_names.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&Fpokemon_species_names);
		psn_count = 0;
		while(!in.atEnd()){
			QString line = in.readLine();
			QStringList list = line.split(",");
			if(lang=="7"||lang=="8"){
				temp_lang = "9";
			}else{
				temp_lang = lang;
			}
			if(list[1]==temp_lang){
				pokemon_list.append(list[0] + ","+list[2]); // adds it to the list of pokemon
				count++;

				//keeps track of how many pokemon there are
			}
		}
	}
	else {
		cerr << "failed to find pokemon species names " << endl;
		exit(0);
	}
	//read in pokemons_types*************************************************************************
	if(Fpokemon_types.open(QIODevice::ReadOnly | QIODevice::Text)){

		QTextStream in(&Fpokemon_types);
		while(!in.atEnd()){
			QString line = in.readLine();
			QStringList list = line.split(",");
			searching = true;
			track =0;
			if(list[0].toInt()<10000){

				while(searching&&track<=count){
					pl_split = pokemon_list[track].split(",");
					if(pl_split[0]==list[0]){
						pokemon_list[track]+=","+list[1];
						pl_split = pokemon_list[track].split(",");

						searching=false;
					}
					track++;
				}
			}



		}
	}else {
		cerr << "failed to find pokemon types " << endl;
		exit(0);
	}
	//read in type_names.csv **************************************************************************
	if(Ftypes_names.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&Ftypes_names);
		tn_count = 0;
		while(!in.atEnd()){
			QString line = in.readLine();
			QStringList list = line.split(",");
			if(list[1]==lang&&list[0].toInt() < 10000){ //finds valid types
				type_names.append(list[0]+","+list[2]);

			}
			if(list[1]=="9"&&list[0].toInt() < 10000){ //finds valid types
				type_names_default.append(list[0]+","+list[2]);

			}


		}

	}
	else {
			cerr << "failed to find types names " << endl;
			exit(0);
		}
	for(int i = 0; i<=count; i++){
		pl_split = pokemon_list[i].split(",");
		if(pl_split.length()==3){
			if(pl_split[2].toInt()==listType||listType==-1){
				filtered_type_names = type_names.filter(pl_split[2]);
				if(filtered_type_names.length()>0){
					filter_split = filtered_type_names[0].split(",");
					pokemon_list[i] = pl_split[0]+","+pl_split[1]+"["+filter_split[1]+"]";
					keep.append("+");
				}else{
					filtered_type_names = type_names_default.filter(pl_split[2]);
					filter_split = filtered_type_names[0].split(",");
					pokemon_list[i] = pl_split[0]+","+pl_split[1]+"["+filter_split[1]+"]";
					keep.append("+");
				}
			}else{
				pokemon_list[i]="null";
				keep.append("-");
			}

		}else if(pl_split.length()==4){
			if(pl_split[2].toInt()==listType||pl_split[3].toInt()==listType||listType==-1){


				filtered_type_names = type_names.filter(pl_split[2]);

				if(filtered_type_names.length()>0){
					filter_split = filtered_type_names[0].split(",");
					pokemon_list[i] = pl_split[0]+","+pl_split[1]+","+filter_split[1];
					keep.append("+");
				}else{
					filtered_type_names = type_names_default.filter(pl_split[2]);
					filter_split = filtered_type_names[0].split(",");
					pokemon_list[i] = pl_split[0]+","+pl_split[1]+","+filter_split[1];
					keep.append("+");
				}

				filtered_type_names = type_names.filter(pl_split[3]);

				if(filtered_type_names.length()>0){
					filter_split = filtered_type_names[0].split(",");
					pokemon_list[i] += ","+filter_split[1];
				}else{
					filtered_type_names = type_names_default.filter(pl_split[3]);
					filter_split = filtered_type_names[0].split(",");
					pokemon_list[i]  += ","+filter_split[1];
				}
			}else{
				pokemon_list[i]="null";
				keep.append("-");
			}
		}
	}


	//GET ALL OF THE MAIN DATA BELOW************************************************************************************************


	//read in pokemon
	first = true;
	if(Fpokemon.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&Fpokemon);
		while(!in.atEnd()){
			QString line = in.readLine();
			if(first==false){
				QStringList list = line.split(",");
				if(list[0].toInt()<10000){
					pokemon_stats.append(list[0]+","+list[3]+","+list[4]);
				}
			}
			first = false;
		}
	}
	else {
		cerr << "failed to find pokemon " << endl;
		exit(0);
	}






	//read in ability names
	first = true;
	if(Fability_names.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&Fability_names);
		while(!in.atEnd()){
			QString line = in.readLine();
			if(first==false){
				QStringList list = line.split(",");
				if(list[0].toInt()<10000){
					if(list[1]==lang){
						ability_names.append(line[0]+","+line[2]);
					}else if(list[1]=="9"){
						ability_names.append(line[0]+","+line[2]);
					}
				}
			}
			first = false;
		}
	}
	else {
		cerr << "failed to find ability names " << endl;
		exit(0);
	}



	//read in pokemon abilities

	if(Fpokemon_abilities.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&Fpokemon_abilities);
		while(!in.atEnd()){
			QString line = in.readLine();
			QStringList list = line.split(",");

		}

	}else{
		cerr << "failed to find pokemon abilities " << endl;
		exit(0);
	}

	//modify list
QStringList list;
	for(int i = 0; i<pokemon_list.length(); i++){
		list = pokemon_list[i].split(",");
		if(list[0].length()==1){
        pokemon_list[i] = "#00"+list[0]+" "+list[1];
		}else if((list[0].length()==2)){
			pokemon_list[i]= "#0"+list[0]+" "+list[1];
		}else if((list[0].length()==3)){
			pokemon_list[i]= "#"+list[0]+" "+list[1];
		}
if(list.length()==4){
	pokemon_list[i]+=" ["+list[2]+", "+list[3]+"]";
}else if (list.length()==3){
	pokemon_list[i]+=" ["+list[2]+"]";
}
		if(pokemon_list[i]=="null"){
			pokemon_stats[i]= "null";
		}
	}

	//read in pokemon stats
	if(Fpokemon_stats.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&Fpokemon_stats);
		while(!in.atEnd()){
			QString line = in.readLine();
			QStringList list = line.split(",");
		}
	}
	else {
		cerr << "failed to find pokemon stats " << endl;
		exit(0);
	}




	pokemon_stats.removeAll("null");
	//GET ALL OF THE MAIN DATA ABOVE************************************************************************************************
	pokemon_list.removeAll("null");
	return pokemon_list.length();


}

bool PokemonList::hasChildren(const QVariantList& indexPath) {
	if (indexPath.empty())
		return true; // The root node always has children
	else
		return false;
}

// Return the data for the item given by indexPath
QVariant PokemonList::data(const QVariantList& indexPath) {



	int i = indexPath[0].toInt(); // Get the menu index
	QVariantMap data;
	QStringList pokemon_type = pokemon_list[i].split("[");
	pokemon_type[1] = pokemon_type[1].remove(pokemon_type[1].length()-1, 1);
	data["aaa"] = pokemon_list[i];	// Get the name of pokemon for this index
	data["type"] = pokemon_type[1];
	data["height"] = pokemon_stats[i].split(",")[1].toInt()/10.000;
	data["weight"] = pokemon_stats[i].split(",")[2].toInt()/10.000;
	return data;			// Return the name as a QVariant object
}

PokemonList::~PokemonList() {
}

