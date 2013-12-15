
#ifndef POKEMONLIST_H_
#define POKEMONLIST_H_
#include <bb/cascades/DataModelChangeType>
#include <bb/cascades/DataModel>

class PokemonList: public bb::cascades::DataModel {
	Q_OBJECT
public:
	PokemonList(QObject *parent = 0);

	virtual int childCount(const QVariantList& indexPath);
	virtual bool hasChildren(const QVariantList& indexPath);
	virtual QVariant data(const QVariantList& indexPath);
    QString lang;
    int listType;
	virtual ~PokemonList();
};
#endif /* POKEMONLIST_H_ */
