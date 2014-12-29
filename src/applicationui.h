#ifndef ApplicationUI_H_
#define ApplicationUI_H_

#include <QObject>
#include <bb/cascades/AbstractPane>

namespace bb
{
    namespace cascades
    {
        class Application;
    }
}


class PokemonList; // forward declaration to avoid including header

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    Q_INVOKABLE void typeSelected(int type);
    Q_INVOKABLE void languageSelected(QString language);
    void init();
    virtual ~ApplicationUI() { }
private:
    PokemonList *m_pokemonList;
    bb::cascades::AbstractPane *root;
};

#endif /* ApplicationUI_H_ */
